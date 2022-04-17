#include "serializationclass.h"

SerializationClass::SerializationClass()
{
    QDir serialization_dir;
    if(!serialization_dir.exists("SavedTables")){
        serialization_dir.mkdir("SavedTables");
    }
}

void SerializationClass::save_information()
{
    // сохранение информации
    //cохранение информации о путях загруженных файлов
    QFile file_list_of_upload_files_path("SavedTables\\listUploadedFilePaths.txt");

    if(file_list_of_upload_files_path.open(QFile::WriteOnly)){
        QTextStream writeStream(&file_list_of_upload_files_path);
        for(int i = 0; i < this->list_of_upload_file_path.length(); i++){
            if(i != this->list_of_upload_file_path.length()-1){
                writeStream << this->list_of_upload_file_path[i] + '\n';
            }
            else{
                writeStream << this->list_of_upload_file_path[i];
            }
        }
        file_list_of_upload_files_path.close();
    }
}

void SerializationClass::upload_information()
{
    //загрузка информации

    //загрузка информации об ранее добавленных файлах
    QFile file_list_of_upload_files_path("SavedTables\\listUploadedFilePaths.txt");
    QString line;
    if(file_list_of_upload_files_path.open(QFile::ReadOnly | QFile::Text)){
        while (!file_list_of_upload_files_path.atEnd())
        {
            line = file_list_of_upload_files_path.readLine();
            line.resize(line.length()-1);
            this->list_of_upload_file_path << line;
            //qDebug() << line; //проверка чтения
            line = "";
        }
        file_list_of_upload_files_path.close();
    }
}

void SerializationClass::set_list_of_upload_file_path(QStringList list)
{
    this->list_of_upload_file_path = list;
}

QStringList SerializationClass::get_list_of_upload_file_path()
{
    return this->list_of_upload_file_path;
}
