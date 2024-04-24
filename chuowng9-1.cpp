#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>

// Ð?nh nghia Node c?a cây Huffman
struct Node {
    char data;
    int frequency;
    Node* left;
    Node* right;

    Node(char data, int frequency) : data(data), frequency(frequency), left(NULL), right(NULL) {}
};

// Hàm so sánh 2 node trong hàng d?i uu tiên
struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->frequency > right->frequency;
    }
};

// Hàm xây d?ng cây Huffman t? d? li?u d?u vào
Node* buildHuffmanTree(const std::string& data) {
    // Ð?m t?n s? xu?t hi?n c?a các ký t?
    std::unordered_map<char, int> frequencyMap;
    for (char c : data) {
        frequencyMap[c]++;
    }

    // T?o hàng d?i uu tiên t? các node lá
    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;
    for (const auto& pair : frequencyMap) {
        Node* newNode = new Node(pair.first, pair.second);
        pq.push(newNode);
    }

    // Xây d?ng cây Huffman
    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        Node* parent = new Node('\0', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }

    // Tr? v? node g?c c?a cây Huffman
    return pq.top();
}

// Hàm t?o b?ng mã huffman t? cây Huffman
void buildHuffmanCodes(Node* root, const std::string& prefix, std::unordered_map<char, std::string>& huffmanCodes) {
    if (root->left == NULL && root->right == NULL) {
        huffmanCodes[root->data] = prefix;
        return;
    }

    buildHuffmanCodes(root->left, prefix + "0", huffmanCodes);
    buildHuffmanCodes(root->right, prefix + "1", huffmanCodes);
}

// Hàm nén d? li?u thành chu?i mã Huffman
std::string compress(const std::string& data) {
    // Xây d?ng cây Huffman
    Node* root = buildHuffmanTree(data);

    // T?o b?ng mã Huffman
    std::unordered_map<char, std::string> huffmanCodes;
    buildHuffmanCodes(root, "", huffmanCodes);

    // Nén d? li?u
    std::string compressedData;
    for (char c : data) {
        compressedData += huffmanCodes[c];
    }

    return compressedData;
}

// Hàm gi?i nén chu?i mã Huffman thành d? li?u g?c
std::string decompress(const std::string& compressedData, Node* root) {
    std::string decompressedData;
    Node* curr = root;

    for (char c : compressedData) {
        if (c == '0') {
            curr = curr->left;
        } else {
            curr = curr->right;
        }

        if (curr->left == NULL && curr->right == NULL) {
            decompressedData += curr->data;
            curr = root;
        }
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
        std::string compressedData = compress(input);
        std::cout << "Compressed data: " << compressedData << std::endl;
    } else if (operation == "D") {
        Node* root = buildHuffmanTree(input.cpp");
        std::string decompressedData = decompress(input, root);
        std::cout << "Decompressed data: " << decompressedData << std::endl;
    } else {
        std::cout << "Invalid operation. Please enter 'C' or 'D'." << std::endl;
    }

    return 0;
}
