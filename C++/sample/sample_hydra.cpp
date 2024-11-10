#include <iostream>
#include <e3475/hydra.hpp>

int main()
{
    try {
        e3475::hydra sample1("9223372036854775807");
        e3475::hydra sample2("-7FFFFFFFFFFFFFFF", 16);
        e3475::hydra sample3 = sample1 * -sample2;

        std::cout << sample1.finalize<std::string>(10) << std::endl;
        std::cout << sample2.finalize<std::string>(10) << std::endl;
        std::cout << sample3.finalize<std::string>(10) << std::endl;
        std::cout << sample3.finalize<std::string>(16) << std::endl;
    }
    catch (std::exception& exp) {
        std::cout << exp.what() << std::endl;
    }
}
