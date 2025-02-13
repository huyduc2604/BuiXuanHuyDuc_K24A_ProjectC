#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
//#include "datatype.h"
#define MAX_BOOKS 100

const char *filebooks = "C:\\Users\\Admin\\Desktop\\projectC\\books.bin";

void login() {
    char email[50];
    char password[50];
    int loginSuccessful = 0;
    
    do {
        printf("+------------------------------------------+\n");
        printf("%-8s %-33s %s\n","|","STUDENT MANAGEMENT SYSTEM", "|");
        printf("+------------------------------------------+\n");
        printf("%-17s %-24s %s\n","|","LOGIN", "|");

        printf("+------------------------------------------+\n");
        
        // Yêu cau nhap email
        printf("Email: ");
        scanf("%s", email);
        
        // Yeu cau nhap mat khau
        printf("Password: ");
        scanf("%s", password);
        
        // Kiem tra thông tin dang nhap
        if (strcmp(email, "buixuanhuyduc") == 0 && strcmp(password, "1") == 0) {
            printf("Login successful!\n");
            loginSuccessful = 1;
        } else {
            printf("Invalid email or password. Please try again.\n");
        }
    } while (!loginSuccessful);
}

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
void writeBooksToFile(const char* filename, struct Book books[], int numBooks) {// ham ghi sach 
    FILE *file = fopen(filebooks, "w");
    if (file == NULL) {
        perror("Error opening file!\n");
        return;
    }
    int i;
    for (i = 0; i < numBooks; i++) {
        fprintf(file, "%s %s %s %d %d %02d/%02d/%04d\n",
                books[i].bookId,
                books[i].title,
                books[i].author,
                books[i].quantity,
                books[i].price,
                books[i].publication.day,
                books[i].publication.month,
                books[i].publication.year);
    }
    fclose(file);
}

void readBooksFromFile(const char* filename, struct Book books[], int *numBooks) {// ham doc danh sach 
    FILE *file = fopen(filebooks, "r");
    if (file == NULL) {
        perror("Error opening file!\n");
        return;
    }
    int i = 0;
    while (fscanf(file, "%s %s %s %d %d %d/%d/%d",
                  books[i].bookId,
                  books[i].title,
                  books[i].author,
                  &books[i].quantity,
                  &books[i].price,
                  &books[i].publication.day,
                  &books[i].publication.month,
                  &books[i].publication.year) != EOF) {
        i++;
    }
    *numBooks = i;
    if (ferror(file)) {
        perror("Error reading from file");
    }
    fclose(file);
}

// them sach


void addBook(struct Book books[], int *numBooks) {
    FILE *file = fopen(filebooks, "a"); // M? file v?i ch? ð? ghi ti?p
    if (file == NULL) {
        printf("L?i m? file!\n");
        return;
    }

    struct Book newBook; // Tao bien tam de tranh loi bo nho

    // Nhap id sach
    do {
        printf("Nhap ID book (toi da 9 ki tu): ");
        scanf("%9s", newBook.bookId);
        getchar(); // Xoa ki tu xuong dong trong butter
    }while (strlen(newBook.bookId) == 0);

    // Nhap tieu de sach
    printf("Nhap tieu de sach: ");
    fgets(newBook.title, sizeof(newBook.title), stdin);
    newBook.title[strcspn(newBook.title, "\n")] = '\0'; // Xoa ki tu xuong dong

    // Nh?p tác gi?
    printf("Nhap ten tac gia: ");
    fgets(newBook.author, sizeof(newBook.author), stdin);
    newBook.author[strcspn(newBook.author, "\n")] = '\0';

    // Nh?p s? lý?ng
    do{
        printf("Nhap so luong sach: ");
        if (scanf("%d", &newBook.quantity) != 1 || newBook.quantity < 0){
            printf("So luong khong hop li vui long nhap lai.\n");
            while (getchar() != '\n'); // Xoa bo dem
        }else{
            break;
        }
    }while(1);
    getchar();

    // Nhap gia sach
    do{
        printf("Nhap gia sach: ");
        if (scanf("%d", &newBook.price) != 1 || newBook.price < 0){
            printf("Gia sach khong hop le vui long nhap lai.\n");
            while (getchar() != '\n');
        }else{
            break;
        }
    } while (1);
    getchar();

    // Nhap ngay xuat ban
    do {
        printf("Nhap ngay xuat ban (dd mm yyyy): ");
        if (scanf("%d %d %d", &newBook.publication.day, &newBook.publication.month, &newBook.publication.year) != 3){
            printf("Ngay xuat ban khong hop le vui long nhap lai.\n");
            while (getchar() != '\n');
        } else {
            break;
        }
    } while (1);
    getchar();

    // Ghi du lieu vao file
    fprintf(file, "%s %s %s %d %d %02d/%02d/%04d\n",
            newBook.bookId, newBook.title, newBook.author,
            newBook.quantity, newBook.price,
            newBook.publication.day, newBook.publication.month, newBook.publication.year);

    fclose(file); // dong file

    // Them vao danh sach trong bo nho
    books[*numBooks] = newBook;
    (*numBooks)++;

    printf("Them sach thanh cong!\n");
}


// Hien thi sach
void showBook(struct Book book[], int countBook) {
    if (countBook == 0) {
        printf("Khong co danh sach hien thi\n");
        return;
    }

    printf("\n========================================================================================================================\n");
    printf("| %-12s | %-30s | %-20s | %-10s | %-10s | %-12s |\n", "ID", "TIEU DE", "TAC GIA", "SO LUONG", "GIA", "NGAY XUAT BAN");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
	int i; 
    for (i = 0; i < countBook; i++) {
        printf("| %-12s | %-30s | %-20s | %-10d | %-12d | %02d/%02d/%04d |\n",
               book[i].bookId, book[i].title, book[i].author,
               book[i].quantity, book[i].price,
               book[i].publication.day, book[i].publication.month, book[i].publication.year);
    }

    printf("========================================================================================================================\n");
}


//chinh sua sach
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

//Xoa sach
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

//sap xep sach
void sortBooks(struct Book book[], int countBook){
    if (countBook < 2){
        printf("Khong co du lieu de sap xep!\n");
        return;
    }
    int order;
    printf("Chon thu tu sap xep: \n1. Tang dan \n2. Giam dan: \n");
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

//tim kiem sach
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
	login();
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
            	readBooksFromFile(filebooks, books, &countBook);
                showBook(books, countBook);
                break;
            case 3:
            	readBooksFromFile(filebooks, books, &countBook);
                editBook(books, countBook);
                writeBooksToFile(filebooks, books, &countBook);
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
