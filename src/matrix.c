#include "matrix.h"

#include "math.h"
#include "stdio.h"
#include "stdlib.h"

int MatrixCreate(int rows, int columns, matrix_t *result) {
  int fail = 0;
  if (rows > 0 && columns > 0) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix == NULL) {
      fail = 1;
    }
    for (int i = 0; i < rows && fail == 0; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
      if (result->matrix[i] == NULL) {
        fail = 1;
      }
    }
  } else {
    result->matrix = NULL;
    fail = 1;
  }
  if (fail != 0) {
    result->rows = 0;
    result->columns = 0;
  }
  return fail;
}

void MatrixRemove(matrix_t *A) {
  if (A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
  }
  A->rows = 0;
  A->columns = 0;
}

int MatrixCheckFail(double A, double B) {
  int fail = 0;
  if (A == INF || A == -INF || B == INF || B == -INF) {
    fail = 2;
  } else if (A != A || B != B) {
    fail = 2;
  }
  return fail;
}

void MatrixRoundNum(int i, int j, matrix_t *A) {
  long double c = A->matrix[i][j] * pow(10, 7);
  c = round(c);
  c *= pow(10, -7);
  A->matrix[i][j] = c;
}

int MatrixEq(matrix_t *A, matrix_t *B) {
  int fail = SUCCESS;
  if (A->matrix == NULL || B->matrix == NULL) {
    fail = FAILURE;
  } else if ((A->rows != B->rows) || A->columns != B->columns) {
    fail = FAILURE;
  } else {
    for (int i = 0; i < A->rows && fail == SUCCESS; i++) {
      for (int j = 0; j < A->columns && fail == SUCCESS; j++) {
        MatrixRoundNum(i, j, A);
        MatrixRoundNum(i, j, B);
        if (A->matrix[i][j] == INF || A->matrix[i][j] == -INF) {
          fail = FAILURE;
        } else if (B->matrix[i][j] == INF || B->matrix[i][j] == -INF) {
          fail = FAILURE;
        } else if (A->matrix[i][j] == B->matrix[i][j]) {
          fail = SUCCESS;
        } else {
          fail = FAILURE;
        }
      }
    }
  }

  return fail;
}

int MatrixSumSub(matrix_t *A, matrix_t *B, matrix_t *result, int mod) {
  int fail = 0;
  if (A->matrix == NULL || B->matrix == NULL) {
    fail = 1;
  } else if (A->rows != B->rows) {
    fail = 2;
  } else if ((A->columns != B->columns)) {
    fail = 2;
  }
  if (fail != 0) {
    result->matrix = NULL;
  } else {
    fail = MatrixCreate(A->rows, A->columns, result);
    for (int i = 0; i < result->rows && fail == 0; i++) {
      for (int j = 0; j < result->columns && fail == 0; j++) {
        if (mod == 0) {
          if ((fail = MatrixCheckFail(A->matrix[i][j], B->matrix[i][j])) == 0) {
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
          }
        } else {
          if ((fail = MatrixCheckFail(A->matrix[i][j], B->matrix[i][j])) == 0) {
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
          }
        }
      }
    }
  }

  return fail;
}

int MatrixSum(matrix_t *A, matrix_t *B, matrix_t *result) {
  int fail = 0;
  int mod = 0;
  fail = MatrixSumSub(A, B, result, mod);
  return fail;
}

int MatrixSub(matrix_t *A, matrix_t *B, matrix_t *result) {
  int fail = 0;
  int mod = 1;
  fail = MatrixSumSub(A, B, result, mod);
  return fail;
}

