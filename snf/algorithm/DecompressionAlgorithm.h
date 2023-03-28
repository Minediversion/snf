#ifndef SNF_DECOMPRESSIONALGORITHM_H
#define SNF_DECOMPRESSIONALGORITHM_H

#include <iostream>
#include <filesystem>
#include <fstream>
#include <cmath>

namespace snf {
    class DecompressionAlgorithm{
        public:
            static bool decompressFile(const std::string&, const std::string&);
    };
}

#endif //SNF_DECOMPRESSIONALGORITHM_H
