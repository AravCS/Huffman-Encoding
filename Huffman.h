#include <string>
#include <queue>
#include <fstream>
#include "Node.h"
#include "Storage/Storage.h"
#include <unordered_map>

#ifndef HUFFMAN_H

/**
 * @class Huffman
 * @brief This class serves as the basis for a file compression/decompression program. It is implemented through the
 * utilization of the Huffman algorithm.
 */
class Huffman {
private:
    /**
     * @brief Creates a frequency table through the use of an unordered_map to store (key : value) pairs, in which the
     * key is the character and the value is its frequency
     * @param inputFile the file to read character by character
     * @param frequencyTable the unordered_map representing the frequency table
     */
    void BuildTable(std::ifstream &inputFile, std::unordered_map<char, int> &frequencyTable);
    /**
     * @brief Builds the Huffman tree by utilizing a min-heap priority queue, the last node in the queue is the root
     * of the Huffman tree
     * @param nodes the priority queue we are utilizing to build the Huffman tree
     * @param frequencyTable the frequency table created in a prior step
     */
    void BuildHuffmanTree(std::priority_queue<Node*, std::vector<Node*>, compareWeights> &nodes,
                          std::unordered_map<char, int> &frequencyTable);
    /**
     * @brief Generates the bit encoding by utilizing an in-order traversal of the Huffman tree
     * @param tree the root of the Huffman tree
     * @param codes an unordered_map to store key, value pairs, in which the key represents the character and the value
     * represents its encoding
     * @param encoding a string to use during recursion when we need to count the zero or one during in-order traversal
     */
    void generateCodes(Node *tree, std::unordered_map<char, std::string> &codes, std::string encoding);
    /**
     * @brief Builds the header to store in a storage object needed to rebuild the Huffman tree during decompression
     * @param codes the unordered_map which stores all the characters (key) and their encodings (value)
     * @return the header as a string to store in the storage object
     */
    std::string buildHeader(std::unordered_map<char, std::string> &codes);
    /**
     * @brief Builds the compressed file to utilize during decompression
     * @param codes the unordered_map that stores all the characters (key) and their encodings (value)
     * @param out_file the name of the output file
     * @param in_file the name of the input file
     * @param inputFile the input file
     */
    void buildCompressedFile(std::unordered_map<char, std::string> &codes, std::string &out_file,
                             std::string &in_file, std::ifstream &inputFile);
    /**
     * @brief Rebuilds the Huffman tree for decompression through the compressed file's header
     * @param inputFile the input file (compressed file) to read the header from
     * @return the root of the rebuilt Huffman tree
     */
    Node *RebuildTree(std::ifstream &inputFile);
    /**
     * @brief Deletes the Huffman tree after compression and decompression by a recursive post-Order traversal
     * @param tree the root of the Huffman tree
     */
    void deleteAll(Node *tree);
    /**
     * @brief Builds the decompressed file
     * @param root the root of the rebuilt Huffman tree
     * @param in_file the name of the input file
     * @param out_file the name of the output file
     * @param inputFile the input file
     */
    void buildDecompressedFile(Node *root, std::string &in_file, std::string &out_file, std::ifstream &inputFile);
public:
    /**
     * @brief Main method for compression, utilizes different helper functions to attain the goal of compressing a file
     * with the utilization of the Huffman algorithm
     * @param in_file the name of the input file
     * @param out_file the name of the output file
     */
    void compress(std::string& in_file, std::string &out_file);
    /**
     * @brief Main method for decompression, utilizes different helper functions to decompress the given compressed file
     * @param in_file the name of the input file
     * @param out_file the name of the output file
     */
    void decompress(std::string& in_file, std::string &out_file);
};


#define HUFFMAN_H

#endif //HUFFMAN_H
