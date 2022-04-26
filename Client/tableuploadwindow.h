#ifndef TABLEUPLOADWINDOW_H
#define TABLEUPLOADWINDOW_H

#include <QWidget>
#include <QFileDialog>
#include <QTreeView>
#include <QLibraryInfo>
#include <QTranslator>
#include <QDebug>
#include <QResizeEvent>
#include <QMessageBox>
//для таблиц
#include <QStandardItemModel>
#include <QListWidgetItem>
#include <QFileInfo>
#include <QAxObject>
#include "assistantclasss.h"
#include <QTableWidget>
#include <QCheckBox>

namespace Ui {
class TableUploadWindow;
}

class TableUploadWindow : public QWidget
{
    Q_OBJECT

public:

    explicit TableUploadWindow(QWidget *parent = nullptr);
    ~TableUploadWindow();
    void choose_files();
    void add_lines(QStringList lines);
    void set_list_of_upload_file_path(QStringList list);
    void add_saved_files();
    QStringList get_list_of_upload_file_path();
    bool check_in_list(QString line);
    QString get_last_path();
    void set_last_path(QString path);
    bool check_doc_format(QString path);

    //ЗАп

signals:
    void send_to_main_window();

private slots:
    void on_file_delete_button_clicked();
    void on_file_select_button_clicked();
    void on_item_is_clicked(QListWidgetItem *item);
    void resizeEvent(QResizeEvent *event);

    void on_pushButton_clicked();

private:
    Ui::TableUploadWindow *ui;
    QString last_path = "C:\\";
    QStringList *csvModel;  // Указатель на модель данных, которая
                            // будет содержать данные из CSV файла
    QStringList list_of_upload_file_path; // список с путями к файлам ранее или только что загруженным
    const QStringList patterns_of_file_extention = {".xls", ".xlsx", "xltx", ".ods", "ots", ".csv", ".pdf"};
    AssistantClasss *frequently_used_functions;

    QTableWidget *summary_table;
};

#endif // TABLEUPLOADWINDOW_H
