#include <string>
#include <iostream>
#include <vector>		// creating the table of unknown size
#include <iomanip>		// formating when printing the table
using namespace std;

vector<vector<int>> calculate(vector<vector<int>> table, string str1, string str2);		// builds matrix
void print_table(vector<vector<int>> table);											// prints matrix
string* find_alignment(vector<vector<int>> table, string* arr);							// finds alignment

int main() {
	string str1;
	string str2;

	// recieve string input
	cout << "Enter first string: ";
	cin >> str1;
	cout << "Enter second string: ";
	cin >> str2;

	int len1 = str1.length() + 1;
	int len2 = str2.length() + 1;

	vector<vector<int>> table;

	// initialize table
	for (int i = 0; i < len1; i++) {
		vector<int> temp;
		for (int j = 0; j < len2; j++) {
			temp.push_back(0);
		}
		table.push_back(temp);
	}

	// fill in table
	table = calculate(table, str1, str2);

	// print the values to console
	print_table(table);

	// print the corner value as distance
	int distance = table[len1 - 1][len2 - 1];
	cout << "The edit distance is: " << distance << endl << endl;

	// pass string array to calculate alignment
	string arr[] = { str1, str2 };
	string* alignment = find_alignment(table, arr);

	cout << "Alignment is:" << endl;
	cout << alignment[0] << endl;
	cout << alignment[1] << endl;
	return 0;
}

vector<vector<int>> calculate(vector<vector<int>> table, string str1, string str2) {
	int len1 = str1.length() + 1;
	int len2 = str2.length() + 1;


	for (int i = 0; i < len1; i++) {
		table[i][0] = i;
	}
	for (int i = 0; i < len2; i++) {
		table[0][i] = i;
	}

	int left, upper, upper_left = 0;

	for (int i = 1; i < len1; i++) {
		for (int j = 1; j < len2; j++) {
			left = table[i][j - 1];
			upper = table[i - 1][j];
			upper_left = table[i - 1][j - 1];

			if (str1[i - 1] == str2[j - 1]) {
				table[i][j] = upper_left;
			} else if (upper_left < left && upper_left < upper) {
				table[i][j] = upper_left + 1;
			} else if (upper < left) {
				table[i][j] = upper + 1;
			} else {
				table[i][j] = left + 1;
			}
		}
	}

	return table;
}

void print_table(vector<vector<int>> table) {
	int len1 = table.size();
	int len2 = table[0].size();

	cout << "   ";
	for (int i = 0; i < len2; i++) {
		cout << setw(5) << i;
	}
	cout << endl;

	for (int j = 0; j < len1; j++) {
		cout << "     ";
		for (int i = 0; i < len2; i++) {
			cout << "---- ";
		}
		cout << endl;

		cout << setw(3) << j << " |";

		for (int i = 0; i < len2; i++) {
			cout << setw(3) << table[j][i] << " |";
		}
		cout << endl;
	}

	cout << "     ";
	for (int i = 0; i < len2; i++) {
		cout << "---- ";
	}
	cout << endl;
}

string* find_alignment(vector<vector<int>> table, string* arr) {
	string str1 = "";
	string str2 = "";
	int i = arr[0].length();
	int j = arr[1].length();

	int left, upper, upper_left;

	while (i > 0 || j > 0) {
		if (i < 1) {
			left = table[i][j - 1];
			upper = INT_MAX;
			upper_left = INT_MAX;
		} else if (j < 1) {
			left = INT_MAX;
			upper = table[i - 1][j];
			upper_left = INT_MAX;
		} else {
			left = table[i][j - 1];
			upper = table[i - 1][j];
			upper_left = table[i - 1][j - 1];
		}

		if (upper_left <= upper && upper_left <= left) {
			str1 = str1.insert(0, 1, arr[0][i - 1]);
			str2 = str2.insert(0, 1, arr[1][j - 1]);
			i--;
			j--;
		} else if (left <= upper) {
			str1 = str1.insert(0, 1, '_');
			str2 = str2.insert(0, 1, arr[1][j - 1]);
			j--;
		} else {
			str1 = str1.insert(0, 1, arr[0][i - 1]);
			str2 = str2.insert(0, 1, '_');
			i--;
		}
	}
	arr[0] = str1;
	arr[1] = str2;

	return arr;
}
