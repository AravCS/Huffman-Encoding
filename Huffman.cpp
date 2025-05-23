#include "Huffman.h"

void Huffman::compress(std::string& in_file, std::string& out_file) {
    // Open input file for reading
    std::ifstream inputFile;
    inputFile.open(in_file);

    // Declare a hash table and build a table of key : value (character : frequency) pairs
    std::unordered_map<char, int> frequencyTable;
    BuildTable(inputFile, frequencyTable);

    // Declare a priority queue to hold nodes with their letter and frequency, and build Huffman tree
    std::priority_queue<Node*, std::vector<Node*>, compareWeights> nodes;
    BuildHuffmanTree(nodes, frequencyTable);

    // Root of Huffman tree
    Node *root = new Node(*nodes.top());
    nodes.pop();

    // Generate codes from the Huffman tree by recursive traversal of the tree
    std::unordered_map<char, std::string> codes;
    generateCodes(root, codes, "");

    // Build compressed output file with header and bit encodings
    buildCompressedFile(codes, out_file, in_file, inputFile);

    // Get rid of the dynamically allocated Huffman tree to avoid memory leaks
    deleteAll(root);
}

void Huffman::decompress(std::string &in_file, std::string &out_file) {
    // Open the input file
    std::ifstream inputFile;
    inputFile.open(in_file);

    // Rebuild the tree based on given input file
    Node *root = RebuildTree(inputFile);

    // After rebuilding, we can convert our bit encodings to actual characters by using the Huffman tree
    buildDecompressedFile(root, in_file, out_file, inputFile);

    // Get rid of the dynamically allocated tree to avoid memory leaks
    deleteAll(root);
}

void Huffman::BuildTable(std::ifstream &inputFile, std::unordered_map<char, int> &frequencyTable) {
    // Read file ch by ch, adding it to a table of the char and its count (frequency)
    if (inputFile.is_open()) {
        char ch;
        while (inputFile.get(ch)) {
            // Character exists in the set, so we increment the frequency
            if (frequencyTable.count(ch) > 0) {
                frequencyTable[ch]++;
            }
            // If it does not exist, create a new element in the set with the character and initial frequency
            else {
                frequencyTable.emplace(ch, 1);
            }
        }
    }
    // Sentinel character to use for stopping during decompression
    frequencyTable.emplace('`', 1);
    // Close the file to reset "cursor"
    inputFile.close();
}

void Huffman::BuildHuffmanTree(std::priority_queue<Node*, std::vector<Node*>, compareWeights> &nodes,
    std::unordered_map<char, int> &frequencyTable) {
    // Iterate over the table of characters
    for (std::unordered_map<char, int>::iterator it  = frequencyTable.begin(); it != frequencyTable.end(); ++it) {
        // Create a node with the key (character) and value (frequency), then push it onto the queue
        Node *node = new Node(it->first, it->second);
        nodes.push(node);
    }

    // Build the Huffman tree using the priority queue
    while (nodes.size() > 1) {
        // Get the left node
        Node *left = new Node(*nodes.top());
        nodes.pop();

        // Get the right node
        Node *right = new Node(*nodes.top());
        nodes.pop();

        // Combine the frequencies, build the parent node, push it onto priority queue
        Node *parent = new Node('\0', left->weight + right->weight, left, right);
        nodes.push(parent);
    }
}

void Huffman::generateCodes(Node *tree, std::unordered_map<char, std::string> &codes, std::string encoding) {
    // Base Case
    if (tree->zero == nullptr && tree->one == nullptr) {
        tree->code = encoding;
        codes.emplace(tree->letter, tree->code);
        return;
    }
    // Recursive Cases
    generateCodes(tree->zero, codes, encoding + "0");
    generateCodes(tree->one, codes, encoding + "1");
}

std::string Huffman::buildHeader(std::unordered_map<char, std::string> &codes) {
    std::string header;
    // Iterate over our encoded table
    for (std::unordered_map<char, std::string>::iterator it = codes.begin(); it != codes.end(); ++it) {
        // Get the character and its encoding from the table
        char character = it->first;
        std::string encoding = it->second;

        // Set up delimiters
        std::string firstDelimiter = "=";
        std::string secondDelimiter = "<";

        // Add the current character and its encoding to the header string
        header += character + firstDelimiter + encoding + secondDelimiter;
    }
    // This is a sentinel character. It is useful when we are decoding the header to rebuild
    // huffman tree and need to know when to exit
    header += ">";
    return header;
}

