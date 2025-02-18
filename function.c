#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "function.h"
#include "datatype.h"
#define MAX_BOOKS 100
struct Book books[MAX_BOOKS];
int countBook=0;
const char *filebooks = "C:\\Users\\Admin\\Desktop\\projectC\\books.txt";

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
        
        // Y?u cau nhap email
        printf("Email: ");
        scanf("%s", email);
        
        // Yeu cau nhap mat khau
        printf("Password: ");
        scanf("%s", password);
        fflush (stdin);
        
        // Kiem tra th?ng tin dang nhap
        if (strcmp(email, "buixuanhuyduc") == 0 && strcmp(password, "1") == 0) {
            printf("Login successful!\n");
            loginSuccessful = 1;
        } else {
            printf("Invalid email or password. Please try again.\n");
        }
    } while (!loginSuccessful);
}

void readBooksFromFile(const char* filename, struct Book books[], int *countBook) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file!");
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
    *countBook = i;
    if (ferror(file)) {
        perror("Error reading from file");
    }
    fclose(file);
}

void writeBooksToFile(const char* filename, struct Book books[], int countBook){
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file!");
        return;
    }
    int i; 
    for (i = 0; i < countBook; i++) {
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

int isValidDate(int day, int month, int year) {
    if (year < 1000 || year > 9999 || month < 1 || month > 12 || day < 1) {
        return 0;
    }
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) {
        daysInMonth[2] = 29;
    }
    return day <= daysInMonth[month];
}

void addBook(int *countBook) {
    do {
        printf("Moi ban nhap ID: ");
        fgets(book[*countBook].bookId, sizeof(book[*countBook].bookId), stdin);
        book[*countBook].bookId[strcspn(book[*countBook].bookId, "\n")] = '\0';
        if (strlen(book[*countBook].bookId) == 0){
            printf("ID khong duoc de trong!\n");
        }else if (strlen(book[*countBook].bookId) > 9) {
            printf("ID qua dai toi da 9 ky tu\n");
        }
    }while(strlen(book[*countBook].bookId) == 0 || strlen(book[*countBook].bookId) > 9);

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
        if (scanf("%d", &book[*countBook].price) != 1 || book[*countBook].price <= 0) {
            getchar();
            printf("Gia phai la so nguyen duong\n");
            while (getchar() != '\n');
        } else {
            break;
        }
    } while (1);

    do {
        printf("Moi ban nhap ngay xuat ban (dd mm yyyy): ");
        scanf("%d %d %d", &book[*countBook].publication.day, &book[*countBook].publication.month, &book[*countBook].publication.year);
        getchar();
        if (!isValidDate(book[*countBook].publication.day, book[*countBook].publication.month, book[*countBook].publication.year)) {
            printf("Ngay khong hop le\n");
        }
    } while (!isValidDate(book[*countBook].publication.day, book[*countBook].publication.month, book[*countBook].publication.year));

    (*countBook)++;
//    saveToFile(countBook);
	
    printf("Them sach thanh cong\n");
}

//void addBook(int *countBook){
//	do{
//		do{
//        	printf("moi ban nhap ID: ");
//        	fgets(book[*countBook].bookId,sizeof(book[*countBook].bookId),stdin);
//        	book[*countBook].bookId[strcspn(book[*countBook].bookId,"\n")]='\0';
//        	if(strlen(book[*countBook].bookId)==0){
//            	printf("ID khong duoc de trong!\n");
//        	}else if(strlen(book[*countBook].bookId)>9){
//            	printf("ID qua dai toi da 9 ky tu\n");
//        	}
//    	}while(strlen(book[*countBook].bookId)==0||strlen(book[*countBook].bookId)>10);
//    }while(isIdBook(book[*countBook].bookId,*countBook));
//    do{
//    	do{
//        	printf("moi ban nhap tieu de: ");
//        	fgets(book[*countBook].title,sizeof(book[*countBook].title),stdin);
//        	book[*countBook].title[strcspn(book[*countBook].title,"\n")] ='\0';
//        	if(strlen(book[*countBook].title)==0){
//            	printf("khong duoc de trong\n");
//        	}else if(strlen(book[*countBook].title)>29){
//            	printf("tieu de qua dai toi da 29 ky tu\n");
//        	}
//    	}while(strlen(book[*countBook].title)==0||strlen(book[*countBook].title)>30);
//    }while(isTitle(book[*countBook].title,*countBook));
//    do{
//        printf("moi ban nhap tac gia: ");
//        fgets(book[*countBook].author,sizeof(book[*countBook].author),stdin);
//        book[*countBook].author[strcspn(book[*countBook].author,"\n")]='\0';
//        if(strlen(book[*countBook].author)==0){
//            printf("tac gia khong duoc de trong\n");
//        }else if (strlen(book[*countBook].author)>20){
//            printf("ten tac gia qua dai toi da 19 ky tu\n");
//        }
//    }while(strlen(book[*countBook].author)==0||strlen(book[*countBook].author)>20);
//    do{
//        printf("moi ban nhap so luong: ");
//        if(scanf("%d",&book[*countBook].quantity)!=1||book[*countBook].quantity<=0){
//        	getchar();
//            printf("so luong la so nguyen duong\n");
//            while(getchar()!='\n');
//        }else{
//            break;
//        }
//    }while(1);
//	do{
//        printf("Moi ban nhap gia: ");
//        if(scanf("%d",&book[*countBook].price)!=1||book[*countBook].price<=0){
//        	getchar();
//            printf("So luong la so nguyen duong\n");
//            while(getchar()!='\n');
//        }else{
//            break;
//        }
//    }while(1);
//	do{
//		printf("Moi ban nhap ngay xuat ban(dd mm yyyy): ");
//        scanf("%d %d %d",&book[*countBook].publication.day,&book[*countBook].publication.month,&book[*countBook].publication.year);
//        getchar();
//        if (!isValidDate(book[*countBook].publication.day,book[*countBook].publication.month,book[*countBook].publication.year)){
//        	printf("Ngay khong hop le\n");
//        	}   	
//    }while(!isValidDate(book[*countBook].publication.day,book[*countBook].publication.month,book[*countBook].publication.year));
//	(*countBook)++;
//	saveToFile(*countBook);
//	printf("them sach thanh cong\n");
//}

