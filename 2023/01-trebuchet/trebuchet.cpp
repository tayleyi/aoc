#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

int main()
{
	std::ifstream input( "input.txt" );

	if ( !input.is_open() ) {
		return -1;
	}

	std::vector<std::string> numbers = {
			"zero", "one", "two", "three", "four",
			"five", "six", "seven", "eight", "nine"
	};

	int total = 0;
	int count = 0;

	for ( std::string line; getline( input, line ); ) {
		int length = line.length();
		int ten = -1;
		int one = -1;
		for ( int i = 0; i < length; i++ ) {
			if ( ten == -1 ) {
				char first = line.at(i);
				if ( first >= '0' && first <= '9' ) {
					ten = first - '0';
					int current_index = i;
					for ( int j = 1; j < 10; j++ ) {
						std::size_t found_index = line.find( numbers[j] );
						if ( found_index < current_index ) {
							current_index = found_index;
							ten = j;
						}
					}
				}
			}

			if ( one == -1 ) {
				int current_index = length - 1 - i;
				char second = line.at(length - 1 - i);
				if ( second >= '0' && second <= '9') {
					one = second - '0';
				}
				std::string subline = line.substr( current_index, length );
				for ( int j = 1; j < 10; j++ ) {
					std::size_t found_index = subline.find( numbers[j] );
					if ( found_index != std::string::npos ) {
						one = j;
					}
				}
			}

			if ( ten > -1 && one > -1 ) {
				break;
			}

		}

		if ( ten == -1 ) {
			int min_index = length;
			for ( int i = 1; i < 10; i++ ) {
				std::size_t found_index = line.find( numbers[i] );
				if ( found_index < min_index ) {
					min_index = found_index;
					ten = i;
				}
			}
		}

		if ( one == -1 ) {
			for ( int i = 1; i < 10; i++ ) {
				std::string subline = line.substr( length - i, length );
				for ( int j = 1; j < 10; j++ ) {
					std::size_t found_index = line.find( numbers[i] );
					if (found_index != std::string::npos ) {
						one = j;
						break;
					}
				}
			}
		}
		total = total + (ten * 10 + one);
		std::cout << line << "(" << count << "): " << (ten * 10 + one) << "\n";
		count++;
	}

	input.close();

	std::ofstream output("output.txt", std::ofstream::out);
	output << total;
	output.close();
}