#pragma once

#include <vector>
#include <iostream>
#include "Utils/utils.h"

/*
template<typename T = int>
class Matrix_row
{
private:
    std::vector<T> row;
public:

    explicit Matrix_row(std::size_t n) {
        row.reserve(n);
        for (int i = 0;i < n; ++i)
            row.push_back(0);
    }
    explicit Matrix_row(std::vector<T>& row_of_matrix) :row(row_of_matrix) {
    }

    T& operator[](size_t j) {
        return row[j];
    }

    //T* begin(){return this->row.begin();}
    //T* end(){return this->row.end();}
};
*/
template<typename T = int>
class matrix {
//private: friend class Matrix_row<T>;
public:
    //вложенный класс вектор - строки матрицы
    class Matrix_row {
    private:
        std::vector<T> row;
    public:

        explicit Matrix_row(std::size_t n) {
            row.reserve(n);
            for (int i = 0; i < n; ++i)
                row.push_back(0);
        }

        explicit Matrix_row(std::vector<T> &row_of_matrix) : row(row_of_matrix) {
        }

        T &operator[](size_t j) {
            return j<row.size()?row[j]:row[row.size()-1];
        }

        //T* begin(){return this->row.begin();}
        //T* end(){return this->row.end();}
    };
    /*
    struct iterator// : public std::iterator<std::input_iterator_tag, T, T, const T*, T>
    {
        T* p = nullptr;
        //T itt_value = 0;
        std::size_t _i = 0;
        matrix<T>& link;
        explicit iterator(matrix<T>& mtr, std::size_t i, std::size_t j) :p(mtr[i][j]), _i(i){}
        iterator& operator++() { p != link.column_of_row.end() ? ++p : ++_i; }
        bool operator ==(iterator& rside_itt) { return this->p == rside_itt.p; }
        bool operator !=(iterator& rside_itt) { return !(this == rside_itt); }
        T& operator*() const { return *plink[_i][_j]; }
    };*/
private:
    std::size_t n_ = 0;
    //вектор столбец содержащий вектор-строки
    std::vector<Matrix_row> column_of_row;

public:
    //конструктор
    matrix(std::size_t m, std::size_t n) : n_(n) {
        this->column_of_row.reserve(m);

        for (int i = 0; i < m; ++i) { this->column_of_row.emplace_back(Matrix_row(n)); }
    }
    //переопределние конструктора копирования
    template<typename U>
    matrix(const matrix<U>& that){
        //this(that.getRowSize(), that.getColumnSize());

        for(int i=0;i<this->getRowSize();++i)
            for(int j=0;j<this->getColumnSize();++j) {
                U tmp_elem = const_cast<matrix<U>&>(that)(i,j);
                (*this)[i][j] = static_cast<T>(tmp_elem);//static_cast<T>(that[i][j]);
            }
    }
    //переопределение оператора присваивания
    template<typename U>
    matrix<T>& operator=(matrix<U>& that){
        if(typeid((*this)[0][0]) == typeid(that[0][0])){
            n_ = that.n_;
            column_of_row = that.column_of_row;
        }

        return *this;
    }

    //перегрузка метода заполнения матрицы для выхода из рекурсии метода переменного количества аргументов
    template<typename V>
    void fillMatrix(std::size_t &m, std::size_t &n, V& elem){
        (*this)[m][n] = static_cast<T>(elem);
    }

