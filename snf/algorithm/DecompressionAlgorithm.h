#ifndef SNF_DECOMPRESSIONALGORITHM_H
#define SNF_DECOMPRESSIONALGORITHM_H

#include <iostream>
#include <filesystem>
#include <fstream>
#include <cmath>

namespace snf {
    class DecompressionAlgorithm{
    public:
        static int decompressFile(const std::string&);
        DecompressionAlgorithm();
    };
}

#endif //SNF_DECOMPRESSIONALGORITHM_H
