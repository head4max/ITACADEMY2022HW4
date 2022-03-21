#include <iomanip>
//#include <string>
//#include "utils.h"
#include "MyMatrix.h"

int main() {
    std::size_t m = 1;    std::size_t n = 1;

    m = 5, n = 5;
    //matrix<double> mtrx1 = matrix<double>(m, n, 1.2, 1.3, 1.4, 1.5);
    matrix<double> mtrx1(5,5);
    std::cout << "mtrx1: " << mtrx1;

    //Проверка метода заполнения матрицы
    m = 0, n = 0;
    std::array<int,10> tmp_value = {1,2,3,4,5,6,7,8,9,0};
    matrix<int> mtrx(3,3);
    mtrx.fillMatrix(m,n,tmp_value[0],tmp_value[1],tmp_value[2],tmp_value[3],tmp_value[4],tmp_value[5],
                     tmp_value[6],tmp_value[7],tmp_value[8],tmp_value[9]);

    //проверка конструктора копирования
    matrix<int> mtrx2 = mtrx;
    mtrx2[0][0] = 100;mtrx2[0][1] = 101;mtrx2[0][2] = 102;mtrx2[1][0] = 201;mtrx2[1][1] = 201;mtrx2[1][2] = 202;
    std::cout << "copy constructor mtrx: " << std::endl << mtrx;
    std::cout << "copy constructor mtrx2: " << std::endl << mtrx2;

    //проверка оператора присваивания
    //mtrx2 = mtrx1;
    //std::cout << "operator= matrix<int>->matrix<double> for mtrx2: " << mtrx2;
    mtrx2 = mtrx;
    std::cout << "operator= matrix<int>->matrix<int> for mtrx2: " << mtrx2;
    std::cout << "operator= matrix<int>->matrix<int> for mtrx: " << mtrx;

    //Здесь можно проверить переопределение операции ввода
    //std::cin >> mtrx1;
    std::cout << "mtrx1 after << operation" << mtrx1;
    std::cout << "matrix compare(=): ";
    std::cout << (mtrx == mtrx1) << std::endl;
    //std::cin >> mtrx;
    std::cout << "Hello, Matrix!" << std::endl;

    //std::cout << mtrx[2][2];
    //std::cout << mtrx.getColumnSize();
    //Matrix_row<> mr = Matrix_row<>(5);
    //std::cout << "Matrix_row" << std::endl;
    //std::cout << mr[0] << std::endl;
    //std::cout << mr.row.size() << std::endl;
    std::cout << "Matrix" << std::endl;
    std::cout << "row length: ";
    std::cout << mtrx.getRowSize() << std::endl;
    std::cout << "column length: ";
    std::cout << mtrx.getColumnSize() << std::endl;
    std::cout << "elem getter(): ";
    std::cout << mtrx(2,2) << std::endl;
    mtrx[3][3] = 1;

    std::cout << "elem setter+getter[][]: ";
    std::cout << mtrx[3][3] << std::endl;

    std::cout << "matrix compare(!=): ";
    std::cout << (mtrx != mtrx1) << std::endl;

    std::cout << "increment number: " << std::endl;
    mtrx += 1.0;
    ++mtrx;
    std::cout << mtrx;
    std::cout << "decrement number: " << std::endl;
    mtrx -= 1.5;
    --mtrx;
    std::cout << mtrx;

    mtrx *= 2;
    std::cout << "multiply number: " << std::endl;
    std::cout << mtrx;

    mtrx /= 2.0;
    std::cout << "divide by number: " << std::endl;
    std::cout << mtrx;

    mtrx /= 0.0;
    std::cout << "divide by zero: " << std::endl;
    std::cout << mtrx;

    mtrx -= 4;

    std::cout << "multiply matrix: " << std::endl;
    std::cout << mtrx;
    std::cout << mtrx2;
    mtrx *= mtrx2;
    std::cout << mtrx;

    std::cout << "plus matrix: " << std::endl;
    std::cout << mtrx;
    std::cout << mtrx2;
    mtrx += mtrx2;
    std::cout << mtrx;

    std::cout << "minus matrix: " << std::endl;
    std::cout << mtrx;
    std::cout << mtrx2;
    mtrx -= mtrx2;
    std::cout << mtrx;

    std::cout << mtrx + mtrx2;
    std::cout << mtrx - mtrx2;
    std::cout << mtrx * mtrx2;

    return 0;
}