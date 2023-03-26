#include "CompressionAlgorithm.h"
#include "DecompressionAlgorithm.h"
#include <iostream>

int main(){
    std::string txtFilePath;
    std::getline(std::cin, txtFilePath);
    int output = snf::CompressionAlgorithm::compressFile(txtFilePath);
    if(output) std::cout << output << std::endl;

    txtFilePath = "";
    std::getline(std::cin, txtFilePath);
    output = snf::DecompressionAlgorithm::decompressFile(txtFilePath);
    if(output) std::cout << output << std::endl;

    return 0;
}