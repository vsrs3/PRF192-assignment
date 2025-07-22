#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants
#define MAX_NAME_LENGTH 50
#define FILENAME "students.txt"
#define MAX_STUDENTS 100

// Student structure
typedef struct {
    int id;
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    float gpa;
} Student;

// Function prototypes
void addStudent(const char *filename);
void displayStudents(const char *filename);
void searchStudentById(const char *filename, int id);
void searchStudentByLastName(const char *filename, const char *lastName);
void sortStudentsByLastName(const char *filename);
void displayMenu();
int getMenuChoice();

/**
 * Function: addStudent
 * Purpose: Add a new student record to the file
 * Parameters: filename - name of the file to write to
 * Returns: void
 */
void addStudent(const char *filename) {
    // TODO: Implement adding student functionality
    // 1. Get student information from user input
    // 2. Validate input data
    // 3. Open file in append mode
    // 4. Write student data in CSV format (ID,FirstName,LastName,GPA)
    // 5. Close file
    // 6. Display success message
    
    printf("=== Add Student ===\n");
    // Implementation here
}

/**
 * Function: displayStudents
 * Purpose: Display all students from the file
 * Parameters: filename - name of the file to read from
 * Returns: void
 */
void displayStudents(const char *filename) {
    // TODO: Implement display functionality
    // 1. Open file in read mode
    // 2. Read each line and parse student data
    // 3. Display in formatted table
    // 4. Handle case when file doesn't exist or is empty
    // 5. Close file
    
    printf("=== All Students ===\n");
    // Implementation here
}

/**
 * Function: searchStudentById
 * Purpose: Search for a student by their ID
 * Parameters: filename - name of the file to search in
 *            id - student ID to search for
 * Returns: void
 */
void searchStudentById(const char *filename, int id) {
    // TODO: Implement search by ID functionality
    // 1. Open file in read mode
    // 2. Read each line and parse student data
    // 3. Compare ID with target ID
    // 4. Display student info if found, or "not found" message
    // 5. Close file
    
    printf("=== Search Student by ID ===\n");
    // Implementation here
}

/**
 * Function: searchStudentByLastName
 * Purpose: Search for students by their last name
 * Parameters: filename - name of the file to search in
 *            lastName - last name to search for
 * Returns: void
 */
void searchStudentByLastName(const char *filename, const char *lastName) {
    // TODO: Implement search by last name functionality
    // 1. Open file in read mode
    // 2. Read each line and parse student data
    // 3. Compare last name (case-insensitive)
    // 4. Display matching students or "not found" message
    // 5. Close file
    
    printf("=== Search Student by Last Name ===\n");
    // Implementation here
}

/**
 * Function: sortStudentsByLastName
 * Purpose: Sort all students by last name and save to file
 * Parameters: filename - name of the file to sort
 * Returns: void
 */
void sortStudentsByLastName(const char *filename) {
    // TODO: Implement sorting functionality
    // 1. Read all student records into an array
    // 2. Implement bubble sort algorithm based on last name
    // 3. Write sorted data back to file
    // 4. Display success message
    
    printf("=== Sorting Students by Last Name ===\n");
    // Implementation here
}

/**
 * Function: displayMenu
 * Purpose: Display the main menu options
 * Returns: void
 */
void displayMenu() {
    printf("\n-- Student Management System --\n");
    printf("1. Add Student\n");
    printf("2. Search Student by ID\n");
    printf("3. Search Student by Last Name\n");
    printf("4. Display Students Sorted by Last Name\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

/**
 * Function: getMenuChoice
 * Purpose: Get and validate user's menu choice
 * Returns: integer representing the user's choice
 */
int getMenuChoice() {
    int choice;
    // TODO: Implement input validation
    // 1. Read user input
    // 2. Validate range (1-5)
    // 3. Handle invalid input
    // 4. Return valid choice
    
    scanf("%d", &choice);
    return choice;
}

/**
 * Main function
 * Purpose: Program entry point, handles menu system
 */
int main() {
    int choice;
    int searchId;
    char searchLastName[MAX_NAME_LENGTH];
    
    printf("Welcome to Student Management System!\n");
    
    // TODO: Implement main program loop
    do {
        // 1. Display menu
        displayMenu();
        
        // 2. Get user choice
        choice = getMenuChoice();
        
        // 3. Handle menu selection using switch statement
        switch (choice) {
            case 1:
                // Add student
                addStudent(FILENAME);
                break;
                
            case 2:
                // Search by ID
                printf("Enter Student ID to search: ");
                scanf("%d", &searchId);
                searchStudentById(FILENAME, searchId);
                break;
                
            case 3:
                // Search by last name
                printf("Enter Last Name to search: ");
                scanf("%s", searchLastName);
                searchStudentByLastName(FILENAME, searchLastName);
                break;
                
            case 4:
                // Display sorted students
                sortStudentsByLastName(FILENAME);
                displayStudents(FILENAME);
                break;
                
            case 5:
                // Exit
                printf("Exiting...\n");
                break;
                
            default:
                // Invalid choice
                printf("Invalid choice! Please enter 1-5.\n");
                break;
        }
        
        // Optional: pause before showing menu again
        if (choice != 5) {
            printf("\nPress Enter to continue...");
            getchar(); // consume newline
            getchar(); // wait for Enter
        }
        
    } while (choice != 5);
    
    printf("Thank you for using Student Management System!\n");
    return 0;
}

/*
 * IMPLEMENTATION NOTES:
 * 
 * Stage 1 - Basic Functionality (2 points):
 * - Implement addStudent() and displayStudents()
 * - Handle file operations properly
 * 
 * Stage 2 - Search Operations (2.5 points):
 * - Implement searchStudentById() and searchStudentByLastName()
 * - Handle "not found" cases
 * 
 * Stage 3 - Sorting Functionality (3 points):
 * - Implement sortStudentsByLastName() using bubble sort
 * - Read data into array, sort, write back to file
 * 
 * Stage 4 - Menu and Error Handling (2.5 points):
 * - Implement robust menu system with do-while loop
 * - Add input validation and error handling
 * - Handle file errors gracefully
 * 
 * FILE FORMAT:
 * Each line in students.txt should follow: ID,FirstName,LastName,GPA
 * Example: 101,John,Doe,3.75
 * 
 * HELPER FUNCTIONS YOU MAY WANT TO ADD:
 * - parseStudentLine() - parse a CSV line into Student struct
 * - validateInput() - validate user input
 * - fileExists() - check if file exists
 * - countStudents() - count number of students in file
 */