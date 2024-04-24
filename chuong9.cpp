#include <iostream>
#include <string>

std::string runLengthEncoding(const std::string& data) {
    std::string encodedData = "";
    int count = 1;
    for (int i = 1; i < data.length(); i++) {
        if (data[i] == data[i - 1]) {
            count++;
        } else {
            encodedData += data[i - 1] + std::to_string(count);
            count = 1;
        }
    }
    encodedData += data[data.length() - 1] + std::to_string(count);
    return encodedData;
}

int main() {
    std::string input;
    std::cout << "Enter the input string: ";
    std::cin >> input;

    std::string encodedString = runLengthEncoding(input);
    std::cout << "Encoded string: " << encodedString << std::endl;

    return 0;
}