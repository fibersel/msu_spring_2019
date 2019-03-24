#pragma once
#include <stack>
#include <vector>
#include "Token.h"

class Calc
{
private:
    std::stack<int64_t> eval_stack;  
    const std::vector<Token>& arr;
    std::vector<Token>::const_iterator iter;
    
    void parse_sum();
    void parse_mul();
    void parse_ident();
    void shift_ptr();
    int64_t pop();
public:
    Calc(const std::vector<Token>& arr);
    int64_t evaluate();
};