int MatrixMultNum(matrix_t *A, double number, matrix_t *result) {
  int fail = 0;
  if (A->matrix == NULL) {
    fail = 1;
  }
  if (fail != 0) {
    result->matrix = NULL;
  } else {
    fail = MatrixCreate(A->rows, A->columns, result);
    for (int i = 0; i < A->rows && fail == 0; i++) {
      for (int j = 0; j < A->columns && fail == 0; j++) {
        if ((fail = MatrixCheckFail(A->matrix[i][j], number)) ==
            0) {  // if ((long double = *A * number) > MAX_LONG_DOUBLE) return 1
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    }
  }

  return fail;
}

int MatrixMultMatrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int fail = 0;
  if (A->matrix == NULL || B->matrix == NULL) {
    fail = 1;
  } else if (A->rows != B->columns) {
    fail = 2;
  }
  if (fail != 0) {
    result->matrix = NULL;
  } else {
    fail = MatrixCreate(A->rows, B->columns, result);
    for (int i = 0; i < A->rows && fail == 0; i++) {
      for (int j = 0; j < B->columns && fail == 0; j++) {
        for (int k = 0; k < A->columns; k++) {
          if ((fail = MatrixCheckFail(A->matrix[i][k], B->matrix[k][j])) == 0) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
    }
  }
  return fail;
}

int MatrixTranspose(matrix_t *A, matrix_t *result) {
  int fail = 0;
  if (A->matrix == NULL) {
    fail = 1;
  }
  if (fail != 0) {
    result->matrix = NULL;
  } else {
    fail = MatrixCreate(A->columns, A->rows, result);
    for (int i = 0; i < result->rows && fail == 0; i++) {
      for (int j = 0; j < result->columns && fail == 0; j++) {
        if ((fail = MatrixCheckFail(A->matrix[j][i], 0)) == 0) {
          result->matrix[i][j] = A->matrix[j][i];
        }
      }
    }
  }
  return fail;
}

void MatrixEqMatrixForDet(int a, int b, matrix_t *A, matrix_t *B) {
  for (int i = 0, i1 = 0; i < A->rows; i++) {
    if (i != a) {
      for (int j = 0, j1 = 0; j < A->columns; j++) {
        if (j != b) {
          B->matrix[i1][j1] = A->matrix[i][j];
          j1++;
        }
      }
      i1++;
    }
  }
}

double MatrixHelpFuctDet(int a, int b, matrix_t A) {
  double result = 0;
  int fail = 0;
  matrix_t E;
  if (a != -1 || b != -1) {
    fail = MatrixCreate(A.rows - 1, A.columns - 1, &E);
  } else {
    fail = MatrixCreate(A.rows, A.columns, &E);
  }
  MatrixEqMatrixForDet(a, b, &A, &E);
  if (E.rows > 2) {
    for (int j = 0; j < E.columns; j++) {
      int alg_dop = 1;
      if (((0 + j) % 2) != 0) {
        alg_dop = -1;
      }
      result += E.matrix[0][j] * alg_dop * MatrixHelpFuctDet(0, j, E);
    }
  } else if (E.rows == 2) {
    result =
        E.matrix[0][0] * E.matrix[1][1] - (E.matrix[0][1] * E.matrix[1][0]);
  } else if (E.rows == 1) {
    result = E.matrix[0][0];
  }
  if (fail == 1) {
    result = 1.0 / 0.0;
  }
  MatrixRemove(&E);

  return result;
}

int Matrixcalc_complements_cycle(int a, int b, matrix_t *A, matrix_t *result) {
  int fail = 0;
  int alg_dop = 1;
  if (((a + b) % 2) != 0) {
    alg_dop = -1;
  }
  matrix_t E;
  if (A->rows > 1) {
    fail = MatrixCreate(A->rows - 1, A->columns - 1, &E);
    if (fail == 0) {
      MatrixEqMatrixForDet(a, b, A, &E);
      result->matrix[a][b] = alg_dop * MatrixHelpFuctDet(-1, -1, E);
    }
    MatrixRemove(&E);
  } else {
    result->matrix[0][0] = A->matrix[0][0];
  }

  return fail;
}

int MatrixCalcComplements(matrix_t *A, matrix_t *result) {
  int fail = 0;
  if (A->matrix == NULL) {
    fail = 1;
  } else if (A->rows != A->columns) {
    fail = 2;
  }
  if (fail != 0) {
    result->matrix = NULL;
  } else {
    fail = MatrixCreate(A->rows, A->columns, result);
    if (A->rows > 1 && A->columns > 1) {
      for (int i = 0; i < A->rows && fail == 0; i++) {
        for (int j = 0; j < A->columns && fail == 0; j++) {
          if ((fail = MatrixCheckFail(A->matrix[i][j], 0)) == 0) {
            fail = Matrixcalc_complements_cycle(i, j, A, result);
          }
        }
      }
    } else {
      fail = 2;
    }
  }

  return fail;
}

int MatrixDet(matrix_t *A, double *result) {
  int fail = 0;
  if (A->matrix == NULL) {
    fail = 1;
  } else if (A->rows != A->columns) {
    fail = 2;
  }
  if (fail == 0) {
    if (A->rows == 1 && A->columns == 1) {
      *result = A->matrix[0][0];
    } else {
      *result = MatrixHelpFuctDet(-1, -1, *A);
    }
  }
  if (*result == INF) {
    fail = 1;
  }

  return fail;
}

int MatrixInverse(matrix_t *A, matrix_t *result) {
  int fail = 0;
  double det = 0;
  if (A->matrix == NULL) {
    fail = 1;
  }
  if (fail != 0) {
    result->matrix = NULL;
  } else {
    if ((A->rows > 1 || A->columns > 1) && fail == 0) {
      fail = MatrixDet(A, &det);
      if (det != 0 && fail == 0) {
        det = 1 / det;
        matrix_t transp;
        matrix_t transp2;
        fail = MatrixCalcComplements(A, &transp);
        if (fail == 0) fail = MatrixTranspose(&transp, &transp2);
        if (fail == 0) fail = MatrixMultNum(&transp2, det, result);
        MatrixRemove(&transp);
        MatrixRemove(&transp2);
      } else {
        fail = 2;
      }
    } else if (A->rows == 1 && A->columns == 1 && fail == 0) {
      fail = MatrixCreate(1, 1, result);
      if (fail == 0) {
        result->matrix[0][0] = 1 / (A->matrix[0][0]);
      }
    }
  }

  return fail;
}
