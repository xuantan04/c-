#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

// Hàm nén d? li?u Lempel-Ziv-Welch
std::vector<int> compress(const std::string& data) {
    std::unordered_map<std::string, int> dictionary;
    std::vector<int> compressedData;

    std::string current;
    for (char c : data) {
        std::string combined = current + c;
        if (dictionary.find(combined) != dictionary.end()) {
            // N?u chu?i hi?n t?i k?t h?p v?i ký t? ti?p theo dã t?n t?i trong t? di?n
            // Ti?p t?c m? r?ng chu?i hi?n t?i
            current = combined;
        } else {
            // N?u chu?i hi?n t?i k?t h?p không t?n t?i trong t? di?n
            // Ghi mã cho chu?i hi?n t?i vào d? li?u nén và thêm chu?i hi?n t?i k?t h?p vào t? di?n
            compressedData.push_back(dictionary[current]);
            dictionary[combined] = dictionary.size();
            current = std::string(1, c);
        }
    }

    // Ghi mã cho chu?i hi?n t?i vào d? li?u nén
    if (!current.empty()) {
        compressedData.push_back(dictionary[current]);
    }

    return compressedData;
}

// Hàm gi?i nén d? li?u Lempel-Ziv-Welch
std::string decompress(const std::vector<int>& compressedData) {
    std::unordered_map<int, std::string> dictionary;
    std::string decompressedData;

    // Kh?i t?o b?ng t? di?n ban d?u cho các ký t? don
    for (int i = 0; i < 256; i++) {
        dictionary[i] = std::string(1, static_cast<char>(i));
    }

    int nextCode = 256;
    for (int code : compressedData) {
        if (dictionary.find(code) != dictionary.end()) {
            // N?u mã dã t?n t?i trong t? di?n
            std::string entry = dictionary[code];
            decompressedData += entry;

            // Thêm chu?i k?t h?p c?a chu?i hi?n t?i và ký t? d?u tiên c?a chu?i entry vào t? di?n
            dictionary[nextCode++] = current + entry[0];
        } else {
            // N?u mã chua t?n t?i trong t? di?n
            // L?y chu?i tuong ?ng c?a mã tru?c dó và thêm ký t? d?u tiên c?a chu?i dó vào
            std::string entry = current + current[0];
            decompressedData += entry;

            // Thêm chu?i entry vào t? di?n
            dictionary[nextCode++] = entry;
        }
        current = entry;
    }

    return decompressedData;
}

int main() {
    std::string input;
    std::cout << "Enter the input data: ";
    std::getline(std::cin, input);

    std::string operation;
    std::cout << "Enter the operation (C for compress, D for decompress): ";
    std::cin >> operation;

    if (operation == "C") {
        std::vector<int> compressedData = compress(input);
        std::cout << "Compressed data: ";
        for (int code : compressedData) {
            std::cout << code << ", ";
        }
        std::cout << std::endl;
    } else if (operation == "D") {
        std::vector<int> compressedData;
        std::cout << "Enter the compressed data (separated by commas): ";
        std::string codeString;
        std::getline(std::cin >> std::ws, codeString);

        size_t startPos = 0;
        size_t commaPos = codeString.find(',', startPos);
        while (commaPos != std::string::npos) {
            std::string code = codeString.substr(startPos, commaPos - startPos);
            compressedData.push_back(std::stoi(code));
            startPos = commaPos + 1;
            commaPos = codeString.find(',', startPos);
        }

        std::string code = codeString.substr(startPos);
        compressedData.push_back(std::stoi(code));

        std::string decompressedData = decompress(compressedData);
        std::cout << "Decompressed data: " << decompressedData << std::endl;
