#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

// H�m n�n d? li?u Lempel-Ziv-Welch
std::vector<int> compress(const std::string& data) {
    std::unordered_map<std::string, int> dictionary;
    std::vector<int> compressedData;

    std::string current;
    for (char c : data) {
        std::string combined = current + c;
        if (dictionary.find(combined) != dictionary.end()) {
            // N?u chu?i hi?n t?i k?t h?p v?i k� t? ti?p theo d� t?n t?i trong t? di?n
            // Ti?p t?c m? r?ng chu?i hi?n t?i
            current = combined;
        } else {
            // N?u chu?i hi?n t?i k?t h?p kh�ng t?n t?i trong t? di?n
            // Ghi m� cho chu?i hi?n t?i v�o d? li?u n�n v� th�m chu?i hi?n t?i k?t h?p v�o t? di?n
            compressedData.push_back(dictionary[current]);
            dictionary[combined] = dictionary.size();
            current = std::string(1, c);
        }
    }

    // Ghi m� cho chu?i hi?n t?i v�o d? li?u n�n
    if (!current.empty()) {
        compressedData.push_back(dictionary[current]);
    }

    return compressedData;
}

// H�m gi?i n�n d? li?u Lempel-Ziv-Welch
std::string decompress(const std::vector<int>& compressedData) {
    std::unordered_map<int, std::string> dictionary;
    std::string decompressedData;

    // Kh?i t?o b?ng t? di?n ban d?u cho c�c k� t? don
    for (int i = 0; i < 256; i++) {
        dictionary[i] = std::string(1, static_cast<char>(i));
    }

    int nextCode = 256;
    for (int code : compressedData) {
        if (dictionary.find(code) != dictionary.end()) {
            // N?u m� d� t?n t?i trong t? di?n
            std::string entry = dictionary[code];
            decompressedData += entry;

            // Th�m chu?i k?t h?p c?a chu?i hi?n t?i v� k� t? d?u ti�n c?a chu?i entry v�o t? di?n
            dictionary[nextCode++] = current + entry[0];
        } else {
            // N?u m� chua t?n t?i trong t? di?n
            // L?y chu?i tuong ?ng c?a m� tru?c d� v� th�m k� t? d?u ti�n c?a chu?i d� v�o
            std::string entry = current + current[0];
            decompressedData += entry;

            // Th�m chu?i entry v�o t? di?n
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
