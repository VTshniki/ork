#ifndef TABLEUPLOADWINDOW_H
#define TABLEUPLOADWINDOW_H

#include <QWidget>
#include <QFileDialog>
#include <QTreeView>
#include <QLibraryInfo>
#include <QTranslator>
#include <QDebug>
#include <QResizeEvent>

//для таблиц
#include <QStandardItemModel>
#include <QListWidgetItem>

#define START_DIR "C:\\"

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

private slots:
    void on_file_delete_button_clicked();
    void on_file_select_button_clicked();
    void on_item_is_clicked(QListWidgetItem* item);
    void resizeEvent(QResizeEvent *event);

private:
    Ui::TableUploadWindow *ui;
    QStandardItemModel *csvModel;  // Указатель на модель данных, которая
                                   // будет содержать данные из CSV файла
    QStringList list_of_upload_file_path; // список с путями к файлам ранее или только что загруженным
};

#endif // TABLEUPLOADWINDOW_H
