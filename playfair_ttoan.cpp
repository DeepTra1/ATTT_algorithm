#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Tạo ma trận 5x5
vector<vector<char>> createMatrix(string key) {
    vector<vector<char>> matrix(5, vector<char>(5));
    bool used[26] = {false};
    used['J' - 'A'] = true; // Bỏ qua J, gộp vào I
    
    string matrixChars = "";
    
    // Xử lý key
    for (char c : key) {
        if (isalpha(c)) {
            char upperC = toupper(c);
            if (upperC == 'J') upperC = 'I';
            if (!used[upperC - 'A']) {
                matrixChars += upperC;
                used[upperC - 'A'] = true;
            }
        }
    }
    
    // Thêm các chữ cái còn lại
    for (char c = 'A'; c <= 'Z'; ++c) {
        if (!used[c - 'A']) {
            matrixChars += c;
            used[c - 'A'] = true;
        }
    }
    
    // Điền vào ma trận 5x5
    int idx = 0;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            matrix[i][j] = matrixChars[idx++];
        }
    }
    return matrix;
}

// Xử lý chuỗi đầu vào (xóa khoảng trắng, thêm X nếu trùng hoặc lẻ)
//Examble:  do you like diddy
//input:    do yo ul ik ed id dy
string prepareText(string text) {
    string filtered = "";
    for (char c : text) {
        if (isalpha(c)) {
            char upperC = toupper(c);
            filtered += (upperC == 'J') ? 'I' : upperC;
        }
    }
    
    string prepared = "";
    for (size_t i = 0; i < filtered.length(); i++) {
        prepared += filtered[i];
        if (i + 1 < filtered.length() && filtered[i] == filtered[i+1]) {
            prepared += 'X';
        } else if (i + 1 < filtered.length()) {
            prepared += filtered[++i];
        } else {
            prepared += 'X'; // Nếu chữ cuối cùng bị lẻ
        }
    }
    return prepared;
}

// Tìm vị trí ký tự trong ma trận
void findPosition(const vector<vector<char>>& matrix, char c, int& row, int& col) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (matrix[i][j] == c) {
                row = i; col = j; return;
            }
        }
    }
}

// Mã hóa
string encryptPlayfair(string plaintext, string key) {
    vector<vector<char>> matrix = createMatrix(key);
    string prepared = prepareText(plaintext);
    string ciphertext = "";
    
    for (size_t i = 0; i < prepared.length(); i += 2) {
        int r1, c1, r2, c2;
        findPosition(matrix, prepared[i], r1, c1);
        findPosition(matrix, prepared[i+1], r2, c2);
        
        if (r1 == r2) { // Cùng hàng
            ciphertext += matrix[r1][(c1 + 1) % 5];
            ciphertext += matrix[r2][(c2 + 1) % 5];
        } else if (c1 == c2) { // Cùng cột
            ciphertext += matrix[(r1 + 1) % 5][c1];
            ciphertext += matrix[(r2 + 1) % 5][c2];
        } else { // Hình chữ nhật
            ciphertext += matrix[r1][c2];
            ciphertext += matrix[r2][c1];
        }
    }
    return ciphertext;
}

int main() {
    string key = "Monarchy";
    string plaintext = "do you like to study a cryptography course";
    
    string prepared = prepareText(plaintext);
    string ciphertext = encryptPlayfair(plaintext, key);
    
    cout << "Plaintext da xu ly: " << prepared << endl;
    cout << "Ciphertext:         " << ciphertext << endl;
    
    return 0;
}