    //заполнение матрицы элементами (если их будет меньше или больше чем элементов матрицы,
    // то заполнение будет продолжаться пока не достигнет размерности матрицы либо размерности количества аргументов метода)
    template<typename V, typename...U>
    void fillMatrix(std::size_t &m, std::size_t &n, V& elem, U&...args) {
        (*this)[m][n] = static_cast<T>(elem);

        if (this == nullptr) {
            return;
        } else {
            (*this)[m][n] = static_cast<T>(elem);
            if (n == this->getColumnSize() - 1)
                if (m == this->getRowSize() - 1)
                    return;
                else {
                    ++m;
                    n = 0;
                }
            else
                ++n;
            fillMatrix(m, n, args...);
        }
    }
    //получить количество строк
    std::size_t getRowSize() const { return this->column_of_row.size();}
    //получить количество столбцов
    std::size_t getColumnSize() const { return n_; }
    //возвращение иттератора на начало матрицы
    const T *begin() { return this->column_of_row[0].begin(); }
    //переопределение оператора индексирования
    Matrix_row &operator[](const size_t i) { return i<column_of_row.size()?column_of_row[i]:column_of_row[column_of_row.size()-1]; }
    //переопределение оператора индексирования в круглых скобках
    int operator()(std::size_t i, std::size_t j) { return column_of_row[i][j]; }
    //переопределение оператора ==
    template<typename U>
    bool operator==(matrix<U> &that) {
        if (this->getRowSize() != that.getRowSize() or this->getColumnSize() != that.getColumnSize())
            return false;
        for (std::size_t i = 0; i < getRowSize(); ++i)
            for (std::size_t j = 0; j < getColumnSize(); ++j)
                if ((*this)[i][j] - static_cast<T>(that[i][j]) > 0.000001)
                    return false;

        return true;
    }
    //переопределение оператора !=
    template<typename U>
    bool operator!=(matrix<U> &that) {
        return !(*this == that);
    }
    //переопределение оператора += для числа шаблонного типа
    template<typename U>
    matrix<T> &operator+=(U numb) {
        //iterator itt;
        //auto itt = this->column_of_row.begin();
        //itt = iterator(this, 0, 0);
        /*
        for (auto itt_row:this->column_of_row)
            for(auto itt_column:*itt_row) {
                std::cout << *itt_column;
                *itt_column += static_cast<T>(numb);
            }
*/
        for (std::size_t i = 0; i < (*this).getRowSize(); ++i)
            for (std::size_t j = 0; j < getColumnSize(); ++j)
                (*this)[i][j] += static_cast<T>(numb);

        return *this;
    }
    //переопределение оператора -= для числа шаблонного типа
    template<typename U>
    matrix<T> &operator-=(U numb) {
        return *this += (-numb);
    }
    //переопределение оператора *= для числа шаблонного типа
    template<typename U>
    matrix<T> &operator*=(U numb) {
        for (std::size_t i = 0; i < (*this).getRowSize(); ++i)
            for (std::size_t j = 0; j < getColumnSize(); ++j)
                (*this)[i][j] += static_cast<T>(numb);

        return *this;
    }
    //переопределение оператора /= для числа шаблонного типа
    template<typename U>
    matrix<T> &operator/=(U numb) {
        if (std::abs(static_cast<T>(numb)) < 0.000000001)
            return *this;

        for (std::size_t i = 0; i < (*this).getRowSize(); ++i)
            for (std::size_t j = 0; j < getColumnSize(); ++j)
                (*this)[i][j] /= static_cast<T>(numb);
        return *this;
    }
    //переопределение оператора + для числа шаблонного типа
    template<typename U>
    matrix<T> &operator+(U numb) {
        matrix<T> tmp(getRowSize(), getColumnSize());

        for (std::size_t i = 0; i < (*this).getRowSize(); ++i)
            for (std::size_t j = 0; j < getColumnSize(); ++j)
                tmp[i][j] = (*this)[i][j] + static_cast<T>(numb);

        return tmp;
    }
    //переопределение оператора - для числа шаблонного типа
    template<typename U>
    matrix<T> &operator-(U numb) {
        return *this + (-numb);
    }
    //переопределение оператора * для числа шаблонного типа
    template<typename U>
    matrix<T> &operator*(U numb) {
        matrix<T> tmp(getRowSize(), getColumnSize());

        for (std::size_t i = 0; i < (*this).getRowSize(); ++i)
            for (std::size_t j = 0; j < getColumnSize(); ++j)
                tmp[i][j] = (*this)[i][j] * static_cast<T>(numb);

        return tmp;
    }


    //переопределение оператора += для матрицы шаблонного типа
    template<typename U>
    matrix<T>& operator+=(matrix<U> that){
        if(getRowSize() == that.getRowSize() and getColumnSize() == that.getColumnSize())
            for (std::size_t i = 0; i < getRowSize(); ++i)
                for (std::size_t j = 0; j < getColumnSize(); ++j)
                    this->column_of_row[i][j] += static_cast<T>(that[i][j]);
        return *this;
    }

    //переопределение оператора -= для матрицы шаблонного типа
    template<typename U>
    matrix<T>& operator-=(matrix<U> that){
        if(getRowSize() == that.getRowSize() and getColumnSize() == that.getColumnSize())
            for (std::size_t i = 0; i < getRowSize(); ++i)
                for (std::size_t j = 0; j < getColumnSize(); ++j)
                    this->column_of_row[i][j] -= static_cast<T>(that[i][j]);
        return *this;
    }

