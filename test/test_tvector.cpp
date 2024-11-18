#include "tmatrix.h"

#include <gtest.h>

template <typename T>
class TDynamicVector_Test : public ::testing::Test {
protected:
	void SetUp() {
		vector = new TDynamicVector<T>(5);
	}
	void SetUpCopy() {
		T* pMem = new T[3]{ 2, 5, 2 };
		vector = new TDynamicVector<T>(pMem, 3);
		delete[] pMem;

		T* pMem_1 = new T[4]{ 3, 5, 3, 2 };
		vector_1 = new TDynamicVector<T>(pMem_1, 4);
		delete[] pMem_1;

		T* pMem_2 = new T[3]{ 4, 7, 4 };
		vector_2 = new TDynamicVector<T>(pMem_2, 3);
		delete[] pMem_2;

		T* pMem_3 = new T[3]{ 4, 10, 4 };
		vector_3 = new TDynamicVector<T>(pMem_3, 3);
		delete[] pMem_3;

		T* pMem_4 = new T[3]{ 6, 12, 6 };
		vector_4 = new TDynamicVector<T>(pMem_4, 3);
		delete[] pMem_4;

		vector_copy = new TDynamicVector<T>(3);

		*vector_copy = *vector;
	}
	void SetUpNewLenght(int lenght) {
		vector = new TDynamicVector<T>(lenght);
	}
	void TearDown() {
		delete vector;
	}
	void TearDownCopy() {
		delete vector;
		delete vector_1;
		delete vector_2;
		delete vector_3;
		delete vector_4;
		delete vector_copy;
	}
	TDynamicVector<T>* vector;
	TDynamicVector<T>* vector_1;
	TDynamicVector<T>* vector_2;
	TDynamicVector<T>* vector_3;
	TDynamicVector<T>* vector_4;
	TDynamicVector<T>* vector_copy;
};
TYPED_TEST_CASE_P(TDynamicVector_Test);

TYPED_TEST_P(TDynamicVector_Test, can_create_vector_with_positive_length) {
	ASSERT_NO_THROW(this->SetUpNewLenght(5));
}

TYPED_TEST_P(TDynamicVector_Test, cant_create_too_large_vector) {
	ASSERT_ANY_THROW(this->SetUpNewLenght(MAX_VECTOR_SIZE + 1));
}

TYPED_TEST_P(TDynamicVector_Test, throws_when_create_vector_with_negative_length) {
	ASSERT_ANY_THROW(this->SetUpNewLenght(-5));
}

TYPED_TEST_P(TDynamicVector_Test, can_create_copied_vector) {
	ASSERT_NO_THROW(this->SetUpCopy());
}

TYPED_TEST_P(TDynamicVector_Test, copied_vector_is_equal_to_source_one) {
	this->SetUpCopy();
	EXPECT_EQ(*vector, *vector_copy);
}

TYPED_TEST_P(TDynamicVector_Test, copied_vector_has_its_own_memory) {
	this->SetUpCopy();
	EXPECT_NE(vector, vector_copy);
}

TYPED_TEST_P(TDynamicVector_Test, can_get_size) {
	EXPECT_EQ(5, vector->size());
}

TYPED_TEST_P(TDynamicVector_Test, can_set_and_get_element) {
	this->vector[0][0] = 2;

	EXPECT_EQ(2, this->vector[0][0]);
}

TYPED_TEST_P(TDynamicVector_Test, throws_when_set_element_with_negative_index) {
	ASSERT_ANY_THROW(vector->at(-2) = 0);
}

TYPED_TEST_P(TDynamicVector_Test, throws_when_set_element_with_too_large_index) {
	ASSERT_ANY_THROW(vector->at(8) = 0);
}

TYPED_TEST_P(TDynamicVector_Test, can_assign_vector_to_itself) {
	EXPECT_EQ(*vector, *vector);
}

TYPED_TEST_P(TDynamicVector_Test, can_assign_vectors_of_equal_size) {
	this->SetUpCopy();
	EXPECT_EQ(*vector, *vector_copy);
}

TYPED_TEST_P(TDynamicVector_Test, assign_operator_change_vector_size) {
	this->SetUpCopy();
	*vector = *vector_1;
	EXPECT_EQ(vector->size(), vector_1->size());
}

