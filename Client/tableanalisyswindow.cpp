#include "tableanalisyswindow.h"
#include "ui_tableanalisyswindow.h"

TableAnalisysWindow::TableAnalisysWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableAnalisysWindow)
{
    ui->setupUi(this);
}

TableAnalisysWindow::~TableAnalisysWindow()
{
    delete ui;
}

void TableAnalisysWindow::resizeEvent(QResizeEvent *event)
{

}

//Метод по созданию дополнительных вкладок
void TableAnalisysWindow::createTabs(QStringList list_of_upload_file_path){

    for (int i = 0; i < list_of_upload_file_path.length(); i++) {

        QStandardItemModel *csvModel = new QStandardItemModel;

        //создание вкладки - таблицы
        QTableView *tab = new QTableView;

        QString path = list_of_upload_file_path[i];

        QFile file(path);
        if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
            //qDebug() << "File not exists";
        }
        else {
            int cur_line = 0;
            int quantity_column = 1;
            QStringList list;
            QString word;

            // Создаём поток для извлечения данных из файла
            QTextStream in(&file);
            // Считываем данные до конца файла
            while (!in.atEnd())
            {
                QString line = in.readLine();
                if(cur_line == 0){
                    for (int j = 0; j < line.length(); j++){
                        if(line[j] == ';'){
                            quantity_column++;
                            list << word;
                            word = "";
                        }
                        else{
                            word += line[j];
                        }
                    }

                    list << word;
                    csvModel->setColumnCount(quantity_column);
                    csvModel->setHorizontalHeaderLabels(list);
                    tab->setModel(csvModel); // Устанавливаем модель в таблицу
                }
                else{
                    // Добавляем в модель по строке с элементами
                    QList<QStandardItem *> standardItemsList;
                    // учитываем, что строка разделяется точкой с запятой на колонки
                    for (const QString &item : line.split(";")) {
                        standardItemsList.append(new QStandardItem(item));
                    }
                    csvModel->insertRow(csvModel->rowCount(), standardItemsList);
                }
                cur_line ++;
            }
            file.close();
        }

        //создание заголовка для вкладки
        QString title = "Вкладка #***";
        //добавление вкладки на виджет
        ui->tabWidget->addTab(tab, title);
    }
}
