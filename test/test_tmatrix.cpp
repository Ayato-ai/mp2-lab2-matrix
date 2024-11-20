#include "tmatrix.h"

#include <gtest.h>


template <typename T>
class TDynamicMatrix_Test : public ::testing::Test {
protected:
	void SetUp() {
		matrix = new TDynamicMatrix<T>(3);
		matrix_3 = new TDynamicMatrix<T>(3);
		matrix_copy = new TDynamicMatrix<T>(3);
		matrix_copy_2 = new TDynamicMatrix<T>(2);
		//  1 1 1   6 6 6 
		//  2 2 2   12 12 12
		//  3 3 3   18 18 18

		T* pMem_0 = new T[3]{ 1, 1, 1 };
		T* pMem_1 = new T[3]{ 2, 2, 2 };
		T* pMem_2 = new T[3]{ 3, 3, 3 };

		T* pMem = new T[3]{ 1, 2, 3 };

		vector = new TDynamicVector<T>(pMem_1, 3);
		//  3 3 3
		vector_1 = new TDynamicVector<T>(pMem, 3);
		//  1 2 3
		TDynamicVector<T> v_0(pMem_0, 3);
		TDynamicVector<T> v_1(pMem_1, 3);
		TDynamicVector<T> v_2(pMem_2, 3);

		delete[] pMem;

		delete[] pMem_0;
		delete[] pMem_1;
		delete[] pMem_2;

		matrix[0][0] = v_0;
		matrix[0][1] = v_1;
		matrix[0][2] = v_2;		
		//  2 2 2
		//  4 4 4
		//  6 6 6
		T* pMem_0_ = new T[3]{ 2, 2, 2 };
		T* pMem_1_ = new T[3]{ 4, 4, 4 };
		T* pMem_2_ = new T[3]{ 6, 6, 6 };
		
		TDynamicVector<T> v_0_(pMem_0_, 3);
		TDynamicVector<T> v_1_(pMem_1_, 3);
		TDynamicVector<T> v_2_(pMem_2_, 3);

		delete[] pMem_0_;
		delete[] pMem_1_;
		delete[] pMem_2_;

		matrix_3[0][0] = v_0_;
		matrix_3[0][1] = v_1_;
		matrix_3[0][2] = v_2_;

		*matrix_copy = *matrix;
	}

	void SetUpNewLenght(int lenght) {
		matrix = new TDynamicMatrix<T>(lenght);
	}

	void TearDown() {
		delete matrix;
		delete matrix_copy;
		delete vector;
		delete matrix_copy_2;
		delete matrix_3;
		delete vector_1;
	}

	TDynamicMatrix<T>* matrix;
	TDynamicMatrix<T>* matrix_copy;
	TDynamicVector<T>* vector;
	TDynamicMatrix<T>* matrix_copy_2;
	TDynamicMatrix<T>* matrix_3;
	TDynamicVector<T>* vector_1;

};
TYPED_TEST_CASE_P(TDynamicMatrix_Test);




TYPED_TEST_P(TDynamicMatrix_Test, can_create_matrix_with_positive_length) {
	ASSERT_NO_THROW(this->SetUpNewLenght(10));
}

TYPED_TEST_P(TDynamicMatrix_Test, cant_create_too_large_matrix) {
	ASSERT_ANY_THROW(this->SetUpNewLenght(MAX_MATRIX_SIZE + 1));
}

TYPED_TEST_P(TDynamicMatrix_Test, throws_when_create_matrix_with_negative_length) {
	ASSERT_ANY_THROW(this->SetUpNewLenght(-5));
}

TYPED_TEST_P(TDynamicMatrix_Test, can_create_copied_matrix) {
	ASSERT_NO_THROW(this->SetUp());
}

TYPED_TEST_P(TDynamicMatrix_Test, copied_matrix_is_equal_to_source_one) {
	this->SetUp();
	EXPECT_EQ(*this->matrix, *this->matrix_copy);
}

TYPED_TEST_P(TDynamicMatrix_Test, copied_matrix_has_its_own_memory) {
	this->SetUp();
	EXPECT_NE(this->matrix, this->matrix_copy);
}

TYPED_TEST_P(TDynamicMatrix_Test, can_get_size) {
	this->SetUp();
	EXPECT_EQ(this->matrix->size(), 3);
}

TYPED_TEST_P(TDynamicMatrix_Test, can_set_and_get_element) {
	this->SetUp();
	EXPECT_EQ(this->matrix[0][1], *this->vector);
}

TYPED_TEST_P(TDynamicMatrix_Test, throws_when_set_element_with_negative_index) {
	this->SetUp();
	ASSERT_ANY_THROW(this->matrix->at(-2) = 0);
}

TYPED_TEST_P(TDynamicMatrix_Test, throws_when_set_element_with_too_large_index) {
	this->SetUp();
	ASSERT_ANY_THROW(this->matrix->at(5) = 0);
}

TYPED_TEST_P(TDynamicMatrix_Test, can_assign_matrix_to_itself) {
	this->SetUp();
	ASSERT_NO_THROW(*this->matrix = *this->matrix);
}

