#include "calculation.h"
#include "memory.h"

double searchMaximum(double* arr, size_t lines) {
    double maximum = arr[0];
    for(size_t i = 1; i < lines; i++) {
        if (arr[i] > maximum) {
            maximum = arr[i];
        }
    }
    return maximum;
}

double searchMinimum(double* arr, size_t lines) {
    double minimum = arr[0];
    for(size_t i = 1; i < lines; i++) {
        if (arr[i] < minimum) {
            minimum = arr[i];
        }
    }
    return minimum;
}

double searchMedian(double* arr, size_t lines) {
    double medium;
    double* array = sortArray(arr,lines);
    if (lines % 2 == 0) {
        medium = (array[lines / 2] + array[lines / 2 - 1]) / 2;
    } else {
        medium = array[lines / 2];
    }
    return medium;
}

double* convertData(char*** data, size_t lines, int numcolumn) {
    double* arr=(double*)malloc(lines*sizeof(double));
    if (arr != NULL) {
    for (size_t i = 0; i < lines; i++) {
        const char *number = data[i][numcolumn - 1];
        if (*number) {
            arr[i]= atof(number);
        }
      }
    }
    return arr;
}

double* sortArray(double* arr, size_t lines) {
    for (size_t i = 0; i < lines - 1; i++){
        for (size_t j = 0; j < lines - 1 - i; j++){
            if (arr[j] > arr[j+1]){
                double t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t;
            }
        }
    }
    return arr;
}

//функция для запоминания значений для графика
double **serchValue(char*** data, size_t lines, int numcolumn) {
    double** tmpgraph = memoryMatrix(lines);
    if (tmpgraph != NULL) {
    for (size_t i = 0; i < lines; i++) {
        tmpgraph[i][0] = atof(data[i][0]);
        tmpgraph[i][1] = atof(data[i][numcolumn - 1]);
       }
    }
   return tmpgraph;
}
