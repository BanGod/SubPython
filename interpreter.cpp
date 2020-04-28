#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>
#include <stack>

#include "parser/parser.hpp"

int main(int argc, char* argv[]) {
	if (argc != 2) {
    	std::cerr << "expected argument" << std::endl;
    	return 1;
  	}

	try {
		std::ifstream input(argv[1]);

		execution::Context context;
		Parser parser(input);
		parser.Run(context);
		
		while (context.operation_index < parser.operations.size()) {
			const auto& operation = parser.operations[context.operation_index];
			++context.operation_index;
			operation->Do(context);
		} 
    	return 0;
	}
	catch (CustomException& e) {
		std::cerr << e.what();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}