#include <thread>
#include <iostream>
#include <fstream>
#include <mutex>
#include <condition_variable>
#include <algorithm>

const int batch_size = 10000;
const std::string dir_name = "tmp";
std::condition_variable vars[2];

class data_accessor {
public:
    uint64_t*  buf;
    std::mutex mutex;
    size_t size;
    bool end;
    bool ready;
    
    data_accessor(int batch_size):buf(new uint64_t[batch_size]), end(false), ready(false){};
};


void merge(const std::string& filename, const std::string& resulting, const std::string& name){
    std::ifstream f1(filename, std::ios::binary | std::ios::in);
    std::ifstream f2(resulting, std::ios::binary | std::ios::in);
    std::ofstream out(name + std::string("tmp.bin"), std::ios::binary | std::ios::out);
    uint64_t in1, in2;
    size_t pos1 = 0, pos2 = 0, count1, count2;
    f1.seekg(pos1++ * sizeof(uint64_t));
    f2.seekg(pos2++ * sizeof(uint64_t));
    f1.read((char*) &in1, sizeof(uint64_t));
    f2.read((char*) &in2, sizeof(uint64_t));
    count1 = f1.gcount();
    count2 = f2.gcount();
    while(count1 || count2){
        if(!count1){
            out.write((char*) &in2, sizeof(uint64_t));
            f2.seekg(pos2++ * sizeof(uint64_t));
            f2.read((char*) &in2, sizeof(uint64_t));
            count2 = f2.gcount();
        } else if(!count2){
            out.write((char*) &in1, sizeof(uint64_t));
            f1.seekg(pos1++ * sizeof(uint64_t));
            f1.read((char*) &in1, sizeof(uint64_t));
            count1 = f1.gcount();   
        } else {
            if(in1 < in2){
                out.write((char*) &in1, sizeof(uint64_t));
                f1.seekg(pos1++ * sizeof(uint64_t));
                f1.read((char*) &in1, sizeof(uint64_t));
                count1 = f1.gcount(); 
            } else {
                out.write((char*) &in2, sizeof(uint64_t));
                f2.seekg(pos2++ * sizeof(uint64_t));
                f2.read((char*) &in2, sizeof(uint64_t));
                count2 = f2.gcount();
            }
        }
    }
    f1.close();
    f2.close();
    std::remove(filename.c_str());
    std::remove(resulting.c_str());
    std::rename((name + std::string("tmp.bin")).c_str(), resulting.c_str());
}



void sorter(const std::string& name, data_accessor* access, int id){
    uint64_t* buf = new uint64_t[batch_size];  
    int size;
    int files_ctr = 0;
    while(true){
        {
            std::unique_lock<std::mutex> lock(access->mutex);
            vars[id].wait(lock, 
            [access]()
            {
                return access->ready;
            });
            access->ready = false;
            if(access->end)
                break;
            size = access->size;
            std::copy(access->buf, access->buf + size, buf); 
        }
        std::sort(buf, buf + size);
        std::ofstream out(name + std::to_string(files_ctr), 
        std::ios::out | std::ios::binary);
        out.write((char*) buf, size);
        files_ctr++;
   }
   system((std::string("touch ") + name + std::string(".bin")).c_str());
   while(files_ctr){
       merge(name + std::to_string(files_ctr - 1), name + std::string(".bin"), name);
       files_ctr--;
    }
}



int main(int argc, char * argv[]){
    if (argc != 2)
        return -1;
    std::string filename(argv[1]); 
    data_accessor*  accessor_1 = new data_accessor(batch_size);
    data_accessor* accessor_2 = new data_accessor(batch_size);
    std::string threadname_1 = "first";
    std::string threadname_2 = "second";
    std::thread worker_1(sorter, threadname_1, accessor_1, 0);
    std::thread worker_2(sorter, threadname_2, accessor_2, 1);
    std::ifstream f(filename, std::ios::binary | std::ios::in);
    int batch_num = 0, count_1 = 1, count_2 = 1;
    while(count_1 || count_2){
        {
            std::lock_guard<std::mutex> lock(accessor_1->mutex);
            f.seekg(batch_num++ * sizeof(uint64_t) * batch_size);
            f.read((char*) accessor_1->buf, sizeof(uint64_t) * batch_size);
            count_1 = f.gcount() / sizeof(uint64_t);
            accessor_1->size = count_1;
            accessor_1->ready = true;
            if(count_1 == 0)
                accessor_1->end = true;
        }
        vars[0].notify_one();
        {
            std::lock_guard<std::mutex> lock(accessor_2->mutex);
            f.seekg(batch_num++ * sizeof(uint64_t) * batch_size);
            f.read((char*) accessor_2->buf, sizeof(uint64_t) * batch_size);
            count_2 = f.gcount() / sizeof(uint64_t);
            accessor_2->size = count_2;
            accessor_2->ready = true;
            if(count_2 == 0)
                accessor_2->end = true;
        }
        vars[1].notify_one();
    }
    f.close();
    worker_1.join();
    worker_2.join();
    merge(threadname_1 + std::string(".bin"), threadname_2 + std::string(".bin"), std::string("main"));
    std::rename((threadname_2 + std::string(".bin")).c_str(), "result.bin");
    return 0;
}
