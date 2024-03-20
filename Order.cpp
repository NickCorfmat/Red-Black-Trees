// --------------------------------------------------------------
// Nicolas Corfmat
// CruzID: ncorfmat
// Assignment: pa8
// --------------------------------------------------------------

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>

#include "Dictionary.h"

using namespace std;

int main(int argc, char * argv[]) {

	// CHECK for exactly two command line arguments.

	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
		return EXIT_FAILURE;
	}

	// OPEN input and output files.

        std::ifstream input(argv[1]);
        std::ofstream output(argv[2]);

        // CHECK if input and output files are valid.

        if (!input) {
                std::cerr << "Failed to access input file." << endl;
                return EXIT_FAILURE;
        }

        if (!output) {
                std::cerr << "Failed to access output file." << endl;
                return EXIT_FAILURE;
        }

	Dictionary D;

	std::string line;
	int line_num = 1;

	while(std::getline(input, line)) {
		D.setValue(line, line_num);
		line_num++;
	}

	output << D.to_string() << endl;
	output << D.pre_string() << endl;

	// CLOSE files.
	
	input.close();
	output.close();


	return EXIT_SUCCESS;
}
