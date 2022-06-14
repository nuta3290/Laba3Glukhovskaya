#include "memory.h"

//функция очищения char**
void clean2DArray(char **arr, size_t size) {
    if (arr == NULL)
        return;
    for (size_t i = 0; i < size; i++)
    {
        free(*(arr + i));
    }
    free(arr);
}

//функция очищения char***
void clean3DArray(char ***arr, size_t sizeX, size_t sizeY) {
    if (arr == NULL)
        return;
    for (size_t i = 0; i < sizeX; i++)
    {
        clean2DArray(*(arr + i), sizeY);
    }
    free(arr);
}

//функция выделения памяти под матрицу
double** memoryMatrix(size_t lines) {
    double** tmp = (double**)malloc(sizeof(double*) * lines);
    if (tmp == NULL) {
        free(tmp);
    } else {
        for (size_t i = 0; i < lines; i++) {
            *(tmp + i) = (double*)malloc(sizeof(double) * GRAPH_VALUE);
            if (*(tmp + i) == NULL) {
                for (size_t t = i; t >= 0; t--) {
                    free(*(tmp + t));
                }
                free(tmp);
            }
        }
    }
    return tmp;
}

