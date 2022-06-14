#ifndef OPERATION_H
#define OPERATION_H

#include "struct.h"
#include "calculation.h"
#include "memory.h"

char** readFromFile(FILE* file, size_t *lines); //чтение строк из файла
char** strSplit(char* crudeData, size_t* box, const char sign); //функция разбития строки на массив слов
FuncReturningValue* sortingByRegion(FuncReturningValue* tmp, const char* regiononenametmp); //сортировка данных (чтобы остался один регион)

#endif // OPERATION_H
