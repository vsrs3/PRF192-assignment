#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "student.h"

// Helper functions
int loadStudents(const char *filename, Student students[], int *count);
int saveStudents(const char *filename, Student students[], int count);
void toLowerStr(char *str);

void addStudent(const char *filename) {
    Student students[MAX_STUDENTS];
    int count = 0;
    loadStudents(filename, students, &count);

    if (count >= MAX_STUDENTS) {
        printf("Student list is full!\n");
        return;
    }

    Student s;
    printf("Enter student ID: ");
    scanf("%d", &s.id);
    getchar();

    // Check for duplicate ID
    for (int i = 0; i < count; i++) {
        if (students[i].id == s.id) {
            printf("ID already exists!\n");
            return;
        }
    }

    printf("Enter first name: ");
    fgets(s.firstName, MAX_NAME_LEN, stdin);
    s.firstName[strcspn(s.firstName, "\n")] = '\0';

    printf("Enter last name: ");
    fgets(s.lastName, MAX_NAME_LEN, stdin);
    s.lastName[strcspn(s.lastName, "\n")] = '\0';

    printf("Enter GPA: ");
    scanf("%f", &s.gpa);

    students[count++] = s;

    if (saveStudents(filename, students, count)) {
        printf("Student added successfully.\n");
    } else {
        printf("Error writing to file!\n");
    }
}

void displayStudents(const char *filename) {
    Student students[MAX_STUDENTS];
    int count = 0;
    if (!loadStudents(filename, students, &count)) {
        printf("Cannot read file!\n");
        return;
    }
    printf("Student List:\n");
    printf("ID\tLast Name\t\tFirst Name\t\tGPA\n");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%-15s%-15s%.2f\n", students[i].id, students[i].lastName, students[i].firstName, students[i].gpa);
    }
}

void searchStudentById(const char *filename, int id) {
    Student students[MAX_STUDENTS];
    int count = 0;
    int found = 0;
    if (!loadStudents(filename, students, &count)) {
        printf("Cannot read file!\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("Student found:\n");
            printf("ID: %d\nLast Name: %s\nFirst Name: %s\nGPA: %.2f\n",
                   students[i].id, students[i].lastName, students[i].firstName, students[i].gpa);
            found = 1;
            break;
        }
    }
    if (!found) printf("No student found with this ID.\n");
}

void searchStudentByLastName(const char *filename, const char *lastName) {
    Student students[MAX_STUDENTS];
    int count = 0;
    int found = 0;
    if (!loadStudents(filename, students, &count)) {
        printf("Cannot read file!\n");
        return;
    }
    char query[MAX_NAME_LEN];
    strncpy(query, lastName, MAX_NAME_LEN);
    toLowerStr(query);

    for (int i = 0; i < count; i++) {
        char temp[MAX_NAME_LEN];
        strncpy(temp, students[i].lastName, MAX_NAME_LEN);
        toLowerStr(temp);
        if (strcmp(temp, query) == 0) {
            if (!found) {
                printf("Search results:\n");
                printf("ID\tLast Name\t\tFirst Name\t\tGPA\n");
                printf("-------------------------------------------------------------\n");
            }
            printf("%d\t%-15s%-15s%.2f\n", students[i].id, students[i].lastName, students[i].firstName, students[i].gpa);
            found = 1;
        }
    }
    if (!found) printf("No student found with this last name.\n");
}

void sortStudentsByLastName(const char *filename) {
    Student students[MAX_STUDENTS];
    int count = 0;
    if (!loadStudents(filename, students, &count)) {
        printf("Cannot read file!\n");
        return;
    }
    // Bubble sort by lastName, if equal then sort by firstName
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            int cmp = strcmp(students[j].lastName, students[j+1].lastName);
            if (cmp > 0 || (cmp == 0 && strcmp(students[j].firstName, students[j+1].firstName) > 0)) {
                Student temp = students[j];
                students[j] = students[j+1];
                students[j+1] = temp;
            }
        }
    }
    if (saveStudents(filename, students, count)) {
        printf("Students sorted and saved to file.\n");
    } else {
        printf("Error writing to file!\n");
    }
    displayStudents(filename);
}

// ---- HELPER FUNCTIONS ----
int loadStudents(const char *filename, Student students[], int *count) {
    FILE *f = fopen(filename, "r");
    if (!f) return 0;
    *count = 0;
    while (fscanf(f, "%d,%49[^,],%49[^,],%f\n",
                  &students[*count].id,
                  students[*count].firstName,
                  students[*count].lastName,
                  &students[*count].gpa) == 4) {
        (*count)++;
        if (*count >= MAX_STUDENTS) break;
    }
    fclose(f);
    return 1;
}

int saveStudents(const char *filename, Student students[], int count) {
    FILE *f = fopen(filename, "w");
    if (!f) return 0;
    for (int i = 0; i < count; i++) {
        fprintf(f, "%d,%s,%s,%.2f\n", students[i].id, students[i].firstName, students[i].lastName, students[i].gpa);
    }
    fclose(f);
    return 1;
}

void toLowerStr(char *str) {
    for (; *str; ++str) *str = tolower(*str);
}