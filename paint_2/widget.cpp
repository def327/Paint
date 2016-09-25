#include "widget.h"

Widget::Widget(QWidget *parent): QWidget(parent)
{
    lbl = new QLabel;

    ///--Slider-----------------------
    slider = new QSlider(Qt::Horizontal);
    slider->setToolTip("Pen width ");
    slider->setMaximumHeight(20);
    slider->setMaximumWidth(800);
    slider->setMinimum(1);
    slider->setMaximum(30);

    ///--Buttons-----------------------
    btn_save = new QPushButton;
    btn_save->setToolTip("Save");
    btn_save->setIcon(QIcon(":/new/for_buttons/resourses/save.png"));
    btn_save->setIconSize(QSize(60,20));

    btn_open = new QPushButton;
    btn_open->setToolTip("Open");
    btn_open->setIcon(QIcon(":/new/for_buttons/resourses/open.png"));
    btn_open->setIconSize(QSize(60,20));

    btn_color = new QPushButton;
    btn_color->setToolTip("Set pen&color");
    btn_color->setIcon(QIcon(":/new/for_buttons/resourses/color.png"));
    btn_color->setIconSize(QSize(60,20));

    btn_rectangle = new QPushButton;
    btn_rectangle->setToolTip("Select Rectangle");
    btn_rectangle->setIcon(QIcon(":/new/for_buttons/resourses/rectangle.png"));
    btn_rectangle->setIconSize(QSize(60,20));

    btn_elipse = new QPushButton;
    btn_elipse->setToolTip("Select Elipse");
    btn_elipse->setIcon(QIcon(":/new/for_buttons/resourses/elipse.png"));
    btn_elipse->setIconSize(QSize(60,20));

    btn_rubber = new QPushButton;
    btn_rubber->setToolTip("Select Rubber");
    btn_rubber->setIcon(QIcon(":/new/for_buttons/resourses/rubber.png"));
    btn_rubber->setIconSize(QSize(60,20));

    ///--Layouts and sizes of widgets------------
    resize(800,400);
    setWindowTitle("Fast Paint v 1.0");

    btn_elipse->setFixedSize(80,30);
    btn_rectangle->setFixedSize(80,30);
    btn_save->setFixedSize(80,30);
    btn_open->setFixedSize(80,30);
    btn_color->setFixedSize(80,30);
    btn_rubber->setFixedSize(80,30);


    lbl->setFrameStyle(QFrame::StyledPanel);
    QVBoxLayout *v_lout = new QVBoxLayout;
    QHBoxLayout *h_lout = new QHBoxLayout;
    QVBoxLayout *v_but_lout = new QVBoxLayout;
    v_but_lout->addWidget(btn_elipse);
    v_but_lout->addWidget(btn_rectangle);    
    v_but_lout->addWidget(btn_color);
    v_but_lout->addWidget(btn_rubber);
    v_but_lout->addWidget(btn_save);
    v_but_lout->addWidget(btn_open);
    h_lout->addWidget(lbl);
    h_lout->addLayout(v_but_lout);
    v_lout->addLayout(h_lout);
    v_lout->addWidget(slider,Qt::AlignBottom);
    v_lout->setAlignment(slider,Qt::AlignBottom);
    setLayout(v_lout);

    ///--Cursors-----------------------------
    cursor_lbl = QCursor(QPixmap(":/new/for_cursor/resourses/cursor_brush.png"));
    lbl->setCursor(cursor_lbl);

    cursor_btn = QCursor(Qt::PointingHandCursor);
    btn_save->setCursor(cursor_btn);
    btn_color->setCursor(cursor_btn);
    btn_rectangle->setCursor(cursor_btn);
    btn_elipse->setCursor(cursor_btn);

    cursor_slider = QCursor(Qt::SizeHorCursor);
    slider->setCursor(cursor_slider);

    ///--Signals & Slots--------------------------------
    connect(btn_save,SIGNAL(clicked(bool)),SLOT(slot_save()));
    connect(btn_open,SIGNAL(clicked(bool)),SLOT(slot_open()));
    connect(btn_color,SIGNAL(clicked(bool)),SLOT(set_color()));
    connect(btn_rubber,SIGNAL(clicked(bool)),SLOT(slot_rubber()));
    connect(slider,SIGNAL(valueChanged(int)),SLOT(set_size(int)));
    connect(btn_rectangle,SIGNAL(clicked(bool)),SLOT(slot_rectangle()));
    connect(btn_elipse,SIGNAL(clicked(bool)),SLOT(slot_elipse()));    

    ///--Tools for paint-------------------------
    QImage image2(800,400,QImage::Format_RGB32);  //to use the copie's size and format
    image = image2;
    image.fill(Qt::white);
    lbl->setPixmap(QPixmap::fromImage(image));
    color = Qt::black;
    brush.setColor(color);
    pen.setColor(color);

    ///--Flags for elipse & rectangle----------------------------
    draw_rectangle = false;
    draw_elipse = false;
    draw_rubber = false;
}

