#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::resizeEvent(QResizeEvent *event)
{
    this->ui->main_frame->resize(event->size().width(), event->size().height());
    this->ui->button_frame->resize(this->ui->main_frame->size().width()*0.25, this->ui->main_frame->size().height()*0.25);
    this->ui->pushButton_1->resize(this->ui->button_frame->size().width(), this->ui->button_frame->size().height()/3);
    this->ui->pushButton_3->resize(this->ui->button_frame->size().width(), this->ui->button_frame->size().height()/3);
    this->ui->pushButton_2->resize(this->ui->button_frame->size().width(), this->ui->button_frame->size().height()/3);

    this->ui->button_frame->move((this->ui->main_frame->size().width()-this->ui->button_frame->size().width())/2, this->ui->main_frame->size().height()/3);
    this->ui->pushButton_1->move(0, 0);
    this->ui->pushButton_2->move(0, this->ui->button_frame->size().height()/3);
    this->ui->pushButton_3->move(0, this->ui->button_frame->size().height()/3*2);
}

void Menu::on_pushButton_1_clicked()
{
    emit send_to_upload_window();
}

