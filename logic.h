#ifndef LOGIC_H
#define LOGIC_H

#include "operation.h"
#include "memory.h"
#include "struct.h"

enum FunctionType {
    getDataFromFile, //чтение данных из файла csv
    calculationData, //вычисление данных таблицы
    cleanData //очищение данных
};

FuncReturningValue* entryPoint(FunctionType func, FunctionArgument* funcA); //единая точка входа

char** lineProcessing(char*** data, char** crudeData, size_t lines, size_t box, size_t i);

#endif // LOGIC_H
