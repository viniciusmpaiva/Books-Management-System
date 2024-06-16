#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include "addbookwindow.h"
#include"./ui_addbookwindow.h"
#include "readregisterwindow.h"
#include "./ui_readregisterwindow.h"
#include "editregisterwindow.h"
#include "./ui_editregisterwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_pushButton_clicked()
{
    addBookWindow* addBook;
    if(!addBook){
        addBook = new addBookWindow();
    }
    addBook->show();
    this->close();
}


void MainWindow::on_pushButton_2_clicked()
{
    readRegisterWindow* readRegister;
    if(!readRegister){
        readRegister = new readRegisterWindow();
    }
    readRegister->show();
    this->close();
}




void MainWindow::on_pushButton_3_clicked()
{
    editRegisterWindow* editRegister;
    if(!editRegister){
        editRegister = new editRegisterWindow();
    }
    editRegister->show();
    this->close();
}

