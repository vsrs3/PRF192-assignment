#include <stdio.h>         
#include <stdlib.h>        
#include <string.h>        
#include "student.h"       

#define FILENAME "students.txt" // Định nghĩa tên file chứa dữ liệu sinh viên.

void menu();               // Khai báo hàm menu hiển thị giao diện cho người dùng.

int main() {
    menu();                // Gọi hàm menu để bắt đầu chương trình.
    return 0;              // Kết thúc chương trình, trả về 0.
}

/*
 * Hàm menu:
 * Hiển thị menu chức năng cho người dùng.
 * Xử lý lựa chọn và gọi các hàm tương ứng để quản lý sinh viên.
 * Lặp lại cho đến khi người dùng chọn thoát.
 */
void menu() {
    int choice;            // Lưu lựa chọn của người dùng.
    char lastName[MAX_NAME_LEN]; // Biến lưu họ cần tìm kiếm.
    int id;                // Biến lưu mã số sinh viên cần tìm.
    do {
        printf("\n-- Student Management System --\n");
        printf("1. Add student\n");
        printf("2. Search student by ID\n");
        printf("3. Search student by last name\n");
        printf("4. Display all students (sorted by last name)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {           // Nhập giá trị lựa chọn, kiểm tra hợp lệ.
            printf("Invalid choice!\n");
            while(getchar()!='\n');                // Xóa bộ đệm nhập.
            continue;
        }
        getchar();                                 // Xóa ký tự xuống dòng khỏi bộ đệm.

        switch (choice) {
            case 1:
                addStudent(FILENAME);              // Gọi hàm thêm sinh viên mới.
                break;
            case 2:
                printf("Enter ID: ");            // Nhập mã số sinh viên cần tìm.
                scanf("%d", &id);
                getchar();
                searchStudentById(FILENAME, id);   // Gọi hàm tìm kiếm theo mã số.
                break;
            case 3:
                printf("Enter last name to search: ");       // Nhập họ cần tìm kiếm.
                fgets(lastName, MAX_NAME_LEN, stdin);
                lastName[strcspn(lastName, "\n")] = '\0'; // Xóa ký tự xuống dòng.
                searchStudentByLastName(FILENAME, lastName); // Gọi hàm tìm kiếm theo họ.
                break;
            case 4:
                sortStudentsByLastName(FILENAME);  // Gọi hàm sắp xếp và hiển thị danh sách sinh viên.
                break;
            case 5:
                printf("Goodbye!\n");             // Thoát chương trình.
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 5);                         // Lặp lại menu đến khi người dùng chọn thoát.
}