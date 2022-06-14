#include "logic.h"
#include "calculation.h"


FuncReturningValue* getDataFromFileDo(const char* filename, const char* regiononename); //чтение данных из файла
FuncReturningValue* calculationDataDo(char*** data, size_t lines, int numcolumn); //функция вычисления макс, мин, мед
void cleanAll(FunctionArgument *arg); //функция очищения данных
FuncReturningValue* fillingStruct(FuncReturningValue* result, size_t lines, size_t box, char** table_headers, char*** data);
char*** createAndFillData(char** crudeData, size_t lines, size_t* box);

//единая точка входа
FuncReturningValue* entryPoint(FunctionType func, FunctionArgument* funcA) {
    FuncReturningValue *result = NULL;
    switch(func)
    {
        case getDataFromFile:
            result = getDataFromFileDo(funcA->filename, funcA->regionname);
            break;
        case calculationData:
            result = calculationDataDo(funcA->data, funcA->lines, funcA->numcolumns);
            break;
        case cleanData:
            cleanAll(funcA);
            break;
        default:
            break;
    }

    return result;
}

//чтение данных из файла
FuncReturningValue* getDataFromFileDo(const char* filename, const char* regiononename) {
    FuncReturningValue* result = (FuncReturningValue*)calloc(1, sizeof(FuncReturningValue)); //структура, куда считываются данные
    if (result == NULL)
        return result;
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        result->is_file_error = true;
        return result;
    }
    size_t lines, box; //количество строк и колонок
    char **crudeData = readFromFile(file, &lines); //массив строк
    if (crudeData == NULL)
            result->is_file_error = true;
    else {
        char **table_headers = strSplit(*(crudeData + HEADER), &box, ',');
        char ***data = createAndFillData(crudeData, lines, &box);
        if ((table_headers == NULL) || (data == NULL))
        {
            result->is_file_error = true;
            clean3DArray(data, box, lines);
            clean2DArray(table_headers, box);
        } else {
                result = fillingStruct(result, lines, box, table_headers, data);
                result = sortingByRegion(result, regiononename);
        }
        clean2DArray(crudeData, lines);
    }
    fclose(file);
    return result;
}

char*** createAndFillData(char** crudeData, size_t lines, size_t* box)
{
    char ***data = (char***)malloc(sizeof(char**) * (lines - 1)); //массив строк, поделённых на слова
    if (data == NULL)
        return NULL;
    for(size_t i = 0; i < lines - 1; i++) {
        data[i] = strSplit(crudeData[(i + 1)], box, ',');
        if (data[i] == NULL) {
            for (size_t j = i; j >= 0; j--) {
                clean2DArray(data[i], lines-1);
            }
            free(data);
            data = NULL;
            break;
        }
    }
    return data;
}

//функция вычисления
FuncReturningValue* calculationDataDo(char*** data, size_t lines, int numcolumn) {
    FuncReturningValue* smt = (FuncReturningValue*)malloc(sizeof(FuncReturningValue)); //структура, куда считываются данные
    if (smt == NULL)
        return smt;

    if (lines == 0) {
        smt->calculation_res[NUM_MAX] = 0.0 / 0.0;
        smt->calculation_res[NUM_MIN] = 0.0 / 0.0;
        smt->calculation_res[NUM_MED] = 0.0 / 0.0;
        smt->graphic = NULL;
        smt->lines = 0;
        smt->numcolumns = 0;
    } else {
        double** tmp = serchValue(data, lines, numcolumn);
        double* arr = convertData(data, lines, numcolumn);
        if ((tmp != NULL) && (arr != NULL)) {
            smt->calculation_res[NUM_MAX] = searchMaximum(arr, lines);
            smt->calculation_res[NUM_MIN] = searchMinimum(arr, lines);
            smt->calculation_res[NUM_MED] = searchMedian(arr, lines);
            smt->graphic = tmp;
            smt->lines = lines;
            smt->numcolumns = numcolumn;
        } else {
            for (size_t i = 0; i < lines; i++)
                free(*(tmp+i));
            free(tmp);
            free(arr);
            smt = NULL;
        }
    }
    return smt;
}

//функция очищения всей структуры
void cleanAll(FunctionArgument *arg) {
    if(arg->filename != NULL)
        free(arg->filename);
    if(arg->regionname != NULL)
        free(arg->regionname);
    if(arg->data != NULL)
        clean3DArray(arg->data, arg->lines, arg->columns);
    if(arg->table_headers != NULL)
        clean2DArray(arg->table_headers, arg->columns);
}

FuncReturningValue* fillingStruct(FuncReturningValue* result, size_t lines, size_t box, char** table_headers, char*** data) {
    if (result != NULL) {
        result->lines = lines;
        result->columns = box;
        result->table_headers = table_headers;
        result->data = data;
    }
    return result;
}
