#include "mainwindow.h"
#include "serializationclass.h"
#include <QTextCodec>
#include <QApplication>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8")); //изменения
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
