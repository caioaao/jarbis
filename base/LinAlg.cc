#include "LinAlg.h"

#include <array>

#include <cstdint>
#include <cstddef>

namespace base
{
    template <typename T, size_t ROWS, size_t COLS>
    Matrix<T, ROWS, COLS>::Matrix()
    {
        mat_.fill(MatRow_t_(0));
    }


    template <typename T, size_t ROWS, size_t COLS> Matrix<T, COLS, ROWS>
    Matrix<T, COLS, ROWS>::t()
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


    template <typename T, size_t ROWS, size_t COLS>
    Matrix<T, ROWS, COLS>::MatRow_t_& operator[](unsigned idx)
    {
        return mat_[idx];
    }

    template <typename T2, size_t SZ> Matrix<T2, SZ, SZ>
    Matrix<T2, SZ, SZ>::identity(void)
    {
        Matrix<T2, SZ, SZ> identity_mat;

        for(unsigned i = 0; i < SZ; ++i)
        {
            identity_mat[i][i] = (T)1;
        }

        return identity_mat;
    }
};
