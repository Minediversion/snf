#include "CompressionAlgorithm.h"
#include "DecompressionAlgorithm.h"
#include <iostream>

namespace fs = std::filesystem;

bool isFileValid(const std::string&, const std::string&);

int main(){
    snf::CompressionAlgorithm compressionAlgorithm;
    snf::DecompressionAlgorithm decompressionAlgorithm;

    std::string filePath;
    std::getline(std::cin, filePath);
    if(!isFileValid(filePath, ".txt")) return 0;
    std::string output = compressionAlgorithm.compressFile(filePath);
    if(output.empty()) std::cout << compressionAlgorithm.snfFilePathCom << std::endl;

    filePath = "";
    std::getline(std::cin, filePath);
    if(!isFileValid(filePath, ".snf")) return 0;
    output = decompressionAlgorithm.decompressFile(filePath);
    if(output.empty()) std::cout << decompressionAlgorithm.txtFilePathDecom << std::endl;

    return 0;
}

bool isFileValid(const std::string &filePath, const std::string& fileExtension){
    if(filePath.length()>=7) { //Checks if file has at least "Drive:/.snf"
        if (filePath[1] != ':') std::cout << "Filepath is not a drive" << std::endl;  // Checks if Drive: exist
        else if (filePath.substr(filePath.length() - 4, 4) != fileExtension) std::cout << "File is not " << fileExtension << std::endl; // Checks if file ends in .snf
        else{
            if(fs::exists(fs::path(filePath))){ // Checks if file exists
                std::cout << "Valid file" << std::endl;
                return true;
            }else std::cout << "File doesn't exist" << std::endl;
        }
    }else std::cout << "Not a valid path" << std::endl;
    return false;
}