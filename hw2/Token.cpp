#include "Token.h"

Token::Token(const char& raw)
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



Token::Token(const std::string& s)
{
    val = stoi(s);
    type = number;
};
