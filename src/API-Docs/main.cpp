#include "APIGenerator.hpp"

auto main(int argc, char *argv[]) -> int {
    
    auto apiGenerator = new quick::APIGenerator();
    
    return apiGenerator->execute();
}
