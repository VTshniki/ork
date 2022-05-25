#include "tableuploadwindow.h"
#include "ui_tableuploadwindow.h"

TableUploadWindow::TableUploadWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableUploadWindow)
{
    ui->setupUi(this);

    connect(ui->file_names_list, SIGNAL(itemClicked(QListWidgetItem*)),
                this, SLOT(on_item_is_clicked(QListWidgetItem*)));

    //ui->file_names_list->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->file_names_list->setSelectionMode(QAbstractItemView::SingleSelection);


    frequently_used_functions= new AssistantClasss();
}

TableUploadWindow::~TableUploadWindow()
{
    delete ui;
}

void TableUploadWindow::choose_files()
{
    QString headName;

    QFileDialog* menuDialog = new QFileDialog(this);
    menuDialog->setFileMode(QFileDialog::ExistingFile);
    headName = QString("Выберите файлы");

    menuDialog->setOption(QFileDialog::DontUseNativeDialog, true);
    menuDialog->setDirectory(last_path);

    QTreeView* munuDialogInTree = menuDialog->findChild<QTreeView*>();
    if (munuDialogInTree)
        munuDialogInTree->setSelectionMode(QAbstractItemView::ExtendedSelection);

    menuDialog->setWindowTitle(headName);

    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    QApplication::installTranslator(&qtTranslator);

    int acceptCode = menuDialog->exec();

    if(acceptCode == QDialog::Accepted) {
        QStringList lines = menuDialog->selectedFiles();
        add_lines(lines);
        set_last_path(lines[lines.length()-1]);
    }
}

//void TableUploadWindow::on_file_delete_button_clicked()
//{
//    bool isChosen = true;
//    int number = -1;

//    while(isChosen)
//    {
//        isChosen = false;
//        for(int i = 0; i < this->list_of_upload_file_path.length(); i++){
//            if(ui->file_names_list->item(i)->isSelected())
//            {
//                number = i;
//                isChosen = true;
//                //qDebug() << i << "is selected";
//                break;
//            }
//        }
//        if(isChosen){
//           ui->file_names_list->removeItemWidget(ui->file_names_list->takeItem(number));
//           this->list_of_upload_file_path.removeAt(number);
//        }
//    }
//}

void TableUploadWindow::on_file_delete_button_clicked()
{

    for(int i = 0; i < this->list_of_upload_file_path.length(); i++){
        if(ui->file_names_list->item(i)->isSelected())
        {
            ui->file_names_list->removeItemWidget(ui->file_names_list->takeItem(i));
            //           this->list_of_upload_file_path.removeAt(number);
            break;
        }
    }
}


void TableUploadWindow::on_file_select_button_clicked()
{
    this->choose_files();
}


void TableUploadWindow::add_lines(QStringList lines)
{
    bool isAlreadyExist = true;
    for(int i = 0; i < lines.size(); i++){
            isAlreadyExist = true;
            for(int j = 0; j < ui->file_names_list->count(); j++)
            {
                if(ui->file_names_list->item(j)->text() == lines[i])
                {
                    isAlreadyExist = false;
                    break;
                }
            }

            if(isAlreadyExist){
                if(this->check_in_list(lines[i])){
                    if(this->check_doc_format(lines[i])){
                        ui->file_names_list->addItem(frequently_used_functions->name_selection(lines[i]));
                        this->list_of_upload_file_path << lines[i];
                        //qDebug() << lines; // для проверки пути файла
                    }
                    else{
                        QMessageBox msg;
                        msg.setText("Файл с таким расширением недопустим");
                        msg.setWindowTitle("Ошибка добавления");
                        msg.setIcon(QMessageBox::Information);
                        msg.setStandardButtons(QMessageBox::Ok);
                        msg.exec();
                    }
                }
                else{
                    QMessageBox msg;
                    msg.setText("Файл с таким именем загружен!\n"+lines[i]);
                    msg.setWindowTitle("Ошибка добавления");
                    msg.setIcon(QMessageBox::Information);
                    msg.setStandardButtons(QMessageBox::Ok);
                    msg.exec();
                }
            }
    }
}

