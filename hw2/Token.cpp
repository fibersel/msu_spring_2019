#include "Token.h"

Token::Token(char& raw)
{
    switch (raw)
    {
        case '/':
            type = oper;
            action = division;
            break;    
        case '*':
            type = oper;
            action = mul;
            break;    
        case '-':
            type = oper;
            action = minus;
            break;    
        case '+':
            type = oper;
            action = plus;
            break;    


    };  
};



Token::Token(std::string s)
{
    val = stoi(s);
    type = number;
};
