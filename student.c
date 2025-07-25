#include <stdio.h>        
#include <stdlib.h>       
#include <string.h>       
#include <ctype.h>        
#include <limits.h>       
#include "student.h"      // Bao gồm file header định nghĩa cấu trúc và hàm.

/*******************************************************
 *           		NHÓM KHAI BÁO HÀM                  *
 *******************************************************/
int loadStudents(const char *filename, Student students[], int *count);
int saveStudents(const char *filename, Student students[], int count);
void toLowerStr(char *str);
int isValidPositiveInt(const char *str);
void trimAndValidateName(char *name, const char *fieldName);
void capitalizeWords(char *str);

int inputStudentId(Student students[], int count);
void inputStudentName(char *name, const char *fieldName);
float inputStudentGpa();

void addStudent(const char *filename);
void displayStudents(const char *filename);
void searchStudentById(const char *filename, int id);
void searchStudentByLastName(const char *filename, const char *lastName);
void sortStudentsByLastName(const char *filename);

/**************************************************************
 *            												  *
 *  	NHÓM HÀM CHÍNH XỬ LÝ CHỨC NĂNG QUẢN LÝ SINH VIÊN      *
 *           												  *
 **************************************************************/

/*
 * Hàm addStudent:
 * Thêm một sinh viên mới vào file danh sách sinh viên.
 * Đọc danh sách sinh viên hiện có từ file.
 * Kiểm tra danh sách đã đầy chưa.
 * Nhập và kiểm tra hợp lệ mã số sinh viên, họ, tên, GPA.
 * Thêm sinh viên vào mảng.
 * Ghi lại toàn bộ danh sách ra file.
 */
void addStudent(const char *filename) {
    Student students[MAX_STUDENTS]; // Mảng lưu danh sách sinh viên
    int count = 0; // Số lượng sinh viên hiện có
    loadStudents(filename, students, &count); // Đọc dữ liệu từ file

    // Kiểm tra số lượng sinh viên đã đầy chưa
    if (count >= MAX_STUDENTS) {
        printf("Student list is full!\n");
        return;
    }

    Student s; // Biến lưu thông tin sinh viên mới

    // Nhập và kiểm tra mã số sinh viên hợp lệ, không trùng
    s.id = inputStudentId(students, count);

    // Nhập và kiểm tra hợp lệ tên sinh viên
    inputStudentName(s.firstName, "first name");

    // Nhập và kiểm tra hợp lệ họ sinh viên
    inputStudentName(s.lastName, "last name");

    // Nhập và kiểm tra hợp lệ GPA
    s.gpa = inputStudentGpa();

    // Thêm sinh viên mới vào mảng
    students[count++] = s;

    // Ghi danh sách sinh viên mới ra file
    if (saveStudents(filename, students, count)) {
        printf("Student added successfully.\n");
    } else {
        printf("Error writing to file!\n");
    }
}

/*
 * Hàm displayStudents:
 * Hiển thị danh sách sinh viên lên màn hình.
 * Đọc toàn bộ sinh viên từ file và in theo định dạng bảng.
 */
void displayStudents(const char *filename) {
    Student students[MAX_STUDENTS]; // Mảng lưu danh sách sinh viên.
    int count = 0; // Biến lưu số lượng sinh viên.
    if (!loadStudents(filename, students, &count)) { // Đọc danh sách từ file, kiểm tra thành công.
        printf("Cannot read file!\n");
        return;
    }
    printf("Student list:\n");
    printf("%-5s %-15s %-15s %-5s\n", "ID", "Last Name", "First Name", "GPA"); // In tiêu đề bảng.
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) { // Duyệt mảng sinh viên và in ra từng dòng.
        printf("%d\t%-15s%-15s%.2f\n", students[i].id, students[i].lastName, students[i].firstName, students[i].gpa);
    }
}

