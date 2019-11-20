#include <string>
#include <iostream>
#include <vector>
using namespace std;



vector<vector<int>> calculate(vector<vector<int>> table, string str1, string str2);
void print_table(vector<vector<int>> table);
string* find_alignment(string* arr, vector<vector<int>> table);

int main() {
	string str1 = "088128367890";
	string str2 = "9990126790";
	/*cout << "Enter first string\n";
	cin >> str1;
	cout << "Enter second string\n";
	cin >> str2;*/

	int len1 = str1.length() + 1;
	int len2 = str2.length() + 1;

	vector<vector<int>> table;

	for (int i = 0; i < len1; i++) {
		vector<int> temp;
		for (int j = 0; j < len2; j++) {
			temp.push_back(0);
		}
		table.push_back(temp);
	}


	table = calculate(table, str1, str2);
	print_table(table);

	int distance = table[len1 - 1][len2 - 1];

	cout << "The edit distance is: " << distance << endl << endl;

	string arr[] = { str1, str2 };
	string *alignment = find_alignment(arr, table);


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

	cout << "     ";
	for (int i = 0; i < len2; i++) {
		cout << "  " << i << "  ";
	}
	cout << endl;

	for (int j = 0; j < len1; j++) {
		cout << "     ";
		for (int i = 0; i < len2; i++) {
			cout << "---- ";
		}
		cout << endl;

		cout << "  " << j << " |";
		for (int i = 0; i < len2; i++) {
			cout << "  " << table[j][i] << " |";
		}
		cout << endl;
	}

	cout << "     ";
	for (int i = 0; i < len2; i++) {
		cout << "---- ";
	}
	cout << endl;
}

string* find_alignment(string* arr, vector<vector<int>> table) {
	string str1 = "";
	string str2 = "";
	int len1 = arr[0].length() - 1;
	int len2 = arr[1].length() - 1;

	for (int i = 5; i >= 0; i--) {

	}

	cout << str1 << endl;
	cout << str2 << endl;

	return arr;
}
