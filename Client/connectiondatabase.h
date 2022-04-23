#ifndef CONNECTIONDATABASE_H
#define CONNECTIONDATABASE_H

#include <QMessageBox>
#include <QSql>
#include <QSqlDatabase>
#include <QString>
#include <QSqlError>
#include <QSqlQuery>

inline bool create_connection(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL7");
    db.setDatabaseName("");
    db.setUserName("postgres");
    db.setPassword("PasswOrd3");
    if (!db.open()){

        QMessageBox::warning(0, "Ошибка подключение к БД ", db.lastError().text());
        return false;
    }
    else{

        QMessageBox::information(0, "Успешно", " Соединение с БД установлено!");
        return true;
    }
}
inline bool create_table(QString par_table = "CREATE TABLE passwords("
                                             "id INTEGER PRIMARY KEY, "
                                             "login VARCHAR(10) NOT NULL, "
                                             "passwd VARCHAR(10) NOT NULL, "
                                             "datepass DATE NOT NULL)"){
    QSqlQuery query;
    query.exec(par_table);
    return 1;
}
#endif // CONNECTIONDATABASE_H
