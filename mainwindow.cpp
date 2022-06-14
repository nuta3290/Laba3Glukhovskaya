#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logic.h"
#include "draw.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setlocale(LC_NUMERIC, "en_US.UTF-8");
}

MainWindow::~MainWindow()
{
    delete ui;
}

//функия при нажатии на открыть файл
void MainWindow::on_pushButton_namefile_clicked() {
    QString FileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/Users/dariav/Desktop", "CSV File (*.csv)"); //открывает каталог файлов
    ui->namefile->setText(FileName);
    if(FileName.isEmpty()) { //isEmpty() проверяет, является ли QString пустым
        ui->error->setText("Файл не выбран!");
        return;
    }
}

//функция при нажатии загрузить данные
void MainWindow::on_pushButton_loaddata_clicked() {
    QString FileName = ui->namefile->text();
    QString RegName = ui->nameregion->text();
    if (FileName.isEmpty()) { //isEmpty() проверяет, является ли QString пустым
        ui->error->setText("Файл не выбран!");
        return;
    } else if (RegName.isEmpty()) { //isEmpty() проверяет, является ли QString пустым
        ui->error->setText("Не введено название региона!");
        return;
    } else {
        ui->error->setText("");
        FunctionArgument struct_for_output = {
            .filename = QStringToCharLine(FileName),
            .regionname = QStringToCharLine(RegName)
        };
        FuncReturningValue* for_output = entryPoint(getDataFromFile, &struct_for_output);
        if(for_output->lines == 0)
            ui->error->setText("Данный регион не найден!");
        showData(for_output);
        entryPoint(cleanData, &struct_for_output);
        free(for_output);
    }
}

//функция при нажатии вычисления
void MainWindow::on_pushButton_calculations_clicked() {
    ui->error->setText("");
    QString FileName = ui->namefile->text();
    QString RegName = ui->nameregion->text();
    if(FileName.isEmpty() || RegName.isEmpty()) { //isEmpty() проверяет, является ли QString пустым
        ui->error->setText("Вычисления недопустимы!");
    } else {
        ui->error->setText("");
        FunctionArgument struct_for_output = {
            .numcolumns = ui->numcolomn->value(),
            .table_headers = getHeaderFromTable(),
            .data = getDataFromTable(),
            .lines = (size_t)ui->tableWidget->rowCount(), //rowCount() - возвращает количество строк.
            .columns = (size_t)ui->tableWidget->columnCount() //columnCount() - возвращает количество столбцов.
        };
        if ((size_t)struct_for_output.numcolumns > struct_for_output.columns)
            ui->error->setText("Вычисления недопустимы!");
        else {
            FuncReturningValue* tmp = entryPoint(calculationData, &struct_for_output);
            if (tmp->lines == 0) {
                ui->error->setText("Вычисления недопустимы!");
            } else {
                tmp->table_headers = struct_for_output.table_headers;
                ui->maximum->setText(QString::number(tmp->calculation_res[NUM_MAX]));
                ui->minimum->setText(QString::number(tmp->calculation_res[NUM_MIN]));
                ui->median->setText(QString::number(tmp->calculation_res[NUM_MED]));
                showGraphic(tmp->graphic, tmp->table_headers, tmp->lines, tmp->calculation_res, tmp->numcolumns);
                entryPoint(cleanData, &struct_for_output);
            }
            free(tmp);
        }
    }
}

//функция выведения данных в таблицу
void MainWindow::showData(FuncReturningValue* for_output) {
    if (for_output->is_file_error) {
        ui->error->setText("Ошибка чтения");
        return;
    }
    ui->tableWidget->setColumnCount(for_output->columns);
    QStringList QColumns = ConvertRowToQTFormat(for_output->table_headers, for_output->columns);
    ui->tableWidget->setHorizontalHeaderLabels(QColumns); //устанавливает горизонтальные метки заголовков с помощью labels.
    if (for_output->data != NULL) {
        ui->tableWidget->setRowCount(for_output->lines);
        for(size_t i = 0; i < for_output->lines; i++) {
            QStringList currentSeries = ConvertRowToQTFormat(*((for_output)->data + i), for_output->columns);
            for(int j = 0; j < currentSeries.count(); j++) {
                QTableWidgetItem *Item = new QTableWidgetItem(); //класс QTableWidgetItem предоставляет элемент для использования с классом QTableWidget                                        
                Item->setData(Qt::EditRole, currentSeries.at(j));
                Item->setText(currentSeries.at(j));
                ui->tableWidget->setItem(i, j, Item); //устанавливает элемент для данной строки и столбца в значение item.
            }
        }
    }
}

//функция получения данных из таблицы
char*** MainWindow::getDataFromTable() {
    char*** data = (char***)malloc(sizeof(char**) * ui->tableWidget->rowCount());
    if (data != NULL) {
    for(size_t i = 0; i < (size_t)ui->tableWidget->rowCount(); i++) {
        *(data + i) = (char**)malloc(sizeof(char*) * ui->tableWidget->columnCount());
        if (*(data+i)!=NULL){
        for(size_t j = 0; j < (size_t)ui->tableWidget->columnCount(); j++) {
            QTableWidgetItem *item = ui->tableWidget->item(i,j); //item() - возвращает элемент для данной строки и столбца
            char *str = QStringToCharLine(item->text());
            data[i][j] = str;
          }
        }
      }
    }
    return data;
}

//функция получения заголовков из таблицы
char** MainWindow::getHeaderFromTable() {
    char** header = (char**)malloc(sizeof(char*) * ui->tableWidget->columnCount());
    if (header != NULL) {
    for(size_t i = 0; i < (size_t)ui->tableWidget->columnCount(); i++) {
        QTableWidgetItem *item = ui->tableWidget->horizontalHeaderItem(i);
        char *str = QStringToCharLine(item->text());
        header[i] = str;
      }
    }
    return header;
}

//функция перевода QString в char
char* QStringToCharLine(QString FileName) {
    char* new_str = (char*)malloc(sizeof(char) * (FileName.size() + 1));
    if(new_str != NULL){
        for(qsizetype i = 0; i < FileName.size(); i++) { //size() количество символов в строке
            *(new_str + i) = FileName.at(i).unicode(); //at() - возвращает символ по указанному индексу position в строке.
        }
        *(new_str + FileName.size()) = 0;
    }
    return new_str;
}

//функция перевода массива строк в формат QT
QStringList ConvertRowToQTFormat(char** row, size_t size) {
    QStringList nstr;
    for(size_t i = 0; i < size; i++) {
        nstr.append(*(row + i)); //append() - добавление к строке справа
    }
    return nstr;
}

//функция выведения графика
void MainWindow::showGraphic(double** Gr, char** header, size_t lines, double* metrics, int numcolumn) {
    QPixmap *pix = new QPixmap(600, 600);
    QPainter paint(pix);
    coordinatePlane(paint);
    drawText(paint, header, numcolumn);
    drawGraphic(paint, Gr, lines, metrics);
    ui->graphic->setPixmap(*pix);
}

