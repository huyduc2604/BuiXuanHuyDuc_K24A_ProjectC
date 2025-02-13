#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
//#include "datatype.h"
#define MAX_BOOKS 100


bool isValidDate(int day, int month, int year){
    if (year < 1 || month < 1 || month > 12 || day < 1) {
        return false;
    }
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[1] = 29;
    }
    if (day > daysInMonth[month - 1]){
        return false;
    }
    return true;
}

void addBook(struct Book book[], int *countBook){

    do {
        printf("Moi ban nhap ID: ");
        fgets(book[*countBook].bookId, sizeof(book[*countBook].bookId), stdin);
        book[*countBook].bookId[strcspn(book[*countBook].bookId, "\n")] = '\0';
        if (strlen(book[*countBook].bookId) == 0) {
            printf("ID khong duoc de trong!\n");
        } else if (strlen(book[*countBook].bookId) > 9) {
            printf("ID qua dai toi da 9 ky tu\n");
        }
    } while (strlen(book[*countBook].bookId) == 0 || strlen(book[*countBook].bookId) > 9);

    do {
        printf("Moi ban nhap tieu de: ");
        fgets(book[*countBook].title, sizeof(book[*countBook].title), stdin);
        book[*countBook].title[strcspn(book[*countBook].title, "\n")] = '\0';
        if (strlen(book[*countBook].title) == 0) {
            printf("Tieu de khong duoc de trong\n");
        } else if (strlen(book[*countBook].title) > 29) {
            printf("Tieu de qua dai toi da 29 ky tu\n");
        }
    } while (strlen(book[*countBook].title) == 0 || strlen(book[*countBook].title) > 29);

    do {
        printf("Moi ban nhap tac gia: ");
        fgets(book[*countBook].author, sizeof(book[*countBook].author), stdin);
        book[*countBook].author[strcspn(book[*countBook].author, "\n")] = '\0';
        if (strlen(book[*countBook].author) == 0) {
            printf("Tac gia khong duoc de trong!\n");
        } else if (strlen(book[*countBook].author) > 19) {
            printf("Ten tac gia qua dai toi da 19 ky tu\n");
        }
    } while (strlen(book[*countBook].author) == 0 || strlen(book[*countBook].author) > 19);

    do {
        printf("Moi ban nhap so luong: ");
        if (scanf("%d", &book[*countBook].quantity) != 1 || book[*countBook].quantity <= 0) {
            getchar();
            printf("So luong phai la so nguyen duong\n");
            while (getchar() != '\n');
        } else {
            break;
        }
    } while (1);

    do {
        printf("Moi ban nhap gia: ");
        if (scanf("%d", &book[*countBook].price) != 1 || book[*countBook].price <= 0){
            getchar();
            printf("Gia phai la so nguyen duong\n");
            while (getchar() != '\n');
        }else{
            break;
        }
    } while (1);

    do{
        printf("Moi ban nhap ngay xuat ban (dd mm yyyy): ");
        scanf("%d %d %d", &book[*countBook].publication.day, &book[*countBook].publication.month, &book[*countBook].publication.year);
        getchar();
        if (!isValidDate(book[*countBook].publication.day, book[*countBook].publication.month, book[*countBook].publication.year)) {
            printf("Ngay khong hop le\n");
        }
    }while (!isValidDate(book[*countBook].publication.day, book[*countBook].publication.month, book[*countBook].publication.year));

    (*countBook)++;
    printf("Them sach thanh cong\n");
}



void showBook(struct Book book[], int countBook){
    if (countBook == 0) {
        printf("Khong co sach de hien thi\n");
        return;
    }
    printf("\n=============================== All Book ==============================\n\n");
    printf("|======|==============|===============|========|==========|===============|\n");
    printf("|%-6s|%-14s|%-15s|%-8s|%-10s|%-15s|\n", "ID", "TIEU DE", "TAC GIA", "SO LUONG", "GIA", "NGAY XUAT BAN");
    printf("|======|==============|===============|========|==========|===============|\n");
    int i; 
    for (i = 0; i < countBook; i++) {
        printf("|%-6s|%-14s|%-15s|%-8d|%-10d|%02d/%02d/%04d|\n", book[i].bookId, book[i].title, book[i].author, book[i].quantity, book[i].price, book[i].publication.day, book[i].publication.month, book[i].publication.year);
        printf("|======|==============|===============|========|==========|===============|\n");
    }
}

