#include "editregisterwindow.h"
#include "ui_editregisterwindow.h"
#include "mainwindow.h"
#include "booksManagement.h"


editRegisterWindow::editRegisterWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::editRegisterWindow)
{
    ui->setupUi(this);
    toggleElementsVisibility(false);
    ui->bookNotFound->setVisible(false);
}


void editRegisterWindow::toggleElementsVisibility(bool visible) {
    ui->title->setVisible(visible);
    ui->title_line->setVisible(visible);
    ui->author->setVisible(visible);
    ui->author_line->setVisible(visible);
    ui->startYear->setVisible(visible);
    ui->startYear_line->setVisible(visible);
    ui->endYear->setVisible(visible);
    ui->endYear_line->setVisible(visible);
    ui->editionYear->setVisible(visible);
    ui->editionYearLine->setVisible(visible);
    ui->genre->setVisible(visible);
    ui->genre_line->setVisible(visible);
    ui->magazine->setVisible(visible);
    ui->magazine_line->setVisible(visible);
    ui->volumes->setVisible(visible);
    ui->volumes_line->setVisible(visible);
    ui->publisher->setVisible(visible);
    ui->publisher_line->setVisible(visible);
    ui->line->setVisible(visible);
    ui->line_2->setVisible(visible);
    ui->line_3->setVisible(visible);
    ui->line_4->setVisible(visible);
    ui->line_5->setVisible(visible);
    ui->line_6->setVisible(visible);
    ui->line_7->setVisible(visible);
    ui->line_8->setVisible(visible);
    ui->line_9->setVisible(visible);
    ui->line_10->setVisible(visible);
    ui->line_11->setVisible(visible);
    ui->applyChanges->setVisible(visible);

}
editRegisterWindow::~editRegisterWindow()
{
    delete ui;
}

void editRegisterWindow::on_pushButton_2_clicked()
{
    MainWindow* mainWindow;
    if(!mainWindow){
        mainWindow = new MainWindow();
    }

    mainWindow->show();
    this->close();
}


Book bookAux;
void editRegisterWindow::on_searchButton_clicked()
{

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
    ui->title_line->setText(bookAux.title);
    ui->author_line->setText(bookAux.author);
    QDate startYear(bookAux.startYear,1,1);
    ui->startYear_line->setDate(startYear);
    QDate endYear(bookAux.endYear,1,1);
    ui->endYear_line->setDate(endYear);
    QDate editiontYear(bookAux.editionYear,1,1);
    ui->editionYearLine->setDate(editiontYear);
    ui->genre_line->setText(bookAux.genre);
    ui->magazine_line->setText(bookAux.magazine);
    ui->volumes_line->setValue(bookAux.numOfVolumes);
    ui->publisher_line->setText(bookAux.publisher);
    toggleElementsVisibility(true);


}




void editRegisterWindow::on_applyChanges_clicked()
{

    Book oldBook;
    strcpy(oldBook.title,bookAux.title);
    strcpy(oldBook.author,bookAux.author);
    strcpy(oldBook.genre,bookAux.genre);
    strcpy(oldBook.magazine,bookAux.magazine);
    strcpy(oldBook.publisher,bookAux.publisher);
    strcpy(oldBook.isbn,bookAux.isbn);
    oldBook.editionYear = bookAux.startYear;
    oldBook.startYear = bookAux.startYear;
    oldBook.numOfVolumes = bookAux.numOfVolumes;
    oldBook.endYear = bookAux.endYear;



    Book newBook;
    QString titleQStr = ui->title_line->text();
    QByteArray byteArray = titleQStr.toUtf8();
    const char* title = byteArray.constData();

    if(titleQStr.isEmpty()){
        ui->bookNotFound->setText("You need to fill the title section");
        ui->bookNotFound->setVisible(true);
        return;
    }
    ui->bookNotFound->setVisible(false);
    std::strcpy(newBook.title, title);


    if(isInCollection(newBook) && strcmp(newBook.title,bookAux.title)!=0){
        ui->bookNotFound->setText("Book already in collection!");
        ui->bookNotFound->setVisible(true);
        return;
    }
    ui->bookNotFound->setVisible(false);

    QString autorQStr = ui->author_line->text();
    byteArray = autorQStr.toUtf8();
    const char* autor = byteArray.constData();
    std::strcpy(newBook.author, autor);

    QDate date = ui->startYear_line->date();
    int startYearNewBook = date.year();
    newBook.startYear = startYearNewBook;

    date = ui->endYear_line->date();
    int endYearNewBook = date.year();
    newBook.endYear = endYearNewBook;

    date = ui->editionYearLine->date();
    int editionYear = date.year();
    newBook.editionYear = editionYear;

    QString genreQStr = ui->genre_line->text();
    byteArray = genreQStr.toUtf8();
    const char* genre = byteArray.constData();
    std::strcpy(newBook.genre, genre);

    QString magazineQStr = ui->magazine_line->text();
    byteArray = magazineQStr.toUtf8();
    const char* magazine = byteArray.constData();
    std::strcpy(newBook.magazine, magazine);

    int volumes = ui->volumes_line->value();
    newBook.numOfVolumes = volumes;

    QString publisherQstr = ui->publisher_line->text();
    byteArray = publisherQstr.toUtf8();
    const char* publisher = byteArray.constData();
    std::strcpy(newBook.publisher, publisher);


    ui->bookNotFound->setVisible(false);
    ui->bookNotFound->setText("Book Edited Successfully!");

    ui->bookNotFound->setVisible(true);


    updateRegister(oldBook,newBook);
    testeReadData();
    toggleElementsVisibility(false);
}

