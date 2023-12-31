# Матрицы

--- 

Матрицы на языке си.
Данный проект был сделан с целью создания библиотеки, где будут простые операции для работы с матрциами.

---

- [матрциа](#матрица)
- [cоздание матрицы](#создание-матрицы)
- [удаление матрицы](#удаление-матрицы)
- [сравнение](#сравнение)
- [сложение матриц](#сложение-матриц)
- [вычитание матриц](#вычитание-матриц)
- [умножение матрицы на число](#умножение-матрицы-на-число)
- [умножение двуъ матриц](#умножение-двух-матриц)
- [транспонирование матриц](#транспонирование-матрицы)
- [матрица алгебраических дополнений](#матрица-алгебраический-дополнений)
- [определитель](#определитель)
- [обратная матрица](#обратная-матрица)
- [библиотека](#библиотека)

---

## матрица

    матрица как тип данных

Матрица пресдавлена в качестве структуры - ``` matrix_t ```

```c
typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;
```

Пример создания матрицы как тип данных:

```c
int main() {
    matrix_t my_matrix;
}
```

Многие функции принимают матрицу результата. Матрица результата должна быть пустая.

---

## создание матрицы

Для создания матрицы, надо вызвать функцию ```MatrixCreate()``` и передать туда три аргумента - необходимое количество строк, столбцов, сам тип данных (его адрес). Функция вернет 0, если все выполнено успешно.

```c
matrix_t my_matrix;
int fail = MatrixCreate(4, 4, &my_matrix);

```

---

## удаление матрицы

Для удаления матрицы надо вызвать функцию ```MatrixRemove()```.
Принимает на себя функция один параметр - ```matrix_t```
Если память не выделена, тип данных защищен от удаления, если он содержит NULL; На случай если его содержимое было изменено некорректно, вне этих функций - поулчите ошибку во время работы программы.

```c
int main() {
matrix_t my_matrix;
int fail = MatrixCreate(4, 4, &my_matrix);
MatrixRemove(&my_matrix);
}
```

---

## Сравнение

Сравнение двух матриц. 
Чтобы сравнить две марицы, необходимо вызвать функцию ```MatrixEq()``` и передать в нее в качестве двух аргументов, две матрицы.

```c
#define SUCCESS 1
#define FAILURE 0 

int succes = (MatrixEq(&my_matrix, &other_matrix) == 1) ? SUCCESS : FAILURE;
```

Функция вернет 1 если матрицы равны, в противном случаее 0;

---

## Сложение матриц

Для сложения двух матриц используйте функцию ```MatrixSum()```.
Передайте в нее три аргумента, последний из которых будет результатом сложения. Функция вернет единицу, если будет ошибка.

```c
matrix_t result;
int fail = MatrixSum(&matrix_one, &matrix_two, &result);
```

---

## Вычитание матриц

Для вычитания двух матриц используйте функцию ```MatrixSub()```.
Передайте в нее три аргумента, последний из которых будет результатом вычитания. Функция вернет единицу, если будет ошибка.

```c
matrix_t result;
int fail = MatrixSub(&matrix_one, &matrix_two, &result);
```

---

## Умножение матрицы на число

Для умножения матрциы на число используйте функцию ```MatrixMultNum()```. Функция принимает три параметра, первый - матрица, второй число, третий - возвращаемый резульат.
Функция вернет число отличное от 0 - если будет ошибка (или невозможно будет умножить две матрицы).

```c
double other_num = 5.3;
matrix_t result;
int fail = MatrixMultNum(&my_matrix, other_num, &result);
```

---

## Умножение двух матриц

Для умножения двух матриц - используйте функцию ```MatrixMultMatrix()```. Функция принимает три параметра, все матрицы последняя - матрица результат. Функция верент 0, если все было успешно. 

```c
matrix_t result;
int fail = MatrixMultNum(&my_matrix, &other_matrix, &result);
```

---

## Транспонирование матрицы

Для получения транспонированный матрицы в функцию ```MatrixTranspose()``` передайте два аргумента, первый - это ваша матрица. Второй - матрица результата.

```c
matrix_t result;
int fail = MatrixTranspose(&my_matrix, &result);
```

---

## Матрица алгебраический дополнений

Для получения матрицы алгебраических дополнений используйте функцию ```MatrixCalcComplements()```. Первый аргумент функции - это ваша матрица. Второй аргумент функции - матрица результата.

```c
matrix_t result;
int fail = MatrixCalcComplements(&my_matrix, &result);
```

--- 

## Определитель

    Для нахождения использовал рекурсию


Для того, чтобы найти определитель матрицы(determinant), используйте функцию ```MatrixDet()```. Первый аргумент функции - матрица, второй аргумент функции - результат типа ```double```

```c
double result; 
int fail = MatrixDet(&my_matrix, &result);
```

---

## Обратная матрица

Для того, чтобы найти обратную матрицу, используйте ```MatrixInverse()```.  Первый аргумент функции - матрица, второй аргумент функции - матрица для результат.
Вернет число отличное от 0 в случае возникновения самых разнообразных ошибок.

```c
matrix_t result;
int fail = MatrixInverse(&my_matrix, &result)
```

---

## библиотека

Для сборки проектов я использую makefile. Для того, чтобы собрать библиотеку, используйте цель makefile matrix.a. Он ее соберет в директорию lib.

```bash
jokerooo7@pc macOS % make matrix.a

```
