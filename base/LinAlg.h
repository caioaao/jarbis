#ifndef LINALG_H
#define LINALG_H

#include <array>
#include <type_traits>

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

        size_t rows() const {return mat_.size(); }
        size_t cols() const {return mat_[0].size(); }
    };

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
