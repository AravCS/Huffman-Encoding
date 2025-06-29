# 📦 Huffman Compression & Decompression

A C++ program that compresses and decompresses text files using the **Huffman encoding algorithm** for efficient, lossless data compression.

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

1. **Build frequency table** using `unordered_map<char, int>`
2. **Construct Huffman Tree** with a min-heap priority queue
3. **Generate encoding map** using in-order traversal
4. **Create header** with character:code mappings and a sentinel character
5. **Write compressed data** using the encoding map

### 🔧 Decompression Steps

1. **Rebuild Huffman Tree** using header data
2. **Decode bitstream** by traversing the tree and writing decoded characters until sentinel is reached

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

