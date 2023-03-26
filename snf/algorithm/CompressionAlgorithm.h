#ifndef SNF_COMPRESSIONALGORITHM_H
#define SNF_COMPRESSIONALGORITHM_H

#include <iostream>
#include <filesystem>
#include <fstream>

namespace snf {
    class CompressionAlgorithm{
        public:
            static int compressFile(const std::string&);
            CompressionAlgorithm();
    };
}

#endif //SNF_COMPRESSIONALGORITHM_H
