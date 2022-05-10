#include "sortedwidgetinanalisyswindow.h"
#include "ui_sortedwidgetinanalisyswindow.h"

SortedWidgetInAnalisysWindow::SortedWidgetInAnalisysWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SortedWidgetInAnalisysWindow)
{
    ui->setupUi(this);
    this->hide();
}

SortedWidgetInAnalisysWindow::~SortedWidgetInAnalisysWindow()
{
    delete ui;
}

void SortedWidgetInAnalisysWindow::show_this_widget()
{
    this->show();
}

void SortedWidgetInAnalisysWindow::on_pushButton_clicked()
{
    this->hide();
}

