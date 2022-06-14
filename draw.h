#ifndef DRAW_H
#define DRAW_H

#include <QPainter>
#include <QPixmap>
#include <QGraphicsWidget>
#include <QGraphicsView>
#include <QApplication>

void drawLine(QPainter &paint, double** dGr, size_t lines, int n, double* metrics);
void drawGraphic(QPainter &paint, double** dGr, size_t lines, double* metrics);
void drawText(QPainter &paint, char** header, int numcolumn);
void coordinatePlane(QPainter &paint);


#endif // DRAW_H
