# Matrices

--- 

Matrices in the C language.
This project was made with the aim of creating a library where there will be simple operations for working with matrices.

---

- [matrix](#matrix)
- [creating a matrix](#creating-a-matrix)
- [removing the matrix](#removing-the-matrix)
- [comparison](#comparison)
- [matrix addition](#matrix-addition)
- [matrix subtraction](#matrix-subtraction)
- [Multiplying a matrix by a number](#multiplying-a-matrix-by-a-number)
- [two-matrix multiplication](#two-matrix-multiplication)
- [Matrix transposition](#matrix-transposition)
- [matrix of algebraic additions](#matrix-of-algebraic-additions)
- [determinant](#determinant)
- [inverse matrix](#inverse-matrix)
- [library](#library)

---

## matrix

    matrix as a data type

The matrix is pressed as a structure - `` matrix_t ``

```c
typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;
```

Example of creating a matrix as a data type:

```c
int main() {
    matrix_t my_matrix;
}
```

Many functions accept a result matrix. The result matrix should be empty.

---

## creating a matrix

To create a matrix, you need to call the function ``MatrixCreate()`` and pass three arguments there - the required number of rows, columns, the data type itself (its address). The function will return 0 if everything is completed successfully.

```c
matrix_t my_matrix;
int fail = MatrixCreate(4, 4, &my_matrix);

```

---

## removing the matrix

To delete a matrix, call the function ``MatrixRemove()``.
The function takes on one parameter - ``matrix_t``
If memory is not allocated, the data type is protected from deletion if it contains NULL; In case its contents were changed incorrectly, outside of these functions, make an error while the program is running.

```c
int main() {
matrix_t my_matrix;
int fail = MatrixCreate(4, 4, &my_matrix);
MatrixRemove(&my_matrix);
}
```

---

## Comparison

Comparison of two matrices. 
To compare two matrices, you need to call the function ``MatrixEq()`` and pass two matrices to it as two arguments.

```c
#define SUCCESS 1
#define FAILURE 0 

int succes = (MatrixEq(&my_matrix, &other_matrix) == 1) ? SUCCESS : FAILURE;
```

The function will return 1 if the matrices are equal, otherwise 0;

---

## Matrix addition

To add two matrices, use the function ``MatrixSum()``.
Pass three arguments to it, the last of which will be the result of addition. The function will return one if there is an error.

```c
matrix_t result;
int fail = MatrixSum(&matrix_one, &matrix_two, &result);
```

---

## Matrix subtraction

To subtract two matrices, use the function ``MatrixSub()``.
Pass three arguments to it, the last of which will be the result of subtraction. The function will return one if there is an error.

```c
matrix_t result;
int fail = MatrixSub(&matrix_one, &matrix_two, &result);
```

---

## Multiplying a matrix by a number

To multiply a matrix by a number, use the function ``MatrixMultNum()``. The function takes three parameters, the first is a matrix, the second is a number, and the third is the returned result.
The function will return a number other than 0 - if there is an error (or it will be impossible to multiply two matrices).

```c
double other_num = 5.3;
matrix_t result;
int fail = MatrixMultNum(&my_matrix, other_num, &result);
```

---

## Multiplication of two matrices

To multiply two matrices, use the function ``MatrixMultMatrix()``. The function takes three parameters, all matrices the last one is the result matrix. The function returns 0 if everything was successful. 

```c
matrix_t result;
int fail = MatrixMultNum(&my_matrix, &other_matrix, &result);
```

---

## Matrix transposition

To get the transposed matrix in the function ``MatrixTranspose()`` pass two arguments, the first is your matrix. The second is the result matrix.

```c
matrix_t result;
int fail = MatrixTranspose(&my_matrix, &result);
```

---

## Matrix of algebraic additions

To get the matrix of algebraic complements, use the function ``MatrixCalcComplements()`'. The first argument of the function is your matrix. The second argument of the function is the result matrix.

```c
matrix_t result;
int fail = MatrixCalcComplements(&my_matrix, &result);
```

--- 

## Determinant

    I used recursion to find


In order to find the determinant of the matrix (determinant), use the function ``MatrixDet()``. The first argument of the function is the matrix, the second argument of the function is the result of the type ``double``

```c
double result; 
int fail = MatrixDet(&my_matrix, &result);
```

---

## Inverse matrix

To find the inverse matrix, use ``MatrixInverse()``.  The first argument of the function is the matrix, the second argument of the function is the matrix for the result.
Returns a number other than 0 in case of a wide variety of errors.

```c
matrix_t result;
int fail = MatrixInverse(&my_matrix, &result)
```

---

## library

I use a makefile to build projects. To build the library, use the makefile matrix.a target. He will put it in the lib directory.

```bash
jokerooo7@pc macOS % make matrix.a

```
