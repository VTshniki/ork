#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QWidget>
#include <QResizeEvent>

namespace Ui {
class Authorization;
}

class Authorization : public QWidget
{
    Q_OBJECT

public:
    explicit Authorization(QWidget *parent = nullptr);
    ~Authorization();

signals:
    void send_to_main_window();

private slots:
    void on_push_enter_clicked();
    void resizeEvent(QResizeEvent *event);

private:
    Ui::Authorization *ui;
};

#endif // AUTHORIZATION_H
