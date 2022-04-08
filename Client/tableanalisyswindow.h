#ifndef TABLEANALISYSWINDOW_H
#define TABLEANALISYSWINDOW_H

#include <QWidget>

namespace Ui {
class TableAnalisysWindow;
}

class TableAnalisysWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TableAnalisysWindow(QWidget *parent = nullptr);
    ~TableAnalisysWindow();

private:
    Ui::TableAnalisysWindow *ui;
};

#endif // TABLEANALISYSWINDOW_H