TYPED_TEST_P(TDynamicMatrix_Test, can_assign_matrices_of_equal_size) {
	this->SetUp();
	EXPECT_EQ(*this->matrix_copy, *this->matrix);
}

TYPED_TEST_P(TDynamicMatrix_Test, assign_operator_change_matrix_size) {
	this->SetUp();
	*this->matrix_copy_2 = *this->matrix;

	EXPECT_EQ(this->matrix_copy_2->size(), 3);
}

TYPED_TEST_P(TDynamicMatrix_Test, can_assign_matrices_of_different_size) {
	this->SetUp();
	*this->matrix_copy_2 = *this->matrix;

	EXPECT_EQ(*this->matrix, *this->matrix_copy_2);
}

TYPED_TEST_P(TDynamicMatrix_Test, compare_equal_matrices_return_true) {
	this->SetUp();
	*this->matrix_copy_2 = *this->matrix;

	EXPECT_EQ(*this->matrix == *this->matrix_copy_2, 1);
}

TYPED_TEST_P(TDynamicMatrix_Test, compare_matrix_with_itself_return_true) {
	this->SetUp();
	EXPECT_EQ(*this->matrix == *this->matrix, 1);
}

TYPED_TEST_P(TDynamicMatrix_Test, matrices_with_different_size_are_not_equal) {
	this->SetUp();
	EXPECT_EQ(*this->matrix != *this->matrix_copy_2, 1);
}

TYPED_TEST_P(TDynamicMatrix_Test, can_add_matrices_with_equal_size) {
	this->SetUp();
	EXPECT_EQ(*this->matrix + *this->matrix, *this->matrix_3);
}

TYPED_TEST_P(TDynamicMatrix_Test, cant_add_matrices_with_not_equal_size) {
	this->SetUp();
	ASSERT_ANY_THROW(*this->matrix + *this->matrix_copy_2);
}

TYPED_TEST_P(TDynamicMatrix_Test, can_subtract_matrices_with_equal_size) {
	this->SetUp();
	EXPECT_EQ(*this->matrix_3 - *this->matrix, *this->matrix);
}

TYPED_TEST_P(TDynamicMatrix_Test, cant_subtract_matrixes_with_not_equal_size) {
	this->SetUp();
	ASSERT_ANY_THROW(*this->matrix - *this->matrix_copy_2);
}

TYPED_TEST_P(TDynamicMatrix_Test, can_multiplying_matrix_by_scalar) {
	this->SetUp();
	EXPECT_EQ(*this->matrix * 2, *this->matrix_3);
}

TYPED_TEST_P(TDynamicMatrix_Test, can_multiplying_matrix_by_vector_with_correct_size) {
	this->SetUp();
	EXPECT_EQ(*this->matrix * *this->vector, *this->vector_1 * 6);
}

TYPED_TEST_P(TDynamicMatrix_Test, cant_multiplying_matrix_by_vector_with_not_correct_size) {
	this->SetUp();
	ASSERT_ANY_THROW(*this->matrix_copy_2 * *this->vector);
}

TYPED_TEST_P(TDynamicMatrix_Test, can_multiplying_matrix_by_matrix_with_correct_size) {
	this->SetUp();
	EXPECT_EQ(*this->matrix * *this->matrix, *this->matrix * 6);
}

TYPED_TEST_P(TDynamicMatrix_Test, cant_multiplying_matrix_by_matrix_with_not_correct_size) {
	this->SetUp();
	ASSERT_ANY_THROW(*this->matrix * *this->matrix_copy_2);
}



REGISTER_TYPED_TEST_CASE_P(TDynamicMatrix_Test, can_create_matrix_with_positive_length, cant_create_too_large_matrix, throws_when_create_matrix_with_negative_length, can_create_copied_matrix, copied_matrix_is_equal_to_source_one, copied_matrix_has_its_own_memory, can_get_size, can_set_and_get_element, throws_when_set_element_with_negative_index, throws_when_set_element_with_too_large_index, can_assign_matrix_to_itself, can_assign_matrices_of_equal_size, assign_operator_change_matrix_size, can_assign_matrices_of_different_size, compare_equal_matrices_return_true, compare_matrix_with_itself_return_true, matrices_with_different_size_are_not_equal, can_add_matrices_with_equal_size, cant_add_matrices_with_not_equal_size, can_subtract_matrices_with_equal_size, cant_subtract_matrixes_with_not_equal_size, can_multiplying_matrix_by_scalar, can_multiplying_matrix_by_vector_with_correct_size, cant_multiplying_matrix_by_vector_with_not_correct_size, can_multiplying_matrix_by_matrix_with_correct_size, cant_multiplying_matrix_by_matrix_with_not_correct_size);
typedef ::testing::Types<int, double, long long, char, float, long> ContainerTypes;
INSTANTIATE_TYPED_TEST_CASE_P(ContainerTypesInstantiation, TDynamicMatrix_Test, ContainerTypes);
