#pragma once
#include <stack>
#include <vector>
#include "Token.h"

class Calc
{
private:
    std::stack<int64_t> eval_stack;  
    std::vector<Token>& arr;
    std::vector<Token>::iterator iter;
    void E();
    void T();
    void S();
    void shift_ptr();
    int64_t pop();
public:
    Calc(std::vector<Token>& arr);
    
    
    int64_t evaluate();
};

