#ifndef STRUCT_H
#define STRUCT_H
#define BUFFER_SIZE 256 //максимальное количество символов в строке
#define NUM_MAX 0 //номер максимального элемента в массиве
#define NUM_MIN 1 //номер минимального элемента в массиве
#define NUM_MED 2 //номер среднего элемента в массиве
#define NUMBER_OF_VALUE 3 //количество чисел в массиве с максимум, минимум, медианой
#define HEADER 0 //номер строки с заголовками
#define REG_COLUMN_NUM 1 //элемент с именем региона
#define NUM_OF_COLUMNS 1 //начальное число колонок
#define NUM_OF_LINES 0 //начальное число строк
#define MAX_SIZE 1 //изначальная длина строк
#define GRAPH_VALUE 2 //количество переменных для графика
#define YEARS 1980 //коэффициент для вывода на график года
#define RATIO 10 //коэффициент для вывода на график года

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>

//исходные данные
typedef struct {
    char *filename; //имя файла
    char *regionname; //имя региона
    int numcolumns; //номер колонки
    char **table_headers; //заголовки таблицы
    char ***data; //данные
    size_t lines; //количество строк
    size_t columns; //количество столбцов
} FunctionArgument;

//выходные данные
typedef struct {
    char **table_headers; //заголовки таблицы
    char ***data; //данные
    double calculation_res[NUMBER_OF_VALUE]; //результаты вычисления
    double **graphic; //данные для графика
    int numcolumns; //номер колонки
    size_t lines; //количество строк
    size_t columns; //количество столбцов
    bool is_file_error; //проверка
} FuncReturningValue;

#endif // STRUCT_H
