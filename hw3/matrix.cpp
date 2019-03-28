#include "matrix.h"
#include <exception>


Row::Row(int num) {
    arr = new int[num];
    len = num;
    for(int i = 0; i < num; i++)
        arr[i] = 0;
};


Row::~Row() {
    delete arr;
}

int& Row::operator[](int n) {
    if(n >= len)
        throw std::out_of_range("");
    return arr[n];
};

const int& Row::operator[](int n) const {
    if(n >= len)
        throw std::out_of_range("");
    return arr[n];
};

void Row::operator*=(int n)  {
    for(int i = 0; i < len; i++)
        arr[i] *= n;
};


bool Row::operator==(const Row& row) const {
    for(int i = 0; i < len; i++)
        if(arr[i] != row.arr[i])
            return false;
    return true;
};

bool Row::operator!=(const Row& row) const {
    for(int i = 0; i < len; i++)
        if(arr[i] == row.arr[i])
            return false;
    return true;
};


Matrix::Matrix(int rows, int cols) {
    rows_n = rows;
    cols_n = cols;
    arr = new Row*[rows];
    for(int i = 0; i < rows; i++)
        arr[i] = new Row(cols);
};


Row& Matrix::operator[](int n) {
    if(n >= rows_n)
        throw std::out_of_range("");
    return *arr[n];
};

const Row& Matrix::operator[](int n) const {
    if(n >= rows_n)
        throw std::out_of_range("");
    return *arr[n];
};

bool Matrix::operator==(const Matrix& matr) const {
    for(int i = 0; i < rows_n; i++)
        if(arr[i] != matr.arr[i])
            return false;
    return true;
};

bool Matrix::operator!=(const Matrix& matr) const  {
    for(int i = 0; i < rows_n; i++)
        if(arr[i] == matr.arr[i])
            return false;
    return true;
};

Matrix& Matrix::operator*=(int n)  {
    for(int i = 0; i < rows_n; i++)
        *arr[i] *= n;
    return *this;
};


int Matrix::getRows() const {
    return rows_n;
};


int Matrix::getColumns() const {
    return cols_n;
};


Matrix::~Matrix() {
    delete[] arr;
};
