#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one) {

	int* pMem = new int [7]{ 2,5,2,6,2,4,6 };
	TDynamicVector<int> v(pMem, 7);
	TDynamicVector<int> v_copy(v);

	delete[] pMem;

	EXPECT_EQ(v, v_copy);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory) {

	int* pMem = new int [7] { 2, 5, 2, 6, 2, 4, 6 };
	TDynamicVector<int> v(pMem, 7);
	TDynamicVector<int> v_copy(v);

	TDynamicVector<int>* ptr = &v;
	TDynamicVector<int>* ptr_copy = &v_copy;

	delete[] pMem;

	EXPECT_NE(ptr, ptr_copy);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element) {
  TDynamicVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index) {

	TDynamicVector<int> v(7);

	ASSERT_ANY_THROW(v.at(-2) = 0);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index) {

	TDynamicVector<int> v(7);

	ASSERT_ANY_THROW(v.at(8) = 0);
}

TEST(TDynamicVector, can_assign_vector_to_itself) {

	int* pMem = new int [7] { 2, 5, 2, 6, 2, 4, 6 };
	TDynamicVector<int> v(pMem, 7);

	delete[] pMem;

	ASSERT_NO_THROW(v = v);

	EXPECT_EQ(v, v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size) {

	int* pMem_1 = new int [7] { 2, 5, 2, 6, 2, 4, 6 };
	int* pMem_2 = new int [7] { 2, 5, 2, 4, 6, 12, 54 };
	TDynamicVector<int> v_1(pMem_1, 7);
	TDynamicVector<int> v_2(pMem_2, 7);

	delete[] pMem_1;
	delete[] pMem_2;

	v_1 = v_2;

	EXPECT_EQ(v_1, v_2);
}

TEST(TDynamicVector, assign_operator_change_vector_size) {

	int* pMem_1 = new int [7] { 2, 5, 2, 6, 2, 4, 6 };
	int* pMem_2 = new int [9] { 2, 5, 2, 6, 2, 4, 6, 12, 54 };
	TDynamicVector<int> v_1(pMem_1, 7);
	TDynamicVector<int> v_2(pMem_2, 9);

	delete[] pMem_1;
	delete[] pMem_2;

	ASSERT_NO_THROW(v_1 = v_2);

	EXPECT_EQ(v_1.size(), v_2.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size) {

	int* pMem_1 = new int [7] { 2, 5, 2, 6, 2, 4, 6 };
	int* pMem_2 = new int [9] { 2, 5, 2, 6, 2, 4, 6, 12, 54 };
	TDynamicVector<int> v_1(pMem_1, 7);
	TDynamicVector<int> v_2(pMem_2, 9);

	delete[] pMem_1;
	delete[] pMem_2;

	v_1 = v_2;

	EXPECT_EQ(v_1, v_2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true) {

	int* pMem_1 = new int [7] { 2, 5, 2, 6, 2, 4, 6 };
	TDynamicVector<int> v_1(pMem_1, 7);
	TDynamicVector<int> v_2(pMem_1, 7);

	delete[] pMem_1;

	EXPECT_EQ(v_1 == v_2, 1);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true) {

	int* pMem_1 = new int [7] { 2, 5, 2, 6, 2, 4, 6 };
	TDynamicVector<int> v_1(pMem_1, 7);

	delete[] pMem_1;

	EXPECT_EQ(v_1 == v_1, 1);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal) {

	int* pMem_1 = new int [3] { 2, 5, 2};
	int* pMem_2 = new int [4] { 2, 6, 12, 54 };

	TDynamicVector<int> v_1(pMem_1, 3);
	TDynamicVector<int> v_2(pMem_2, 4);

	delete[] pMem_1;
	delete[] pMem_2;

	EXPECT_EQ(v_1 != v_2, 1);
	EXPECT_EQ(v_1 == v_2, 0);
}

TEST(TDynamicVector, can_add_scalar_to_vector) {

	int val = 6;
	int* pMem = new int [3] { 2, 5, 2};
	int* pMem_new = new int [3] { 8, 11, 8};
	TDynamicVector<int> v(pMem, 3); // (2, 5, 2)
	TDynamicVector<int> v_new(pMem_new, 3); // (8, 13, 8)


	delete[] pMem;
	delete[] pMem_new;

	EXPECT_EQ(v_new, v + val);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector) {

	int val = 6;
	int* pMem = new int [3] { 2, 5, 2};
	int* pMem_new = new int [3] { -4, -1, -4};
	TDynamicVector<int> v(pMem, 3);
	TDynamicVector<int> v_new(pMem_new, 3);


	delete[] pMem;
	delete[] pMem_new;

	EXPECT_EQ(v_new, v - val);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector) {

	int val = 6;
	int* pMem = new int [3] { 2, 5, 2};
	int* pMem_new = new int [3] { 12, 30, 12};
	TDynamicVector<int> v(pMem, 3);
	TDynamicVector<int> v_new(pMem_new, 3);


	delete[] pMem;
	delete[] pMem_new;

	EXPECT_EQ(v_new, v * val);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size) {

	int* pMem = new int [3] { 7, 8, 9 };
	int* pMem_1 = new int [3] { 2, 5, 2 };
	int* pMem_2 = new int[3] { 5, 3, 7 };

	TDynamicVector<int> v(pMem, 3);
	TDynamicVector<int> v_1(pMem_1, 3);
	TDynamicVector<int> v_2(pMem_2, 3);

	delete[] pMem;
	delete[] pMem_1;
	delete[] pMem_2;

	EXPECT_EQ(v_2 + v_1, v);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size) {

	int* pMem = new int [3] { 7, 8, 9 };
	int* pMem_1 = new int [5] { 2, 5, 2, 1, 6 };

	TDynamicVector<int> v(pMem, 3);
	TDynamicVector<int> v_1(pMem_1, 5);

	delete[] pMem;
	delete[] pMem_1;

	ASSERT_ANY_THROW(v + v_1);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size) {

	int* pMem = new int [3] { 3, -2, 5 };
	int* pMem_1 = new int [3] { 2, 5, 2 };
	int* pMem_2 = new int[3] { 5, 3, 7 };

	TDynamicVector<int> v(pMem, 3);
	TDynamicVector<int> v_1(pMem_1, 3);
	TDynamicVector<int> v_2(pMem_2, 3);

	delete[] pMem;
	delete[] pMem_1;
	delete[] pMem_2;

	EXPECT_EQ(v_2 - v_1, v);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size) {

	int* pMem = new int [3] { 7, 8, 9 };
	int* pMem_1 = new int [5] { 2, 5, 2, 1, 6 };

	TDynamicVector<int> v(pMem, 3);
	TDynamicVector<int> v_1(pMem_1, 5);

	delete[] pMem;
	delete[] pMem_1;

	ASSERT_ANY_THROW(v - v_1);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size) {

	int sum = 72;

	int* pMem = new int [3] { 7, 8, 9 };
	int* pMem_1 = new int [3] { 2, 5, 2};

	TDynamicVector<int> v(pMem, 3);
	TDynamicVector<int> v_1(pMem_1, 3);

	delete[] pMem;
	delete[] pMem_1;

	EXPECT_EQ(v * v_1, sum);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size) {

	int* pMem = new int [3] { 7, 8, 9 };
	int* pMem_1 = new int [5] { 2, 5, 2, 1, 6 };

	TDynamicVector<int> v(pMem, 3);
	TDynamicVector<int> v_1(pMem_1, 5);

	delete[] pMem;
	delete[] pMem_1;

	ASSERT_ANY_THROW(v * v_1);
}

