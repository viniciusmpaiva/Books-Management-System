#include "booksManagement.h"
#include "qdebug.h"
char indexStr[INDEXSTRMAXLEN];



static void insertSecundaryIndexFile(Book book, FILE* filePointer){
    fwrite(book.title,sizeof(book.title),1,filePointer);
    // char isbnStr[ISBNSTRMAXLEN];
    // sprintf(isbnStr,"%d",book.isbn);
    fwrite(book.isbn,sizeof(book.isbn),1,filePointer);
}

static void insertPrimaryIndexFile(Book book, FILE* filePointer){
    FILE* fileTemp = fopen(PRIMARYINDEXFILENAME,"r");
    Book bookAux;
    char tempIdx[INDEXSTRMAXLEN];
    int count= 0;
    if(fileTemp){
        while(1){
            size_t keyRead = fread(&bookAux.isbn,sizeof(bookAux.isbn),1,fileTemp);
            size_t idxRead = fread(&tempIdx,sizeof(tempIdx),1,fileTemp);
            printf("Primary file Title = %s\n",bookAux.title);
            if(idxRead !=1){
                printf("Deu o break\n");
                break;
            }
            count++;
        }
        fclose(fileTemp);
    }

    fwrite(book.isbn,sizeof(book.isbn),1,filePointer);
    int curIdx = (sizeof(book)+INDEXSTRMAXLEN) * count;
    sprintf(indexStr,"%d",curIdx);
    fwrite(indexStr,sizeof(indexStr),1,filePointer);

}

static void insertDataFile(Book book, FILE* filePointer){
    FILE* fileTemp = fopen(DATAFILENAME,"r");
    Book bookAux;
    int count=0;
    if(fileTemp){
        while(1){
            size_t indexRead = fread(&indexStr,sizeof(indexStr),1,fileTemp);
            if(indexRead !=1){
                break;
            }
            size_t keyRead = fread(&bookAux,sizeof(book),1,fileTemp);
            count++;
        }
        fclose(fileTemp);
    }

    int curIdx = (sizeof(book)+INDEXSTRMAXLEN) * count;

    sprintf(indexStr,"%d",curIdx);
    fseek(filePointer,curIdx,SEEK_SET);
    fwrite(indexStr,sizeof(indexStr),1,filePointer);
    fwrite(&book,sizeof(Book),1,filePointer);
}

int isbnInCollection(Book book){
    FILE* filePointer = fopen(SECONDARYINDEXFILENAME,"r");
    Book bookAux;
    while(1){
        size_t titleRead = fread(&bookAux.title,sizeof(bookAux.title),1,filePointer);
        size_t keyRead = fread(&bookAux.isbn,sizeof(bookAux.isbn),1,filePointer);
        if(titleRead !=1){
            break;
        }
        if(strcmp(bookAux.isbn,book.isbn)==0){
            return 1;
        }
    }
    return 0;
}


static int findBookIdx(char* title){
    Book bookAux;
    char isbnStr1[ISBNSTRMAXLEN];

    FILE* filePointerData = fopen(DATAFILENAME,"r");
    FILE* filePointerPrimaryIndex = fopen(PRIMARYINDEXFILENAME,"r");
    FILE* filePointerSecondaryIndex = fopen(SECONDARYINDEXFILENAME,"r");

    //Search in secondary index
    while(1){
        size_t titleRead = fread(&bookAux.title,sizeof(bookAux.title),1,filePointerSecondaryIndex);
        size_t keyRead = fread(&bookAux.isbn,sizeof(bookAux.isbn),1,filePointerSecondaryIndex);

        if(titleRead !=1 || keyRead !=1){
            break;
        }

        if(strcmp(bookAux.title,title)==0){

            break;
        }
    }
    strcpy(isbnStr1,bookAux.isbn);
    //gets the key and search for the index in the primary index file
    char tempIdx[INDEXSTRMAXLEN];
    char isbnStr2[ISBNSTRMAXLEN];
    int num =0;

    while(1){
        size_t isbnRead = fread(&bookAux.isbn,sizeof(bookAux.isbn),1,filePointerPrimaryIndex);
        size_t idxRead = fread(&tempIdx,sizeof(tempIdx),1,filePointerPrimaryIndex);

        if(idxRead!=1 || isbnRead !=1){

            break;
        }
        strcpy(isbnStr2,bookAux.isbn);
        if(strcmp(isbnStr1,isbnStr2) == 0){

            break;
        }

    }

    return atoi(tempIdx);
}

void testeReadSecondaryIndex(){
    printf("\nTESTE\n");
    FILE* filePointer = fopen(SECONDARYINDEXFILENAME,"r");
    Book book;
    while(1){
        size_t titleRead = fread(&book.title,sizeof(book.title),1,filePointer);
        if(titleRead !=1){

            break;
        }

        size_t keyRead = fread(&book.isbn,sizeof(book.isbn),1,filePointer);
    }
    fclose(filePointer);
}


