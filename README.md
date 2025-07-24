# Student Management System

**Course:** PRF192 - Programming Fundamental with C  
**Assignment:** Student Management System

## 📋 Overview

A console-based student management system implemented in C that allows users to store, search, and sort student data using text file operations. The system provides a menu-driven interface for managing student records efficiently.

## 🎯 Objectives

- Develop a comprehensive student management system for data storage and retrieval
- Practice file handling operations with text files
- Implement structured programming using modular functions
- Apply sorting algorithms and searching techniques in real-world scenarios

## ✨ Features

### Core Functionality
- **Add Students**: Store new student records with ID, name, and GPA
- **Search by ID**: Find specific students using their unique ID
- **Search by Last Name**: Locate students by their last name
- **Sort & Display**: View all students sorted alphabetically by last name
- **File Persistence**: All data stored in `students.txt` file

### Menu Options
1. Add a new student
2. Search for a student by ID
3. Search for a student by last name
4. Display all students sorted by last name
5. Exit program

## 📊 Data Structure

Each student record contains:
- **ID**: Integer (e.g., 101)
- **First Name**: String (e.g., "John")
- **Last Name**: String (e.g., "Doe")
- **GPA**: Float (e.g., 3.75)

### File Format
Data is stored in `students.txt` with comma-separated values:
```
ID,FirstName,LastName,GPA
```

## 🛠️ Technical Requirements

### Required Functions
```c
void addStudent(const char *filename);
void displayStudents(const char *filename);
void searchStudentById(const char *filename, int id);
void searchStudentByLastName(const char *filename, const char *lastName);
void sortStudentsByLastName(const char *filename);
```

### Technologies Used
- **File Handling**: Reading from and writing to text files
- **String Manipulation**: Handling student names and search operations
- **Sorting Algorithm**: Bubble sort for last name ordering
- **Menu System**: Do-while loops with switch statements
- **Error Handling**: Graceful handling of invalid inputs and file errors

## 🏗️ Program Structure

### Stage 1: Basic Functionality (2 points)
- Implement `addStudent()` function
- Implement `displayStudents()` function
- Handle file operations (open, read, write, close)

### Stage 2: Search Operations (2.5 points)
- Implement search by ID functionality
- Implement search by last name functionality
- Handle cases where no records are found

### Stage 3: Sorting Functionality (3 points)
- Implement bubble sort algorithm for last names
- Write sorted records back to file
- Integration with display function

### Stage 4: Menu & Error Handling (2.5 points)
- Create interactive menu system
- Implement input validation
- Handle file errors and invalid data gracefully

## 📖 Usage Example

```
-- Student Management System --
1. Add Student
2. Search Student by ID
3. Search Student by Last Name
4. Display Students Sorted by Last Name
5. Exit
Enter your choice: 1

Enter Student ID: 101
Enter First Name: John
Enter Last Name: Doe
Enter GPA: 3.75
Student added successfully.
```

### Search Results Display
```
Student Found:
--------------------------------
ID: 101
First Name: John
Last Name: Doe
GPA: 3.75
```

### Sorted Display Format
```
Students Sorted by Last Name:
------------------------------------------------------------
ID    First Name    Last Name    GPA
------------------------------------------------------------
103   Bob           Allen        3.50
101   John          Doe          3.75
102   Alice         Smith        3.90
```

## 🏁 Getting Started

### 1. **Project Structure**

To build and run the project, make sure you have the following files in your project directory:

```
/PRF192-assignment
│
├── main.c          # Contains the main function and menu logic
├── student.c       # Implements all student management functions
├── student.h       # Defines Student struct and function prototypes
├── students.txt    # Text file to store student records (auto-created if missing)
└── README.md       # Documentation
```

### 2. **Building and Running (Dev-C++ or GCC)**

#### **With Dev-C++ IDE**

1. **Create a new Console Application project** (C language).
2. **Add all source files to your project**:  
   - Go to `Project → Add to Project...` and select both `main.c`, `student.c`, and `student.h`.
3. **Place `students.txt` in the project directory** (add sample data if you wish).
4. **Build & Run the project** using `F9` (Build & Run).

#### **With GCC (command line)**

Open terminal in the project folder and run:
```sh
gcc main.c student.c -o student_manager
./student_manager
```

### 3. **Mock Data Example**
You can create (or use) a sample `students.txt` file:
```csv
101,John,Doe,3.75
102,Anna,Smith,3.90
103,Peter,Johnson,2.85
104,Linda,Brown,3.65
```
The program will update and append new students to this file without erasing existing records.

## 🗂️ File Structure

- **main.c**  
  Contains the entry point (`main()`) and menu system.

- **student.h**  
  Declares the `Student` struct and all function prototypes for managing students.

- **student.c**  
  Implements all logic for adding, searching (by ID/last name), displaying, sorting students, and file handling.

- **students.txt**  
  Stores student records in CSV format:  
  ```
  ID,FirstName,LastName,GPA
  ```
  The file is read and updated automatically by the program.

## 🔧 Implementation Notes

- The program uses comma-separated values for data storage
- Bubble sort algorithm is implemented for sorting by last name
- File operations include proper error checking
- Menu system provides continuous operation until user exits
- All functions are modular and reusable

## ⚠️ Error Handling

The system handles:
- Invalid menu choices
- File access errors
- Missing student records
- Invalid data formats
- Memory allocation issues

## 📈 Evaluation Criteria

- **Basic Functionality**: File operations and data management
- **Search Operations**: Accurate ID and name-based searching
- **Sorting Algorithm**: Correct implementation of bubble sort
- **User Interface**: Robust menu system with error handling

## 👥 Contributing

This is an academic assignment. Follow your institution's guidelines regarding collaboration and academic integrity.

## 📄 License

Educational use only - Part of PRF192 coursework.