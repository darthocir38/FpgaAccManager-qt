#include "fpgaacc.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FPGAAcc w;
    w.show();

    return a.exec();
}
