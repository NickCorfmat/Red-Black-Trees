// --------------------------------------------------------------
// Nicolas Corfmat
// CruzID: ncorfmat
// Assignment: pa8
// --------------------------------------------------------------

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <stdexcept>

#include "Dictionary.h"

using namespace std;

void parse(const std::string& line, Dictionary& D) {
	std::string word;
	std::string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";

	size_t start = 0;
	
	while (start != std::string::npos) {
		start = line.find_first_not_of(delim, start);

		if (start != std::string::npos) {
			size_t end = line.find_first_of(delim, start);

			if (end == std::string::npos) {
				end = line.length();
			}

			word = line.substr(start, end - start);

			for (char& c : word) {
				c = tolower(c);
			}

			if (word.length() > 0) {
				if (D.contains(word)) {
					D.getValue(word)++;
				} else {
					D.setValue(word, 1);
				}
			}

			start = end + 1;
		}
	}
}

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

        while(std::getline(input, line)) {
		parse(line, D);
        }

        output << D << endl;

        // CLOSE files.

        input.close();
        output.close();

	return EXIT_SUCCESS;
}