QStringList TableUploadWindow::get_list_of_upload_file_path()
{
    return this->list_of_upload_file_path;
}

bool TableUploadWindow::check_in_list(QString line)
{
    for(int i = 0; i < this->list_of_upload_file_path.length(); i++){
        if(frequently_used_functions->name_selection(line) == frequently_used_functions->name_selection(this->list_of_upload_file_path[i])){
            return false;
        }
    }
    return true;
}

QString TableUploadWindow::get_last_path()
{

    return last_path;
}

void TableUploadWindow::set_last_path(QString path)
{
    bool check_slash = false;
    QString new_path = "";

    for(int i = path.length()-1; i >= 0; i--){
        if( path[i] == 92 || path[i] == 47){
            check_slash = true;
        }
        if (check_slash){
            new_path += path[i];
        }
    }
    std::reverse(new_path.begin(), new_path.end());
    last_path = new_path;
    //qDebug() << last_path;
}

bool TableUploadWindow::check_doc_format(QString path)
{
    QFileInfo *file = new QFileInfo(path);
    for(int i = 0; i < this->patterns_of_file_extention.length(); i++){
        //qDebug() << '.' + file->suffix();
        if(patterns_of_file_extention[i] == '.' + file->suffix()){
            delete file;
            return true;
        }
    }
    delete file;
    return false;
}

QList<QString> TableUploadWindow::compareLists(QList<QString> mainList, QList<QString> helpList)
{
    for(int i = 0; i < helpList.length(); i++){
            bool mainListAlreadyConsistElement = false;

            for(int j = 0; j < mainList.length(); j++){
                if(helpList[i] == mainList[j]){
                    mainListAlreadyConsistElement = true;
                    break;
                }
            }
            if(mainListAlreadyConsistElement == false)
                mainList.push_back(helpList[i]);
        }
    return mainList;
}

void TableUploadWindow::get_summary_table()
{
    emit send_summary_table(this->summary_table);
}

void TableUploadWindow::set_list_of_upload_file_path(QStringList list)
{
    this->list_of_upload_file_path = list;
}

void TableUploadWindow::add_saved_files()
{
    for(int i = 0; i < this->list_of_upload_file_path.length(); i++){
        //qDebug() <<  this->list_of_upload_file_path[i];
        ui->file_names_list->addItem(frequently_used_functions->name_selection(this->list_of_upload_file_path[i]));
    }
}

void TableUploadWindow::resizeEvent(QResizeEvent *event)
{
    if(event->size().width() < 1000){
        this->ui->frame_2->resize(event->size().width()*0.5625, 100);
    }
    else{
        this->ui->frame_2->resize(event->size().width()*0.75, 100);
    }
    this->ui->upload_files_tableView->resize(this->ui->frame_2->size().width(), this->ui->frame_2->size().height());
    this->ui->pushButton->move(270+this->ui->frame_2->size().width(), 10);
    this->ui->progressBar->move(320+(this->ui->frame_2->size().width()-400)/2, 210);
}


void TableUploadWindow::on_pushButton_clicked()
{
    emit send_to_main_window();
}

