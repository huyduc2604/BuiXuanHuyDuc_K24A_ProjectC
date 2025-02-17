
#ifndef DATATYPE_H  // N?u DATATYPE_H chua du?c d?nh nghia
#define DATATYPE_H  // ??nh nghia DATATYPE_H
#include <stdbool.h>
#define MAX_STUDENTS 100

struct Date{
	int month,day,year;
};
struct Date date[100];
struct Book{
	char bookId[10]; //id book
	char title[30];  //ghi chu
	char author[20]; //tac gia
	int quantity;	//so luong
	int price;		//gia tien
	struct Date publication;
};
struct Book book[100];

struct Menber{
	char memberId[10];
	char name[20];
	char phone[10];
	char status[10];
	struct Book BrrowedBooks[];
};
struct Menber menber[100];
#endif
