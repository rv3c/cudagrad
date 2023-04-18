// Copyright 2023 Ryan Moore

#include <gtest/gtest.h>
#include <torch/torch.h>

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "torchy.h"  // NOLINT (build/include_subdir)

// The tests are now wrapped in TEST() macros from Google Test
// The first argument of the TEST() macro is the test suite name,
// and the second argument is the test name.

TEST(Basic, CreateTensors) {
  Tensor<float> t1({3}, {1, 2, 3});
  Tensor<float> t2({3, 3}, {1, 2, 3, 4, 5, 6, 7, 8, 9});
  Tensor<float> t3({3, 3, 3},
                   {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13,
                    14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26});
  ASSERT_EQ(t1.repr(), "Tensor({3}, {1, 2, 3})");
  ASSERT_EQ(t2.repr(), "Tensor({3, 3}, {1, 2, 3, 4, 5, 6, 7, 8, 9})");
  ASSERT_EQ(
      t3.repr(),
      "Tensor({3, 3, 3}, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, "
      "15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26})");
}

TEST(Basic, AccessTensorElement) {
  Tensor<float> tensor({3, 3}, {1, 2, 3, 4, 5, 6, 7, 8, 9});
  ASSERT_EQ(tensor({0, 1}), 2);
}

TEST(Basic, CatchRuntimeError) {
  Tensor<float> tensor({3, 3}, {1, 2, 3, 4, 5, 6, 7, 8, 9});
  try {
    tensor({0, 15});
    FAIL();  // This line should not be reached
  } catch (const std::runtime_error& e) {
    ASSERT_EQ(std::string(e.what()), std::string("Index out of bounds."));
  }
}

// Since the original create_and_print_tensor_slices() test was not working,
// I am not including it in this revised code.
// However, you can create a new test using the TEST() macro if you fix the
// issue.

TEST(Basic, CreateTensorWithValues) {
  std::vector<size_t> dimensions = {3, 3};
  std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  Tensor<int> t(dimensions, values);
  EXPECT_EQ(t.repr(), "Tensor({3, 3}, {1, 2, 3, 4, 5, 6, 7, 8, 9})");
}

