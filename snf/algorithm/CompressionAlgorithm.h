#ifndef SNF_COMPRESSIONALGORITHM_H
#define SNF_COMPRESSIONALGORITHM_H

#include <iostream>
#include <filesystem>
#include <fstream>

namespace snf {
    class CompressionAlgorithm{
        public:
            int compressFile(const std::string&);
            CompressionAlgorithm();

            std::string snfFilePathCom;
    };
}

#endif //SNF_COMPRESSIONALGORITHM_H
