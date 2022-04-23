#ifndef TABLEANALISYSWINDOW_H
#define TABLEANALISYSWINDOW_H

#include <QWidget>
#include <QResizeEvent>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QTableView>
#include <QDebug>
#include "AssistantClasss.h"

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
private slots:
    void resizeEvent(QResizeEvent *event);

private:
    Ui::TableAnalisysWindow *ui;
    AssistantClass *frequently_used_functions;
};

#endif // TABLEANALISYSWINDOW_H
