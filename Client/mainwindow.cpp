#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    stack_widgets = new QStackedWidget(this);
    authorization = new Authorization(this);
    table_upload_window = new TableUploadWindow(this);
    table_analisys_window= new TableAnalisysWindow(this);
    menu = new Menu(this);

    this->serialization.upload_information();
    this->table_upload_window->set_list_of_upload_file_path(this->serialization.get_list_of_upload_file_path());
    this->table_upload_window->add_saved_files();

    stack_widgets->addWidget(authorization);
    stack_widgets->addWidget(menu);
    stack_widgets->addWidget(table_upload_window);
    stack_widgets->addWidget(table_analisys_window);

    setCentralWidget(stack_widgets);

    connect(authorization, &Authorization::send_to_main_window, this, &MainWindow::get_from_authorization_window);
    connect(menu, &Menu::send_to_upload_window, this, &MainWindow::get_from_menu_to_upload_window);
    connect(menu, &Menu::send_to_analisys_window, this, &MainWindow::get_from_menu_to_analisys_window);
    connect(table_upload_window, &TableUploadWindow::send_to_main_window, this, &MainWindow::get_from_upload_window_to_menu);
    connect(this, &MainWindow::get_summary_table, table_upload_window, &TableUploadWindow::get_summary_table);
    connect(table_upload_window, &TableUploadWindow::send_summary_table, table_analisys_window, &TableAnalisysWindow::set_summary_table);
    connect(table_analisys_window, &TableAnalisysWindow::send_to_main_window, this, &MainWindow::get_from_analisys_window_to_menu);
    stack_widgets->setCurrentIndex(0);

}

MainWindow::~MainWindow()
{
    this->serialization.set_list_of_upload_file_path(this->table_upload_window->get_list_of_upload_file_path());
    this->serialization.save_information();
    delete ui;
    delete authorization;
    delete menu;
    delete table_upload_window;
    delete table_analisys_window;
    delete stack_widgets;
}

void MainWindow::get_from_authorization_window()
{
    stack_widgets->setCurrentIndex(1);
}

void MainWindow::get_from_menu_to_upload_window()
{
    stack_widgets->setCurrentIndex(2);
}

void MainWindow::get_from_menu_to_analisys_window()
{
    stack_widgets->setCurrentIndex(3);
    emit get_summary_table();
    table_analisys_window->createTabs(this->table_upload_window->get_list_of_upload_file_path());
}

void MainWindow::get_from_upload_window_to_menu()
{
    stack_widgets->setCurrentIndex(1);
}

void MainWindow::get_from_analisys_window_to_menu()
{
    stack_widgets->setCurrentIndex(1);
}
