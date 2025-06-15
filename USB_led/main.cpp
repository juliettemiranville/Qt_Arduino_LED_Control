#include "usbled.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    USBLed w;
    w.show();
    return a.exec();
}
