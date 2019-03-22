#pragma once
#include <stdint.h>
#include <iostream>
#include <stdexcept>

enum token_type {
    number,
    oper
};


enum action_type {
    plus,
    minus,
    mul,
    division 
};


class Token
{
public:
    int64_t val;
    token_type type;
    action_type action;

    Token(char& raw);


    Token(std::string raw);
};

