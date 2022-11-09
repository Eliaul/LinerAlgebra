#include <iostream>
#include "Matrix.hpp"
#include "Vec.hpp"
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main()
{
    Vec v1{ 1,2,3,4 };
    Vec v2{ 0,0,0,1 };
    Vec v3{ 0,0,0 };
    cout << Vec::Dot(v1, v3);
    Matrix m(5, 6);
    auto s = high_resolution_clock::now();
    for (int i = 0; i < 2000000; i++)
    {
        Matrix m = Matrix::Identity(5);
        m.SwapRow(1, 2);
        m.DeleteCol(1);
        m.DeleteCol(1);
        m.DeleteCol(3);
        m.DeleteRow(1);
    }
    auto e = high_resolution_clock::now();
    cout << duration_cast<duration<double, milli>>(e - s);
    
    
	
	return 0;
}