#include "tableuploadwindow.h"
#include "ui_tableuploadwindow.h"

TableUploadWindow::TableUploadWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableUploadWindow)
{
    ui->setupUi(this);
    // Создаём модель данных для отображения таблицы из CSV файла
    csvModel = new QStandardItemModel(this);

    connect(ui->file_names_list, SIGNAL(itemClicked(QListWidgetItem*)),
                this, SLOT(on_item_is_clicked(QListWidgetItem*)));

    ui->file_names_list->setSelectionMode(QAbstractItemView::MultiSelection);
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
    //qDebug() << "item number " << number << " is selected"; // проверка на получение индекса выбранного файла
    //qDebug() << path << " is selected"; // проверка выбранного файла

    // Открываем файл из ресурсов. Вместо данного файла
    // необходимо указывать путь к вашему требуемому файлу
    QFile file(path);
    if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
        //qDebug() << "File not exists";
    }
    else {
        csvModel->clear();
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
                for (int i = 0; i < line.length(); i++){
                    if(line[i] == ';'){
                        quantity_column++;
                        list << word;
                        word = "";
                    }
                    else{
                        word += line[i];
                    }
                }
                list << word;
                csvModel->setColumnCount(quantity_column);
                csvModel->setHorizontalHeaderLabels(list);
                ui->upload_files_tableView->setModel(csvModel); // Устанавливаем модель в таблицу
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
                        ui->file_names_list->addItem(this->name_selection(lines[i]));
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
                    msg.setText("Файл с таким путем загружен!\n"+lines[i]);
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

QString TableUploadWindow::name_selection(QString name)
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

bool TableUploadWindow::check_in_list(QString line)
{
    for(int i = 0; i < this->list_of_upload_file_path.length(); i++){
        if(line == this->list_of_upload_file_path[i]){
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

    for(int i = path.length(); i >= 0; i--){
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
        qDebug() << '.' + file->suffix();
        if(patterns_of_file_extention[i] == '.' + file->suffix()){
            return true;
        }
    }
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
        ui->file_names_list->addItem(this->name_selection(this->list_of_upload_file_path[i]));
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

