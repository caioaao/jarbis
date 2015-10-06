#include "base/test/LinAlgTest.h"

#include <cstdint>

#include "base/LinAlg.h"
#include "base/Logger.h"
#include "base/debug.h"

namespace base_test
{
    void test_create_mat_();
    void test_create_identity_mat_();

    template<typename T, size_t R, size_t C>
    void check_matrix_(const base::Matrix<T,R,C>& mat,
                       const std::array<std::array<T, C>, R>& gabarito);


    void
    lin_alg_test()
    {
        test_create_mat_();
        test_create_identity_mat_();
    }


    void
    test_create_mat_()
    {
        const size_t ROWS = 10;
        const size_t COLS = 10;
        std::array<std::array<uint32_t, COLS>, ROWS> gabarito;

        for(unsigned i = 0; i < ROWS; ++i)
        {
            gabarito[i].fill(0);
        }

        base::Matrix<uint32_t, ROWS, COLS> mat;

        check_matrix_(mat, gabarito);
    }


    void
    test_create_identity_mat_()
    {
        const size_t MAT_SZ = 10;
        std::array<std::array<uint32_t, MAT_SZ>, MAT_SZ> gabarito;

        for(unsigned i = 0; i < MAT_SZ; ++i)
        {
            gabarito[i].fill(0);
            gabarito[i][i] = 1;
        }

        base::Matrix<uint32_t, MAT_SZ, MAT_SZ> mat =
            base::identity_matrix<uint32_t, MAT_SZ> ();

        check_matrix_(mat, gabarito);
    }


    template<typename T, size_t R, size_t C>
    void
    check_matrix_(const base::Matrix<T, R, C>& mat,
                  const std::array<std::array<T, C>, R>& gabarito)
    {
        ASSERT(R == mat.rows());
        ASSERT(C == mat.cols());

        for(unsigned i = 0; i < R; ++i)
        {
            for(unsigned j = 0; j < C; ++j)
            {
                ASSERT(gabarito[i][j] == mat[i][j]);
            }
        }
    }
};
