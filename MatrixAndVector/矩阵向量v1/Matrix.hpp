#pragma once

#include "MatrixBase.hpp"
#include <initializer_list>

class Matrix : public MatrixBase<Matrix>
{
public:
	//Matrix() = default;
	Matrix(int row, int col) :MatrixBase<Matrix>(row, col) {}
	Matrix(std::initializer_list<std::initializer_list<double>> list);
	Matrix(const Matrix& matrix);
	Matrix(Matrix&& matrix) noexcept :MatrixBase<Matrix>(std::move(matrix)) {}
	Matrix CloneSize() const { return Matrix(row, col); }
	double& operator()(int rowIndex, int colIndex);

	Matrix& operator=(const Matrix& matrix);
    Matrix& operator=(Matrix&& matrix) noexcept;

    Matrix& Resize(int row, int col);
    Matrix& DeleteRow(int row);
    Matrix& DeleteCol(int col);
};

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> list)
	:MatrixBase<Matrix>(static_cast<int>(list.size()), static_cast<int>(list.begin()->size()))
{
	for (int i = 0; i < this->row; i++)
	{
		for (int j = 0; j < this->col; j++)
		{
			this->elements[i][j] = *((list.begin() + i)->begin() + j);
		}
	}
}

Matrix::Matrix(const Matrix& matrix)
	:MatrixBase<Matrix>(matrix.row, matrix.col)
{
	for (int i = 0; i < matrix.row; i++)
	{
		for (int j = 0; j < matrix.col; j++)
		{
			this->elements[i][j] = matrix.elements[i][j];
		}
	}
}

double& Matrix::operator()(int rowIndex, int colIndex)
{
	return *(elements[rowIndex - 1] + colIndex - 1);
}

inline Matrix& Matrix::operator=(const Matrix& matrix)
{
	return MatrixVecBase<Matrix>::operator=(matrix);
}

inline Matrix& Matrix::operator=(Matrix&& matrix) noexcept
{
    return MatrixVecBase<Matrix>::operator=(std::move(matrix));
}

inline Matrix& Matrix::Resize(int row, int col)
{
    if (row <= this->row && col <= this->col)
    {
        this->row = row;
        this->col = col;
        for (int i = this->row; i < this->realRow; i++)
        {
            delete[] elements[i];
            elements[i] = nullptr;
        }
        this->realRow = row;
        this->realCol = col;
        return *this;
    }
    for (int i = 0; i < this->realRow; i++)
    {
        delete[] this->elements[i];
        elements[i] = nullptr;
    }
    delete this->elements;
    elements = nullptr;
    this->row = row;
    this->col = col;
    this->realRow = row;
    this->realCol = col;
    this->elements = new double* [row];
    for (int i = 0; i < row; i++)
    {
        this->elements[i] = new double[col];
    }
    return *this;
}

inline Matrix& Matrix::DeleteRow(int row)
{
    if (row < 0 || row > this->row)
    {
        throw "³¬³ö¾ØÕó·¶Î§";
    }
    double* temp = this->elements[row - 1];
    for (int i = row - 1; i < this->row - 1; i++)
    {
        this->elements[i] = this->elements[i + 1];
    }
    this->elements[this->row - 1] = temp;
    delete[] elements[this->row - 1];
    elements[this->row - 1] = nullptr;
    temp = nullptr;
    this->row--;
    this->realRow--;
    return *this;
}

inline Matrix& Matrix::DeleteCol(int col)
{
    if (col < 0 || col > this->col)
    {
        throw "³¬³ö¾ØÕó·¶Î§";
    }
    for (int i = 0; i < this->row; i++)
    {
        for (int j = col - 1; j < this->col - 1; j++)
        {
            this->elements[i][j] = this->elements[i][j + 1];
        }
    }
    this->col--;
    return *this;
}

