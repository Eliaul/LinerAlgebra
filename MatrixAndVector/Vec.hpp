#pragma once

#include "VecBase.hpp"
#include <initializer_list>

class Vec : public VecBase<Vec>
{

public:
	//Vec() = default;
	Vec(int length) :VecBase<Vec>(length) {}
	Vec(std::initializer_list<double> list);
	Vec(const Vec& vec);
	Vec(Vec&& vec) noexcept :VecBase<Vec>(std::move(vec)) {}
	Vec CloneSize() const { return Vec(row); }
	double& operator()(int index);

    Vec& operator=(const Vec& vec);
    Vec& operator=(Vec&& vec) noexcept;
};

Vec::Vec(std::initializer_list<double> list)
	:VecBase<Vec>(static_cast<int>(list.size()))
{
	for (int i = 0; i < this->row; i++)
	{
		this->elements[i][0] = *(list.begin() + i);
	}
}

Vec::Vec(const Vec& vec)
	:VecBase<Vec>(vec.row)
{
	for (int i = 0; i < row; i++)
	{
		this->elements[i][0] = vec.elements[i][0];
	}
}

double& Vec::operator()(int index)
{
	return *(elements[index - 1]);
}

inline Vec& Vec::operator=(const Vec& vec)
{
    return MatrixVecBase<Vec>::operator=(vec);
}

inline Vec& Vec::operator=(Vec&& vec) noexcept
{
    return MatrixVecBase<Vec>::operator=(std::move(vec));
}
