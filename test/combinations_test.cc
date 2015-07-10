#include "combinations.h"

#include <stdio.h>

#include <algorithm>
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

int get_input(const string &_file_name, int *_n, int *_k)
{
	fstream infs(_file_name.c_str(), fstream::in);
	if (!infs) {
		fprintf(stderr, "failed to open(%s)\n", _file_name.c_str());
		return -1;
	}

	int val;
	string line;
	int n = -1;
	int k = -1;

	if (std::getline(infs, line)) {
		stringstream ss(line);

		while (ss >> val) {
			if (-1 == n) {
				n = val;
			} else if (-1 == k) {
				k = val;
				break;
			}
		}
	}

	*_n = n;
	*_k = k;
	infs.close();
	return 0;
}

int get_matrix(const string &_file_name, vector<vector<int> > *_matrix)
{
	fstream infs(_file_name.c_str(), fstream::in);
	if (!infs) {
		fprintf(stderr, "failed to open(%s)\n", _file_name.c_str());
		return -1;
	}

	int val;
	string line;

	vector<vector<int> > matrix;
	while (std::getline(infs, line)) {
		stringstream ss(line);
		vector<int> nums;
		while (ss >> val)
			nums.push_back(val);
		matrix.push_back(nums);
	}

	*_matrix = matrix;
	infs.close();
	return 0;
}

int TEST_combinations_kai()
{
	TimeUtil tu;

	if (0 != get_files("combinations_test_data/", &in_files, &out_files))
		return -1;
	for (int iii = 0; iii < in_files.size(); iii++) {
		const string in_file_name = in_files[iii];

		int n, k;
		get_input(in_file_name, &n, &k);

		// Run
		tu.restart();

		vector<vector<int> > ans = combine_kai(n, k);

		tu.stop();

		vector<vector<int> > expected_ans;
		get_matrix(out_files[iii], &expected_ans);

		std::sort(ans.begin(), ans.end());
		std::sort(expected_ans.begin(), expected_ans.end());

		if (ans != expected_ans) {
			cout << __FUNCTION__ << " case " << iii + 1 << " failed  :" << endl;
			return -1;
		}
	}
	cout << __FUNCTION__ << "  total run time=" << tu.get_total_run_time() << "ms" << endl;

	return 0;
}

int TEST_combinations_backtrack()
{
	TimeUtil tu;

	if (0 != get_files("combinations_test_data/", &in_files, &out_files))
		return -1;
	for (int iii = 0; iii < in_files.size(); iii++) {
		const string in_file_name = in_files[iii];

		int n, k;
		get_input(in_file_name, &n, &k);

		// Run
		tu.restart();

		vector<vector<int> > ans = combine_backtrack(n, k);

		tu.stop();

		vector<vector<int> > expected_ans;
		get_matrix(out_files[iii], &expected_ans);

		std::sort(ans.begin(), ans.end());
		std::sort(expected_ans.begin(), expected_ans.end());

		if (ans != expected_ans) {
			cout << __FUNCTION__ << " case " << iii + 1 << " failed  :" << endl;
			return -1;
		}
	}
	cout << __FUNCTION__ << "  total run time=" << tu.get_total_run_time() << "ms" << endl;

	return 0;
}

int TEST_combinations_01()
{
	TimeUtil tu;

	if (0 != get_files("combinations_test_data/", &in_files, &out_files))
		return -1;
	for (int iii = 0; iii < in_files.size(); iii++) {
		const string in_file_name = in_files[iii];

		int n, k;
		get_input(in_file_name, &n, &k);

		// Run
		tu.restart();

		vector<vector<int> > ans = combine_01(n, k);

		tu.stop();

		vector<vector<int> > expected_ans;
		get_matrix(out_files[iii], &expected_ans);

		std::sort(ans.begin(), ans.end());
		std::sort(expected_ans.begin(), expected_ans.end());

		if (ans != expected_ans) {
			cout << __FUNCTION__ << " case " << iii + 1 << " failed  :" << endl;
			return -1;
		}
	}
	cout << __FUNCTION__ << "  total run time=" << tu.get_total_run_time() << "ms" << endl;

	return 0;
}

int TEST_combinations_bit_operation()
{
	TimeUtil tu;

	if (0 != get_files("combinations_test_data/", &in_files, &out_files))
		return -1;
	for (int iii = 0; iii < in_files.size(); iii++) {
		const string in_file_name = in_files[iii];

		int n, k;
		get_input(in_file_name, &n, &k);

		// Run
		tu.restart();

		vector<vector<int> > ans = combine_bit_operation(n, k);

		tu.stop();

		vector<vector<int> > expected_ans;
		get_matrix(out_files[iii], &expected_ans);

		std::sort(ans.begin(), ans.end());
		std::sort(expected_ans.begin(), expected_ans.end());

		if (ans != expected_ans) {
			cout << __FUNCTION__ << " case " << iii + 1 << " failed  :" << endl;
			return -1;
		}
	}
	cout << __FUNCTION__ << "  total run time=" << tu.get_total_run_time() << "ms" << endl;

	return 0;
}

int main()
{
	TimeUtil tu;
	if (0 != TEST_combinations_kai())
		return -1;
	if (0 != TEST_combinations_backtrack())
		return -1;
	if (0 != TEST_combinations_01())
		return -1;
	if (0 != TEST_combinations_bit_operation())
		return -1;

	cout << __FILE__ << "  total run time=" << tu.get_run_time() << "ms" << endl;

	return 0;
}
