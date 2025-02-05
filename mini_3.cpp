#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>


using namespace std;


void print_help(const char *arg0) {
	cout << "Usage: " << arg0 << " {REPO_DIR} {BAD_COMMIT} {GOOD_COMMIT} \"{command_to_execute}\"\n\n";
}

void load_commits(const char *dir, vector<string> &buff) {
	string fdir = dir;
	if (dir[fdir.size() - 1] != '/')
		fdir += "/";
	fdir += ".git/logs/HEAD";
	ifstream file;
	file.open(fdir);

	string line;

	while (getline(file, line)) {
		string commit;
		bool flag = false;
		for (char &c : line) {
			if (c == ' ') {
				if (!flag) {
					flag = true;
					continue;
				} else {
					buff.push_back(commit);
					break;
				}
			}
			if (flag)
				commit += c;
		}
	}

	reverse(buff.begin(), buff.end());
	file.close();

	if (!buff.size()) {
		cout << "NO COMMTIS FOUND\n";
		exit(1);
	}
}

void bin_search(vector<string> &commits, string left_name, string right_name, string test_cmd) {

	int left = 0, right = 0;

	for (int i = 0; i < commits.size(); i++) {
		if (!commits[i].rfind(left_name, 0))
			left = i;
		if (!commits[i].rfind(right_name, 0))
			right = i;
	}

	if (right < left) {
		cout << "INVALID COMMITS RANGE\n";
		exit(1);
	}

	while (left != right) {
		int mid = (left + right) / 2;
		system(("git checkout " + commits[mid] + " > /dev/null").c_str());
		if (!system((test_cmd + " > /dev/null").c_str())) {
			right = mid - 1;
		} else {
			left = mid;
		}
	}

	cout << "found bad commit: " << commits[right] << '\n';
}


signed main(int argc, char const *argv[])
{
	if (argc != 5) {
		print_help(argv[0]);
		return 0;
	}
	vector<string> commits;
	load_commits(argv[1], commits);

	string left_name = argv[2];
	string right_name = argv[3];
	string test_cmd = argv[4];
	bin_search(commits, left_name, right_name, test_cmd);

	// return to master branch
	system("git checkout master > /dev/null");

	return 0;
}
