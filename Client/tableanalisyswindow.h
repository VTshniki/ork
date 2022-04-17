#ifndef TABLEANALISYSWINDOW_H
#define TABLEANALISYSWINDOW_H

#include <QWidget>
#include <QResizeEvent>

namespace Ui {
class TableAnalisysWindow;
}

class TableAnalisysWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TableAnalisysWindow(QWidget *parent = nullptr);
    ~TableAnalisysWindow();
private slots:
    void resizeEvent(QResizeEvent *event);

private:
    Ui::TableAnalisysWindow *ui;
};

#endif // TABLEANALISYSWINDOW_H