void TableUploadWindow::on_save_button_clicked()
{
    QTableWidgetItem *item1 = new QTableWidgetItem;

    QFileInfo *file_check_format = new QFileInfo(path_for_upload_data_in_summary_table);
    QString type = "." + file_check_format->suffix();

    if(type == ".csv"){
        QString key = "";

        QFile file(path_for_upload_data_in_summary_table);

        if (file.open(QFile::ReadOnly | QFile::Text)) {
            // Создаём поток для извлечения данных из файла
            QTextStream in(&file);
            // Считываем данные до конца файла
            while(!in.atEnd()){
                csvModel = new QStringList(in.readLine().split(";"));
                QStringList str_insert;

                for (int i = 0; i < check_boxes_list.size(); i++) {
                    item1 = check_boxes_list[i];
                    if(item1->checkState() != 0){
                        if(csvModel->at(i) != "")
                            str_insert.push_back(csvModel->at(i));
                        else
                            str_insert.push_back(" ");
                        //qDebug() << "#" << i << csvModel->at(i);
                    }
                    if(check_boxes_list[i]->text() == "Личный номер" || check_boxes_list[i]->text() == "Шифр" || check_boxes_list[i]->text() == "Зачетная книжка"){
                        str_insert.push_front(csvModel->at(i));
                    }
                }

                key = str_insert[0];
                str_insert.pop_front();
                if(summary_table.count(key) == 0){
                    summary_table.insert(key, str_insert);
                    //qDebug() << key << " " << str_insert;
                }
                else{
                    QStringList main_list = summary_table[key];
                    QMap <QString, QStringList> :: iterator dubl;
                    dubl = summary_table.find(key);
                    summary_table.erase(dubl);
                    //summary_table[key] = compareLists(main_list, str_insert);
                    summary_table.insert(key, compareLists(main_list, str_insert));
                    //qDebug() << key << " " << compareLists(main_list, str_insert);
                }
                //qDebug() << key << " " << str_insert;
                key = "";
                str_insert.clear();
                delete csvModel;
            }
        }
    }

    if(type == ".xls" || type == ".xlsx" || type == ".xltx"){
        QAxObject *excel = new QAxObject("Excel.Application", this);
        QAxObject *workbooks = excel->querySubObject("Workbooks");
        QAxObject *workbook = workbooks->querySubObject("Open(const QString&)", path_for_upload_data_in_summary_table);
        excel->dynamicCall("SetVisible(bool)", false);

        QAxObject *worksheet = workbook->querySubObject("WorkSheets(int)", 1);

        QAxObject *usedrange = worksheet->querySubObject("UsedRange");
        QAxObject *rows =usedrange->querySubObject("Rows");
        QAxObject *columns = usedrange->querySubObject("Columns");

        int intCols = columns->property("Count").toInt();
        int intRows = rows->property("Count").toInt();

        QMap <int, QStringList> qmap;
        int shfr = 0, key_map = 0;

        //Выбор нужных столбцов
        for(int col = 0; col < intCols; col++){
            QStringList str_insert;
            item1 = check_boxes_list[col];
            if(item1->checkState() != 0){
                for(int row = 0; row < intRows; row++){
                    QAxObject *cell = worksheet->querySubObject("Cells(string, string)", row+1, col+1);
                    QVariant value = cell->dynamicCall("Value()");
                    str_insert.push_back(value.toString());
                }
                qmap.insert(key_map, str_insert);
                key_map++;
            }
            if(check_boxes_list[col]->text() == "Личный номер" || check_boxes_list[col]->text() == "Шифр" || check_boxes_list[col]->text() == "Зачетная книжка"){
                for(int row = 0; row < intRows; row++){
                    QAxObject *cell = worksheet->querySubObject("Cells(string, string)", row+1, col+1);
                    QVariant value = cell->dynamicCall("Value()");
                    str_insert.push_back(value.toString());
                    /*if(value.toString( != " ")
                        str_insert.push_back(value.toString());
                    else
                        str_insert.push_back(" ");*/
                }
                qmap.insert(key_map, str_insert);
                shfr = key_map;
                key_map++;
            }
        }
        workbook->dynamicCall("Close");
        excel->dynamicCall("Quit()");

        QStringList str_list;
        for(int i = 0; i < qmap[shfr].size(); i++){
            if(summary_table.count(qmap[shfr][i]) == 0){
                for(int j = 0; j < qmap.size(); j++){
                    if(j != shfr){
                        str_list.append(qmap[j][i]);
                    }
                }
                summary_table.insert(qmap[shfr][i], str_list);
                //qDebug() << qmap[shfr][i] << " " << str_list;
                str_list.clear();
            }
            else{
                QStringList help_list = summary_table[qmap[shfr][i]];
                QMap <QString, QStringList> :: iterator dubl;
                dubl = summary_table.find(qmap[shfr][i]);
                summary_table.erase(dubl);
                for(int j = 0; j < qmap.size(); j++){
                    if(j != shfr){
                        str_list.append(qmap[j][i]);
                    }
                }

                //summary_table[qmap[shfr][i]]= compareLists(help_list, str_list);
                summary_table.insert(qmap[shfr][i], compareLists(help_list, str_list));
                //qDebug() << qmap[shfr][i] << " " << compareLists(help_list, str_list);
                str_list.clear();
            }
        }
    }

     path_for_upload_data_in_summary_table = "";
}

