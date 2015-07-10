#include "test.h"

#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include <dirent.h>

using std::cout;
using std::endl;
using std::fstream;
using std::stringstream;

fstream ofs;

int str_to_int(const string &_str)
{
	stringstream ss(_str);
	int val;
	ss >> val;
	return val;
}

int get_files(const string &_path, vector<string> *_in_files, vector<string> *_out_files)
{
	DIR *dir;
	struct dirent *ent;
	const string path = _path + "/input/";
	const string out_path = _path + "/output/";
	vector<string> in_files, out_files;
	string file_name;

	dir = opendir(path.c_str());
	if (NULL == dir) {
		printf("path=%s\n", path.c_str());
		perror("opendir()");
		return -1;
	}
	while (true) {
		ent = readdir(dir);
		if (NULL == ent)
			break;
		file_name = string(ent->d_name);
		if ('.' != file_name[0]) {
			in_files.push_back(path + file_name);
			out_files.push_back(out_path + file_name);
		}
	}
	closedir(dir);

	std::sort(in_files.begin(), in_files.end());
	std::sort(out_files.begin(), out_files.end());

	*_in_files = in_files;
	*_out_files = out_files;
	return 0;
}

int compare_file(const string &_left_file, const string &_right_file)
{
// cout << "_left_file=" << _left_file << " _right_file=" << _right_file << endl;
	fstream left_fs(_left_file.c_str(), fstream::in);
	fstream right_fs(_right_file.c_str(), fstream::in);

	if (!left_fs) {
		fprintf(stderr, "file=%s does not exist\n", _left_file.c_str());
		cout << "expected:" << _left_file << endl;
		cout << "actual  :" << _right_file << endl;
		return 1;
	}
	if (!right_fs) {
		fprintf(stderr, "file=%s does not exist\n", _right_file.c_str());
		cout << "expected:" << _left_file << endl;
		cout << "actual  :" << _right_file << endl;
		return 1;
	}

	string left_line, right_line;
	bool left_flag = false;
	bool right_flag = true;

	while (true) {
		if (std::getline(left_fs, left_line))
			left_flag = true;
		else
			left_flag = false;
		if (std::getline(right_fs, right_line))
			right_flag = true;
		else
			right_flag = false;
		if (left_flag && right_flag && left_line != right_line)
			goto diff;
		if (!left_flag || !right_flag)
			break;
	}

	if (left_flag || right_flag)
		goto diff;

	left_fs.close();
	right_fs.close();
	return 0;

diff:
	left_fs.close();
	right_fs.close();
	cout << "expected:" << _left_file << endl;
	cout << "actual  :" << _right_file << endl;
	return 1;
}
