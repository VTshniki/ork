#include "authorization.h"
#include "ui_authorization.h"

Authorization::Authorization(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Authorization)
{
    ui->setupUi(this);
}

Authorization::~Authorization()
{
    delete ui;
}

void Authorization::on_push_enter_clicked()
{
    emit send_to_main_window();
}

void Authorization::resizeEvent(QResizeEvent *event)
{
    this->ui->main_frame->resize(event->size().width(), event->size().height());
    this->ui->greeting->move((this->ui->main_frame->size().width()-this->ui->greeting->size().width())/2, this->ui->main_frame->size().height()/5);
    this->ui->login_label->move((this->ui->main_frame->size().width()-this->ui->login->size().width())/2, this->ui->main_frame->size().height()/5+this->ui->greeting->size().height()+this->ui->main_frame->size().height()/10-15);
    this->ui->login->move((this->ui->main_frame->size().width()-this->ui->login->size().width())/2, this->ui->main_frame->size().height()/5+this->ui->greeting->size().height()+this->ui->main_frame->size().height()/10);
    this->ui->password_label->move((this->ui->main_frame->size().width()-this->ui->password->size().width())/2, this->ui->main_frame->size().height()/5+this->ui->greeting->size().height()+this->ui->login->size().height()+this->ui->main_frame->size().height()/10+15);
    this->ui->password->move((this->ui->main_frame->size().width()-this->ui->password->size().width())/2, this->ui->main_frame->size().height()/5+this->ui->greeting->size().height()+this->ui->login->size().height()+this->ui->main_frame->size().height()/10+30);
    this->ui->push_enter->move((this->ui->main_frame->size().width()-this->ui->push_enter->size().width())/2, this->ui->main_frame->size().height()/5+this->ui->greeting->size().height()+this->ui->login->size().height()+this->ui->password->size().height()+this->ui->main_frame->size().height()/10*2.5);
}