TEST(Basic, TensorAddition) {
  std::vector<int> values1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<int> values2 = {2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<size_t> dimensions = {3, 3};
  Tensor<int> t1(dimensions, values1);
  Tensor<int> t2(dimensions, values2);
  Tensor<int> t3 = t1 + t2;
  EXPECT_EQ(t1.repr(), "Tensor({3, 3}, {1, 2, 3, 4, 5, 6, 7, 8, 9})");
  EXPECT_EQ(t2.repr(), "Tensor({3, 3}, {2, 3, 4, 5, 6, 7, 8, 9, 10})");
  EXPECT_EQ(t3.repr(), "Tensor({3, 3}, {3, 5, 7, 9, 11, 13, 15, 17, 19})");
}

TEST(Basic, TensorScalarAddition) {
  std::vector<size_t> dimensions = {3, 3};
  std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  Tensor<int> t(dimensions, values);
  Tensor<int> t2 = t + 3;
  EXPECT_EQ(t2.repr(), "Tensor({3, 3}, {4, 5, 6, 7, 8, 9, 10, 11, 12})");
}

TEST(Basic, TensorDivision) {
  std::vector<int> values1 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  std::vector<int> values2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<size_t> dimensions = {3, 3};
  Tensor<int> t1(dimensions, values1);
  Tensor<int> t2(dimensions, values2);
  Tensor<int> t3 = t1 / t2;
  EXPECT_EQ(t1.repr(), "Tensor({3, 3}, {9, 8, 7, 6, 5, 4, 3, 2, 1})");
  EXPECT_EQ(t2.repr(), "Tensor({3, 3}, {1, 2, 3, 4, 5, 6, 7, 8, 9})");
  EXPECT_EQ(t3.repr(), "Tensor({3, 3}, {9, 4, 2, 1, 1, 0, 0, 0, 0})");
}

TEST(Basic, TensorScalarDivision) {
  std::vector<size_t> dimensions = {3, 3};
  std::vector<int> values = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  Tensor<int> t(dimensions, values);
  Tensor<int> t2 = t / 3;
  EXPECT_EQ(t2.repr(), "Tensor({3, 3}, {3, 2, 2, 2, 1, 1, 1, 0, 0})");
}

TEST(Basic, TensorMultiplication) {
  std::vector<int> values1 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  std::vector<int> values2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<size_t> dimensions = {3, 3};
  Tensor<int> t1(dimensions, values1);
  Tensor<int> t2(dimensions, values2);
  Tensor<int> t3 = t1 * t2;
  EXPECT_EQ(t1.repr(), "Tensor({3, 3}, {9, 8, 7, 6, 5, 4, 3, 2, 1})");
  EXPECT_EQ(t2.repr(), "Tensor({3, 3}, {1, 2, 3, 4, 5, 6, 7, 8, 9})");
  EXPECT_EQ(t3.repr(), "Tensor({3, 3}, {9, 16, 21, 24, 25, 24, 21, 16, 9})");
}

TEST(Basic, TensorSubtraction) {
  std::vector<int> values1 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  std::vector<int> values2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<size_t> dimensions = {3, 3};
  Tensor<int> t1(dimensions, values1);
  Tensor<int> t2(dimensions, values2);
  Tensor<int> t3 = t1 - t2;
  EXPECT_EQ(t1.repr(), "Tensor({3, 3}, {9, 8, 7, 6, 5, 4, 3, 2, 1})");
  EXPECT_EQ(t2.repr(), "Tensor({3, 3}, {1, 2, 3, 4, 5, 6, 7, 8, 9})");
  EXPECT_EQ(t3.repr(), "Tensor({3, 3}, {8, 6, 4, 2, 0, -2, -4, -6, -8})");
}

TEST(Basic, TensorScalarMultiplication) {
  std::vector<size_t> dimensions = {3, 3};
  std::vector<int> values = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  Tensor<int> t(dimensions, values);
  Tensor<int> t2 = t * 3;
  EXPECT_EQ(t2.repr(), "Tensor({3, 3}, {27, 24, 21, 18, 15, 12, 9, 6, 3})");
}

TEST(Basic, MatrixMultiplication) {
  std::vector<size_t> dimensions1 = {2, 3};
  std::vector<int> values1 = {1, 2, 3, 4, 5, 6};
  std::vector<size_t> dimensions2 = {3, 2};
  std::vector<int> values2 = {7, 8, 9, 10, 11, 12};
  Tensor<int> t1(dimensions1, values1);
  Tensor<int> t2(dimensions2, values2);
  Tensor<int> t3 = t1.matmul(t2);
  EXPECT_EQ(t3.repr(), "Tensor({2, 2}, {58, 64, 139, 154})");
}

TEST(Basic, CatchRuntimeErrorZeroDivideScalar) {
  std::vector<size_t> dimensions = {3, 3};
  std::vector<int> values = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  Tensor<int> t(dimensions, values);
  ASSERT_THROW(t / 0, std::runtime_error);
}

TEST(Basic, CreateAndPrintTensorRepr) {
  std::vector<size_t> dimensions = {3, 3};
  std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  Tensor<int> t(dimensions, values);
  EXPECT_EQ(t.repr(), "Tensor({3, 3}, {1, 2, 3, 4, 5, 6, 7, 8, 9})");
}

TEST(Basic, StorageDtypeIsInt) {
  Storage<int> storage(5, {1, 2, 3, 4, 5});
  ASSERT_TRUE((std::is_same<Storage<int>::dtype, int>::value));
}

TEST(Basic, TensorDtypeIsInt) {
  Tensor<int> tensor({3, 3}, {1, 2, 3, 4, 5, 6, 7, 8, 9});
  ASSERT_TRUE((std::is_same<Tensor<int>::dtype, int>::value));
}

// FIXME(yrom1) this is broken and submatrix doesnt exist

// TEST(TensorTest, CreateAndPrintTensorSlices) {
//   std::vector<size_t> dimensions = {3, 3};
//   std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9};
//   Tensor<int> t(dimensions, values);

//   // Row slice
//   Tensor<int> row_slice = t.slice({0}, {1, 3});
//   EXPECT_EQ(row_slice.repr(), "Tensor({1, 3}, {1, 2, 3})");

//   // Column slice
//   Tensor<int> col_slice = t.slice({1}, {3, 1});
//   EXPECT_EQ(col_slice.repr(), "Tensor({3, 1}, {2, 5, 8})");

//   // Submatrix slice
//   Tensor<int> submatrix_slice = t.slice({0, 1}, {2, 2});
//   EXPECT_EQ(submatrix_slice.repr(), "Tensor({2, 2}, {2, 3, 5, 6})");
// }

template <typename T>
std::vector<T> tensorToVector(const torch::Tensor& tensor) {
  size_t num_elements = tensor.numel();
  std::vector<T> result(num_elements);
  std::memcpy(result.data(), tensor.data_ptr<T>(), num_elements * sizeof(T));
  return result;
}

TEST(Torch, Neuron) {
  // Test input tensors
  Tensor<int> x({3, 2}, {1, 2, 3, 4, 5, 6});
  Tensor<int> w({2, 4}, {1, 2, 3, 4, 5, 6, 7, 8});
  Tensor<int> b({1, 4}, {1, 2, 3, 4});
  Tensor<int> result = x.matmul(w) + b;
  auto result_v = result.storage()->data();

  std::vector<int> data1 = {1, 2, 3, 4, 5, 6};
  std::vector<int> data2 = {1, 2, 3, 4, 5, 6, 7, 8};
  at::Tensor x_aten = at::from_blob(data1.data(), {3, 2}, at::kInt);
  at::Tensor w_aten = at::from_blob(data2.data(), {2, 4}, at::kInt);
  at::Tensor b_aten = at::tensor({1, 2, 3, 4}).unsqueeze(0);
  at::Tensor result_aten = x_aten.matmul(w_aten) + b_aten;
  std::vector<int> result_aten_v = tensorToVector<int>(result_aten);
  // std::cout << result_v << std::endl;
  // std::cout << result_aten_v << std::endl;
  EXPECT_EQ(result_v, result_aten_v);
}

TEST(Torch, BackwardAdd) {
  torch::Tensor a =
      torch::tensor({{1.0, 2.0}, {3.0, 4.0}}, torch::requires_grad(true));
  torch::Tensor b =
      torch::tensor({{2.0, 3.0}, {4.0, 5.0}}, torch::requires_grad(true));
  torch::Tensor c = a + b;
  torch::Tensor scalar_output = c.sum();
  scalar_output.backward();
  auto result_torch_a = tensorToVector<float>(a.grad());
  auto result_torch_b = tensorToVector<float>(b.grad());

  std::vector<float> result_torchy = {42.0, 42.0, 42.0, 42.0};

  EXPECT_EQ(result_torch_a, result_torchy);
  EXPECT_EQ(result_torch_b, result_torchy);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