/*
 * Hàm searchStudentById:
 * Tìm kiếm sinh viên theo mã số đã nhập.
 * Nếu tìm thấy thì hiển thị thông tin sinh viên đó, ngược lại báo không tìm thấy.
 */
void searchStudentById(const char *filename, int id) {
    Student students[MAX_STUDENTS]; // Mảng lưu danh sách sinh viên.
    int count = 0;
    int found = 0; // Biến kiểm tra đã tìm thấy chưa.
    if (!loadStudents(filename, students, &count)) {
        printf("Cannot read file!\n");
        return;
    }
    for (int i = 0; i < count; i++) { // Duyệt từng sinh viên trong danh sách.
        if (students[i].id == id) { // So sánh mã số.
            printf("Student found:\n");
            printf("ID: %d\nLast Name: %s\nFirst Name: %s\nGPA: %.2f\n",
                   students[i].id, students[i].lastName, students[i].firstName, students[i].gpa);
            found = 1; // Đánh dấu đã tìm thấy.
            break; // Kết thúc vòng lặp.
        }
    }
    if (!found) printf("No student found with this ID.\n"); // Nếu không tìm thấy.
}

/*
 * Hàm searchStudentByLastName:
 * Tìm kiếm tất cả sinh viên có họ trùng với họ nhập vào (không phân biệt hoa/thường).
 * Hiển thị danh sách các sinh viên tìm được.
 */
void searchStudentByLastName(const char *filename, const char *lastName) {
    Student students[MAX_STUDENTS]; // Mảng lưu danh sách sinh viên.
    int count = 0;
    int found = 0;
    if (!loadStudents(filename, students, &count)) {
        printf("Cannot read file!\n");
        return;
    }
    char query[MAX_NAME_LEN];
    strncpy(query, lastName, MAX_NAME_LEN); // Sao chép họ cần tìm vào query.
    toLowerStr(query); // Chuyển họ cần tìm sang chữ thường.

    for (int i = 0; i < count; i++) {
        char temp[MAX_NAME_LEN];
        strncpy(temp, students[i].lastName, MAX_NAME_LEN); // Sao chép họ của sinh viên vào temp.
        toLowerStr(temp); // Chuyển họ sinh viên sang chữ thường.
        if (strcmp(temp, query) == 0) { // So sánh với họ cần tìm (không phân biệt hoa/thường).
            if (!found) { // Nếu là sinh viên đầu tiên tìm thấy, in tiêu đề bảng.
                printf("Search results:\n");
                printf("%-5s %-15s %-15s %-5s\n", "ID", "Last Name", "First Name", "GPA");
                printf("-------------------------------------------------------------\n");
            }
            printf("%d\t%-15s%-15s%.2f\n", students[i].id, students[i].lastName, students[i].firstName, students[i].gpa);
            found = 1; // Đánh dấu đã tìm thấy.
        }
    }
    if (!found) printf("No student found with this last name.\n");
}

/*
 * Hàm sortStudentsByLastName:
 * Sắp xếp danh sách sinh viên theo họ (sử dụng thuật toán Bubble Sort).
 * Nếu họ trùng nhau thì tiếp tục so sánh theo tên.
 * Sau khi sắp xếp sẽ lưu lại file và hiển thị danh sách mới.
 */
void sortStudentsByLastName(const char *filename) {
    Student students[MAX_STUDENTS]; // Mảng lưu danh sách sinh viên.
    int count = 0;
    if (!loadStudents(filename, students, &count)) {
        printf("Cannot read file!\n");
        return;
    }
    // Thuật toán Bubble Sort: so sánh và đổi chỗ sinh viên theo họ, nếu họ giống nhau thì so sánh tên.
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
        printf("List sorted and saved to file.\n");
    } else {
        printf("Error writing to file!\n");
    }
    displayStudents(filename); // Hiển thị danh sách sau khi sắp xếp.
}


/**************************************************************
 *    NHÓM HÀM HỖ TRỢ ĐẦU VÀO CHO addStudent (NHẬP/LÀM SẠCH) *
 *  Bao gồm: inputStudentId, inputStudentName, inputStudentGpa*
 **************************************************************/

