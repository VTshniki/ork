#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    stack_widgets = new QStackedWidget(this);
    authorization = new Authorization(this);
    menu = new Menu(this);

    stack_widgets->addWidget(authorization);
    stack_widgets->addWidget(menu);

    setCentralWidget(stack_widgets);

    connect(authorization, &Authorization::send_to_main_window, this, &MainWindow::get_from_authorization_window);
    stack_widgets->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete authorization;
    delete menu;
    delete stack_widgets;
}

void MainWindow::get_from_authorization_window()
{
    stack_widgets->setCurrentIndex(1);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{

}
