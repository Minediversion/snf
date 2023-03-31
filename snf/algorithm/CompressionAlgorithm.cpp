#include "CompressionAlgorithm.h"
#include "snfmultitool.h"

#define dWordAppearance 3 // How many times the word appears for it to compress it
#define snfIdentifier "*-*-*" // How the file will be identified by the algorithm

std::unordered_map<std::string, std::size_t> classifyWords(const std::string&);

namespace fs = std::filesystem;

bool snf::CompressionAlgorithm::compressFile(const std::string& txtFilePath, const std::string &snfFilePath) {
    // File preparation
    std::ofstream snfFile (snfFilePath, std::ofstream::out); // Create file, opened for writing

    //------------------------------------------------------------------------------------------------------------------
    std::unordered_map<std::string, std::size_t> compWords = classifyWords(txtFilePath);
    if(compWords.empty()) {
        //std::cout << "Can't be compressed more" << std::endl;
        snfFile.close();
        fs::remove(snfFilePath);
        SnFMultitoolAddons::sendErrorMessage("File can't be compressed more");
        return false;
    }
    //------------------------------------------------------------------------------------------------------------------

    // Build compressed file
    for(auto & word : compWords) snfFile << std::to_string(word.second) << word.first << std::endl; // Put at the start of the .snf file the ids
    snfFile << snfIdentifier << std::endl;

    std::string strBuf;
    std::fstream txtFile (txtFilePath, std::fstream::in); // Open text file in read mode.
    char nextChar;
    while(txtFile.get(nextChar)){
        if(!iswalnum(nextChar)){
            // Check if is compressible
            if(compWords.find(strBuf) != compWords.end()) snfFile << compWords[strBuf] << nextChar; // Replace it with the id of the string
            else snfFile << strBuf << nextChar; // Leave it as is
            strBuf = "";
        }else strBuf += nextChar;
    }
    // Close files to save memory
    snfFile.close();
    txtFile.close();

    return true;
}

// Classify words
std::unordered_map<std::string, std::size_t> classifyWords(const std::string& txtFilePath){
    std::fstream txtFile (txtFilePath, std::fstream::in); // Opening text file in read mode

    std::string strBuf;
    std::unordered_map<std::string, std::size_t> words; // Create a map in order to classify words
    while(txtFile){
        txtFile >> strBuf;
        // Delete non-alphanumeric characters from string classify
        if(!isalpha(strBuf[strBuf.length()-1])) strBuf.erase(strBuf.length()-1, 1);
        if(!isalpha(strBuf[0])) strBuf.erase(0, 1);
        words[strBuf]++;
    }
    int count;
    int wordAppearance = dWordAppearance;
    do {
        count = 0;
        for (auto &word: words) {
            if (word.second >= wordAppearance) count++;
            if (count == 100) {
                wordAppearance++;
                break;
            }
        }
    } while (count == 100);
    wordAppearance--;
    std::unordered_map<std::string, std::size_t> compWords;
    std::size_t id = 0;
    for(auto & word : words) if(word.second >= wordAppearance) if(word.first[0] != 0) compWords[word.first] = id, id++;// Set ids for words that appear multiple times
    txtFile.close();
    words.clear();
    return compWords;
}