/*
 * Hàm inputStudentId:
 * Nhập mã số sinh viên từ bàn phím, kiểm tra xem có phải số nguyên dương không,
 * đồng thời kiểm tra mã số này đã tồn tại trong danh sách sinh viên chưa.
 * Nếu hợp lệ và chưa trùng, trả về ID vừa nhập.
 */
int inputStudentId(Student students[], int count) {
    char buf[100]; // Mảng ký tự để lưu chuỗi nhập vào
    int valid = 0, enteredId;
    do {
        // Yêu cầu người dùng nhập mã số sinh viên là số nguyên dương
        printf("Enter student ID (positive integer): ");
        if (!fgets(buf, sizeof(buf), stdin)) {
            // Nếu đọc lỗi thì thông báo và nhập lại
            printf("Input error!\n");
            continue;
        }
        // Loại bỏ ký tự xuống dòng nếu có
        buf[strcspn(buf, "\n")] = '\0';
        // Kiểm tra chuỗi nhập vào có phải số nguyên dương không
        if (!isValidPositiveInt(buf)) {
            printf("ID must be a positive integer and contain only digits!\n");
            continue;
        }
        enteredId = atoi(buf); // Chuyển chuỗi thành số nguyên
        int duplicated = 0;
        // Kiểm tra mã số vừa nhập có bị trùng không
        for (int i = 0; i < count; i++) {
            if (students[i].id == enteredId) {
                printf("ID already exists! Please enter another ID.\n");
                duplicated = 1;
                break;
            }
        }
        if (duplicated) continue; // Nếu bị trùng thì nhập lại
        valid = 1; // Đánh dấu nhập thành công
    } while (!valid); // Lặp đến khi nhập đúng và không trùng
    return enteredId; // Trả về ID hợp lệ
}

/*
 * Hàm inputStudentName:
 * Nhập họ hoặc tên sinh viên, sau đó chuẩn hóa và kiểm tra hợp lệ.
 * Nếu không hợp lệ thì yêu cầu nhập lại.
 * Sau khi hợp lệ, tự động viết hoa chữ cái đầu mỗi từ.
 */
void inputStudentName(char *name, const char *fieldName) {
    do {
        // In thông báo nhập họ hoặc tên
        printf("Enter %s: ", fieldName);
        // Đọc chuỗi nhập vào từ bàn phím
        fgets(name, MAX_NAME_LEN, stdin);
        // Loại bỏ ký tự xuống dòng nếu có
        name[strcspn(name, "\n")] = '\0';
        // Chuẩn hóa và kiểm tra hợp lệ tên/họ
        trimAndValidateName(name, fieldName);
        // Nếu hợp lệ thì viết hoa chữ cái đầu mỗi từ
        if (strlen(name) > 0) {
            capitalizeWords(name);
        }
    } while (strlen(name) == 0); // Lặp đến khi nhập hợp lệ
}

/*
 * Hàm inputStudentGpa:
 * Nhập điểm GPA, kiểm tra hợp lệ (là số, nằm trong khoảng 0-10).
 * Nếu không hợp lệ thì yêu cầu nhập lại.
 * Trả về GPA hợp lệ.
 */
float inputStudentGpa() {
    float gpa = -1;
    do {
        // Thông báo nhập GPA
        printf("Enter GPA (0-10): ");
        // Kiểm tra nhập có đúng kiểu số không
        if (scanf("%f", &gpa) != 1) {
            printf("GPA must be a number between 0 and 10!\n");
            // Xóa bộ đệm nhập nếu nhập sai
            while(getchar()!='\n');
            gpa = -1;
            continue;
        }
        // Kiểm tra GPA có nằm trong khoảng hợp lệ không
        if (gpa < 0 || gpa > 10)
            printf("GPA must be between 0 and 10. Please re-enter.\n");
    } while (gpa < 0 || gpa > 10); // Lặp đến khi nhập hợp lệ
    // Xóa bộ đệm nhập để chuẩn bị cho lần nhập tiếp theo
    while(getchar()!='\n');
    return gpa; // Trả về GPA hợp lệ
}


