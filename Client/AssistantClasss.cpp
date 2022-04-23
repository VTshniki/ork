#include "AssistantClasss.h"

AssistantClass::AssistantClass()
{

}

QString AssistantClass::name_selection(QString name)
{
    QString file_name = "", name2 = "";
    for(int i = name.length()-1; i >= 0; i--){
        if( name[i] == 92 || name[i] == 47){
            break;
        }
        file_name += name[i];
    }
    /*for(int i = name2.length()-1; i >= 0; i--){
        file_name += name2[i];
    }*/
    std::reverse(file_name.begin(), file_name.end());
    return file_name;
}

void AssistantClass::write_in_database()
{

}

void AssistantClass::read_from_datebase()
{

}
