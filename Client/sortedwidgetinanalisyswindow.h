#ifndef SORTEDWIDGETINANALISYSWINDOW_H
#define SORTEDWIDGETINANALISYSWINDOW_H

#include <QWidget>

namespace Ui {
class SortedWidgetInAnalisysWindow;
}

class SortedWidgetInAnalisysWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SortedWidgetInAnalisysWindow(QWidget *parent = nullptr);
    ~SortedWidgetInAnalisysWindow();

public slots:
    void show_this_widget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SortedWidgetInAnalisysWindow *ui;
};

#endif // SORTEDWIDGETINANALISYSWINDOW_H