void Widget::slot_save()
{
    str_file_name = QFileDialog::getSaveFileName(this,
                                                 tr("Save Image"),
                                                 "/untitled.png",
                                                 tr("Images (*.png *.xpm *.jpg)")
                                                 );
    if(str_file_name == "")
    {        
        return;
    }
    image.save(str_file_name);
}

void Widget::set_color()
{
    cursor_lbl = QCursor(QPixmap(":/new/for_cursor/resourses/cursor_brush.png"));
    pen.setColor(QColorDialog::getColor());
    brush.setColor(pen.color());
    if( draw_rubber == true)
    {
        draw_rubber = false;
        btn_rectangle->setEnabled(true);
        btn_elipse->setEnabled(true);
        cursor_lbl = QCursor(QPixmap(":/new/for_cursor/resourses/cursor_brush.png"));
        lbl->setCursor(cursor_lbl);
        if(pen.color().isValid() == false)
        {
           pen.setColor(Qt::black);
           brush.setColor(pen.color());
        }
    }
}

void Widget::set_size(int a)
{
    pen.setWidth(a);
}

void Widget::slot_rectangle()
{
    draw_rectangle = true;
}

void Widget::slot_elipse()
{
    draw_elipse = true;
}

void Widget::slot_rubber()
{
    if(draw_elipse == true | draw_rectangle == true)
    {
        draw_elipse = false;
        draw_rectangle = false;
    }
    pen.setColor(QColor(Qt::white));
    brush.setColor(pen.color());
    btn_rectangle->setEnabled(false);
    btn_elipse->setEnabled(false);
    draw_rubber = true;
    cursor_lbl = QCursor(QPixmap(":/new/for_cursor/resourses/cursor_rubber.png"));
    lbl->setCursor(cursor_lbl);
}

void Widget::slot_open()
{
    str_file_name = QFileDialog::getOpenFileName(this,
                                                 "Open Image",
                                                 0,
                                                 " *.png *.xpm *.jpg ;; *.jpg ;; *.png ;; All files (*.*)"
                                                 );
    if(str_file_name == "")
    {
        return;
    }
    QImage image2;
    image2.load(str_file_name);
    image = image2.scaled(800,400);
    lbl->setPixmap(QPixmap::fromImage(image));
}

