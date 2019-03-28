#include <iostream>


class Row {
private:
    int* arr;
    int len;
public:
    Row(int len);
    const int& operator[](int n) const;
    int& operator[](int n);
    void operator*=(int n);
    bool operator==(const Row& row) const;
    bool operator!=(const Row& row) const;
    ~Row();
};




class Matrix {
private:
    int rows_n;
    int cols_n;
    Row** arr;
public:
    Matrix(int rows, int cols);
    const Row& operator[](int n) const;
    Row& operator[](int n);
    Matrix& operator*=(int n);
    bool operator==(const Matrix& matr) const;
    bool operator!=(const Matrix& matr) const;
    int getRows() const;
    int getColumns() const;
    ~Matrix();
};


