#include "draw.h"
#include "struct.h"
#include "memory.h"

//функция для создания основания для рисования и осей
void coordinatePlane(QPainter &paint) {
    paint.fillRect(0, 0, 600, 600, QBrush(QColor(Qt::GlobalColor::white)));
    paint.translate(10,300); //translate() - функция для перемещения центра координат
    paint.setPen(*(new QColor(255, 34, 255, 255)));
    paint.drawRect(-10, -300, 600, 600);
    paint.setPen(QColor(Qt::GlobalColor::black));
    paint.drawLine( 10, 290, 10, -290); //оси
    paint.drawLine(-5, 0, 580, 0);
    paint.drawLine(5, -280, 10, -295); //стрелки к осям
    paint.drawLine(10, -295, 15, -280);
    paint.drawLine(570, -5, 585, 0);
    paint.drawLine(585, 0, 570, 5);
    paint.drawText(1, 12, "0"); //начало координат
}

//функция для рисования текста
void drawText(QPainter &paint, char** header, int numcolumn) {
    QString  result1(header[0]);
    paint.drawText(520, 10, result1);
    QString  result2(header[numcolumn - 1]);
    paint.save();
    paint.translate(10,300);
    paint.rotate(-90);
    paint.drawText(470,-17,100,60,Qt::AlignHCenter,result2);
    paint.restore();
}

//функция для рисования графика
void drawGraphic(QPainter &paint, double** dGr, size_t lines, double* metrics) {
    if (abs(dGr[0][1]) < 10) {
        drawLine(paint, dGr, lines, 30, metrics);
    } else if ((abs(dGr[0][1]) >= 10) && (abs(dGr[0][1]) <= 50)) {
        drawLine(paint, dGr, lines, 10, metrics);
    } else if ((abs(dGr[0][1]) > 50) && (abs(dGr[0][1]) <= 80)) {
        drawLine(paint, dGr, lines, 3, metrics);
    } else if (abs(dGr[0][1]) > 80 ) {
        drawLine(paint, dGr, lines, 2, metrics);
    }
}

//функция рисования линий графика
void drawLine(QPainter &paint, double** Gr, size_t lines, int n, double* metrics) {
    int count_max = 0, count_min = 0;
    for (size_t i = 0; i < lines - 1; i++) {
        paint.drawLine((int)((Gr[i][0] - YEARS) * RATIO), (int)((-n)*Gr[i][1]), (int)((Gr[i+1][0] - YEARS) * RATIO), (int)((-n)*Gr[i+1][1]));
        if (Gr[i][1] == metrics[NUM_MIN] && count_min == 0) {
            paint.drawText((int)((Gr[i][0] - YEARS) * RATIO), (int)((-n)*Gr[i][1]), "MIN");
            paint.drawText((int)((Gr[i][0] - YEARS) * RATIO), 0, QString::number(Gr[i][0]));
            paint.drawText(-3, (int)((-n)*Gr[i][1]), QString::number(Gr[i][1]));
            count_min += 1;
        } else if (Gr[i][1] == metrics[NUM_MAX] && count_max == 0) {
            paint.drawText((int)((Gr[i][0] - YEARS) * RATIO), (int)((-n)*Gr[i][1]), "MAX");
            paint.drawText((int)((Gr[i][0] - YEARS) * RATIO), 0, QString::number(Gr[i][0]));
            paint.drawText(-3, (int)((-n)*Gr[i][1]), QString::number(Gr[i][1]));
            count_max += 1;
        }
        paint.drawLine(0, (int)((-n)*metrics[NUM_MED]), 580, (int)((-n)*metrics[NUM_MED]));
        paint.drawText(560, (int)((-n)*metrics[NUM_MED]), "MED");
    }
}


