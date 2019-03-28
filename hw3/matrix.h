#include <iostream>


class Row {
private:
    int* arr;
    int len;
public:
    Row(int len);
    int& operator[](int n) const;
    void operator*=(int n) const;
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
    Row& operator[](int n) const;
    void operator*=(int n) const;
    bool operator==(const Matrix& matr) const;
    bool operator!=(const Matrix& matr) const;
    int getRows() const;
    int getColumns() const;
    ~Matrix();
};


