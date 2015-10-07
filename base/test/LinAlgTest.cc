#include "base/test/LinAlgTest.h"

#include <cstdint>

#include "base/LinAlg.h"
#include "base/Logger.h"
#include "base/debug.h"

namespace base_test
{
    void test_create_mat_(void);
    void test_create_identity_mat_(void);
    void test_transpose_(void);
    void test_scale_(void);
    void test_mult_(void);
    void test_sum_(void);
    void test_print_(void);

    template<typename T, size_t R, size_t C>
    void check_matrix_(const base::Matrix<T,R,C>& mat,
                       const std::array<std::array<T, C>, R>& expected_res);


    void
    lin_alg_test(void)
    {
        test_create_mat_();
        test_create_identity_mat_();
        test_transpose_();
        test_scale_();
        test_mult_();
        test_sum_();
        test_print_();
    }


    void
    test_create_mat_(void)
    {
        const size_t ROWS = 10;
        const size_t COLS = 10;
        std::array<std::array<uint32_t, COLS>, ROWS> expected_res;

        for(unsigned i = 0; i < ROWS; ++i)
        {
            expected_res[i].fill(0);
        }

        base::Matrix<uint32_t, ROWS, COLS> mat;

        check_matrix_(mat, expected_res);
    }


    void
    test_create_identity_mat_(void)
    {
        const size_t MAT_SZ = 10;
        std::array<std::array<uint32_t, MAT_SZ>, MAT_SZ> expected_res;

        for(unsigned i = 0; i < MAT_SZ; ++i)
        {
            expected_res[i].fill(0);
            expected_res[i][i] = 1;
        }

        base::Matrix<uint32_t, MAT_SZ, MAT_SZ> mat =
            base::identity_matrix<uint32_t, MAT_SZ> ();

        check_matrix_(mat, expected_res);
    }


    void
    test_transpose_(void)
    {
        const size_t ROWS = 4;
        const size_t COLS = 2;
        std::array<std::array<int32_t, ROWS>, COLS> expected_res;

        expected_res[0] = {1, 2, 3, 4};
        expected_res[1] = {5, 6, 7, 8};

        base::Matrix<int32_t, ROWS, COLS> mat;

        mat[0] = {1, 5};
        mat[1] = {2, 6};
        mat[2] = {3, 7};
        mat[3] = {4, 8};

        check_matrix_(mat.t(), expected_res);
    }


    void
    test_scale_(void)
    {
        const size_t ROWS = 2;
        const size_t COLS = 4;
        std::array<std::array<int32_t, COLS>, ROWS> expected_res;

        expected_res[0] = {2, 4, 6, 8};
        expected_res[1] = {10, 12, 14, 16};

        base::Matrix<int32_t, ROWS, COLS> mat;

        mat[0] = {1, 2, 3, 4};
        mat[1] = {5, 6, 7, 8};

        check_matrix_(mat.scale(2), expected_res);
    }


    void
    test_mult_(void)
    {
        std::array<std::array<int32_t, 2>, 2> expected0;
        expected0[0] = {21, 38};
        expected0[1] = {48, 96};

        std::array<std::array<int32_t, 1>, 1> expected1;
        expected1[0][0] = 31;

        std::array<std::array<int32_t, 1>, 2> expected2;
        expected2[0][0] = 26;
        expected2[1][0] = 36;

        base::Matrix<int32_t, 2, 2> mat00;
        mat00[0] = {2, 3};
        mat00[1] = {4, 8};
        base::Matrix<int32_t, 2, 2> mat01;
        mat01[0] = {6, 4};
        mat01[1] = {3, 10};

        check_matrix_(mat00 * mat01, expected0);

        base::Matrix<int32_t, 1, 2> mat10;
        mat10[0] = {2, 3};
        base::Matrix<int32_t, 2, 1> mat11;
        mat11[0][0] = 5;
        mat11[1][0] = 7;

        check_matrix_(mat10 * mat11, expected1);

        base::Matrix<int32_t, 2, 2> mat20;
        mat20[0] = {2, 5};
        mat20[1] = {4, 6};
        base::Matrix<int32_t, 2, 1> mat21;
        mat21[0][0] = 3;
        mat21[1][0] = 4;

        check_matrix_(mat20 * mat21, expected2);
    }


    void
    test_sum_(void)
    {
        base::Matrix<int32_t, 2, 2> mat0;
        mat0[0] = {2, 3};
        mat0[1] = {4, 8};
        base::Matrix<int32_t, 2, 2> mat1;
        mat1[0] = {6, 4};
        mat1[1] = {5, 10};

        std::array<std::array<int32_t, 2>, 2> expected_res_sum;
        expected_res_sum[0] = {8, 7};
        expected_res_sum[1] = {9, 18};

        std::array<std::array<int32_t, 2>, 2> expected_res_subtract;
        expected_res_subtract[0] = {-4, -1};
        expected_res_subtract[1] = {-1, -2};

        check_matrix_(mat0 + mat1, expected_res_sum);
        check_matrix_(mat0 - mat1, expected_res_subtract);

    }


    void
    test_print_(void)
    {
        base::corelog() << base::log_level(base::LOG_INFO)
                         << base::Matrix<int32_t, 2, 3>() << '\n';

        base::corelog() << base::log_level(base::LOG_INFO)
                        << base::identity_matrix<int32_t, 2>() << '\n';
    }


    template<typename T, size_t R, size_t C>
    void
    check_matrix_(const base::Matrix<T, R, C>& mat,
                  const std::array<std::array<T, C>, R>& expected_res)
    {
        ASSERT(R == mat.rows());
        ASSERT(C == mat.cols());

        for(unsigned i = 0; i < R; ++i)
        {
            for(unsigned j = 0; j < C; ++j)
            {
                ASSERT(expected_res[i][j] == mat[i][j]);
            }
        }
    }
}