static void updateSecondaryIndexFile(Book book,Book newBook){
    Book bookAux;
    FILE* filePointer = fopen(SECONDARYINDEXFILENAME,"r+");
    while (1) {
        size_t titleRead = fread(&bookAux.title, sizeof(bookAux.title), 1, filePointer);
        if (titleRead != 1) {
            break;
        }
        if (strcmp(book.title,bookAux.title ) == 0) {
            fseek(filePointer, - sizeof(book.title), SEEK_CUR);
            fwrite(newBook.title, sizeof(newBook.title), 1, filePointer);
            break;
        }
    }
    fclose(filePointer);
}
static Book searchBook(char* title, FILE* filePointerData, FILE* filePointerPrimaryIndex, FILE* filePointerSecondaryIndex){
    int intTempIdx = findBookIdx(title);
    Book bookAux;
    char tempIdx[INDEXSTRMAXLEN];
    fseek(filePointerData,intTempIdx,SEEK_SET);
    if(fread(&tempIdx,sizeof(tempIdx),1,filePointerData)!=1){
        printf("Erro na leitura do index");
    }
    if(fread(&bookAux,sizeof(bookAux),1,filePointerData)!=1){
        printf("Erro na leitura do livro");
    }
    fclose(filePointerData);
    fclose(filePointerPrimaryIndex);
    fclose(filePointerSecondaryIndex);
    return bookAux;
}
int isInCollection(Book book){
    FILE* filePointer = fopen(SECONDARYINDEXFILENAME,"r");
    Book bookAux;
    while(1){
        size_t titleRead = fread(&bookAux.title,sizeof(bookAux.title),1,filePointer);
        size_t keyRead = fread(&bookAux.isbn,sizeof(book.isbn),1,filePointer);
        // printf("Title = %s\n",bookAux.title);
        if(titleRead !=1){
            break;
        }
        if(strcmp(bookAux.title,book.title)==0 || strcmp(bookAux.isbn,book.isbn)==0){
            return 1;
        }
    }
    return 0;
}


void addBook(Book book){
    FILE *filePointerData = fopen("booksData.txt","a");
    FILE *filePointerPrimaryIndex = fopen("booksPrimaryIndex.txt","a");
    FILE *filePointerSecondaryIndex = fopen("booksSecondaryIndex.txt","a");
    if(isInCollection(book) || isbnInCollection(book)){

        return;
    }
    insertDataFile(book,filePointerData);
    insertPrimaryIndexFile(book,filePointerPrimaryIndex);
    insertSecundaryIndexFile(book,filePointerSecondaryIndex);
    fclose(filePointerData);
    fclose(filePointerPrimaryIndex);
    fclose(filePointerSecondaryIndex);
}

void testeReadData(){
    FILE* filePointer = fopen(DATAFILENAME,"r");
    Book book;
    char tempIdx[INDEXSTRMAXLEN];
    while(1){
        size_t indexRead = fread(&tempIdx,sizeof(tempIdx),1,filePointer);
        if(indexRead !=1){

            break;
        }
        size_t keyRead = fread(&book,sizeof(book),1,filePointer);
    }
    fclose(filePointer);
}

// void testeReadSecondaryIndex(){
//     printf("\nTESTE\n");
//     FILE* filePointer = fopen(SECONDARYINDEXFILENAME,"r");
//     Book book;
//     while(1){
//         size_t titleRead = fread(&book.title,sizeof(book.title),1,filePointer);
//         if(titleRead !=1){
//             printf("Break\n");
//             break;
//         }
//         printf("Title = %s\n",book.title);
//         size_t keyRead = fread(&book.isbn,sizeof(book.isbn),1,filePointer);
//     }
//     fclose(filePointer);
// }
void updateRegister(Book book, Book newBook){
    FILE* filePointerData = fopen("booksData.txt","r+");
    int intBookIdx = findBookIdx(book.title);


    if(strcmp(book.title,newBook.title)!=0){
        printf("Updating secondary index\n");
        updateSecondaryIndexFile(book,newBook);
    }

    fseek(filePointerData,intBookIdx+INDEXSTRMAXLEN,SEEK_SET);
    fwrite(&newBook,sizeof(Book),1,filePointerData);
    qDebug()<<"New Book: "<<newBook.title;
    fclose(filePointerData);
}

void deleteRegister(char *title){
    int delIdx = findBookIdx(title);
    FILE* filePointerData = fopen(DATAFILENAME,"r+b");
    FILE* filePointerPrimaryIndex = fopen(PRIMARYINDEXFILENAME,"r+b");
    FILE* filePointerSecondaryIndex = fopen(SECONDARYINDEXFILENAME,"r+b");
    fseek(filePointerData,delIdx,SEEK_SET);

}


Book readRegister(char* title){
    FILE* filePointerData = fopen("booksData.txt","r");
    FILE* filePointerPrimaryIndex = fopen("booksPrimaryIndex.txt","r");
    FILE* filePointerSecondaryIndex = fopen("booksSecondaryIndex.txt","r");
    Book bookAux;
    strcpy(bookAux.title,title);
    if(!isInCollection(bookAux)){
        return bookAux;
    };
    bookAux = searchBook(title,filePointerData,filePointerPrimaryIndex,filePointerSecondaryIndex);
    return bookAux;
}

