#pragma once

#include "MatrixVecBase.hpp"

template<class Derived>
class VecBase: public MatrixVecBase<Derived>
{
public:
	//VecBase() = default;
    VecBase(int length) :MatrixVecBase<Derived>(length, 1) {}
    VecBase(VecBase&& v) noexcept :MatrixVecBase<Derived>(std::move(v)) {}
	
    static Derived Zeros(int length);
    static Derived Constant(int length, double num);
    static double Norm(const Derived& derived);
    static double Dot(const Derived& derived1, const Derived& derived2);

    int Length() const { return this->row; }
    double Norm() const { return Derived::Norm(this->GetDerived()); }
};

template<class Derived>
inline Derived VecBase<Derived>::Zeros(int length)
{
    Derived derived(length);
    for (int i = 0; i < length; i++)
    {
        derived.elements[i][0] = 0;
    }
    return derived;
}

template<class Derived>
inline Derived VecBase<Derived>::Constant(int length, double num)
{
    Derived derived(length);
    for (int i = 0; i < length; i++)
    {
        derived.elements[i][0] = num;
    }
    return derived;
}

template<class Derived>
inline double VecBase<Derived>::Norm(const Derived& derived)
{
    double res = 0;
    for (int i = 0; i < derived.row; i++)
    {
        res += derived.elements[i][0] * derived.elements[i][0];
    }
    return std::sqrt(res);
}

template<class Derived>
inline double VecBase<Derived>::Dot(const Derived& derived1, const Derived& derived2)
{
    if (derived1.row != derived2.row)
    {
        throw "两个向量长度不同";
    }
    double res = 0;
    for (int i = 0; i < derived1.row; i++)
    {
        res += derived1.elements[i][0] * derived2.elements[i][0];
    }
    return res;
}
