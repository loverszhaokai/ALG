#include "major_element.h"

#include <stdio.h>

#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

#include "test.h"
#include "time_util.h"

using std::cout;
using std::endl;
using std::fstream;
using std::queue;
using std::string;
using std::stringstream;

extern fstream ofs;

static vector<string> in_files, out_files;

int create_nums(const string &_file_name, vector<int> *_nums)
{
	fstream infs(_file_name.c_str(), fstream::in);
	if (!infs) {
		fprintf(stderr, "failed to open(%s)\n", _file_name.c_str());
		return -1;
	}

	int val;
	string line;

	if (std::getline(infs, line)) {
		stringstream ss(line);
		int val;
		ss >> val;
		// cout << "n is : " << val << endl;
	}

	vector<int> nums;

	while (std::getline(infs, line)) {
		stringstream ss(line);
		while (ss >> val) {
			nums.push_back(val);
		}
	}

	*_nums = nums;
	infs.close();
	return 0;
}

int TEST_major_element_2()
{
	TimeUtil tu;

	if (0 != get_files("major_element_test_data/2", &in_files, &out_files))
		return -1;
	for (int iii = 0; iii < in_files.size(); iii++) {
		const string in_file_name = in_files[iii];
		vector<int> nums;

		create_nums(in_file_name, &nums);

		// Run
		ofs.open(OUTPUT_FILE, fstream::out);
		tu.restart();

		major_element_2(nums);

		tu.stop();
		ofs.close();

		if (0 != compare_file(out_files[iii], OUTPUT_FILE)) {
			cout << __FUNCTION__ << " failed  :" << endl;
			return -1;
		}
	}
	cout << __FUNCTION__ << "  total run time=" << tu.get_total_run_time() << "ms" << endl;

	return 0;
}

int TEST_major_element_3()
{
	TimeUtil tu;

	if (0 != get_files("major_element_test_data/3", &in_files, &out_files))
		return -1;
	for (int iii = 0; iii < in_files.size(); iii++) {
		const string in_file_name = in_files[iii];
		vector<int> nums;

		create_nums(in_file_name, &nums);

		// Run
		ofs.open(OUTPUT_FILE, fstream::out);
		tu.restart();

		major_element_3(nums);

		tu.stop();
		ofs.close();

		if (0 != compare_file(out_files[iii], OUTPUT_FILE)) {
			cout << __FUNCTION__ << " failed  :" << endl;
			return -1;
		}
	}
	cout << __FUNCTION__ << "  total run time=" << tu.get_total_run_time() << "ms" << endl;

	return 0;
}

int main()
{
	TimeUtil tu;
	if (0 != TEST_major_element_2())
		return -1;
	if (0 != TEST_major_element_3())
		return -1;

	cout << __FILE__ << "  total run time=" << tu.get_run_time() << "ms" << endl;

	return 0;
}