    //переопределение оператора *= для матрицы шаблонного типа
    template<typename U>
    matrix<T>& operator*=(matrix<U> that){
        if(getRowSize() == that.getRowSize() and getColumnSize() == that.n_ and getColumnSize() == that.getRowSize()) {
            matrix<T> tmp(n_, n_);
            for (std::size_t i = 0; i < getRowSize(); ++i)
                for (std::size_t j = 0; j < getColumnSize(); ++j) {
                    T summa_mult = static_cast<T>(0);
                    //std::cout << i << ":" << j << " = ";
                    for (std::size_t k = 0; k < n_; ++k) {
                        //std::cout << (*this)[i][k] << " * " << static_cast<T>(that[k][j]) << " + ";
                        summa_mult += (*this)[i][k] * static_cast<T>(that[k][j]);
                    }
                    //std::cout << std::endl;
                    tmp[i][j] = summa_mult;
                }

            for (std::size_t i = 0; i < getRowSize(); ++i)
                for (std::size_t j = 0; j < getColumnSize(); ++j)
                    (*this)[i][j] = tmp[i][j];
        }
        return *this;
    }

    //переопределение оператора + для матриц шаблонного типа
    template<typename U>
    matrix<T> operator+(matrix<U> that){
        matrix<T> tmp(getRowSize(), n_);
        if(getRowSize() == that.getRowSize() and getColumnSize() == that.getColumnSize())
            for (std::size_t i = 0; i < getRowSize(); ++i)
                for (std::size_t j = 0; j < getColumnSize(); ++j)
                    tmp[i][j] = (*this)[i][j] + static_cast<T>(that[i][j]);

        return tmp;
    }

    //переопределение оператора - для матриц шаблонного типа
    template<typename U>
    matrix<T> operator-(matrix<U> that){
        matrix<T> tmp(getRowSize(), n_);
        if(getRowSize() == that.getRowSize() and getColumnSize() == that.getColumnSize())
            for (std::size_t i = 0; i < getRowSize(); ++i)
                for (std::size_t j = 0; j < getColumnSize(); ++j)
                    tmp[i][j] = (*this)[i][j] - static_cast<T>(that[i][j]);

        return tmp;
    }

    //переопределение оператора * для матриц шаблонного типа
    template<typename U>
    matrix<T> operator*(matrix<U> that){
        matrix<T> tmp(getRowSize(), that.getColumnSize());
        if(n_ == that.getRowSize())
            for (std::size_t i = 0; i < getRowSize(); ++i)
                for (std::size_t j = 0; j < that.getColumnSize(); ++j) {
                    T summa_mult = static_cast<T>(0);
                    //std::cout << i << ":" << j << " = ";
                    for (std::size_t k = 0; k < n_; ++k) {
                        //std::cout << (*this)[i][k] << " * " << static_cast<T>(that[k][j]) << " + ";
                        summa_mult += (*this)[i][k] * static_cast<T>(that[k][j]);
                    }
                    //std::cout << std::endl;
                    tmp[i][j] = summa_mult;
                }

        return tmp;
    }

    //переопределение префиксного оператора ++
    matrix<T>& operator++(){
        return *this += 1;
    }
    //переопределение постфиксного оператора ++
    matrix<T> operator++(int){
        matrix<T> tmp = *this;
        *this +=1;
        return tmp;
    }
    //переопределение префиксного оператора --
    matrix<T>& operator--(){
        return *this -= 1;
    }
    //переопределение постфиксного оператора --
    matrix<T> operator--(int){
        matrix<T> tmp = *this;
        *this -=1;
        return tmp;
    }

    //переопределение оператора вывода
    friend std::ostream &operator<<(std::ostream &os, const matrix<T> &that) {
        os << std::endl;

        for (int i = 0; i < that.getRowSize(); ++i) {
            for (int j = 0; j < that.getColumnSize(); ++j)
                os << const_cast<matrix &>(that)[i][j] << "\t";

            os << std::endl;
        }

        return os;
    }
    //переопределение оператора ввода
    friend std::istream &operator>>(std::istream &is, matrix<T> &that) {
        std::string strvalues;
        std::istringstream iss;

        getValuesInMatrixRow();

        double val;
        bool is_continue = true;
        for (int i = 0; i < that.getRowSize(); ++i) {
            getline(is, strvalues, '\n');


            iss.str(strvalues);

            for (int j = 0; j < that.getColumnSize(); j++) {
                if (is_continue)
                    iss >> val;
                else
                    val = 0;
                that[i][j] = static_cast<T>(val);
                //std::cout << iss.eof() << "|" << val << " * ";
                is_continue = !iss.eof();
            }
            iss.clear();
            //std::cout << std::endl;

            is_continue = true;
        }

        return is;
    }
};