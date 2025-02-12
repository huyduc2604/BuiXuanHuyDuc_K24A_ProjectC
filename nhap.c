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

void searchBook(int countBook){
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
