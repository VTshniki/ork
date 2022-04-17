#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QResizeEvent>



#include <authorization.h>
#include <menu.h>
#include <tableuploadwindow.h>
#include <tableanalisyswindow.h>
#include <serializationclass.h>

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
    void get_from_menu_to_upload_window();
    void get_from_menu_to_analisys_window();

private:
    SerializationClass serialization;

    Ui::MainWindow *ui;
    Authorization *authorization;
    Menu *menu;
    TableUploadWindow *table_upload_window;
    TableAnalisysWindow *table_analisys_window;
    QStackedWidget *stack_widgets;

};
#endif // MAINWINDOW_H
