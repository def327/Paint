#ifndef WIDGET_H
#define WIDGET_H

#include <QTWidgets>
#include <cmath>

class Widget : public QWidget
{
    Q_OBJECT    
private:    
    QCursor cursor_lbl;
    QCursor cursor_btn;
    QCursor cursor_slider;

    QImage image;

    QLabel *lbl;
    QSlider *slider;
    QPushButton *btn_save;
    QPushButton *btn_open;
    QPushButton *btn_color;
    QPushButton *btn_rectangle;
    QPushButton *btn_elipse;
    QPushButton *btn_rubber;

    QColor color;
    QPoint current;
    QBrush brush;
    QPen pen;
    int diametr;
    QList<QPoint> list;

    QString str_file_name;

    ///For rectangle
    QPoint one;
    QPoint two;

    ///Flags-----------
    bool is_pressed;
    bool draw_rectangle;
    bool draw_elipse;
    bool draw_rubber;

public:
    Widget(QWidget *parent = 0);

public slots:
    void slot_save();
    void set_color();
    void set_size(int);
    void slot_rectangle();
    void slot_elipse();
    ///New Features---
    void slot_rubber();
    void slot_open();

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
};

#endif // WIDGET_H
