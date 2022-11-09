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
