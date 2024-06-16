#include "readregisterwindow.h"
#include "booksManagement.h"
#include "ui_readregisterwindow.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"

readRegisterWindow::readRegisterWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::readRegisterWindow)
{
    ui->setupUi(this);
    toggleElementsVisibility(false);
    ui->bookNotFound->setVisible(false);


}

readRegisterWindow::~readRegisterWindow()
{
    delete ui;
}

void readRegisterWindow::toggleElementsVisibility(bool visible) {
    ui->title->setVisible(visible);
    ui->titlePlaceHolder->setVisible(visible);
    ui->author->setVisible(visible);
    ui->authorPlaceHolder->setVisible(visible);
    ui->startYear->setVisible(visible);
    ui->startYearPlaceHolder->setVisible(visible);
    ui->endYear->setVisible(visible);
    ui->endYearPlaceHolder->setVisible(visible);
    ui->editionYear->setVisible(visible);
    ui->editionYearPlaceHolder->setVisible(visible);
    ui->genre->setVisible(visible);
    ui->genrePlaceHolder->setVisible(visible);
    ui->magazine->setVisible(visible);
    ui->magazinePlaceHolder->setVisible(visible);
    ui->volumes->setVisible(visible);
    ui->volumesPlaceHolder->setVisible(visible);
    ui->publisher->setVisible(visible);
    ui->publisherPlaceHolder->setVisible(visible);
    ui->isbn->setVisible(visible);
    ui->isbnPlaceHolder->setVisible(visible);
    ui->line->setVisible(visible);
    ui->line_2->setVisible(visible);
    ui->line_3->setVisible(visible);
    ui->line_4->setVisible(visible);
    ui->line_5->setVisible(visible);
    ui->line_6->setVisible(visible);
    ui->line_7->setVisible(visible);
    ui->line_8->setVisible(visible);
    ui->line_9->setVisible(visible);
    ui->editButton->setVisible(visible);
    ui->deleteButton->setVisible(visible);
}





void readRegisterWindow::on_pushButton_2_clicked()
{
    Book bookAux;
    QString titleQStr = ui->lineEdit->text();
    QByteArray byteArray = titleQStr.toUtf8();
    const char* title = byteArray.constData();
    std::strcpy(bookAux.title, title);
    if(!isInCollection(bookAux)){
        toggleElementsVisibility(false);
        ui->bookNotFound->setVisible(true);
        return;
    }
    ui->bookNotFound->setVisible(false);
    bookAux = readRegister(bookAux.title);
    ui->titlePlaceHolder->setText(bookAux.title);
    ui->authorPlaceHolder->setText(bookAux.author);
    QString startYearStr = QString::number(bookAux.startYear);
    ui->startYearPlaceHolder->setText(startYearStr);
    QString endYearStr = QString::number(bookAux.endYear);
    ui->endYearPlaceHolder->setText(endYearStr);
    QString editionYearStr = QString::number(bookAux.editionYear);
    ui->editionYearPlaceHolder->setText(editionYearStr);
    ui->genrePlaceHolder->setText(bookAux.genre);
    ui->magazinePlaceHolder->setText(bookAux.magazine);
    QString volumesStr = QString::number(bookAux.numOfVolumes);
    ui->volumesPlaceHolder->setText(volumesStr);
    ui->publisherPlaceHolder->setText(bookAux.publisher);
    ui->isbnPlaceHolder->setText(bookAux.isbn);
    toggleElementsVisibility(true);
}


void readRegisterWindow::on_returnButton_clicked()
{
    MainWindow* mainWindow;
    if(!mainWindow){
        mainWindow = new MainWindow();
    }
    mainWindow->show();
    this->close();
}

