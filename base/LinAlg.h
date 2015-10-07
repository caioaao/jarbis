#ifndef LINALG_H
#define LINALG_H

#include <array>
#include <type_traits>
#include <ostream>

#include <cstdint>
#include <cstddef>

namespace base
{
    template
    <typename T, size_t ROWS, size_t COLS>
    class Matrix
    {
    private:
        typedef std::array<T, COLS> MatRow_t_;
        typedef std::array<MatRow_t_, ROWS> Matrix_t_;
        Matrix_t_ mat_;
    public:
        Matrix()
            {
                for(MatRow_t_& row_: mat_)
                {
                    row_.fill(0);
                }
            }

        Matrix<T, COLS, ROWS> t()
            {
                Matrix<T, COLS, ROWS> ret;
                for(unsigned i = 0; i < ROWS; ++i)
                {
                    for(unsigned j = 0; j < COLS; ++j)
                    {
                        ret[j][i] = mat_[i][j];
                    }
                }
                return ret;
            }

        MatRow_t_& operator[](unsigned idx)
            {
                return mat_[idx];
            }

        const MatRow_t_& operator[](unsigned idx)  const
            {
                return mat_[idx];
            }

        const Matrix<T, ROWS, COLS> scale(T val)
            {
                Matrix<T, ROWS, COLS> mat;

                for(unsigned i = 0; i < ROWS; ++i)
                {
                    for(unsigned j = 0; j < COLS; ++j)
                    {
                        mat[i][j] = val * mat_[i][j];
                    }
                }

                return mat;
            }

        template<size_t COLS2>
        Matrix<T, ROWS, COLS2> operator*(const Matrix<T, COLS, COLS2> & rhs)
            {
                Matrix<T, ROWS, COLS2> res;
                for(unsigned i = 0; i < ROWS; ++i)
                {
                    for(unsigned j = 0; j < COLS2; ++j)
                    {
                        for(unsigned k = 0; k < COLS; ++k)
                        {
                            res[i][j] += (*this)[i][k] * rhs[k][j];
                        }
                    }
                }

                return res;
            }


        Matrix<T, ROWS, COLS> operator+(const Matrix<T, COLS, COLS> & rhs)
            {
                Matrix<T, ROWS, COLS> res;
                for(unsigned i = 0; i < ROWS; ++i)
                {
                    for(unsigned j = 0; j < COLS; ++j)
                    {
                        res[i][j] = (*this)[i][j] + rhs[i][j];
                    }
                }

                return res;
            }


        Matrix<T, ROWS, COLS> operator-(const Matrix<T, COLS, COLS> & rhs)
            {
                Matrix<T, ROWS, COLS> res;
                for(unsigned i = 0; i < ROWS; ++i)
                {
                    for(unsigned j = 0; j < COLS; ++j)
                    {
                        res[i][j] = (*this)[i][j] - rhs[i][j];
                    }
                }

                return res;
            }


        size_t rows() const {return mat_.size(); }
        size_t cols() const {return mat_[0].size(); }
    };

    template<typename T, size_t ROWS, size_t COLS> std::ostream&
    operator<<(std::ostream& stream, const Matrix<T, ROWS, COLS>& mat)
    {
        for(unsigned i = 0; i < mat.rows(); ++i)
        {
            if(i > 0)
            {
                stream << '\n';
            }

            for(unsigned j = 0; j < mat.cols(); ++j)
            {
                if(j > 0)
                {
                     stream << ' ';
                }

                stream << mat[i][j];
            }
        }
        return stream;
    }


    template <typename T, size_t SZ>
    Matrix<T, SZ, SZ> identity_matrix(void)
    {
        Matrix<T, SZ, SZ> identity_mat;

        for(unsigned i = 0; i < SZ; ++i)
        {
            identity_mat[i][i] = (T)1;
        }

        return identity_mat;
    }


}
#endif
