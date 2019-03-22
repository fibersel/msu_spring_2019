#include "Calc.h"

enum State
{
    Start,
    Num  
};


const std::vector<Token> tokenize(std::string& query)
{
    std::vector<Token> container;
    std::string buf = "";
    State cs = Start;

    for(char& c: query){
        switch (cs)
        {
            case Start:
                if(c == '+' || c == '-' || c == '*' || c =='/')
                {
                    container.push_back(Token(c));
                    buf = "";
                }
                else if(isdigit(c))
                {
                    buf += c;
                    cs = Num;
                }
                else if(c == ' '){
                    break;    
                }
                else
                {
                    throw std::invalid_argument("symbol is not allowed!");
                }
                break;
            case Num:
                if(c == '+' || c == '-' || c == '*' || c =='/' || c == ' ')
                {
                    container.push_back(Token(buf));
                    if(c != ' ')
                    {
                        container.push_back(Token(c));
                    }
                    buf = "";
                    cs = Start;    
                } else if(isdigit(c))
                {
                    buf += c;    
                } else 
                {
                    throw std::invalid_argument("symbol is not allowed!");
                }
                break;
        }
    }
    if(buf != "")
        container.push_back(Token(buf));
    return container;
}



int main(int argc, char* argv[])
{
    if(argc == 1 || argc > 2)
    {
        std::cout << "error" << std::endl;
        return 1;    
    }
    std::string query = argv[1]; 
    
    try
    {
        const std::vector<Token> ctr = tokenize(query);
        Calc calc(ctr);
        std::cout << calc.evaluate() << std::endl;
    }
    catch (std::out_of_range& e)
    {
        std::cout << "error" << std::endl;
        return 1;
    }
    catch (std::overflow_error &e)
    {
        std::cout << "error" << std::endl;
        return 1;
    }
    catch (std::invalid_argument& e)
    {
        std::cout << "error" << std::endl;
        return 1;
    }
       return 0;
}