TYPED_TEST_P(TDynamicVector_Test, can_assign_vectors_of_different_size) {
	this->SetUpCopy();
	*vector = *vector_1;
	EXPECT_EQ(*vector, *vector_1);
}

TYPED_TEST_P(TDynamicVector_Test, compare_equal_vectors_return_true) {
	this->SetUpCopy();
	EXPECT_EQ(*vector == *vector_copy, 1);
}

TYPED_TEST_P(TDynamicVector_Test, compare_vector_with_itself_return_true) {
	this->SetUpCopy();
	EXPECT_EQ(*vector == *vector, 1);
}

TYPED_TEST_P(TDynamicVector_Test, vectors_with_different_size_are_not_equal) {
	this->SetUpCopy();
	EXPECT_EQ(*vector != *vector_1, 1);
	EXPECT_EQ(*vector == *vector_1, 0);
}

TYPED_TEST_P(TDynamicVector_Test, can_add_scalar_to_vector) {
	this->SetUpCopy();
	EXPECT_EQ(*vector_2, *vector + 2);
}

TYPED_TEST_P(TDynamicVector_Test, can_subtract_scalar_from_vector) {
	this->SetUpCopy();
	EXPECT_EQ(*vector, *vector_2 - 2);
}

TYPED_TEST_P(TDynamicVector_Test, can_multiply_scalar_by_vector) {
	this->SetUpCopy();
	EXPECT_EQ(*vector_3, *vector * 2);
}

TYPED_TEST_P(TDynamicVector_Test, can_add_vectors_with_equal_size) {
	this->SetUpCopy();
	EXPECT_EQ(*vector_2 + *vector, *vector_4);
}

TYPED_TEST_P(TDynamicVector_Test, cant_add_vectors_with_not_equal_size) {
	this->SetUpCopy();
	ASSERT_ANY_THROW(*vector_1 + *vector);
}

TYPED_TEST_P(TDynamicVector_Test, can_subtract_vectors_with_equal_size) {
	this->SetUpCopy();
	EXPECT_EQ(*vector_4 - *vector, *vector_2);
}

TYPED_TEST_P(TDynamicVector_Test, cant_subtract_vectors_with_not_equal_size) {
	this->SetUpCopy();
	ASSERT_ANY_THROW(*vector_1 - *vector);
}

TYPED_TEST_P(TDynamicVector_Test, can_multiply_vectors_with_equal_size) {
	this->SetUpCopy();
	EXPECT_EQ(*vector_2 * *vector, 51);
}

TYPED_TEST_P(TDynamicVector_Test, cant_multiply_vectors_with_not_equal_size) {
	this->SetUpCopy();
	ASSERT_ANY_THROW(*vector_1 * *vector);
}


REGISTER_TYPED_TEST_CASE_P(TDynamicVector_Test, can_create_vector_with_positive_length, cant_create_too_large_vector, throws_when_create_vector_with_negative_length, can_create_copied_vector, copied_vector_is_equal_to_source_one, copied_vector_has_its_own_memory, can_get_size, can_set_and_get_element, throws_when_set_element_with_negative_index, throws_when_set_element_with_too_large_index, can_assign_vector_to_itself, can_assign_vectors_of_equal_size, assign_operator_change_vector_size, can_assign_vectors_of_different_size, compare_equal_vectors_return_true, compare_vector_with_itself_return_true, vectors_with_different_size_are_not_equal, can_add_scalar_to_vector, can_subtract_scalar_from_vector, can_multiply_scalar_by_vector, can_add_vectors_with_equal_size, cant_add_vectors_with_not_equal_size, can_subtract_vectors_with_equal_size, cant_subtract_vectors_with_not_equal_size, can_multiply_vectors_with_equal_size, cant_multiply_vectors_with_not_equal_size);
typedef ::testing::Types<int, double, long long, char, float, long, unsigned int, unsigned long, unsigned long long> ContainerTypes;
INSTANTIATE_TYPED_TEST_CASE_P(ContainerTypesInstantiation, TDynamicVector_Test, ContainerTypes);
