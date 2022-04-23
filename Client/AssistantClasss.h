#ifndef ASSISTANTCLASSS_H
#define ASSISTANTCLASSS_H

#include <QString>

class AssistantClass
{
public:
    AssistantClass();
    QString name_selection(QString name);
    //Запись в БД
    void write_in_database();
    //Чтение из БД
    void read_from_datebase();
};

#endif // ASSISTANTCLASSS_H
