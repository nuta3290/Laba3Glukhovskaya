#include "operation.h"

//чтение строк из файла
char** readFromFile(FILE* file, size_t *lines) {
    char line[BUFFER_SIZE]; //строка, в которую записывается строка из файла
    size_t count = NUM_OF_LINES, max_size = MAX_SIZE;
    char** data = (char**)malloc(sizeof(char*) * max_size); //массив строк
    if(data != NULL){
        while(fgets(line, BUFFER_SIZE, file)) {
            if(count >= max_size - 1){
                max_size *= 2;
                data = (char**)realloc(data, sizeof(char*) * max_size);
                if (data == NULL){
                    clean2DArray(data, max_size);
                    return data;
                }
            }
            size_t lineLen = strlen(line);
            *(data + count) = (char*)calloc(sizeof(char), lineLen);
            if(*(data + count) != NULL) {
                strncpy(*(data + count), line, lineLen - 1);
                count++;
            }
        }
        *lines = count;
    }
    return data;
}

//функция разбития строки на массив слов
char** strSplit(char* crudeData, size_t* box, const char sign) {
    size_t count = 0; //счётчик столбцов
    char* tmp = crudeData; //временная строка
    char* last = 0;
    char** result = 0; //массив слов
    while(*tmp) {
        if(sign == *tmp){
            count++;
            last = tmp;
        }
        tmp++;
    }
    count++;
    *box = count;
    result = (char**)malloc(sizeof(char*) * count);
    if(result != NULL) {
        size_t indx = 0;
        char *token = crudeData;
        for (char *ending = (char *) strchr(token, sign); //функция strchr выполняет поиск первого вхождения символа symbol в строку string
             ending;
             token = ending + 1, ending = (char *) strchr(token, sign), indx++)
        {
            *(result + indx) = (char *) calloc(sizeof(char), ending - token + 1);
            if (*(result + indx) != NULL)
                strncpy(*(result + indx), token, ending - token);
        }
        *(result + indx++) = strdup(token); //strdup() – дублирование строк с выделением памяти под новую строку.
    }
    return result;
}

//функция сортировки (чтобы убрались лишние регионы)
FuncReturningValue* sortingByRegion(FuncReturningValue* tmp, const char* regiononenametmp) {
    size_t cursor = 0;
    for (size_t i = 0; i < tmp->lines - 1; i++) {
        if (!strcmp(tmp->data[i][REG_COLUMN_NUM], regiononenametmp)) {
            tmp->data[cursor++] = tmp->data[i];
        } else
            clean2DArray(tmp->data[i], tmp->columns);
    }
    tmp->lines = cursor;
    return tmp;
}
