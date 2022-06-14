#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QtAlgorithms>
#include <QVector>
#include <QDebug>
#include <QString>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QStringList>
#include <QPainter>
#include <QPixmap>
#include <QGraphicsWidget>
#include <QGraphicsView>
#include <QApplication>

#include "logic.h"

char* QStringToCharLine(QString FileName); //функция перевода QString в char
QStringList ConvertRowToQTFormat(char** row, size_t size); //функция перевода массива строк в формат QT

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_namefile_clicked(); //функия при нажатии на открыть файл

    void on_pushButton_loaddata_clicked(); //функция при нажатии загрузить данные

    void on_pushButton_calculations_clicked(); //функция при нажатии вычисления

private:
    Ui::MainWindow *ui;

    void showData(FuncReturningValue* for_output); //функция выведения данных в таблицу

    char*** getDataFromTable(); //функция получения данных из таблицы

    char** getHeaderFromTable(); //функция получения заголовков из таблицы

    void showGraphic(double** dataGraph, char** header, size_t lines, double* metrics, int numcolumn); //функция выведения графика
};
#endif // MAINWINDOW_H
