#include "tableanalisyswindow.h"
#include "ui_tableanalisyswindow.h"

TableAnalisysWindow::TableAnalisysWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableAnalisysWindow)
{
    ui->setupUi(this);
    frequently_used_functions= new AssistantClasss();
    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(1);

    swinaw = new SortedWidgetInAnalisysWindow();
    swinaw->hide();
    connect(this, &TableAnalisysWindow::show_sorted_widget, swinaw, &SortedWidgetInAnalisysWindow::show_this_widget);
    connect(this->ui->tabWidget, SIGNAL(pressed(const QModelIndex &)), this, SLOT(onItemPressed(const QModelIndex &)));
}

TableAnalisysWindow::~TableAnalisysWindow()
{
    delete ui;
    delete swinaw;
}

void TableAnalisysWindow::resizeEvent(QResizeEvent *event)
{
    this->ui->sorted_widget->move((event->size().width()-150)/2, 200);
    if(event->size().width() < 100)
        this->ui->tabWidget->resize(event->size().width()*0.9375, event->size().height()*0.66);
    else
        this->ui->tabWidget->resize(event->size().width()*0.96, event->size().height()*0.66);
    this->ui->frame->resize(this->ui->tabWidget->size().width(), 75);

    this->ui->tabWidget->move((event->size().width()-this->ui->tabWidget->size().width())/2, 70);
    this->ui->frame->move((event->size().width()-this->ui->frame->size().width())/2, 70 + this->ui->tabWidget->height());
}

void TableAnalisysWindow::set_summary_table(QMap<QString, QStringList> qmap)
{
    //qDebug() << "Сводная таблица получена \n";
    //qDebug() << qmap;
    //qDebug() << "Конец вывода\n";
    this->summary_table = qmap;
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
        QString title = "Вкладка" + frequently_used_functions->name_selection(path);
        //добавление вкладки на виджет
        ui->tabWidget->addTab(tab, title);
    }
}

//формирование сводной таблицы
void TableAnalisysWindow::on_pushButton_8_clicked()
{
    QStandardItemModel *csvModel = new QStandardItemModel;
    QList<QStandardItem *> standardItemsList;
    QTableView *tab = new QTableView;
    QStringList list;
    bool check = false;
    QMap <QString, QStringList> :: iterator summary_iterator = summary_table.begin();

    while(summary_iterator!=summary_table.end()){
        if(summary_iterator.key() == "Шифр"){
            csvModel->setColumnCount(csvModel->columnCount()+summary_table["Шифр"].size()+1);
            if(check == false){
                list.push_front("Шифр");
                check = true;
            }
            list += summary_table["Шифр"];
            csvModel->setHorizontalHeaderLabels(list);

            QMap <QString, QStringList> :: iterator dubl;
            dubl = summary_table.find("Шифр");
            summary_table.erase(dubl);
        }
        if (summary_iterator.key() == "Личный номер"){
            csvModel->setColumnCount(csvModel->columnCount()+summary_table["Личный номер"].size());
            if(check == false){
                list.push_front("Личный номер");
                check = true;
            }
            list += summary_table["Личный номер"];
            csvModel->setHorizontalHeaderLabels(list);

            QMap <QString, QStringList> :: iterator dubl;
            dubl = summary_table.find("Личный номер");
            summary_table.erase(dubl);
        }
        if(summary_iterator.key() == "Зачетная книжка"){
            csvModel->setColumnCount(csvModel->columnCount()+summary_table["Зачетная книжка"].size());
            if(check == false){
                list.push_front("Зачетная книжка");
                check = true;
            }
            list += summary_table["Зачетная книжка"];
            csvModel->setHorizontalHeaderLabels(list);

            QMap <QString, QStringList> :: iterator dubl;
            dubl = summary_table.find("Зачетная книжка");
            summary_table.erase(dubl);
        }
        summary_iterator++;
    }
    summary_iterator = summary_table.begin();

    QStringList count_string;
    int count_row = 0;

    while(summary_iterator!=summary_table.end()){
        //добавление в таблицу
        count_string.append(summary_iterator.key());
        count_string+=summary_table[summary_iterator.key()];

        QList<QStandardItem *> standardItemsList;
        for(int i = 0; i < count_string.size(); i++){
            standardItemsList.append(new QStandardItem(count_string[i]));
        }
        csvModel->insertRow(count_row, standardItemsList);

        //qDebug()<< summary_iterator.key() << " " << summary_table[summary_iterator.key()];
        count_string.clear();
        count_row++;
        summary_iterator++;
    }

    tab->setModel(csvModel);
    ui->tabWidget->addTab(tab, "Сводная таблица по студентам");
}


void TableAnalisysWindow::on_pushButton_2_clicked()
{
    emit send_to_main_window();
}


void TableAnalisysWindow::on_pushButton_9_clicked()
{
    emit show_sorted_widget();
}

void TableAnalisysWindow::onItemPressed(const QModelIndex &index)
{
    qDebug()<< index.row() << " " << index.column();
}

