#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow window;

    window.setFixedSize(500,450);
    window.setWindowTitle("Розумний таймер");
    window.show();

    return a.exec();
}
