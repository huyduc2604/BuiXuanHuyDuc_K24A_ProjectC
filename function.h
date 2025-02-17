//khai bao ham
#include "datatype.h"
#ifndef FUNCTION_H
#define FUNCTION_H

void menu();
//void showMenu();
void login();
//void isID();
//void isTitle();
int isValidDate(int day, int month, int year); //ngay san xuat sach

//them sach
void addBook() ;

//hien thi sach
void showBookshowBook(int countBook);

//chinh sua sach
void editBook(int countBook);

//Xoa sach
void deleteBook(int *countBook);

//sap xep sach
void sortBooks(struct Book books[], int countBook);

//tim kiem sach
void searchBook(int countBook);

//void showMenuBook();
void writeBooksToFile(const char* filename, struct Book books[], int numBooks);
void readBooksFromFile(const char* filename, struct Book books[], int *countBook);

#endif

