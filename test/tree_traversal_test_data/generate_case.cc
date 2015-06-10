#include <cmath>
#include <cstring>

#include <iostream>
#include <string>
#include <sstream>

using std::cout;
using std::endl;
using std::string;
using std::stringstream;

void print_tree(const int type, const int height)
{
	for (int iii = 1; iii <= height; iii++) {
		if (1 == type)
			cout << iii << " ";

		const int num = pow(2.0, iii - 1) - 1;
		string str = string(2 * num, ' ');

		for (int jjj = 0; jjj < num; jjj++)
			str[2 * jjj] = '#';

		if (2 == type) {
			cout << str << iii;
		} else {
			cout << str.substr(0, str.size() - 1);
		}
		cout << endl;
	}
}

int main(int argc, char **argv)
{
	if (3 != argc) {
		cout << "usage: ./a.out 1/2 Height\n" << endl;
		return 0;
	}

	string str;
	stringstream ss;
	int type;
	int height;

	str = string(argv[1]);
	ss << str << ' ';
	ss >> type;

	str = string(argv[2]);
	ss << str;
	ss >> height;

	print_tree(type, height);
}