void showBook(int countBook){
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
        printf("|%-6s|%-14s|%-15s|%-8d|%-10d|%02d/%02d/%04d%-5s|\n", book[i].bookId, book[i].title, book[i].author, book[i].quantity, book[i].price, book[i].publication.day, book[i].publication.month, book[i].publication.year,"     ");
        printf("|======|==============|===============|========|==========|===============|\n");
    }
}

void editBook(int countBook){
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

void deleteBook(int *countBook){
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

void sortBooks(struct Book books[], int countBook){
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

//void searchBook(int countBook){
//    char title[50];
//    printf("Nhap ten sach can tim: ");
//    getchar(); // Xoa bo nho dem tranh lap chuoi 
//    fgets(title, sizeof(title), stdin);
//    title[strcspn(title, "\n")] = '\0'; // xoa ki tu xuong dong 
//
//    printf("\n%-10s %-30s %-15s %-10s %-15s\n", "ID", "Ten", "Tac Gia", "Gia", "Ngay Xuat Ban");
//    printf("----------------------------------------------------------------------------\n");
//
//    int found = 0;
//    int i; 
//    for (i = 0; i < countBook; i++){
//        if (strstr(books[i].title, title) == 0 ){ // Kiem tra chuoi con
//            printf("%-10s %-30s %-15s %-10d %02d/%02d/%04d\n", 
//                   books[i].bookId, books[i].title, books[i].author, 
//                   books[i].price, 
//                   books[i].publication.day, books[i].publication.month, books[i].publication.year);
//            found = 1;
//        }
//    }
//    if (!found){
//        printf("Khong tim thay sach nao voi ten \"%s\"!\n", title);
//    }
//}
void searchBook(int countBook){
    char temp[30];
    int check=1;
    printf("Nhap ten sach muon tim: ");
    fgets(temp,sizeof(temp),stdin);
    temp[strcspn(temp,"\n")]='\0';
    printf("============================== Search Results =============================\n");
    printf("|======|==============|===============|========|==========|===============|\n");
    printf("|%-6s|%-14s|%-15s|%-6s|%-10s|%-15s|\n","ID","TIEU DE","TAC GIA","SO LUONG","GIA","ngay xuat ban");
    printf("|======|==============|===============|========|==========|===============|\n");
    int i; 
    for(i=0;i<countBook;i++){
        if(strstr(book[i].title,temp)!=NULL){
            printf("|%-6s|%-14s|%-15s|%-8d|%-10d|%02d/%02d/%04d%-5s|\n",book[i].bookId,book[i].title,book[i].author,book[i].quantity,book[i].price,book[i].publication.day,book[i].publication.month,book[i].publication.year,"     ");
            printf("|======|==============|===============|========|==========|===============|\n");
            check=0;
        	}
    }
	if(check){
        printf("Khong tim thay sach\n");
    }
    return;
}

void menu(){
	login();
	int choice;
	int countBook=0;
	
	do{
		printf("\n===================MENU====================\n");
	    printf("===========================================\n");
	    printf("[1]. Them sach moi\n");
	    printf("[2]. Hien thi sach\n");
	    printf("[3]. Chinh sua thong tin sach\n");
	    printf("[4]. Xoa sach\n");
	    printf("[5]. Sap xep sach theo gia tien\n");
	    printf("[6]. Tim kiem sach\n");
	    printf("[0]. Thoat chuong trinh quay lai MENU chinh\n");
	    printf("===========================================\n");
	    printf("Nhap lua chon cua ban: ");
	    scanf("%d",&choice);
	    fflush(stdin); 
	    switch (choice) {
            case 1:
				addBook(&countBook);                
				break;
            case 2:
                showBook(countBook);
                break;
            case 3:
                editBook(countBook);
                break;
                
            case 4:
            	deleteBook(&countBook);
            	break;
            	
            case 5:
				sortBooks(books, countBook);
                break;
				
			case 6:
				searchBook(countBook);
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



//menu dang chinh

//void manageCustomers() {
//    int choice;
//    do {
//        printf("\n========= QUAN LY KHACH HANG =========\n");
//        printf("[1]. Them khach hang moi\n");
//        printf("[2]. Hien thi danh sach khach hang\n");
//        printf("[3]. Chinh sua thong tin khach hang\n");
//        printf("[4]. Xoa khach hang\n");
//        printf("[0]. Quay lai menu chinh\n");
//        printf("=====================================\n");
//        printf("Nhap lua chon cua ban: ");
//        scanf("%d", &choice);
//        fflush(stdin);
//
//        switch (choice) {
//            case 1:
//                addCustomer();
//                break;
//            case 2:
//                showCustomers();
//                break;
//            case 3:
//                editCustomer();
//                break;
//            case 4:
//                deleteCustomer();
//                break;
//            case 0:
//                printf("Quay lai menu chinh...\n");
//                return;
//            default:
//                printf("Lua chon khong hop le. Vui long nhap lai!\n");
//                break;
//        }
//    } while (choice != 0);
//}
//
//void showMainMenu(){
//	printf("\n|=========== MENU ===========|\n");
//	
//	printf("|============================|\n");
//
//	printf("| [1]. Book Management       |\n");
//	printf("| [2]. Customer Management   |\n");
//	printf("| [3]. Admin                 |\n");
//	printf("| [0]. Exit The Program      |\n");
//	printf("|============================|\n");
//	printf(" Enter The Choice: ");
//}
//
//void menu(){
//	int choose,chooseMain,countBook=0,countCustomer=0,countAdmin=0;
//	int choice;
////	int countBook=0;
//do {
//	login();
//	showMainMenu();
//        scanf("%d",&chooseMain);
//        getchar();
//        switch(chooseMain){
//        	case 1:
//        		showMainMenu();
//				int choice;
//				int countBook=0;
//				do{
//				printf("\n===================MENU====================\n");
//	   			printf("===========================================\n");
//	  			printf("[1]. Them sach moi\n");
//	   			 printf("[2]. Hien thi sach\n");
//	   			 printf("[3]. Chinh sua thong tin sach\n");
//				    printf("[4]. Xoa sach\n");
//				    printf("[5]. Sap xep sach theo gia tien\n");
//				    printf("[6]. Tim kiem sach\n");
//				    printf("[0]. Thoat chuong trinh quay lai MENU chinh\n");
//				    printf("===========================================\n");
//				    printf("Nhap lua chon cua ban: ");
//				    scanf("%d",&choice);
//				    fflush(stdin); 
//	   			 switch (choice) {
//          			  case 1:
//						addBook(&countBook);                
//						break;
//		            case 2:
//		                showBook(countBook);
//		                break;
//		            case 3:
//		                editBook(countBook);
//		                break;
//		                
//		            case 4:
//		            	deleteBook(&countBook);
//		            	break;
//		            	
//		            case 5:
//						sortBooks(books, countBook);
//		                break;
//						
//					case 6:
//						searchBook(countBook);
//						break;
//						
//		            case 0:
//		                printf("Exiting the program. Goodbye!\n");
//		                return;
//		            default:
//		                printf("Invalid choice. Please try again.\n");
//		                break;
//		        }
//			} while(choice != 0);
//		} 
//        	case 2:
//    		do {
//	        printf("\n========= QUAN LY KHACH HANG =========\n");
//	        printf("[1]. Them khach hang moi\n");
//	        printf("[2]. Hien thi danh sach khach hang\n");
//	        printf("[3]. Chinh sua thong tin khach hang\n");
//	        printf("[4]. Xoa khach hang\n");
//	        printf("[0]. Quay lai menu chinh\n");
//	        printf("=====================================\n");
//	        printf("Nhap lua chon cua ban: ");
//	        scanf("%d", &choice);
//	        fflush(stdin);
//
//        switch (choice) {
//            case 1:
//                addCustomer();
//                break;
//            case 2:
//                showCustomers();
//                break;
//            case 3:
//                editCustomer();
//                break;
//            case 4:
//                deleteCustomer();
//                break;
//            case 0:
//                printf("Quay lai menu chinh...\n");
//                return;
//            default:
//                printf("Lua chon khong hop le. Vui long nhap lai!\n");
//                break;
//        }
//    } while (choice != 0);
//                break;
//            case 3:
//            	
//            	break;
//        }
//    } while(chooseMain!=0);
//}
