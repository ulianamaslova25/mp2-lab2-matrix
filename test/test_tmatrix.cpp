#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
	TDynamicMatrix<int> m(5);

	ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m(5);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			m[i][j] = i + j * 2;
		}
	}
	TDynamicMatrix<int> cm(m);
	EXPECT_EQ(cm, m);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(5);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			m[i][j] = i + j * 2;
		}
	}
	TDynamicMatrix<int> cm(m);
	cm[1][1] = 0;
	EXPECT_NE(0, m[1][1]);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(10);

	EXPECT_EQ(10, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(5);
	m[0][1] = 0;

	EXPECT_EQ(0, m[0][1]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(5);
	ASSERT_ANY_THROW(m[-1] = 0);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(5);
	ASSERT_ANY_THROW(m[10] = 0);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(5);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			m[i][j] = i + j * 2;
		}
	}
	ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m(5), m1(5);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			m[i][j] = i + j * 2;
		}
	}
	m1 = m;
	EXPECT_EQ(m1, m);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m(5), m1(10);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			m[i][j] = i + j * 2;
		}
	}
	m1 = m;
	EXPECT_EQ(m1.size(), 5);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m(5), m1(10);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			m[i][j] = i + j * 2;
		}
	}
	m1 = m;
	EXPECT_EQ(m1, m);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m(5), m1(10);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			m[i][j] = i + j * 2;
		}
	}
	m1 = m;
	EXPECT_EQ(m1 == m, 1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(5);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			m[i][j] = i + j * 2;
		}
	}
	EXPECT_EQ(m == m, 1);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m(5), m1(10);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			m[i][j] = i + j * 2;
		}
	}
	EXPECT_EQ(m1 == m, 0);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(5), m1(5), m2(5), res(5);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			m[i][j] = i + j * 2 + 1;
			m1[i][j] = i + j * 2;
			m2[i][j] = 1;
		}
	}
	res = m1 + m2;
	EXPECT_EQ(res, m);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m(5), m1(10);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			m[i][j] = i + j * 2 + 1;
			m1[i][j] = i + j * 2;
		}
	}
	ASSERT_ANY_THROW(m + m1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(5), m1(5), m2(5), res(5);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			m[i][j] = i + j * 2;
			m1[i][j] = i + j * 2 + 1;
			m2[i][j] = 1;
		}
	}
	res = m1 - m2;
	EXPECT_EQ(res, m);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m(5), m1(10);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			m[i][j] = i + j * 2 + 1;
			m1[i][j] = i + j * 2;
		}
	}
	ASSERT_ANY_THROW(m - m1);
}

TEST(TDynamicVector, can_multiply_matrix_with_skal_elem)
{
	TDynamicMatrix<int> v1(2), v2(2), res(2);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			v1[i][j] = 2;
			v2[i][j] = 4;
		}
	}

	res = v1 * 2;
	EXPECT_EQ(v2, res);
}

TEST(TDynamicVector, cant_multiply_matrix_and_vector_with_non_equel_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicVector<int> v(5);
	ASSERT_ANY_THROW(m * v);
}

TEST(TDynamicVector, can_multiply_matrix_with_vector)
{
	TDynamicMatrix<int> m(2);
	TDynamicVector<int> v(2), res(2), exp(2);
	for (int i = 0; i < 2; i++) {
		v[i] = 1;
		exp[i] = 4;
		for (int j = 0; j < 2; j++) {
			m[i][j] = 2;
		}
	}

	res = m * v;
	EXPECT_EQ(res, exp);
}

TEST(TDynamicVector, cant_multiply_matrixs_with_non_equel_size)
{
	TDynamicMatrix<int> m1(2), m2(5);
	ASSERT_ANY_THROW(m1 * m2);
}

TEST(TDynamicVector, can_multiply_matrix_with_matrix)
{
	TDynamicMatrix<int> m1(2), m2(2), res(2), exp(2);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			m1[i][j] = 2;
			m2[i][j] = 1;
			exp[i][j] = 4;
		}
	}
	res = m1 * m2;
	EXPECT_EQ(exp, res);
}

TEST(TDynamicVector, can_move_matrix)
{
	TDynamicMatrix<int> v1(2), v2(2), v3(2);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			v1[i][j] = 1;
			v3[i][j] = 1;
			v2[i][j] = 2;
		}
	}
	v2 = std::move(v1);
	EXPECT_EQ(0, v1.size());
	EXPECT_EQ(2, v2.size());
	EXPECT_EQ(v3, v2);
}