void Huffman::buildCompressedFile(std::unordered_map<char, std::string> &codes, std::string &out_file,
    std::string &in_file, std::ifstream &inputFile) {
    // Create a storage variable and open output file for writing
    Storage storage;
    if (!storage.open(out_file, "write")) {
        std::cout << "File did not open." << std::endl;
    }

    // Build and set the header
    std::string header = buildHeader(codes);
    storage.setHeader(header);

    // Open the input file
    char ch;
    inputFile.open(in_file);

    // Read character by character, and then insert the encoding for the character using the encoding table
    while (inputFile.get(ch)) {
        storage.insert(codes[ch]);
    }

    // Insert the sentinel character at the end of the compressed file, so we know when to stop during decompression
    storage.insert(codes['`']);
    storage.close();
}

Node *Huffman::RebuildTree(std::ifstream &inputFile) {
    // Get to the first letter in the file to store as initial letter, we need to skip some parts of the initial
    // text
    char ch;
    while (inputFile.get(ch)) {
        // If the next character is an equal symbol, this indicates that we have reached the first letter
        if (inputFile.peek() == '=') {
            break;
        }
    }

    // Store initial letter
    char letter = ch;

    // Declaration of root and traversal pointer
    Node *root = new Node('\0', 0);
    Node *current = root;

    while (inputFile.get(ch)) {
        // Sentinel - We have reached the end of the header
        if (ch == '>') {
            break;
        }
        // This character indicates that the next character in the header is an actual letter
        if (ch == '<') {
            // update the letter variable with the next character (new letter)
            letter = inputFile.get();
        }
        // if the character is a zero, we build/traverse the tree from the left
        if (ch == '0') {
            // Only build a new node if there is not a preexisting one at the spot
            if (current->zero == nullptr) {
                // if the next character is '<', this means that we have reached the end of encoding for current letter
                if (inputFile.peek() == '<') {
                    // Create a new node with the letter, must move current back to root for the next encoding
                    current->zero = new Node(letter, 0);
                    current = root;
                }
                // If the next character is not '<', then we must continue to build the tree
                else {
                    // Create a new node (not a leaf yet)
                    current->zero = new Node('\0', 0);
                    // Move current onto the new node
                    current = current->zero;
                }
            }
            // Even if there is a preexisting node, we still need to move current for traversal
            else {
                current = current->zero;
            }
        }
        // If the character is a one, we build/traverse the tree from the right
        if (ch == '1') {
            // Only build a new node if there is not a preexisting one at the spot
            if (current->one == nullptr) {
                // if the next character is '<', this means that we have reached the end of encoding for current letter
                if (inputFile.peek() == '<') {
                    // Create a new node with the letter, must move current back to root for the next encoding
                    current->one = new Node(letter, 0);
                    current = root;
                }
                // If the next character is not '<', then we must continue to build the tree
                else {
                    // Create a new node (not a leaf yet)
                    current->one = new Node('\0', 0);
                    // Move current onto the new node
                    current = current->one;
                }
            }
            // Even if there is a preexisting node, we still need to move current for traversal
            else {
                current = current->one;
            }
        }
    }
    return root;
}

void Huffman::buildDecompressedFile(Node *root, std::string &in_file, std::string &out_file, std::ifstream &inputFile) {
    // Close input file to reset "cursor"
    inputFile.close();

    // Open the input file again for reading
    Storage storage;
    if (!storage.open(in_file, "read")) {
        std::cout << "Error opening input file." << std::endl;
    }

    // Skip the header
    std::string header = storage.getHeader();
    std::string bits;

    // Open output file for writing
    std::ofstream outputFile;
    outputFile.open(out_file);

    // Set up traversal pointer
    Node *current = root;

    // Extract 8 bits at a time
    while (storage.extract(bits)) {
        // Iterate over the current 8 bits
        for (char ch : bits) {
            // If the character we are reading is '0', then we must move to the left
            if (ch == '0') {
                current = current->zero;
            }
            // If the character we are reading is '1', then we must move to the right
            else {
                current = current->one;
            }
            // Leaf Node - If we are at a leaf node, then write the letter of the node to the output file
            if (current->zero == nullptr && current->one == nullptr) {
                // If we hit the sentinel, we have reached the end
                if (current->letter == '`') {
                    break;
                }
                // Write character to output file, and we need to move current back onto the root for the next letter
                outputFile << current->letter;
                current = root;
            }
        }
    }
}

void Huffman::deleteAll(Node *tree) {
    // Base Case
    if (tree == nullptr) {
        return;
    }
    // We use postOrder to get rid of the tree
    deleteAll(tree->zero);
    deleteAll(tree->one);
    delete tree;
}


