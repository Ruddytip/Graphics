#include "Matrix.hpp"

Matrix::Matrix(): x(0), y(0), data(nullptr){}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> in):
Matrix(in.size(), in.begin()->size()){

    for(unsigned int i = 0; i < x; ++i){
        for(unsigned int j = 0; j < y; ++j){
            data[i][j] = *((in.begin() + j)->begin() + i);
        }
    }
}

Matrix::Matrix(const unsigned int size): Matrix(size, size){
    for(unsigned int i = 0; i < size; ++i)
        data[i][i] = 1.0;
}

Matrix::Matrix(const unsigned int _x, const unsigned int _y): x(_x), y(_y){
    data = new double*[x];
    for(unsigned int i = 0; i < x; ++i){
        data[i] = new double[y];
        for(unsigned int j = 0; j < y; ++j)
            data[i][j] = 0.0;
    }
}

Matrix::~Matrix(){
    if(data != nullptr){
        for(unsigned int i = 0; i < x; ++i)
            delete[] data[i];
        delete[] data;
    }
}

unsigned int Matrix::getX() const { return x; }

unsigned int Matrix::getY() const { return y; }

Matrix& Matrix::operator=(Matrix& mtr){
    for(unsigned int j = 0; j < y; ++j)
        for(unsigned int i = 0; i < x; ++i)
            data[i][j] = mtr[i][j];
    return *this;
}

bool Matrix::operator==(Matrix& mtr) const{
    bool flag = true;
    for(unsigned int j = 0; j < y; ++j)
        for(unsigned int i = 0; i < x; ++i)
            if(data[i][j] != mtr[i][j]) flag = false;
    return flag;
}

Matrix Matrix::operator+(Matrix& mtr){
    Matrix out(x, y);
    for(unsigned int j = 0; j < y; ++j)
        for(unsigned int i = 0; i < x; ++i)
            out[i][j] = data[i][j] + mtr[i][j];
    return out;
}

void Matrix::operator+=(Matrix& mtr){
    for(unsigned int j = 0; j < y; ++j)
        for(unsigned int i = 0; i < x; ++i)
            data[i][j]+=mtr[i][j];
}

Matrix Matrix::operator-(Matrix& mtr){
    Matrix out(x, y);
    for(unsigned int j = 0; j < y; ++j)
        for(unsigned int i = 0; i < x; ++i)
            out[i][j] = data[i][j] - mtr[i][j];
    return out;
}

void Matrix::operator-=(Matrix& mtr){
    for(unsigned int j = 0; j < y; ++j)
        for(unsigned int i = 0; i < x; ++i)
            data[i][j]-=mtr[i][j];
}

Matrix Matrix::operator*(const double value){
    Matrix out(x, y);
    for(unsigned int j = 0; j < y; ++j)
        for(unsigned int i = 0; i < x; ++i)
            out[i][j] = data[i][j] * value;
    return out;
}

void Matrix::operator*=(const double value){
    for(unsigned int j = 0; j < y; ++j)
        for(unsigned int i = 0; i < x; ++i)
            data[i][j]*=value;
}

Matrix Matrix::operator*(Matrix& mtr){
    unsigned int _x = mtr.getX();
    unsigned int _y = y;
    Matrix out(_x, _y);
    if(x != mtr.getY()) return out;
    for(unsigned int j = 0; j < _y; ++j){
        for(unsigned int i = 0; i < _x; ++i){
            double value = 0.0;
            for(unsigned int k = 0; k < x; ++k)
                value += data[k][j] * mtr[i][k];
            out[i][j] = value;
        }
    }
    return out;
}

Matrix Matrix::operator!(){
    Matrix out(y, x);
    for(unsigned int j = 0; j < y; ++j)
        for(unsigned int i = 0; i < x; ++i)
            out[j][i] = data[i][j];
    return out;
}