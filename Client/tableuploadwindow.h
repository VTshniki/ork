#ifndef TABLEUPLOADWINDOW_H
#define TABLEUPLOADWINDOW_H

#include <QWidget>
#include <QFileDialog>
#include <QTreeView>
#include <QLibraryInfo>
#include <QTranslator>
#include <QDebug>

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

private slots:
    void on_file_delete_button_clicked();
    void on_file_select_button_clicked();
    void on_item_is_clicked(QListWidgetItem* item);

private:
    Ui::TableUploadWindow *ui;
    QStandardItemModel *csvModel;  // Указатель на модель данных, которая
                                   // будет содержать данные из CSV файла
};

#endif // TABLEUPLOADWINDOW_H
