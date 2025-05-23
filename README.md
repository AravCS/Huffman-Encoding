Huffman Encoding Project for CS-124 (Data Structures & Algorithms), Spring 2025. (Note: I did not write the storage class code) 
<h1> How to Use The Program </h1>
This program has two main options, either compressing or decompressing a file. To utilize compression, enter one, for decompression, enter two. See below for more information. 
<h2> Compressing & Decompressing a File </h2>
Compressing a File: Specify the input file path, as well as the path that you would like to save the compressed, output file. 

Decompressing a File: Specify the input file path (compressed file), as well as the output path to save the decompressed file. 

<h1> How the Program is Implemented: </h1>

This compression & decompression program is implemented through the utilization of the Huffman encoding algorithm, which provides lossless data compression.

<h2> Steps for Compression </h2>

1) Built a frequency table by reading the input file character by character, and utilized an unordered_map to store key : value pairs, where the key represents the character and the value represents its frequency in the file. A sentinel character was ended at the end of the frequency table, which is useful during decompression phase to get the file to be exactly the same. 
2) Built the Huffman tree through the utilization of a min-heap priority queue, in which I first created nodes with their character and frequency by reading the frequency table. Then, I iterated over the priority queue until it had a length of 1 by linking a parent to the two nodes at the front of the queue with their added frequencies in order to build the root of the Huffman tree.
3) I proceeded to perform an in-order traversal of the Huffman tree to record the encoding of a letter (leaf node) into an unordered_map with the key as the letter and the value as its encoding.
4) After creating the encoding table, I built my header by iterating over the encoding table and concatenating the character and its encoding along with delimiters to a string. A sentinel character is added at the end of the header, which is useful when rebuilding the Huffman tree. 
5) After creating the encoding table and building my header, I was ready to build my compressed file by rereading the characters in the input file once again and inserting its encoding into a storage object.

<h2> Methods for Compression Phase </h2>

<ul> 
  <li> void compress(std::string &in_file, std::string &out_file) </li>
  <li> void BuildTable(std::ifstream &inputFile, std::unordered_map<char, int> &frequencyTable) </li>
  <li> void generateCodes(Node *tree, std::unordered_map<char, std::string> &codes, string encoding) </li>
  <li> std::string buildHeader(std::unordered_map<char, std::string> &codes) </li>
  <li> void buildCompressedFile(std::unordered_map<char, std::string> &codes, std::string &out_file, std::string in_file, std::ifstream &inputFile) </li>
</ul>

<h2> Steps for Decompression </h2>

<ol> 
  <li> Decompression begins by rebuilding the Huffman tree by utilizing the header. </li>
  <li> After rebuilding the Huffman tree through the use of the header, we can then write to an output file by extracting from our storage object 8 bits at a time, and     using a traversal pointer for our tree to reach the leaf nodes and write its character. A sentinel character is included to indicate the end (added during compression    phase), so we can have the file be exactly the same as the original. </li>
</ol>

<h2> Methods for Decompression Phase </h2>

<ul> 
  <li> void decompress(std::string& in_file, string &out_file) </li>
  <li> Node *RebuildTree(std::ifstream &inputFile) </li>
  <li> void buildDecompressedFile(Node *root, std::string &in_file, std::string &out_file, std::ifstream &inputFile) </li>
</ul>

<h1> Results of the Program </h1>
<h2> Results of Compression </h2>

<b> File 1: Adventures_of_Sherlock_Holmes.txt </b> 
<ul> 
  <li> Original File Size: 6.3 MB </li>
  <li> Compressed File Size: 3.6 MB </li>
  <li> Percentage: ((6.3 - 3.6)/6.3) * 100 = <b> 42.86% </b> </li>
</ul>

<b> File 2: MOBY-DICK.txt </b> 
<ul> 
  <li> Original File Size: 1.3 MB </li>
  <li> Compressed File Size: 720 KB </li>
  <li> Percentage: ((1300 - 720)/1300)) * 100 = <b> 44.62% </b> </li>
</ul>

<b> File 3: 100west.txt </b> 
<ul> 
  <li> Original File Size: 20 KB </li>
  <li> Compressed File Size: 12 KB </li>
  <li> Percentage: ((20 - 12)/20)) * 100 = <b> 40% </b> </li>
</ul>

<b> File 4: sample-2mb-text-file.txt </b> 
<ul> 
  <li> Original File Size: 2.2 MB </li>
  <li> Compressed File Size: 1.1 MB </li>
  <li> Percentage: ((2.2 - 1.1)/2.2)) * 100 = <b> 50% </b> </li>
</ul>
