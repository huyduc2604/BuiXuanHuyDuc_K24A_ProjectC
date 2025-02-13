//khai bao ham
#include "datatype.h"
#ifndef FUNCTION_H
#define FUNCTION_H


void showMenu();
void login();
void isID();
void isTitle();
bool isValidDate(int day, int month, int year); //ngay san xuat sach

//them sach
void addBook(struct Book book[], int *countBook);

//hien thi sach
void showBook(struct Book book[], int countBook);

//chinh sua sach
void editBook(struct Book book[], int countBook);

//Xoa sach
void deleteBook(struct Book book[], int *countBook);

//sap xep sach
void sortBooks(struct Book book[], int countBook);

//tim kiem sach
void searchBook(struct Book book[],int countBook);

void showMenuBook();
void writeBooksToFile(const char* filename, struct Book books[], int numBooks) ;
void readBooksFromFile(const char* filename, struct Book books[], int *numBooks) ;

#endif