/********************************************************************
 *        															*
 *   NHÓM HÀM HỖ TRỢ XỬ LÝ CHUNG/ĐỊNH DẠNG CHUỖI VÀ FILE DỮ LIỆU    *
 *																	*		
 ********************************************************************/

/* 
 * Hàm loadStudents:
 * Đọc danh sách sinh viên từ file và lưu vào mảng students.
 * Trả về 1 nếu thành công, 0 nếu thất bại (ví dụ: không mở được file).
 * Mỗi dòng file có định dạng: id,firstName,lastName,gpa
 * Biến count nhận về số lượng sinh viên đã đọc.
 */
int loadStudents(const char *filename, Student students[], int *count) {
    FILE *f = fopen(filename, "r"); // Mở file ở chế độ đọc ("r")
    if (!f) return 0; // Nếu không mở được file (con trỏ NULL), trả về 0 (thất bại)
    *count = 0; // Khởi tạo số lượng sinh viên đã đọc về 0
    // Vòng lặp đọc từng dòng dữ liệu sinh viên từ file
    while (fscanf(f, "%d,%49[^,],%49[^,],%f\n",
                  &students[*count].id,          
                  students[*count].firstName,     
                  students[*count].lastName,      
                  &students[*count].gpa) == 4) {  // Đọc trường gpa (float), chỉ tiếp tục nếu đọc đủ 4 giá trị
        (*count)++;                              // Tăng biến đếm số lượng sinh viên đã đọc
        if (*count >= MAX_STUDENTS) break;       // Nếu đã đạt số sinh viên tối đa thì dừng lại
    }
    fclose(f); // Đóng file lại để giải phóng tài nguyên
    return 1;  // Trả về 1 (thành công)
}

/*
 * Hàm saveStudents:
 * Ghi danh sách sinh viên từ mảng students ra file.
 * Trả về 1 nếu ghi thành công, 0 nếu thất bại (ví dụ: không mở được file).
 * Ghi lần lượt từng sinh viên theo định dạng: id,firstName,lastName,gpa
 */
int saveStudents(const char *filename, Student students[], int count) {
    FILE *f = fopen(filename, "w"); // Mở file ở chế độ ghi ("w"), nếu không có file sẽ tạo mới
    if (!f) return 0; // Nếu không mở được file (con trỏ NULL), trả về 0 (thất bại)
    for (int i = 0; i < count; i++) { // Duyệt qua từng sinh viên trong mảng
        // Ghi thông tin từng sinh viên ra file với định dạng: id,firstName,lastName,gpa
        // Sử dụng %.2f để ghi gpa với 2 số lẻ thập phân
        fprintf(f, "%d,%s,%s,%.2f\n", students[i].id, students[i].firstName, students[i].lastName, students[i].gpa);
    }
    fclose(f); // Đóng file lại để đảm bảo dữ liệu được ghi xong và giải phóng tài nguyên
    return 1;  // Trả về 1 (thành công)
}

/*
 * Hàm toLowerStr:
 * Chuyển chuỗi ký tự đầu vào sang toàn bộ chữ thường.
 * Dùng cho so sánh chuỗi không phân biệt hoa/thường (ví dụ khi tìm kiếm).
 */
void toLowerStr(char *str) {
    for (; *str; ++str) *str = tolower(*str);
}

/*
 * Hàm trimAndValidateName:
 * Chuẩn hóa và kiểm tra hợp lệ cho trường tên/họ của sinh viên.
 * - Loại bỏ khoảng trắng đầu/cuối chuỗi.
 * - Giữa các từ chỉ giữ một khoảng trắng.
 * - Chỉ cho phép chữ cái và dấu nháy đơn (').
 * Nếu không hợp lệ thì name sẽ là chuỗi rỗng.
 */
