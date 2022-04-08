#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QResizeEvent>



#include <authorization.h>
#include <menu.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void get_from_authorization_window();
    void resizeEvent(QResizeEvent *event);

private:
    Ui::MainWindow *ui;
    Authorization *authorization;
    Menu *menu;

    QStackedWidget *stack_widgets;
};
#endif // MAINWINDOW_H
