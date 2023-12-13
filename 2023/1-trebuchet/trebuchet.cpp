#include <iostream>
#include <fstream>
#include <cstring>

int main()
{
	std::ifstream input( "input.txt" );

	if ( !input.is_open() ) {
		return -1;
	}

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
				}
			}

			if ( one == -1 ) {
				char second = line.at(length - 1 - i);
				if ( second >= '0' && second <= '9') {
					one = second - '0';
				}
			}

			if ( ten > -1 && one > -1 ) {
				break;
			}

		}
			total = total + (ten * 10 + one);
	}

	input.close();

	std::ofstream output("output.txt", std::ofstream::out);
	output << total;
	output.close();
}