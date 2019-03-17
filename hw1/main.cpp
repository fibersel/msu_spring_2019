#include "numbers.dat"
#include <cstdlib>
#include <iostream>



#define MAXVAL 100000


void sieve_fill(bool * prime, size_t size){
	for(size_t i = 2; i < size; i++)
		prime[i] = true;
	prime[1] = prime[0] = false;
	for(unsigned long long i = 2; i < size; i++)
		if(prime[i])
			if(i * i < size)
				for(unsigned long long j = i * i; j < size; j += i)
					prime[j] = false;
	}


size_t count_prime(bool * prime, size_t size, size_t leftIndex, size_t rightIndex){
	size_t ctr = 0;
	if(leftIndex > size || rightIndex > size)
		throw std::out_of_range("Any index is out of range!");
	for(size_t i = leftIndex; i <= rightIndex; i++)
		if(prime[Data[i]])
			ctr++;
	return ctr;
}


int main(int argc, char* argv[]){
	if(argc == 1 || argc % 2 == 0)
		return -1;

	bool * prime = new bool[MAXVAL];
	sieve_fill(prime, MAXVAL);
	
	int leftBound, rightBound;
	for (int i = 1; i < argc; i += 2)
	{
		leftBound = std::atoi(argv[i]);
		rightBound = std::atoi(argv[i + 1]);

		size_t leftIndex = 0, rightIndex = Size - 1;
		while(Data[leftIndex] < leftBound)
		leftIndex++;

		while(Data[rightIndex] > rightBound)
		rightIndex--;


		if(Data[rightIndex] !=  rightBound || Data[leftIndex] != leftBound){
			std::cout << 0 <<std::endl;
		continue;
	}

	size_t counter; 
	try
	{
		counter = count_prime(prime, MAXVAL, leftIndex, rightIndex);
	} 
	catch(std::out_of_range& e)
	{
		std::cout <<"any bound is out of range!" << e.what();
		return -1;
	}
		std::cout << counter << std::endl;
	}
	delete [] prime;

	return 0;
}