void Widget::paintEvent(QPaintEvent *)
{
    if(is_pressed == true)
    {
        if( draw_rectangle == true)
        {
            if( one != two )
            {
                QPainter painter;
                painter.begin(&image);
                painter.setPen(pen);
                int w = (two.x() - one.x());
                int h = (two.y() - one.y());
                painter.drawRect(one.x(),one.y(),w,h);
                painter.end();
                is_pressed = false;
                draw_rectangle = false;
                one.setX(0);
                one.setY(0);
                two=one;
                lbl->setPixmap(QPixmap::fromImage(image));
                return;
            }
        }
        if( draw_elipse == true)
        {
            if( one != two )
            {
                QPainter painter;
                painter.begin(&image);
                painter.setPen(pen);
                int w = (two.x() - one.x());
                int h = (two.y() - one.y());
                painter.drawEllipse(one.x(),one.y(),w,h);
                painter.end();
                is_pressed = false;
                draw_elipse = false;
                one.setX(0);
                one.setY(0);
                two=one;
                lbl->setPixmap(QPixmap::fromImage(image));                
                return;
            }
        }
        QPainter painter;
        painter.begin(&image);
        if (list.size() < 2) return;
        painter.setPen(pen);
        QList<QPoint>::const_iterator it = list.begin();
        QPoint start = *it;
        it++;
        while(it != list.end())
        {
            QPoint end = *it;
            painter.drawLine(start,end);
            start = end;
            it++;
        }
        painter.end();
        lbl->setPixmap(QPixmap::fromImage(image));
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if ( !is_pressed )
    {
        return;
    }

    if(draw_rectangle == true)
    {
        this->update();
        return;
    }

    if(draw_elipse == true)
    {
        this->update();
        return;
    }
    QPoint tmp = event->pos();
    QPoint tmp_correct;
    tmp_correct.setX(tmp.x()-10);
    tmp_correct.setY(tmp.y()-10);
    list.push_back(tmp_correct);
    this->update();
    current = tmp_correct;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
 if (event->button() == Qt::LeftButton)
    {
        if(draw_rectangle == true)
        {
            QToolTip::showText(event->globalPos(),"Keep Button pressed and"
                                                  " Move Cursor to"
                                                  " the next position",
                                                  this
                                                  );
            is_pressed = true;
            QPoint tmp = event->pos();
            QPoint tmp_correct;
            tmp_correct.setX(tmp.x()-10);
            tmp_correct.setY(tmp.y()-10);
            one=tmp_correct;
            two=one;
            return;
        }
        if(draw_elipse == true)
        {
            QToolTip::showText(event->globalPos(),"Keep Button pressed and"
                                                  " Move Cursor to"
                                                  " the next position",
                                                  this
                                                  );
            is_pressed = true;
            QPoint tmp = event->pos();
            QPoint tmp_correct;
            tmp_correct.setX(tmp.x()-10);
            tmp_correct.setY(tmp.y()-10);
            one=tmp_correct;
            two=one;
            return;
        }
        is_pressed = true;
        QPoint tmp = event->pos();
        QPoint tmp_correct;
        tmp_correct.setX(tmp.x()-10);
        tmp_correct.setY(tmp.y()-10);
        list.push_back(tmp_correct);
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if(draw_rectangle == true)
        {
            QPoint tmp = event->pos();
            QPoint tmp_correct;
            tmp_correct.setX(tmp.x()-10);
            tmp_correct.setY(tmp.y()-10);
            two = tmp_correct;
            this->update();
            cursor_lbl = QCursor(QPixmap(":/new/for_cursor/resourses/cursor_brush.png"));
            lbl->setCursor(cursor_lbl);
            return;
        }
        if(draw_elipse == true)
        {
            QPoint tmp = event->pos();
            QPoint tmp_correct;
            tmp_correct.setX(tmp.x()-10);
            tmp_correct.setY(tmp.y()-10);
            two = tmp_correct;
            this->update();
            cursor_lbl = QCursor(QPixmap(":/new/for_cursor/resourses/cursor_brush.png"));
            lbl->setCursor(cursor_lbl);
            return;
        }
        is_pressed = false;
        QPoint tmp = event->pos();
        QPoint tmp_correct;
        tmp_correct.setX(tmp.x()-10);
        tmp_correct.setY(tmp.y()-10);
        list.push_back(tmp_correct);
        this->update();
        list.clear();
    }
}
