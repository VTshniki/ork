#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QResizeEvent>

namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();


signals:
    void send_to_upload_window();
    void send_to_analisys_window();
private slots:
    void resizeEvent(QResizeEvent *event);
    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Menu *ui;
};

#endif // MENU_H
