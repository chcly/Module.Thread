#include <iostream>

#include "oneapi/tbb.h"



int main(int argc, char** argv)
{
    int max = oneapi::tbb::v1::info::default_concurrency();

    std::cout << "max " << max;
    std::cout << std::endl;


    return 0;
}
