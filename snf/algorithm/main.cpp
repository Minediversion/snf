#include <iostream>
#include <filesystem>
#include <fstream>

bool isFileValid(std::string);

namespace fs = std::filesystem;

int main() {
    // File preparation
    /*
    std::string txtFilePath; // C:\Users\marcr\CLionProjects\snf\test.txt
    std::getline(std::cin, txtFilePath); // Get file path
     */
    std::string txtFilePath = R"(C:\Users\marcr\CLionProjects\snf\test.txt)"; // Test file path

    if(!isFileValid(txtFilePath)) return 0; // Check if file is valid, if not en program

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
    std::fstream txtFile (txtFilePath, std::fstream::in); // Open file for reading
    std::ofstream snfFile (snfFilePath, std::ofstream::out); // Create file, opened for writing

    //------------------------------------------------------------------------------------------------------------------

    // Classify words
    std::string strBuf; // Create a buffer for the text file
    std::unordered_map<std::string, std::size_t> words; // Create a map in order to classify words
    while(txtFile){
        txtFile >> strBuf; // Read from space to space of txtFile
        // Delete non-alphanumeric characters from string classify
        if(!isalpha(strBuf[strBuf.length()-1])) strBuf.erase(strBuf.length()-1, 1);
        if(!isalpha(strBuf[0])) strBuf.erase(0, 1);
        words[strBuf]++; // Count how many times strBuf appears in text
    }
    std::unordered_map<std::string, std::size_t> compWords; // Create vector to store words that appear more than once
    std::size_t id = 0;
    for(auto & word : words){
        if(word.second >= 2) compWords[word.first] = id, id++; // Increase size of vector to add words
    }
    words.clear(); // Free up memory

    //------------------------------------------------------------------------------------------------------------------

    // Build compressed file
    for(auto & word : compWords){
        snfFile << std::to_string(word.second) << word.first << std::endl;
    }
    snfFile << "*-*-*" << std::endl;

    strBuf = "";
    txtFile.close();
    txtFile.open(txtFilePath, std::fstream::in);
    while(txtFile){
        char nextChar = (char)txtFile.get();
        if(!iswalnum(nextChar)){
            if(compWords.find(strBuf) != compWords.end()){
                snfFile << compWords[strBuf] << nextChar;
            }else{
                snfFile << strBuf << nextChar;
            }
            strBuf = "";
        }else {
            strBuf += nextChar;
        }
    }

    // CLOSE AND REMOVE FILE IN ORDER FOR EASIER TESTING
    snfFile.close();
    //fs::remove(snfFilePath);

    return 0;
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

/*
 * TODO: Set up a txt compression algorithm.
 * TODO: Set up an app for the use of the .snf file.
 * TODO: Set up an app for the creation of .snf from .txt.
 * TEST
 * */