void editBook(struct Book book[], int countBook){
    char id[10];
    printf("Nhap ID sach can chinh sua: ");
    scanf("%s", id);
    getchar();
    int i;
    for (i = 0; i < countBook; i++){
        if (strcmp(book[i].bookId, id) == 0){
            printf("Chinh sua thong tin sach %s\n", book[i].title);
            printf("Nhap ten moi: ");
            fgets(book[i].title, sizeof(book[i].title), stdin);
            book[i].title[strcspn(book[i].title, "\n")] = '\0';
            printf("Nhap ngay xuat ban moi (dd mm yyyy): ");
            scanf("%d %d %d", &book[i].publication.day, &book[i].publication.month, &book[i].publication.year);
            getchar();
            printf("Nhap ten tac gia moi: ");
            fgets(book[i].author, sizeof(book[i].author), stdin);
            book[i].author[strcspn(book[i].author, "\n")] = '\0';
            printf("Nhap so luong moi: ");
			scanf("%d",&book[i].quantity);
            printf("Nhap gia tien moi: ");
            scanf("%d", &book[i].price);
            getchar();
            printf("Chinh sua thong tin thanh cong!\n");
            return;
        }
    }
    printf("Khong tim thay sach voi ID %s!\n", id);
}

void deleteBook(struct Book book[], int *countBook){
    char id[10];
    printf("Nhap ID sach can xoa: ");
    scanf("%s", id);
    getchar();
    int i;
    for (i = 0; i < *countBook; i++){
        if (strcmp(book[i].bookId, id) == 0){
            char confirm;
            printf("Ban co chac chan muon xoa sach voi ID %s? (y/n): ", id);
            scanf(" %c", &confirm);
            getchar();
            if (confirm == 'y' || confirm == 'Y'){
            	int j;
                for (j = i; j < *countBook - 1; j++){
                    book[j] = book[j + 1];
                }
                (*countBook)--;
                printf("Xoa sach thanh cong!\n");
            }else{
                printf("Huy thao tac xoa sach.\n");
            }
            return;
        }
        printf("Khong tim thay sach voi ID %s!\n", id);
}
//    printf("Khong tim thay sach voi ID %s!\n", id);
}

void sortBooks(struct Book book[], int countBook){
    if (countBook < 2){
        printf("Khong co du lieu de sap xep!\n");
        return;
    }
    int order;
    printf("Chon thu tu sap xep: 1. Tang dan 2. Giam dan: ");
    if (scanf("%d", &order) != 1 || (order != 1 && order != 2)){
        printf("Lua chon khong hop le!\n");
        while (getchar() != '\n'); // Xóa b? nh? ð?m ð?u vào
        return;
	}
    getchar(); // Tranh loi nhap sau scanf

    // Thuat toan sap xep(Bubble Sort)
    int i, j;
    
    for ( i = 0; i < countBook - 1; i++){
        for (j = i + 1; j < countBook; j++){
            if ((order == 1 && book[i].price > book[j].price)|| 
                (order == 2 && book[i].price < book[j].price)){
                struct Book temp = book[i];
                book[i] = book[j];
                book[j] = temp;
            }
        }
    }
    printf("Sap xep sach theo gia tien thanh cong!\n");
}

void searchBook(struct Book book[],int countBook){
    char title[50];
    printf("Nhap ten sach can tim: ");
    scanf(" %[^\n]", title);
    getchar();
    printf("\n%-10s %-30s %-15s %-20s %-10s\n", "ID", "Ten", "Ngay Xuat Ban", "Tac Gia", "Gia");
    printf("--------------------------------------------------------------------------\n");
    int found = 0;
    int i;
    for (i = 0; i < countBook; i++){
        if (strstr(book[i].title, title) != NULL){
            printf("%-10s %-30s %-15s %-20s %-10d\n", book[i].bookId, book[i].title, book[i].publication.day, book[i].author, book[i].price);
            found = 1;
        }
	}
    if (!found){
        printf("Khong tim thay sach nao voi ten %s!\n", title);
    }
}

void menu(){
	struct Book books[MAX_BOOKS];
	int choice;
	int countBook=0;
	do{
		printf("\n======== MENU ========\n");
	    printf("======================\n");
	    printf("[1]. Them sach moi\n");
	    printf("[2]. Hien thi sach\n");
	    printf("[3]. Chinh sua thong tin sach\n");
	    printf("[4]. Xoa sach\n");
	    printf("[5]. Sap xep sach theo gia tien\n");
	    printf("[6]. Tim kiem sach\n");
	    printf("[0]. Thoat chuong trinh quay lai MENU chinh\n");
	    printf("======================\n");
	    printf("Nhap lua chon cua ban: ");
	    scanf("%d",&choice);
	    switch (choice) {
            case 1:
				addBook(books, &countBook);                
				break;
            case 2:
                showBook(books, countBook);
                break;
            case 3:
                editBook(books, countBook);
                break;
                
            case 4:
            	deleteBook(books, &countBook);
            	break;
            	
            case 5:
				sortBooks(books, countBook);
                break;
				
			case 6:
				searchBook(books, countBook);
				break;
				
            case 0:
                printf("Exiting the program. Goodbye!\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
	} while(choice != 0);
} 
