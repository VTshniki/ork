#include "tableanalisyswindow.h"
#include "ui_tableanalisyswindow.h"

TableAnalisysWindow::TableAnalisysWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableAnalisysWindow)
{
    ui->setupUi(this);
}

TableAnalisysWindow::~TableAnalisysWindow()
{
    delete ui;
}

void TableAnalisysWindow::resizeEvent(QResizeEvent *event)
{

}
