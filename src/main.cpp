#include "autohidewidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AutoHideWidget wgt;
    wgt.show();

    return a.exec();
}
