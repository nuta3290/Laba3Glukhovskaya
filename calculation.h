#ifndef CALCULATION_H
#define CALCULATION_H

#include "struct.h"
#include "memory.h"

double searchMaximum(double* arr, size_t lines);
double searchMinimum(double* arr, size_t lines);
double searchMedian(double* arr, size_t lines);

double* convertData(char*** data, size_t lines, int numcolumn);
double* sortArray(double* arr, size_t lines);
double **serchValue(char*** data, size_t lines, int numcolumn);

#endif // CALCULATION_H
