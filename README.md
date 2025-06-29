# 📦 Huffman Compression & Decompression

A C++ program that compresses and decompresses text files using the **Huffman encoding algorithm** for efficient, lossless data compression.

> **Note:** This project was completed for my Data Structures & Algorithms course (Spring 2025) and received a perfect score of 100%.

## 📚 Table of Contents

- [🔧 How to Use](#-how-to-use)
- [⚙️ How It Works](#️-how-it-works)
  - [🛠️ Compression Steps](#️-compression-steps)
  - [🔧 Decompression Steps](#-decompression-steps)
- [🧪 Method Overview](#-method-overview)
- [📈 Results](#-results)

## 🔧 How to Use

When running the program, you'll be prompted to select an operation:
- `1` — Compress a file
- `2` — Decompress a file

### ✂️ Compressing
- Provide the **input file path** of the file to compress
- Specify an **output file path** for the compressed result

### 🪄 Decompressing
- Provide the **input file path** of the compressed file
- Specify the **output file path** for the decompressed result

## ⚙️ How It Works

This program uses the **Huffman coding algorithm** to reduce file size by assigning shorter codes to more frequent characters.

### 🛠️ Compression Steps

1. **Build frequency table** by reading the input file character by character, utilizing an `unordered_map<char, int>` to store key-value pairs where the key represents the character and the value represents its frequency in the file. A sentinel character is added at the end of the frequency table, which is essential during the decompression phase to ensure the file is reconstructed exactly.

2. **Construct Huffman Tree** through the utilization of a min-heap priority queue. First, nodes are created with their character and frequency by reading the frequency table. Then, iterate over the priority queue until it has a length of 1 by linking a parent to the two nodes at the front of the queue with their combined frequencies, building up to the root of the Huffman tree.

3. **Generate encoding map** by performing an in-order traversal of the Huffman tree to record the encoding of each letter (leaf node) into an `unordered_map<char, string>` with the key as the letter and the value as its binary encoding.

4. **Create header** by iterating over the encoding table and concatenating each character with its encoding along with delimiters to form a header string. A sentinel character is added at the end of the header, which is crucial when rebuilding the Huffman tree during decompression.

5. **Write compressed data** by re-reading the characters in the input file and replacing each character with its corresponding encoding from the encoding table, writing the compressed binary data to the output file.

### 🔧 Decompression Steps

1. **Rebuild Huffman Tree** by parsing the header data to reconstruct the exact tree structure used during compression. The header contains character-encoding pairs with delimiters that allow for accurate tree reconstruction.

2. **Decode bitstream** by extracting compressed data from the storage object 8 bits at a time, using a traversal pointer to navigate the Huffman tree. Starting from the root, each bit determines whether to move left (0) or right (1) until reaching a leaf node, at which point the corresponding character is written to the output file. The sentinel character indicates the end of the file (added during compression phase), ensuring the decompressed file matches the original exactly.

## 🧪 Method Overview

### 🧱 Compression Methods

```cpp
void compress(std::string &in_file, std::string &out_file);
void BuildTable(std::ifstream &inputFile, std::unordered_map<char, int> &frequencyTable);
void generateCodes(Node *tree, std::unordered_map<char, std::string> &codes, std::string encoding);
std::string buildHeader(std::unordered_map<char, std::string> &codes);
void buildCompressedFile(std::unordered_map<char, std::string> &codes, std::string &out_file, std::string in_file, std::ifstream &inputFile);
```

### 🔓 Decompression Methods

```cpp
void decompress(std::string &in_file, std::string &out_file);
Node* RebuildTree(std::ifstream &inputFile);
void buildDecompressedFile(Node *root, std::string &in_file, std::string &out_file, std::ifstream &inputFile);
```

## 📈 Results

| 📁 File Name | 🗜️ Original Size | 📉 Compressed Size | 📊 Reduction (%) |
|--------------|------------------|--------------------|------------------|
| *Adventures_of_Sherlock_Holmes.txt* | 6.3 MB | 3.6 MB | **42.86%** |
| *MOBY-DICK.txt* | 1.3 MB | 720 KB | **44.62%** |
| *100west.txt* | 20 KB | 12 KB | **40%** |
| *sample-2mb-text-file.txt* | 2.2 MB | 1.1 MB | **50%** |

## 🚀 Getting Started

### Prerequisites
- C++ compiler (C++11 or later)
- Standard Template Library (STL)

### Building and Running
```bash
# Compile the program
g++ -o huffman main.cpp

# Run the program
./huffman
```
