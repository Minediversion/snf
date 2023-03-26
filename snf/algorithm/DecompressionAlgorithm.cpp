#include "DecompressionAlgorithm.h"

#define snfIdentifier "*-*-*" // How the file will be identified by the algorithm

std::unordered_map<std::size_t, std::string> getCompressionIds(const std::string&);

namespace fs = std::filesystem;

std::fstream snfFile;

//TODO: Make nums be able to be decompressed

snf::DecompressionAlgorithm::DecompressionAlgorithm() {
    txtFilePathDecom = "";
}

int snf::DecompressionAlgorithm::decompressFile(const std::string &snfFilePath) {
    // File preparation
    //std::string snfFilePath;
    //std::getline(std::cin, snfFilePath); // Get file path

    //if(!isFileValid(snfFilePath)) return 0; // Check if file is valid, if not end program

    std::size_t directory = snfFilePath.find_last_of('\\'); // Get last occurrence of \ to get directory
    std::string txtFilePath = snfFilePath.substr(0, directory+1)
                              + snfFilePath.substr(directory+1, snfFilePath.length()-4-directory)
                              + "txt"; // Get the theoretical path were .txt would be

    if(fs::exists(txtFilePath)){ // Checks if there is already a decompressed file
        //Check if user wants to overwrite file
        std::cout << "Do you want to overwrite existing .txt file? Y/N" << std::endl;
        not_valid_input:
        std::string c; std::getline(std::cin, c);
        if(c[0] == 'N') return 0;
        else if(c[0] != 'Y') {
            std::cout << "Response is not valid" << std::endl;
            goto not_valid_input;
        }
        fs::remove(txtFilePath); //Deletes previous file
    }
    std::ofstream txtFile (txtFilePath, std::ofstream::out);

    //------------------------------------------------------------------------------------------------------------------
    std::unordered_map<std::size_t, std::string> wordsIds = getCompressionIds(snfFilePath);
    if(wordsIds.empty()) return 0;
    //------------------------------------------------------------------------------------------------------------------
    snf::DecompressionAlgorithm::txtFilePathDecom = txtFilePath;
    // Reconstruct txt file
    std::string strBuf;
    bool isText = false;
    char nextChar;
    while(snfFile.get(nextChar)) {
        if(!iswalnum(nextChar)){
            if(strBuf.length() > (std::size_t)std::floor(log10(wordsIds.size())+1) || strBuf.empty()){
                txtFile << strBuf << nextChar;
                strBuf = "";
            }else {
                for (const char c: strBuf) if (!std::isdigit(c)){
                    isText = true;
                    break;
                }
                if(isText){
                    txtFile << strBuf << nextChar;
                    strBuf = "";
                    isText = false;
                }else{
                    txtFile << wordsIds[atoll(strBuf.c_str())] << nextChar;
                    strBuf = "";
                }
            }
        }else {
            strBuf += nextChar;
        }
    }
    // Close files to save memory
    txtFile.close();
    snfFile.close();

    return 1;
}

std::unordered_map<std::size_t, std::string> getCompressionIds(const std::string& snfFilePath){
    snfFile.open(snfFilePath, std::fstream::in); // Open snf file in read mode

    std::unordered_map<std::size_t, std::string> wordsIds;
    std::string strBuf;
    // Check if file has snf identifier
    bool valid = false;
    while(snfFile){
        snfFile >> strBuf;
        if(strBuf == snfIdentifier) valid = true;
    }
    if(!valid) {
        std::cout << "SNF file is corrupted" << std::endl;
        return wordsIds;
    }

    // Extract word ids
    snfFile.close();
    snfFile.open(snfFilePath, std::fstream::in); // Re-open file to read again from the beginning
    strBuf = "";
    std::size_t idBuf;
    bool numId = true;
    char nextChar;
    while(snfFile.get(nextChar)) {
        if(strBuf == snfIdentifier){
            break;
        }else if(isalpha(nextChar) && numId){
            idBuf = atoll(strBuf.c_str());
            numId = false;
            strBuf = nextChar;
        }else if(nextChar == '\n'){
            wordsIds[idBuf] = strBuf;
            numId = true;
            strBuf = "";
        }else {
            strBuf += nextChar;
        }
    }
    return wordsIds;
}