#include <fstream>
#include <iostream>
#include <sstream>

#include "AST.hpp"
#include "BigInt.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Token.hpp"

int main(int argc, char* argv[]) {
    // Check arguments
    if (argc < 2 || argc > 3) {
        std::cerr
            << "Usage: " << argv[0]
            << " <input_filepath> <output_filepath> [optional: --print]\n";
        return 1;
    }

    // Read the input file
    std::cout << "Reading the input file...\n";
    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cerr << "Error: Couldn't open input file " << argv[1] << "\n";
        return 1;
    }
    std::stringstream buffer;
    buffer << input.rdbuf();
    std::string text = buffer.str();
    std::cout << "Finished reading the input!\n";

    try {
        // Lexing
        std::cout << "Starting lexer...\n";
        Lexer lexer(text);
        std::vector<Token> tokens = lexer.tokenize();
        std::cout << "Finished lexing!\n";

        // Parsing
        std::cout << "Starting parser...\n";
        Parser parser(tokens);
        std::unique_ptr<ASTNode> root = parser.parse();
        std::cout << "Finished parsing!\n";

        // insert optional AST optimization call here

        // Evaluation
        std::cout << "Starting evaluation...\n";
        BigInt result = root->evaluate();
        std::cout << "Finished evaluation!\n";

        // Convert to string
        std::cout << "Starting conversion to string...\n";
        const std::string result_str = result.toString();
        std::cout << "Finished conversion to string!\n";

        // Printing to output
        std::cout << "Starting to write to output file...\n";
        std::ofstream output(argv[2]);
        if (!output.is_open()) {
            std::cerr << "Error: Couldn't open output file " << argv[2] << "\n";
            return 1;
        }
        output << result_str;
        output.close();
        std::cout << "Finished writing to output file!\n";

        // Printing to cout
        if (argc == 3 && argv[3] == "print") {
            std::cout << "Starting to write to cout...\n\n";
            std::cout << result_str << "\n\n";
            std::cout << "Finished writing to cout!\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Error during execution: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
