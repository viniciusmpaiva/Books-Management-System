#include "addbookwindow.h"
#include "ui_addbookwindow.h"
#include "booksManagement.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "string.h"
addBookWindow::addBookWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::addBookWindow)
{
    ui->setupUi(this);
    ui->label_12->setVisible(false);
}

addBookWindow::~addBookWindow()
{

    delete ui;
}

void addBookWindow::on_pushButton_clicked()
{
    Book book;
    const char* emptyStr ="";
    book.startYear=0;
    book.editionYear=0;
    book.endYear=0;
    book.numOfVolumes=0;
    strcpy(book.title,emptyStr);
    strcpy(book.author,emptyStr);
    strcpy(book.genre,emptyStr);
    strcpy(book.publisher,emptyStr);
    strcpy(book.magazine,emptyStr);
    strcpy(book.isbn,emptyStr);


    QString titleQStr = ui->lineEdit->text();
    QByteArray byteArray = titleQStr.toUtf8();
    const char* title = byteArray.constData();

    if(titleQStr.isEmpty()){
        ui->label_12->setText("You need to fill the title section");
        ui->label_12->setVisible(true);
        return;
    }
    ui->label_12->setVisible(false);
    ui->label_12->setText("Book Added Successfully!");
    std::strcpy(book.title, title);


    if(isInCollection(book)){
        ui->label_12->setText("Book Already in collection");
        ui->label_12->setVisible(true);
        return;
    }
    ui->label_12->setVisible(false);
    ui->label_12->setText("Book Added Successfully!");


    QString authorQStr = ui->lineEdit_2->text();
    byteArray = authorQStr.toUtf8();
    const char* author = byteArray.constData();
    std::strcpy(book.author, author);


    QDate date = ui->dateEdit->date();
    int startYear = date.year();
    book.startYear = startYear;

    date = ui->dateEdit_2->date();
    int endYear = date.year();
    book.endYear = endYear;

    date = ui->dateEdit_3->date();
    int editionYear = date.year();
    book.editionYear = editionYear;

    QString genreQStr = ui->lineEdit_3->text();
    byteArray = genreQStr.toUtf8();
    const char* genre = byteArray.constData();
    std::strcpy(book.genre, genre);

    QString magazineQStr = ui->lineEdit_4->text();
    byteArray = magazineQStr.toUtf8();
    const char* magazine = byteArray.constData();
    std::strcpy(book.magazine, magazine);

    int volumes = ui->spinBox_4->value();
    book.numOfVolumes = volumes;

    QString publisherQstr = ui->lineEdit_5->text();
    byteArray = publisherQstr.toUtf8();
    const char* publisher = byteArray.constData();
    std::strcpy(book.publisher, publisher);

    QString isbnQStr = ui->lineEdit_6->text();
    if(isbnQStr.isEmpty()){
        ui->label_12->setText("You need to fill the ISBN section");
        ui->label_12->setVisible(true);
        return;
    }
    //procurar isbn repetido
    ui->label_12->setVisible(false);
    ui->label_12->setText("Book Added Successfully!");
    byteArray = isbnQStr.toUtf8();
    const char* isbn = byteArray.constData();


    // bool allDigits = true;
    // for (const QChar &ch : isbnQStr) {
    //     if (!ch.isDigit()) {
    //         allDigits = false;
    //         break;
    //     }
    // }

    // if (allDigits) {
    //     // Converta a string para char* e copie para book.isbn
    //     QByteArray byteArray = isbnQStr.toUtf8();
    //     const char* isbn = byteArray.constData();
    //     std::strcpy(book.isbn, isbn);
    // } else {
    //     ui->label_12->setText("ISBN must be numbers only!");
    //     ui->label_12->setVisible(true);
    //     return;
    // }

    // if(isbnInCollection(book)){
    //     ui->label_12->setText("ISBN already registered in the system!");
    //     ui->label_12->setVisible(true);
    // }
    std::strcpy(book.isbn, isbn);
    addBook(book);
    ui->label_12->setText("Book Added Successfully!");
    ui->label_12->setVisible(true);
}


void addBookWindow::on_pushButton_2_clicked()
{
    MainWindow* mainWindow;
    if(!mainWindow){
        mainWindow = new MainWindow();
    }
    mainWindow->show();
    this->close();
}

