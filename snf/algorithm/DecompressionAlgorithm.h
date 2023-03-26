#ifndef SNF_DECOMPRESSIONALGORITHM_H
#define SNF_DECOMPRESSIONALGORITHM_H

#include <iostream>
#include <filesystem>
#include <fstream>
#include <cmath>

namespace snf {
    class DecompressionAlgorithm{
        public:
            int decompressFile(const std::string&);
            DecompressionAlgorithm();

            std::string txtFilePathDecom;
    };
}

#endif //SNF_DECOMPRESSIONALGORITHM_H
