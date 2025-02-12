//khai bao ham
#include "datatype.h"
#ifndef FUNCTION_H
#define FUNCTION_H


void showMenu();
void login();
void isID();
void isTitle();
void isValidDate();
void showBook(int countBook);
void addBook(int *countBook);
//void sortBooks(int countBook);
void searchBook(int countBook);
void deleteBook(int *countBook);
void editBook(int countBook);
void sortBooks(struct Book books[], int countBook);
void showMenuBook();
#endif

