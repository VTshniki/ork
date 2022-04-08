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

private slots:
    void resizeEvent(QResizeEvent *event);

private:
    Ui::Menu *ui;
};

#endif // MENU_H
