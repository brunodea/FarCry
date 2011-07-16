#ifndef _FAR_CRY_CORE_MATRIX_HPP_
#define _FAR_CRY_CORE_MATRIX_HPP_

/* Classe com as funcionalidades basicas de uma Matrix. */

#include <iostream>

namespace core
{
    template<class T, unsigned int M, unsigned int N=M>
    class Matrix
    {
    public:
        Matrix()
        {
        }
        Matrix(T val)
        {
            clear(val);
        }

        ~Matrix()
        {
        }

        inline void set(const T &value, unsigned int row, unsigned int col)
        {
            m_Elements[row*N + col] = value;
        }

        inline T &operator ()(unsigned int i, unsigned int j)
        {
            return m_Elements[i*N + j];
        }

        inline const T &operator ()(unsigned int i, unsigned int j) const
        {
            return m_Elements[i*N + j];
        }

        inline Matrix<T, M, N> &operator =(const Matrix &m)
        {
            for(unsigned int i = 0; i < M; i++)
            {
                for(unsigned int j = 0; j < N; j++)
                    set(m(i,j), i, j);
            }

            return (*this);
        }

        inline void operator +=(const Matrix &m)
        {
            for(unsigned int i = 0; i < M; i++)
            {
                for(unsigned int j = 0; j < N; j++)
                    set((*this)(i,j)+m(i,j), i, j);
            }
        }

        inline void operator -=(const Matrix &m)
        {
            for(unsigned int i = 0; i < M; i++)
            {
                for(unsigned int j = 0; j < N; j++)
                    set((*this)(i,j)-m(i,j), i, j);
            }
        }

        inline void operator *=(const T &val)
        {
            for(unsigned int i = 0; i < M; i++)
            {
                for(unsigned int j = 0; j < N; j++)
                    set((*this)(i,j)*val, i, j);
            }
        }

        inline void operator /=(const T &val)
        {
            for(unsigned int i = 0; i < M; i++)
            {
                for(unsigned int j = 0; j < N; j++)
                    set((*this)(i,j)/val, i, j);
            }
        }

        inline void clear(const T &val)
        {
            for(unsigned int i = 0; i < M; i++)
            {
                for(unsigned int j = 0; j < N; j++)
                    set(val, i, j);
            }

        }

        inline void print()
        {
            for(unsigned int i = 0; i < M; i++)
            {
                for(unsigned int j = 0; j < N; j++)
                {
                    T v = (*this)(i, j);
                    std::cout << v << ' ';
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }

    private:
        bool is_valid(const unsigned int i, const unsigned int j)
        {
            if(i < 0 || i >= M || j < 0 || j >= N)
                return false;
            return true;
        }

    private:
        T m_Elements[M*N];
    }; //end of class Matrix.

    template<class T, unsigned int M, unsigned int N>
    inline Matrix<T, M, N> operator +(const Matrix<T, M, N> &m1, const Matrix<T, M, N> &m2)
    {
        Matrix<T, M, N> res = m1;
        res += m2;

        return res;
    }

    template<class T, unsigned int M, unsigned int N>
    inline Matrix<T, M, N> operator -(const Matrix<T, M, N> &m1, const Matrix<T, M, N> &m2)
    {
        Matrix<T, M, N> res = m1;
        res -= m2;

        return res;
    }

    template<class T, unsigned int M, unsigned int N, unsigned int P>
    inline Matrix<T, M, P> operator *(Matrix<T, M, N> &m1, Matrix<T, N, P> &m2)
    {
        Matrix<T, M, P> res;
        for(unsigned int i = 0; i < M; i++)
        {
            for(unsigned int j = 0; j < P; j++)
            {
                T val = 0;
                for(unsigned int k = 0; k < N; k++)
                    val += m1(i, k)*m2(k, j);
                res.set(val, i, j);
            }
        }
        return res;
    }

    template<class T, unsigned int M, unsigned int N>
    inline Matrix<T, M, N> operator*(Matrix<T, M, N> &m, T val)
    {
        Matrix<T, M, N> res = m;
        res *= val;
        return res;
    }

    template<class T, unsigned int M, unsigned int N>
    inline Matrix<T, M, N> operator/(Matrix<T, M, N> &m, T val)
    {
        Matrix<T, M, N> res = m;
        res /= val;
        return res;
    }

} //end of namespace core.

#endif

