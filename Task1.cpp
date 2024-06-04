#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

class Matrix {
public:
    Matrix(int rows, int cols) : rows(rows), cols(cols), data(rows * cols) {}

    Matrix(Matrix&& other) noexcept : rows(other.rows), cols(other.cols), data(std::move(other.data)) {}

    Matrix& operator=(Matrix&& other) noexcept {
        if (this != &other) {
            rows = other.rows;
            cols = other.cols;
            data = std::move(other.data);
        }
        return *this;
    }

    Matrix operator+(const Matrix& other) const {
        Matrix result(rows, cols);
        std::transform(data.begin(), data.end(), other.data.begin(), result.data.begin(), std::plus<int>());
        return result;
    }

    Matrix operator-(const Matrix& other) const {
        Matrix result(rows, cols);
        std::transform(data.begin(), data.end(), other.data.begin(), result.data.begin(), std::minus<int>());
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                for (int k = 0; k < cols; ++k) {
                    result.data[i * other.cols + j] += data[i * cols + k] * other.data[k * other.cols + j];
                }
            }
        }
        return result;
    }

    Matrix transpose() const {
        Matrix transposed(cols, rows);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                transposed.data[j * rows + i] = data[i * cols + j];
            }
        }
        return transposed;
    }

    void readMatrixFromInput() {
        for (int i = 0; i < rows * cols; ++i) {
            std::cin >> data[i];
        }
    }

    void displayMatrix() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << data[i * cols + j] << " ";
            }
            std::cout << std::endl;
        }
    }

private:
    int rows;
    int cols;
    std::vector<int> data;
};

template<typename T>
void calculateTrace(const T& mat) {
}

int main() {
    int rows, cols;
    std::cout << "Enter the number of rows and columns for matrix 1: ";
    std::cin >> rows >> cols;
    
    Matrix mat1(rows, cols);
    std::cout << "Enter elements for matrix 1:" << std::endl;
    mat1.readMatrixFromInput();

    std::cout << "Matrix 1:" << std::endl;
    mat1.displayMatrix();

    std::cout << std::endl;

    Matrix mat2(rows, cols);
    std::cout << "Enter elements for matrix 2:" << std::endl;
    mat2.readMatrixFromInput();

    std::cout << "Matrix 2:" << std::endl;
    mat2.displayMatrix();

    Matrix result_addition = mat1 + mat2;
    std::cout << "Result of addition:" << std::endl;
    result_addition.displayMatrix();

    Matrix result_multiplication = mat1 * mat2;
    std::cout << "Result of multiplication:" << std::endl;
    result_multiplication.displayMatrix();

    Matrix result_transpose = mat1.transpose();
    std::cout << "Transpose of matrix 1:" << std::endl;
    result_transpose.displayMatrix();

    calculateTrace(mat1);

    return 0;
}