void trimAndValidateName(char *name, const char *fieldName) {
    int start = 0; // Vị trí bắt đầu của chuỗi sau khi bỏ khoảng trắng đầu.
    while (isspace((unsigned char)name[start])) start++;

    int end = strlen(name) - 1; // Vị trí kết thúc của chuỗi sau khi bỏ khoảng trắng cuối.
    while (end >= start && isspace((unsigned char)name[end])) end--;

    char cleaned[MAX_NAME_LEN]; // Chuỗi đã chuẩn hóa.
    int idx = 0, prevSpace = 0; // idx: vị trí ghi ký tự vào cleaned, prevSpace: kiểm tra khoảng trắng liên tục.
    for (int i = start; i <= end && idx < MAX_NAME_LEN - 1; i++) {
        char c = name[i];
        if (isspace((unsigned char)c)) { // Nếu là khoảng trắng
            if (!prevSpace && idx > 0) { // Nếu trước đó không phải khoảng trắng, thêm một khoảng trắng vào cleaned.
                cleaned[idx++] = ' ';
                prevSpace = 1;
            }
        } else { // Nếu là ký tự khác khoảng trắng
            if (!(isalpha(c) || c == '\'')) { // Nếu không phải chữ cái hoặc dấu nháy đơn
                printf("%s must contain only alphabetic characters, spaces, or apostrophes ('). Please re-enter.\n", fieldName);
                name[0] = '\0'; // Gán chuỗi rỗng để báo lỗi.
                return;
            }
            cleaned[idx++] = c; // Ghi ký tự hợp lệ vào cleaned.
            prevSpace = 0;
        }
    }
    cleaned[idx] = '\0'; // Kết thúc chuỗi đã chuẩn hóa.
    strcpy(name, cleaned); // Gán lại kết quả cho biến name.
}

/*
 * Hàm isValidPositiveInt:
 * - Bỏ qua các ký tự trắng đầu/cuối.
 * - Kiểm tra toàn bộ ký tự (trừ ký tự xuống dòng) đều là số.
 * - Chuyển thành số và trả về true nếu > 0.
 * Trả về 1 nếu là số nguyên dương, ngược lại trả về 0.
 */
int isValidPositiveInt(const char *str) {
    // Bỏ qua khoảng trắng ở đầu chuỗi
    while (*str && isspace((unsigned char)*str)) str++;
    if (*str == '\0') return 0; // Nếu chuỗi rỗng thì không hợp lệ

    // Duyệt từng ký tự trong chuỗi
    for (const char *p = str; *p; ++p) {
        // Nếu gặp ký tự xuống dòng hoặc kết thúc chuỗi thì dừng kiểm tra
        if (*p == '\n' || *p == '\r') break;
        // Nếu không phải ký tự số thì trả về 0 (không hợp lệ)
        if (!isdigit((unsigned char)*p)) return 0;
    }

    // Chuyển chuỗi thành số nguyên
    int val = atoi(str);
    // Kiểm tra số đó có lớn hơn 0 không (phải là số nguyên dương)
    return val > 0;
}

/*
 * Hàm capitalizeWords:
 * Viết hoa chữ cái đầu tiên của mỗi từ trong chuỗi (các từ cách nhau bởi khoảng trắng).
 * Các ký tự còn lại của từ sẽ được chuyển thành chữ thường.
 */
void capitalizeWords(char *str) {
    int inWord = 0;
    for (int i = 0; str[i]; i++) {
        if (!isspace((unsigned char)str[i])) {
            if (!inWord) { // Nếu là ký tự đầu tiên của từ
                str[i] = toupper((unsigned char)str[i]);
                inWord = 1;
            } else {
                str[i] = tolower((unsigned char)str[i]);
            }
        } else {
            inWord = 0; // Gặp khoảng trắng, chuẩn bị sang từ mới
        }
    }
}