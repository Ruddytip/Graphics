#pragma once
#include <ostream>

class Matrix{
private:
    unsigned int x, y;
    double** data;
public:
    // Конструктор нулевой матрицы
    Matrix();
    // Конструктор единичной матрицы
    Matrix(const unsigned int size);
    // Конструктор прямоугольной матрицы, инициализирует нулем
    Matrix(const unsigned int _x, const unsigned int _y);
    // Десруктор
    ~Matrix();
    // Возвращает ширину матрицы
    unsigned int getX() const;
    // Возвращает высоту матрицы
    unsigned int getY() const;
    // Оператор доступа по индексу
    double* operator[](const unsigned int index){ return data[index]; }
    // Печать матрицы в консоль
    friend std::ostream& operator<<(std::ostream &out, const Matrix& mtr){
        for(unsigned int j = 0; j < mtr.y; ++j){
            for(unsigned int i = 0; i < mtr.x; ++i){
                out << mtr.data[i][j] << " ";
            }
            out << std::endl;
        }
        return out;
    }
    // Оператор сравнения
    bool operator==(Matrix& mtr) const;
    // Оператор сложения
    Matrix operator+(Matrix& mtr);
    // Оператор сложения и присваивания
    void operator+=(Matrix& mtr);
    // Оператор вычитания
    Matrix operator-(Matrix& mtr);
    // Оператор вычитания и присваивания
    void operator-=(Matrix& mtr);
    // Оператор умножения на число
    Matrix operator*(const double value);
    // Оператор умножения на число и присваивания
    void operator*=(const double value);
    // Оператор перемножения матриц
    Matrix operator*(Matrix& mtr);
    // Оператор транспонирования матрицы
    Matrix operator!();
};