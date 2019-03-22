#include "Calc.h"
#include "Token.h"

Calc::Calc(const std::vector<Token>& arr): arr(arr)
{
    iter = arr.begin();
};


int64_t Calc::pop()
{
    int64_t tmp = eval_stack.top();
    eval_stack.pop();
    return tmp;
}


void Calc::E()
{
    T();
    while(iter->type == oper && (iter->action == plus || iter->action == minus))
    {
        action_type act = iter->action;
        shift_ptr();
        T();
        int64_t o2 = pop();
        int64_t o1 = pop();
        if(act == minus)
            eval_stack.push(o1 - o2);
        else
            eval_stack.push(o1 + o2);
    }  
};


void Calc::shift_ptr()
{
    if(iter == arr.end())
        throw std::out_of_range("Invalid token");
    ++iter;
}


int64_t Calc::evaluate()
{
    E();
    return pop();
};


void Calc::T()
{
    S();
    while(iter->type == oper && (iter->action == mul || iter->action == division))
    {
        action_type act = iter->action;
        shift_ptr();
        S();
        int64_t o2 = pop();
        int64_t o1 = pop();
        if(act == mul)
            eval_stack.push(o1 * o2);
        else
        {    
            if( o2 == 0)
                throw std::overflow_error("Division by zero");
            eval_stack.push(o1 / o2);
        }
    }  
};

   
void Calc::S()
{
    int64_t modifier = 1;
    if(iter->type == oper && iter->action == minus)
    {
        shift_ptr();
        modifier = -1;

    }
    if(iter->type == number)
        eval_stack.push(modifier * iter->val);
    else
        throw std::invalid_argument("invalid token");
    shift_ptr();  
};



