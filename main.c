#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

#define FILENAME "students.txt"

void menu();

int main() {
    menu();
    return 0;
}

void menu() {
    int choice;
    char lastName[MAX_NAME_LEN];
    int id;
    do {
        printf("\n-- Student Management System --\n");
        printf("1. Add student\n");
        printf("2. Search student by ID\n");
        printf("3. Search student by last name\n");
        printf("4. Display all students (sorted by last name)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice!\n");
            while(getchar()!='\n');
            continue;
        }
        getchar(); // clear newline
        switch (choice) {
            case 1:
                addStudent(FILENAME);
                break;
            case 2:
                printf("Enter ID: ");
                scanf("%d", &id);
                getchar();
                searchStudentById(FILENAME, id);
                break;
            case 3:
                printf("Enter last name to search: ");
                fgets(lastName, MAX_NAME_LEN, stdin);
                lastName[strcspn(lastName, "\n")] = '\0';
                searchStudentByLastName(FILENAME, lastName);
                break;
            case 4:
                sortStudentsByLastName(FILENAME);
                break;
            case 5:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 5);
}