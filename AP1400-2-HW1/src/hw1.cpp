#include "hw1.h"

namespace algebra
{
Matrix zeros(size_t n, size_t m){
  return Matrix(n, std::vector<double>(m, 0.0));
}


Matrix ones(size_t n, size_t m){
  return Matrix(n, std::vector<double>(m, 1.0));
}

Matrix random(size_t n, size_t m, double min, double max){
  if (min > max){
    throw std::invalid_argument("max must larger than min");
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dist(min, max);

  Matrix result(n, std::vector<double>(m));

  for (std::vector<double>& row:result){
    for (double& elem:row){
      elem = dist(gen);
    }
  }
  return result;
}

void show(const Matrix& matrix){
  for (auto& row:matrix){
    for (auto& elem:row){
      std::cout << std::setprecision(3) << elem << "\t";
    }
    std::cout << std::endl;
  }
}

//note const
Matrix Multiply(const Matrix& matrix, double c){
  if (matrix.empty()){
    return Matrix{};
  }

  size_t m = matrix.size();
  size_t n = matrix[0].size();

  Matrix result = zeros(m, n);

  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < n; j++)
    {
      result[i][j] = c * matrix[i][j];
    }
  }
  return result;
}

Matrix Multiply(const Matrix& matrix1, const Matrix& matrix2){

  if(matrix1.empty() || matrix2.empty()){
    throw std::logic_error("matrices with wrong dimensions cannot be multiplied");
  }
  size_t m1 = matrix1.size();
  size_t m2 = matrix2.size();
  size_t n1 = matrix1[0].size();
  size_t n2 = matrix2[0].size();
  if (n1 != m2)
  {
      throw std::logic_error("matrices with wrong dimensions cannot be multiplied.");
  }
  Matrix result = zeros(m1, n1);

  for (int k = 0; k < n1; k++){
    for (int i = 0; i < n1; i++){
      for (int j = 0; j < m2; j++){
        result[i][j] = matrix1[i][k] * matrix2[k][j];
     }
    }
  }
  return result;
}


Matrix sum(const Matrix& matrix, double c){
  if (matrix.empty()){
    return Matrix{};
  }

  size_t m = matrix.size();
  size_t n = matrix[0].size();

  Matrix result = zeros(m, n);
  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < n; j++)
    {
      result[i][j] = c + matrix[i][j];
    }
  }
  return result;
}

Matrix sum(const Matrix& matrix1, const Matrix& matrix2){
  if(matrix1.empty() || matrix2.empty()){
    return Matrix{};
  }

  size_t m1 = matrix1.size();
  size_t m2 = matrix2.size();
  size_t n1 = matrix1[0].size();
  size_t n2 = matrix2[0].size();

  Matrix result = zeros(m1, n1);
  if (n1!=m1 || n2!=m2){
    throw std::logic_error("sum matrices should be in same dimension");
  }

  for (int i = 0; i < m1; i++)
  {
    for (int j = 0; j < n1; j++)
    {
      result[i][j] = matrix1[i][j] + matrix2[i][j];
    }
  }
  return result;
}

Matrix transpose(const Matrix& matrix){
  if (matrix.empty()){
    return Matrix{};
  }
  size_t m = matrix.size();
  size_t n = matrix[0].size();

  Matrix result = zeros(m,n);

  for (int i = 0; i < m; i++){
    for (int j = 0; j < n; j++){
      result[j][i] = matrix[i][j];
    }
  }
  return result;
}

Matrix minor(const Matrix& matrix, size_t n, size_t m){
  if (matrix.empty()){
    return Matrix{};
  }
  size_t k = matrix.size();
  size_t g = matrix[0].size();

  Matrix result = zeros(k-1,g-1);

  for (int i = 0, sub_i = 0; i < k; ++i){
    for (int j = 0, sub_j = 0; j < g; ++j){
      if(i == k || j == g){
        continue;
      }
      result[sub_i][sub_j] = matrix[i][j];
      ++sub_j;
    }
    ++sub_i;
  }
  return result;
}

double determinant(const Matrix& matrix){
  if (matrix.empty()){
    return 0;
  }

  size_t k = matrix.size();
  size_t g = matrix[0].size();
  double result = 0;

  if (k != g){
    throw std::logic_error("determinant require matrix be square");
  }

  if (k == 1){
    return matrix[0][0];
  }

  if (k == 2){
    return matrix[0][0] * matrix[1][1] - matrix[0][1]*matrix[1][0];
  }

  for (int j = 0; j < k; ++j){
      result += (j%2 == 0 ? 1 : -1) * determinant(minor(matrix, 0, j)) * matrix[0][j];
    }
  return result;
  }


Matrix inverse(const Matrix& matrix){
  if (matrix.empty()){
    return Matrix{};
  }

  size_t k = matrix.size();
  size_t g = matrix[0].size();

  if (k != g){
    throw std::logic_error("determinant require matrix be square");
  }

  Matrix result = zeros(k,g);
  double det = determinant(matrix);
  for (int i = 0; i < k; ++i){
    for (int j = 0; j < g; ++j){
      result[i][j] = determinant(minor(matrix, i, j))/det;
    }
  }
  return result;
}


Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis) {
    Matrix result = matrix1;
    if (axis == 0) {
        result.insert(result.end(), matrix2.begin(), matrix2.end());
    } else {
        for (size_t i = 0; i < matrix1.size(); ++i) {
            result[i].insert(result[i].end(), matrix2[i].begin(), matrix2[i].end());
        }
    }
    return result;
}

Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2){
  if (r1 >= matrix.size() || r2 >= matrix[0].size()){
    throw std::out_of_range("Row indices out of bounds");
  }
  Matrix result = matrix;
  std::swap(result[r1], result[r2]);
  return result;
}

Matrix ero_multiply(const Matrix& matrix, size_t r, double c){
  Matrix result = matrix;
  if (r >= matrix.size()){
    throw std::out_of_range("Row indices out of bounds");
  }
  for (auto& elem:result[r]){
    elem *= c;
  }
  return result;
}

Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2){
  if (r1 >= matrix.size() || r2 >= matrix.size()){
    throw std::out_of_range("Row indices out of bounds");
  }

  size_t k = matrix.size();
  size_t g = matrix[0].size();
  Matrix result = matrix;

  for (int i = 0; i < k; ++i){
    result[r2][i] += c * result[r1][i];
  }

  return result;
}


Matrix upper_triangular(const Matrix& matrix){
  size_t k = matrix.size();
  size_t g = matrix[0].size();

  if (k != g){
    throw std::logic_error("require matrix be square");
  }

  Matrix result = matrix;

  for (int i = 0; i < k; ++i){
    double diagonal_elem = result[i][i];
    for (int j = i+1; j < k; ++j){
      double elem = result[i][j];
      result = ero_sum(result, i, -elem/diagonal_elem, j);
    }
  }

  return result;
}
}
