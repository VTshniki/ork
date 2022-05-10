#ifndef TABLEANALISYSWINDOW_H
#define TABLEANALISYSWINDOW_H

#include <QWidget>
#include <QResizeEvent>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QTableView>
#include <QDebug>
#include "assistantclasss.h"
#include <QMap>

#include <sortedwidgetinanalisyswindow.h>

namespace Ui {
class TableAnalisysWindow;
}

class TableAnalisysWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TableAnalisysWindow(QWidget *parent = nullptr);
    ~TableAnalisysWindow();
    void createTabs(QStringList list_of_upload_file_path);
signals:
    void send_to_main_window();
    void show_sorted_widget();

private slots:
    void resizeEvent(QResizeEvent *event);

    void on_pushButton_8_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_9_clicked();

    void onItemPressed(const QModelIndex &index);

public slots:
    void set_summary_table(QMap <QString, QStringList> qmap);

private:
    int numberOfTabs;
    Ui::TableAnalisysWindow *ui;
    AssistantClasss *frequently_used_functions;

    QMap <QString, QStringList> summary_table;
    SortedWidgetInAnalisysWindow *swinaw;

};

#endif // TABLEANALISYSWINDOW_H
