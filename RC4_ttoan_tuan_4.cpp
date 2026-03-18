#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Bước 1: Hàm KSA (Key-Scheduling Algorithm)
// Khởi tạo mảng hoán vị S dựa trên khóa (key)
vector<int> KSA(const string& key) {
    vector<int> S(256);
    // Khởi tạo mảng S từ 0 đến 255
    for (int i = 0; i < 256; i++) {
        S[i] = i;
    }

    int j = 0;
    int key_length = key.length();
    
    // Trộn mảng S dựa vào khóa
    for (int i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % key_length]) % 256;
        swap(S[i], S[j]);
    }
    return S;
}

// Bước 2 & 3: Hàm PRGA (Pseudo-Random Generation Algorithm) và XOR
// Hàm này vừa sinh luồng khóa (keystream) vừa thực hiện XOR với dữ liệu gốc
vector<unsigned char> RC4(const string& key, const string& data) {
    vector<int> S = KSA(key);
    vector<unsigned char> result;
    
    int i = 0;
    int j = 0;
    
    for (size_t n = 0; n < data.length(); n++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]); // Hoán đổi S[i] và S[j]
        
        // Lấy giá trị K từ mảng S
        int K = S[(S[i] + S[j]) % 256];
        
        // XOR byte dữ liệu gốc với byte khóa K
        result.push_back(data[n] ^ K);
    }
    
    return result;
}

int main() {
    string key = "khoabimat";
    string plaintext = "Xin chao VS Code bang C++!";

    cout << "--- THUAT TOAN MA HOA RC4 (C++) ---\n";
    cout << "Khoa (Key): " << key << "\n";
    cout << "Van ban goc: " << plaintext << "\n";

    // 1. Mã hóa
    vector<unsigned char> ciphertext = RC4(key, plaintext);
    
    cout << "Ban ma (Hex): ";
    for (unsigned char c : ciphertext) {
        // In ra dưới định dạng Hex (hệ cơ số 16) in hoa, đủ 2 chữ số
        cout << hex << uppercase << setfill('0') << setw(2) << (int)c;
    }
    cout << dec << "\n"; // Trả lại định dạng thập phân mặc định cho cout

    // 2. Giải mã
    // Chuyển bản mã (vector<unsigned char>) sang chuỗi (string) để đưa lại vào hàm RC4
    string ciphertext_str(ciphertext.begin(), ciphertext.end());
    vector<unsigned char> decrypted = RC4(key, ciphertext_str);
    
    cout << "Van ban giai ma: ";
    for (unsigned char c : decrypted) {
        cout << c;
    }
    cout << "\n";

    return 0;
}