#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>

// �?nh nghia Node c?a c�y Huffman
struct Node {
    char data;
    int frequency;
    Node* left;
    Node* right;

    Node(char data, int frequency) : data(data), frequency(frequency), left(NULL), right(NULL) {}
};

// H�m so s�nh 2 node trong h�ng d?i uu ti�n
struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->frequency > right->frequency;
    }
};

// H�m x�y d?ng c�y Huffman t? d? li?u d?u v�o
Node* buildHuffmanTree(const std::string& data) {
    // �?m t?n s? xu?t hi?n c?a c�c k� t?
    std::unordered_map<char, int> frequencyMap;
    for (char c : data) {
        frequencyMap[c]++;
    }

    // T?o h�ng d?i uu ti�n t? c�c node l�
    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;
    for (const auto& pair : frequencyMap) {
        Node* newNode = new Node(pair.first, pair.second);
        pq.push(newNode);
    }

    // X�y d?ng c�y Huffman
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

    // Tr? v? node g?c c?a c�y Huffman
    return pq.top();
}

// H�m t?o b?ng m� huffman t? c�y Huffman
void buildHuffmanCodes(Node* root, const std::string& prefix, std::unordered_map<char, std::string>& huffmanCodes) {
    if (root->left == NULL && root->right == NULL) {
        huffmanCodes[root->data] = prefix;
        return;
    }

    buildHuffmanCodes(root->left, prefix + "0", huffmanCodes);
    buildHuffmanCodes(root->right, prefix + "1", huffmanCodes);
}

// H�m n�n d? li?u th�nh chu?i m� Huffman
std::string compress(const std::string& data) {
    // X�y d?ng c�y Huffman
    Node* root = buildHuffmanTree(data);

    // T?o b?ng m� Huffman
    std::unordered_map<char, std::string> huffmanCodes;
    buildHuffmanCodes(root, "", huffmanCodes);

    // N�n d? li?u
    std::string compressedData;
    for (char c : data) {
        compressedData += huffmanCodes[c];
    }

    return compressedData;
}

// H�m gi?i n�n chu?i m� Huffman th�nh d? li?u g?c
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
