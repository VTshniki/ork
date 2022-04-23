#include "mainwindow.h"
#include "serializationclass.h"
#include "connectiondatabase.h"
#include <QTextCodec>
#include <QApplication>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8")); //изменения
    QApplication a(argc, argv);
    MainWindow w;


    //ConnectionDataBase con_data_base;
     if(!create_connection()){
         //return 1;
     }
     if (!create_table()){
         //return 1;
     }

    w.show();
    return a.exec();
}
