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
    this->ui->button_frame->move(event->size().width()/12, event->size().height()/4.3);
    this->ui->pushButton_1->move(0, 0);
    this->ui->pushButton_3->move(0, this->ui->button_frame->size().height()/4);
    this->ui->pushButton_4->move(0, this->ui->button_frame->size().height()/4*2);

    this->ui->panel_frame->move(event->size().width()/2.66, event->size().height()/6.4);

    this->ui->button_frame->resize(event->size().width()*0.25, event->size().height()*0.625);
    this->ui->pushButton_1->resize(this->ui->button_frame->size().width(), this->ui->button_frame->size().height()/3);
    this->ui->pushButton_3->resize(this->ui->button_frame->size().width(), this->ui->button_frame->size().height()/3);
    this->ui->pushButton_4->resize(this->ui->button_frame->size().width(), this->ui->button_frame->size().height()/3);

    this->ui->panel_frame->resize(200, event->size().height()*0.84);
}
