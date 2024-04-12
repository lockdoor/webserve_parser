#include "Configs.hpp"

int main(void)
{
    try{
        // std::ifstream file("default.conf");
        cfg::Configs configs("default.conf");
        std::cout << configs << std::endl;
    }
    catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
    }
    return (0);
}