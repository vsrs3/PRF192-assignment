#include <stdio.h>        
#include <stdlib.h>       
#include <string.h>       
#include <ctype.h>        
#include <limits.h>       
#include "student.h"      // Bao gồm file header định nghĩa cấu trúc và hàm.

//Các hàm không có body này gọi là khai báo hàm để đảm bảo thứ tự biên dịch nhé
int loadStudents(const char *filename, Student students[], int *count);

int saveStudents(const char *filename, Student students[], int count);

void toLowerStr(char *str);

void trimAndValidateName(char *name, const char *fieldName);

int isValidPositiveInt(const char *str);

/*
 * Hàm addStudent:
 * Thêm một sinh viên mới vào file.
 * - Đọc danh sách hiện có từ file.
 * - Kiểm tra trùng mã số sinh viên.
 * - Nhập tên, họ, GPA và kiểm tra hợp lệ.
 * - Lưu sinh viên mới vào mảng, ghi lại toàn bộ ra file.
 */
void addStudent(const char *filename) {
    Student students[MAX_STUDENTS]; // Mảng lưu danh sách sinh viên.
    int count = 0; // Biến lưu số lượng sinh viên hiện tại.
    loadStudents(filename, students, &count); // Đọc danh sách sinh viên hiện có từ file.

    if (count >= MAX_STUDENTS) { // Kiểm tra số lượng sinh viên vượt quá giới hạn chưa.
        printf("Student list is full!\n");
        return;
    }

    Student s; // Khai báo biến lưu thông tin sinh viên cần thêm.

	char buf[100]; // Khai báo mảng ký tự để lưu chuỗi nhập ID
	int valid = 0; // Biến cờ để xác định khi nào nhập ID hợp lệ
	do {
	    // In thông báo yêu cầu người dùng nhập mã số sinh viên là số nguyên dương
	    printf("Enter student ID (positive integer): ");
	    // Đọc một dòng ký tự từ bàn phím vào biến buf
	    if (!fgets(buf, sizeof(buf), stdin)) {
	        // Nếu không đọc được dữ liệu đầu vào thì thông báo lỗi
	        printf("Input error!\n");
	        continue; // Quay lại đầu vòng lặp để nhập lại
	    }
	    // Xóa ký tự xuống dòng ở cuối chuỗi (nếu có)
	    buf[strcspn(buf, "\n")] = '\0';
	    // Kiểm tra chuỗi nhập vào có phải là số nguyên dương không
	    if (!isValidPositiveInt(buf)) {
	        // Nếu không hợp lệ thì thông báo lỗi và nhập lại
	        printf("ID must be a positive integer and contain only digits!\n");
	        continue; // Quay lại đầu vòng lặp để nhập lại
	    }
	    int enteredId = atoi(buf); // Chuyển chuỗi thành số nguyên để kiểm tra trùng
	
	    int duplicated = 0; // Biến cờ để kiểm tra ID có bị trùng không
	    // Duyệt qua danh sách sinh viên hiện có để kiểm tra trùng lặp
	    for (int i = 0; i < count; i++) {
	        if (students[i].id == enteredId) {
	            // Nếu ID đã tồn tại thì thông báo lỗi
	            printf("ID already exists! Please enter another ID.\n");
	            duplicated = 1; // Đánh dấu ID bị trùng
	            break; // Thoát khỏi vòng lặp kiểm tra trùng
	        }
	    }
	    if (duplicated) continue; // Nếu bị trùng thì quay lại đầu vòng lặp để nhập lại
	
	    s.id = enteredId; // Gán giá trị ID hợp lệ cho sinh viên mới
	    valid = 1; // Đánh dấu đã nhập ID thành công
	} while (!valid); // Lặp lại cho đến khi nhập được ID hợp lệ và không trùng


    // Nhập tên, kiểm tra hợp lệ
    do {
        printf("Enter first name: ");
        fgets(s.firstName, MAX_NAME_LEN, stdin); // Nhập tên sinh viên.
        s.firstName[strcspn(s.firstName, "\n")] = '\0'; // Xóa ký tự xuống dòng.
        trimAndValidateName(s.firstName, "First name"); // Chuẩn hóa, kiểm tra tên.
    } while (strlen(s.firstName) == 0); // Lặp lại nếu tên không hợp lệ.

    // Nhập họ, kiểm tra hợp lệ
    do {
        printf("Enter last name: ");
        fgets(s.lastName, MAX_NAME_LEN, stdin); // Nhập họ sinh viên.
        s.lastName[strcspn(s.lastName, "\n")] = '\0'; // Xóa ký tự xuống dòng.
        trimAndValidateName(s.lastName, "Last name"); // Chuẩn hóa, kiểm tra họ.
    } while (strlen(s.lastName) == 0); // Lặp lại nếu họ không hợp lệ.

    // Nhập GPA, kiểm tra hợp lệ
    do {
        printf("Enter GPA (0-10): ");
        if (scanf("%f", &s.gpa) != 1) { // Kiểm tra nhập GPA là số hay không.
            printf("GPA must be a number between 0 and 10!\n");
            while(getchar()!='\n'); // Xóa bộ đệm nhập.
            s.gpa = -1;
            continue;
        }
        if (s.gpa < 0 || s.gpa > 10) // Kiểm tra GPA nằm trong khoảng hợp lệ.
            printf("GPA must be between 0 and 10. Please re-enter.\n");
    } while (s.gpa < 0 || s.gpa > 10);

    students[count++] = s; // Thêm sinh viên mới vào mảng.

    if (saveStudents(filename, students, count)) { // Ghi danh sách mới ra file.
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


/**************************
 *   HELPER FUNCTION      *
 **************************/

/* 
 * Hàm loadStudents:
 * Đọc danh sách sinh viên từ file và lưu vào mảng students.
 * Trả về 1 nếu thành công, 0 nếu thất bại (ví dụ: không mở được file).
 * Mỗi dòng file có định dạng: id,firstName,lastName,gpa
 * Biến count nhận về số lượng sinh viên đã đọc.
 */
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

/*
 * Hàm saveStudents:
 * Ghi danh sách sinh viên từ mảng students ra file.
 * Trả về 1 nếu ghi thành công, 0 nếu thất bại (ví dụ: không mở được file).
 * Ghi lần lượt từng sinh viên theo định dạng: id,firstName,lastName,gpa
 */
int saveStudents(const char *filename, Student students[], int count) {
    FILE *f = fopen(filename, "w");
    if (!f) return 0;
    for (int i = 0; i < count; i++) {
        fprintf(f, "%d,%s,%s,%.2f\n", students[i].id, students[i].firstName, students[i].lastName, students[i].gpa);
    }
    fclose(f);
    return 1;
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