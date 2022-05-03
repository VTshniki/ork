#include "tableuploadwindow.h"
#include "ui_tableuploadwindow.h"

TableUploadWindow::TableUploadWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableUploadWindow)
{
    ui->setupUi(this);

    connect(ui->file_names_list, SIGNAL(itemClicked(QListWidgetItem*)),
                this, SLOT(on_item_is_clicked(QListWidgetItem*)));

    ui->file_names_list->setSelectionMode(QAbstractItemView::MultiSelection);

    frequently_used_functions= new AssistantClasss();
    summary_table = new QTableWidget();
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

void TableUploadWindow::on_file_delete_button_clicked()
{
    bool isChosen = true;
    int number = -1;

    while(isChosen)
    {
        isChosen = false;
        for(int i = 0; i < this->list_of_upload_file_path.length(); i++){
            if(ui->file_names_list->item(i)->isSelected())
            {
                number = i;
                isChosen = true;
                //qDebug() << i << "is selected";
                break;
            }
        }
        if(isChosen){
           ui->file_names_list->removeItemWidget(ui->file_names_list->takeItem(number));
           this->list_of_upload_file_path.removeAt(number);
        }
    }
}


void TableUploadWindow::on_file_select_button_clicked()
{
    this->choose_files();
}



void TableUploadWindow::on_item_is_clicked(QListWidgetItem *item)
{
    QString path = "";

    for(int i = 0; i < ui->file_names_list->count(); i++){
        if(ui->file_names_list->item(i) == item){
            path = this->list_of_upload_file_path[i];
            break;
        }
    }
    QFileInfo *file_check_format = new QFileInfo(path);
    QString type = "." + file_check_format->suffix();

    //".xls", ".xlsx", "xltx", ".ods", "ots", ".csv", ".pdf"
    if(type == ".csv"){
        int rowsCount = 0;

        QFile file(path);

        if (file.open(QFile::ReadOnly | QFile::Text)) {
            ui->upload_files_tableView->clearFocus();
            ui->upload_files_tableView->clearSpans();
            ui->upload_files_tableView->clearMask();

            // Создаём поток для извлечения данных из файла
            QTextStream in(&file);
            // Считываем данные до конца файла
            while(!in.atEnd()){
                csvModel = new QStringList(in.readLine().split(";"));
                ui->upload_files_tableView->setRowCount(rowsCount);
                ui->upload_files_tableView->setColumnCount(csvModel->size());

                for(int col = 0; col < csvModel->size(); ++col){
                    QTableWidgetItem *items= new QTableWidgetItem(csvModel->at(col));
                    ui->upload_files_tableView->setItem((rowsCount - 1), col, items);
                }

                rowsCount++;
                delete csvModel;
            }
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
            ui->upload_files_tableView->setItem(0, col, item1);
            qDebug()<< 0 << " ; " << col << " ; " << item << " ; ";
            check_boxes_list.push_back(item1);
        }

        workbook->dynamicCall("Close");
        excel->dynamicCall("Quit()");
    }
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
        this->ui->frame_2->resize(event->size().width()*0.5625, event->size().height()*0.85);
    }
    else{
        this->ui->frame_2->resize(event->size().width()*0.75, event->size().height()*0.8);
    }
    this->ui->upload_files_tableView->resize(this->ui->frame_2->size().width(), this->ui->frame_2->size().height());
    this->ui->pushButton->move(20, 10);
}


void TableUploadWindow::on_pushButton_clicked()
{
    emit send_to_main_window();
}

void TableUploadWindow::on_save_button_clicked()
{
    int count = 0;
    QTableWidgetItem *item1;

    for (int i = 0; i < check_boxes_list.size(); i++) {
        item1 = check_boxes_list[i];
        if(item1->checkState() != 0){
            qDebug() << "#" << i;
            count++;
        }
    }
     qDebug() << "Общее количество выбранных checkBox'ов:" << count;
}
