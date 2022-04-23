#ifndef SERIALIZATIONCLASS_H
#define SERIALIZATIONCLASS_H

#include <QDebug>
#include <QDir>
#include <QTextCodec>
#include <QString>

class SerializationClass
{
public:
    SerializationClass();
    void save_information();
    void upload_information();
    void set_list_of_upload_file_path(QStringList list);
    QStringList get_list_of_upload_file_path();

private:
    QStringList list_of_upload_file_path;
};

#endif // SERIALIZATIONCLASS_H
