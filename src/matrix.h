#ifndef MATRIX_C_MATRIX_H_
#define MATRIX_C_MATRIX_H_


#define SUCCESS 1
#define FAILURE 0
#define INF 1.0 / 0.0

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// void p(matrix_t *A);
int MatrixCreate(int rows, int columns, matrix_t *result);
void MatrixRemove(matrix_t *A);
int MatrixCheckFail(double A, double B);
void MatrixRoundNum(int i, int j, matrix_t *A);
int MatrixEq(matrix_t *A, matrix_t *B);
int MatrixSumSub(matrix_t *A, matrix_t *B, matrix_t *result, int mod);
int MatrixSum(matrix_t *A, matrix_t *B, matrix_t *result);
int MatrixSub(matrix_t *A, matrix_t *B, matrix_t *result);
int MatrixMultNum(matrix_t *A, double number, matrix_t *result);
int MatrixMultMatrix(matrix_t *A, matrix_t *B, matrix_t *result);
int MatrixTranspose(matrix_t *A, matrix_t *result);
void MatrixEqMatrixForDet(int a, int b, matrix_t *A, matrix_t *B);
double MatrixHelpFuctDet(int i, int j, matrix_t A);
int MatrixCalcComplements(matrix_t *A, matrix_t *result);
int MatrixDet(matrix_t *A, double *result); // determinant
int MatrixInverse(matrix_t *A, matrix_t *result);

#endif  // MATRIX_C_MATRIX_H_