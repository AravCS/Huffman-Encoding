📦 Huffman Compression & Decompression Program
This program offers two main features: compressing and decompressing files using the Huffman encoding algorithm. It supports lossless data compression and ensures the decompressed file is identical to the original.

🚀 How to Use the Program
🗂️ Main Options:

Enter 1 to compress a file

Enter 2 to decompress a file

📥 Compression:

Input the path of the file you wish to compress

Provide an output path to save the compressed file

📤 Decompression:

Input the path of the compressed file

Provide an output path for the decompressed file

⚙️ How the Program Works
This program is implemented using the Huffman Encoding Algorithm, known for its efficiency in lossless compression.

🛠️ Compression Steps
📊 Build a frequency table using an unordered_map<char, int> by reading characters from the input file.

🌲 Construct a Huffman Tree using a min-heap priority queue based on character frequency.

🔡 Generate binary codes for each character via an in-order traversal of the Huffman Tree.

🧾 Build a header string containing character-encoding pairs with a sentinel character at the end.

📄 Re-read the input file and use the codes to generate a compressed bitstream and write it to the output file.

🧪 Compression Methods
cpp
Copy
Edit
void compress(std::string &in_file, std::string &out_file);
void BuildTable(std::ifstream &inputFile, std::unordered_map<char, int> &frequencyTable);
void generateCodes(Node *tree, std::unordered_map<char, std::string> &codes, std::string encoding);
std::string buildHeader(std::unordered_map<char, std::string> &codes);
void buildCompressedFile(std::unordered_map<char, std::string> &codes, std::string &out_file, std::string in_file, std::ifstream &inputFile);
🧩 Decompression Steps
🌲 Rebuild the Huffman Tree using the header from the compressed file.

📜 Decode the file by traversing the tree 8 bits at a time until reaching a sentinel character, ensuring the result matches the original file.

🔧 Decompression Methods
cpp
Copy
Edit
void decompress(std::string &in_file, std::string &out_file);
Node* RebuildTree(std::ifstream &inputFile);
void buildDecompressedFile(Node *root, std::string &in_file, std::string &out_file, std::ifstream &inputFile);
📈 Compression Results
📘 File 1: Adventures_of_Sherlock_Holmes.txt
Original Size: 6.3 MB

Compressed Size: 3.6 MB

Compression Rate: 42.86%

🐳 File 2: MOBY-DICK.txt
Original Size: 1.3 MB

Compressed Size: 720 KB

Compression Rate: 44.62%

🏙️ File 3: 100west.txt
Original Size: 20 KB

Compressed Size: 12 KB

Compression Rate: 40%

📄 File 4: sample-2mb-text-file.txt
Original Size: 2.2 MB

Compressed Size: 1.1 MB

Compression Rate: 50%


