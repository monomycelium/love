#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cinttypes>
#include "json.h"
#include "curl.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        std::fprintf(stderr, "usage: %s <NAME_ONE> <NAME_TWO>\n", argv[0]);
        std::printf("\n%s: find the chances of success in a relationship using the name of each party.\n", argv[0]);
        return EXIT_FAILURE;
    }

    std::string input = calculate(argv[1], argv[2]); // TODO: use curl
    if (input == std::string{}) return EXIT_FAILURE;

    Love love(input);
    if (love.percentage == 0xff) return EXIT_FAILURE;

    std::printf("%s * %s -> %" PRIu8 "%% (%s)\n", love.fname.c_str(), love.sname.c_str(), love.percentage, love.result.c_str()); // TODO: use built-in formatters
    return EXIT_SUCCESS;
}
