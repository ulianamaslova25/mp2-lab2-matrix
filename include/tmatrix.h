// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz == 0 || sz > MAX_VECTOR_SIZE)
            throw out_of_range("Vector size should be greater than zero");
        pMem = new T[sz]{};// {}; // У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        if (sz == 0 || sz > MAX_VECTOR_SIZE) {
            throw out_of_range("Vector size should be greater than zero");
        }
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v) : sz(v.sz)
    {
        pMem = new T[sz];
        std::copy(v.pMem, v.pMem + sz, pMem);
    }
    TDynamicVector(TDynamicVector&& v) noexcept
    {
        sz = v.sz;
        v.sz = 0;
        pMem = v.pMem;
        v.pMem = nullptr;
    }
    ~TDynamicVector()
    {
        delete[] pMem;
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this != &v) {
            sz = v.sz;
            delete[] pMem;
            pMem = new T[sz];
            std::copy(v.pMem, v.pMem + sz, pMem);
        }
        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this != &v) {
            sz = v.sz;
            pMem = v.pMem;
            v.pMem = nullptr;
            v.sz = 0;
        }
        return *this;
    }

    size_t size() const noexcept { return sz; }

    // индексация
    T& operator[](size_t ind)
    {
        if (ind < 0 || ind >= sz) throw "incorrect operation";
        return pMem[ind];
    }
    const T& operator[](size_t ind) const
    {
        if (ind < 0 || ind >= sz) throw "incorrect operation";
        return pMem[ind];
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind < 0 || ind >= sz) throw "incorrect operation";
        return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (ind < 0 || ind >= sz) throw "incorrect operation";
        return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        bool flag = 1;
        if (sz != v.sz) {
            flag = 0;
        }
        else {
            for (int i = 0; i < sz; i++) {
                if (pMem[i] != v.pMem[i]) {
                    flag = 0;
                }
            }
        }
        return flag;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !(*this == v);
    }

    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector res(*this);
        for (int i = 0; i < sz; i++) {
            res.pMem[i] += val;
        }
        return res;
    }
    TDynamicVector operator-(double val)
    {
        TDynamicVector res(*this);
        for (int i = 0; i < sz; i++) {
            res.pMem[i] -= val;
        }
        return res;
    }
    TDynamicVector operator*(double val)
    {
        TDynamicVector res(*this);
        for (int i = 0; i < sz; i++) {
            res.pMem[i] *= val;
        }
        return res;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        int maxLen = max(sz, v.sz);
        int minLen = min(sz, v.sz);
        TDynamicVector res(maxLen);
        for (int i = 0; i < minLen; i++) {
            res.pMem[i] = pMem[i] + v.pMem[i];
        }
        if (sz > v.sz) {
            for (int i = minLen; i < maxLen; i++) {
                res.pMem[i] = pMem[i];
            }
        }
        if (sz < v.sz) {
            for (int i = minLen; i < maxLen; i++) {
                res.pMem[i] = v.pMem[i];
            }
        }
        return res;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        int maxLen = max(sz, v.sz);
        int minLen = min(sz, v.sz);
        TDynamicVector res(maxLen);
        for (int i = 0; i < minLen; i++) {
            res.pMem[i] = pMem[i] - v.pMem[i];
        }
        if (sz > v.sz) {
            for (int i = minLen; i < maxLen; i++) {
                res.pMem[i] = pMem[i];
            }
        }
        if (sz < v.sz) {
            for (int i = minLen; i < maxLen; i++) {
                res.pMem[i] = -v.pMem[i];
            }
        }
        return res;
    }
    T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
    {
        int minLen = min(sz, v.sz);
        T res = 0;
        for (int i = 0; i < minLen; i++) {
            res += pMem[i] * v.pMem[i];
        }
        return res;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (s < 0 || s > MAX_MATRIX_SIZE) {
            throw out_of_range("Matrix size should be greater than zero");
        }
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    TDynamicMatrix(const TDynamicVector<TDynamicVector<T>>& m) : TDynamicVector<TDynamicVector<T>>(m)
    {
        if (sz == 0 || sz > MAX_MATRIX_SIZE) {
            throw out_of_range("Matrix size should be greater than zero and smaller then max size");
        }
    }
    TDynamicMatrix(const TDynamicMatrix& m)
    {
        sz = m.sz;
        pMem = new TDynamicVector<T>[sz];
        for (int i = 0; i < sz; i++) {
            pMem[i] = m[i];
        }

    }
    TDynamicMatrix(TDynamicMatrix&& m) noexcept
    {
        sz = m.sz;
        pMem = new TDynamicVector<T>[sz];
        for (int i = 0; i < sz; i++) {
            pMem[i] = m[i];
        }
        m.pMem = nullptr;
        m.sz = 0;
    }

    // индексация с контролем
    T& at(size_t inds, size_t indf)
    {
        if (inds < 0 || inds >= sz || indf < 0 || indf >= sz) throw "incorrect operation";
        return (*this)[inds][indf];
    }
    const T& at(size_t inds, size_t indf) const
    {
        if (inds < 0 || inds >= sz || indf < 0 || indf >= sz) throw "incorrect operation";
        return (*this)[inds][indf];
    }

    TDynamicMatrix& operator=(const TDynamicMatrix& m)
    {
        if (this != &m) {
            sz = m.sz;
            delete[] pMem;
            pMem = new TDynamicVector<T>[sz];
            for (int i = 0; i < sz; i++) {
                pMem[i] = m[i];
            }
        }
        return *this;
    }
    TDynamicMatrix& operator=(TDynamicMatrix&& m) noexcept
    {
        if (this != &m) {
            sz = m.sz;
            pMem = m.pMem;
            m.pMem = nullptr;
            m.sz = 0;
        }
        return *this;
    }

    size_t size() const noexcept { return sz; }

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        bool flag = 1;
        if (sz != m.sz) {
            flag = 0;
        }
        else {
            for (int i = 0; i < sz; i++) {
                if (pMem[i] != m.pMem[i]) {
                    flag = 0;
                }
            }
        }
        return flag;
    }

    // матрично-скалярные операции
    TDynamicMatrix<T> operator*(const T& val)
    {
        TDynamicMatrix<T> res(*this);
        for (int i = 0; i < sz; i++) {
            res[i] = (*this)[i] * val;
        }
        return res;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.size()) throw "incorrect operation";
        TDynamicVector<T> res(sz);
        for (int i = 0; i < sz; i++) {
            res[i] = (*this)[i] * v;
        }
        return res;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw "incorrect operation";
        TDynamicMatrix<T> res(sz);
        for (int i = 0; i < sz; i++) {
            res[i] = (*this)[i] + m[i];
        }
        return res;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw "incorrect operation";
        TDynamicMatrix<T> res(sz);
        for (int i = 0; i < sz; i++) {
            res[i] = (*this)[i] - m[i];
        }
        return res;
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw "incorrect operation";
        TDynamicMatrix<T> res(sz);
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++) {
                for (int k = 0; k < sz; k++) {
                    res[j][i] += (*this)[k][i] * m[j][k];
                }
            }
        }
        return res;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++) {
            for (size_t j = 0; j < v.sz; j++) {
                istr >> v.pMem[i][j];
            }
        }
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++) {
            for (size_t j = 0; j < v.sz; j++) {
                ostr << v[i][j] << " ";
            }
            ostr << endl;
        }
        return ostr;
    }
};

#endif
