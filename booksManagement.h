#ifndef BOOKSMANAGEMENT_H
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define BOOKSMANAGEMENT_H
#define MANAGEMENT_H
#define ISBNSTRMAXLEN 15
#define INDEXSTRMAXLEN 5
#define MAXBOOKS 200
#define SECONDARYINDEXFILENAME "booksSecondaryIndex.txt"
#define PRIMARYINDEXFILENAME "booksPrimaryIndex.txt"
#define DATAFILENAME "booksData.txt"

//A chave do indice primário será o isbn
//A chave do indice secundário será o nome do livro

typedef struct Book{
    char isbn[50];
    char title[100];
    char author[100];
    int startYear;
    int endYear;
    char genre[50];
    char magazine[50];
    char publisher[50];
    int editionYear;
    int numOfVolumes;
} Book;

void addBook(Book book);
Book readRegister(char* title);
void updateRegister(Book book, Book newBook);
void deleteRegister(char* title);
int isInCollection(Book book);
int isbnInCollection(Book book);
void testeReadData();
// void testeReadSecondaryIndex()
#endif // BOOKSMANAGEMENT_H