void TableUploadWindow::on_file_names_list_itemDoubleClicked(QListWidgetItem *item)
{
    QString path = "";

    for(int i = 0; i < ui->file_names_list->count(); i++){
        if(ui->file_names_list->item(i) == item){
            path = this->list_of_upload_file_path[i];
            break;
        }
    }

//    for(int i = 0; i < ui->file_names_list->count(); i++){
//        if(ui->file_names_list->item(i)->isSelected()){
//            ui->file_names_list->item(i)->setSelected();
//        }
//    }

    QFileInfo *file_check_format = new QFileInfo(path);
    QString type = "." + file_check_format->suffix();

    path_for_upload_data_in_summary_table = path;

    //".xls", ".xlsx", "xltx", ".ods", "ots", ".csv", ".pdf"
    check_boxes_list.clear();
    if(type == ".csv"){

        QFile file(path);

        if (file.open(QFile::ReadOnly | QFile::Text)) {
            ui->upload_files_tableView->clearFocus();
            ui->upload_files_tableView->clearSpans();
            ui->upload_files_tableView->clearMask();

            // Создаём поток для извлечения данных из файла

            QTextStream in(&file);
            csvModel = new QStringList(in.readLine().split(";"));
            ui->upload_files_tableView->setRowCount(1);
            ui->upload_files_tableView->setColumnCount(csvModel->size());

            for(int col = 0; col < csvModel->size(); ++col){
                QTableWidgetItem *items= new QTableWidgetItem(csvModel->at(col));
                items->setCheckState(Qt::Unchecked);
                if(items->text() == "Шифр" || items->text() == "Личный номер" || items->text() == "Зачетная книжка"){
                    items->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
                }
                ui->upload_files_tableView->setItem(0, col, items);
                //qDebug()<< 0 << " ; " << col << " ; " << items << " ; ";
                check_boxes_list.push_back(items);
            }
            delete csvModel;
        }
    }
    if(type == ".xls" || type == ".xlsx" || type == ".xltx"){

        QAxObject *excel = new QAxObject("Excel.Application", this);
        QAxObject *workbooks = excel->querySubObject("Workbooks");
        QAxObject *workbook = workbooks->querySubObject("Open(const QString&)", path);
        excel->dynamicCall("SetVisible(bool)", false);

        QAxObject *worksheet = workbook->querySubObject("WorkSheets(int)", 1);

        QAxObject *usedrange = worksheet->querySubObject("UsedRange");
        //QAxObject *rows =usedrange->querySubObject("Rows");
        QAxObject *columns = usedrange->querySubObject("Columns");

        int intCols = columns->property("Count").toInt();

        ui->upload_files_tableView->setColumnCount(intCols);
        ui->upload_files_tableView->setRowCount(1);
        //Выбор орком нужных столбцов
        for(int col = 0; col < intCols; col++){
            QAxObject *cell = worksheet->querySubObject("Cells(string, string)", 1, col +1);
            QVariant value = cell->dynamicCall("Value()");

            QTableWidgetItem *item1 = new QTableWidgetItem(value.toString());
            item1->setCheckState(Qt::Unchecked);
            if(item1->text() == "Шифр" || item1->text() == "Личный номер" || item1->text() == "Зачетная книжка"){
                item1->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsSelectable);
            }
            ui->upload_files_tableView->setItem(0, col, item1);
            //qDebug()<< 0 << " ; " << col << " ; " << item << " ; ";
            check_boxes_list.push_back(item1);
        }

        workbook->dynamicCall("Close");
        excel->dynamicCall("Quit()");
    }
}

