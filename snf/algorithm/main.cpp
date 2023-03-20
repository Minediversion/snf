#include <iostream>
#include <filesystem>
#include <fstream>

bool isFileValid(std::string);

namespace fs = std::filesystem;

int main() {/*
    std::string txtFilePath; // C:\Users\marcr\CLionProjects\snf\test.txt
    std::getline(std::cin, txtFilePath); // Get file path*/
    std::string txtFilePath = R"(C:\Users\marcr\CLionProjects\snf\test.txt)"; // Test file path
    if(isFileValid(txtFilePath)){
        std::size_t directory = txtFilePath.find_last_of('\\'); // Get last occurrence of \ to get directory
        std::string snfFilePath = txtFilePath.substr(0, directory+1)
                + txtFilePath.substr(directory+1, txtFilePath.length()-4-directory)
                + "snf"; // Get the theoretical path were .snf would be
        if(!fs::exists(snfFilePath)) std::ofstream snfFile (snfFilePath, std::ofstream::out); //Create file, opened for writing
        else{
            //Check if user wants to overwrite file
            std::cout << "Do you want to overwrite existing .snf file? Y/N" << std::endl;
            char c; std::cin >> c;
            if(c == 'N') return 0;
            fs::remove(snfFilePath); //Deletes previous file
            std::ofstream snfFile (snfFilePath, std::ofstream::out); // Create file, opened for writing
        }
    }
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