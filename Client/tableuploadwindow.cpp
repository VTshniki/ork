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
    menuDialog->setDirectory(START_DIR);

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
        //qDebug() << lines; // для проверки пути файла
    }
}

void TableUploadWindow::on_file_delete_button_clicked()
{
    bool isChosen = true;
    int number;

    while(isChosen)
    {
        isChosen = false;
        for(int i = 0; i < ui->file_names_list->count(); i++)
            if(ui->file_names_list->item(i)->isSelected())
            {
                number = i;
                isChosen = true;
                break;
            }

        if(isChosen)
           ui->file_names_list->removeItemWidget(ui->file_names_list->takeItem(number));
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
            path = ui->file_names_list->item(i)->text();
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
        int cur_line = 0;
        int quantity_column = 1;
        QStringList list;
        QString word;

        // Создаём поток для извлечения данных из файла
        QTextStream in(&file);
        // Считываем данные до конца файла
        while (!in.atEnd())
        {
            // ... построчно
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
    for(int i = 0; i < lines.size(); i++)
        {
            isAlreadyExist = true;
            for(int j = 0; j < ui->file_names_list->count(); j++)
            {
                if(ui->file_names_list->item(j)->text() == lines[i])
                {
                    isAlreadyExist = false;
                    break;
                }
            }

            if(isAlreadyExist)
                ui->file_names_list->addItem(lines[i]);
    }
}

