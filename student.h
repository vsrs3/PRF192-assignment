#ifndef STUDENT_H         
#define STUDENT_H

#define MAX_NAME_LEN 50     // Khai báo giá trị tối đa cho chiều dài tên (họ/tên) của sinh viên.
#define MAX_STUDENTS 1000   // Khai báo số lượng sinh viên tối đa có thể quản lý.

typedef struct {
    int id;                 // Mã số sinh viên (duy nhất cho mỗi sinh viên).
    char firstName[MAX_NAME_LEN]; // Tên sinh viên (ví dụ: "Nam").
    char lastName[MAX_NAME_LEN];  // Họ sinh viên (ví dụ: "Nguyễn").
    float gpa;              // Điểm trung bình tích lũy (GPA) của sinh viên.
} Student;                  // Định nghĩa cấu trúc Student lưu thông tin một sinh viên.

void addStudent(const char *filename);              // Hàm thêm sinh viên mới và lưu vào file.
void displayStudents(const char *filename);         // Hàm hiển thị danh sách sinh viên từ file.
void searchStudentById(const char *filename, int id);           // Hàm tìm kiếm sinh viên theo mã số.
void searchStudentByLastName(const char *filename, const char *lastName); // Hàm tìm kiếm sinh viên theo họ.
void sortStudentsByLastName(const char *filename);  // Hàm sắp xếp danh sách sinh viên theo họ.

#endif                   	// Kết thúc khối kiểm tra định nghĩa.