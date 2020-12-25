#include "breakout.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Breakout w;
    w.resize(300, 400);
    w.setWindowTitle("Breakout!");
    w.show();
    return a.exec();
}
