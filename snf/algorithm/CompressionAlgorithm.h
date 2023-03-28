#ifndef SNF_COMPRESSIONALGORITHM_H
#define SNF_COMPRESSIONALGORITHM_H

#include <iostream>
#include <filesystem>
#include <fstream>

namespace snf {
    class CompressionAlgorithm{
        public:
            static bool compressFile(const std::string&, const std::string&);
    };
}

#endif //SNF_COMPRESSIONALGORITHM_H
