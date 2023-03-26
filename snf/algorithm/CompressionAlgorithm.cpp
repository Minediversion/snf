#include "CompressionAlgorithm.h"

#define wordAppearance 3 // How many times the word appears for it to compress it
#define snfIdentifier "*-*-*" // How the file will be identified by the algorithm

bool isFileValid(std::string);
std::unordered_map<std::string, std::size_t> classifyWords(const std::string&);

namespace fs = std::filesystem;

//TODO: Make nums be able to be compressed

snf::CompressionAlgorithm::CompressionAlgorithm()= default;

int snf::CompressionAlgorithm::compressFile(const std::string& txtFilePath) {
    // File preparation
    //std::string txtFilePath;
    //std::getline(std::cin, txtFilePath); // Get file path

    if(!isFileValid(txtFilePath)) return 0; // Check if file is valid, if not end program

    std::size_t directory = txtFilePath.find_last_of('\\'); // Get last occurrence of \ to get directory
    std::string snfFilePath = txtFilePath.substr(0, directory+1)
            + txtFilePath.substr(directory+1, txtFilePath.length()-4-directory)
            + "snf"; // Get the theoretical path were .snf would be

    if(fs::exists(snfFilePath)){ // Checks if there is already a compressed file
        //Check if user wants to overwrite file
        std::cout << "Do you want to overwrite existing .snf file? Y/N" << std::endl;
        char c; std::cin >> c;
        if(c == 'N') return 0;
        fs::remove(snfFilePath); //Deletes previous file
    }
    std::ofstream snfFile (snfFilePath, std::ofstream::out); // Create file, opened for writing

    //------------------------------------------------------------------------------------------------------------------
    std::unordered_map<std::string, std::size_t> compWords = classifyWords(txtFilePath);
    if(compWords.empty()) {
        std::cout << "Can't be compressed more" << std::endl;
        snfFile.close();
        fs::remove(snfFilePath);
        return 0;
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
    return 1;
}

//Check whether file path is a valid .txt file
bool isFileValid(std::string filePath){
    if(filePath.length()>=7) { //Checks if file has at least "Drive:/.txt"
        if (filePath[1] != ':') std::cout << "Filepath is not a drive" << std::endl;  // Checks if Drive: exist
        else if (filePath.substr(filePath.length() - 4, 4) != ".txt") std::cout << "File is not .txt" << std::endl; // Checks if file ends in .txt
        else{
            if(fs::exists(fs::path(filePath))){ // Checks if file exists
                std::cout << "Valid file" << std::endl;
                return true;
            }else std::cout << "File doesn't exist" << std::endl;
        }
    }else std::cout << "Not a valid path" << std::endl;
    return false;
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
    std::unordered_map<std::string, std::size_t> compWords;
    std::size_t id = 0;
    for(auto & word : words) if(word.second >= wordAppearance) compWords[word.first] = id, id++; // Set ids for words that appear more than twice
    txtFile.close(); // Free up memory
    words.clear(); // Free up memory
    return compWords;
}