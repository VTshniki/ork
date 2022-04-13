#include "tableuploadwindow.h"
#include "ui_tableuploadwindow.h"

TableUploadWindow::TableUploadWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableUploadWindow)
{
    ui->setupUi(this);
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

