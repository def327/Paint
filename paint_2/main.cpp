#include "widget.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle("fusion");
    Widget w;
    w.show();

    return a.exec();
}
