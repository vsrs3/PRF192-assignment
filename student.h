#ifndef STUDENT_H
#define STUDENT_H

#define MAX_NAME_LEN 50
#define MAX_STUDENTS 1000

typedef struct {
    int id;
    char firstName[MAX_NAME_LEN];
    char lastName[MAX_NAME_LEN];
    float gpa;
} Student;

// Main operations
void addStudent(const char *filename);
void displayStudents(const char *filename);
void searchStudentById(const char *filename, int id);
void searchStudentByLastName(const char *filename, const char *lastName);
void sortStudentsByLastName(const char *filename);

#endif