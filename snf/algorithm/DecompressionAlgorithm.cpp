#include "DecompressionAlgorithm.h"
#include "snfmultitool.h"

#define snfIdentifier "*-*-*" // How the file will be identified by the algorithm

std::unordered_map<std::size_t, std::string> getCompressionIds(const std::string&);

namespace fs = std::filesystem;

std::fstream snfFile;

bool snf::DecompressionAlgorithm::decompressFile(const std::string &snfFilePath, const std::string &txtFilePath) {
    // File preparation
    std::ofstream txtFile (txtFilePath, std::ofstream::out);

    //------------------------------------------------------------------------------------------------------------------
    std::unordered_map<std::size_t, std::string> wordsIds = getCompressionIds(snfFilePath);
    if(wordsIds.empty()) {
        txtFile.close();
        fs::remove(txtFilePath);
        SnFMultitoolAddons::sendErrorMessage("File is corrupted");
        return false;
    }
    //------------------------------------------------------------------------------------------------------------------
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

    return true;
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
        //std::cout << "SNF file is corrupted" << std::endl;
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