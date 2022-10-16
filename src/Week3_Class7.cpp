//============================================================================
// Name        : Week3_Class7.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

vector<string> FindNamesHistory(const map<int, string> &names_by_year,
		const int &year) {
	vector<string> names;
	// ���������� ��� ������� � ��������������� �������
	for (const auto &item : names_by_year) {
		// ���� ��������� ��� �� ��������� � �������� � ���������� �� �����������,
		if (item.first <= year
				&& (names.empty() || names.back() != item.second)) {
			// ��������� ��� � �������
			names.push_back(item.second);
		}
	}
	return names;
}

string BuildJoinedName(vector<string> names) {
	// ��� ������� � ��� ����������
	if (names.empty()) {
		return "";
	}
	// ������ ������ ��������������� ������� �� ��������
	reverse(begin(names), end(names));

	// �������� ������� ������ ��� � ������ ����������
	string joined_name = names[0];

	// ���������� ��� ����������� �����
	for (size_t i = 1; i < names.size(); ++i) {
		if (i == 1) {
			// ���� ��� ������ ������������� ���, �������� ��� �� ���������� �������
			joined_name += " (";
		} else {
			// ���� ��� �� ������ ���, �������� �� ����������� �������
			joined_name += ", ";
		}
		// � ��������� ��������� ���
		joined_name += names[i];
	}

	// ���� � ������� ���� ������ ������ �����, �� ��������� ������ � ������� �
	if (names.size() > 1) {
		joined_name += ")";
	}
	// ��� �� ���� �������� ������
	return joined_name;
}

// ��. ������� ���������� ������
string BuildFullName(const string &first_name, const string &last_name) {
	if (first_name.empty() && last_name.empty()) {
		return "Incognito";
	} else if (first_name.empty()) {
		return last_name + " with unknown first name";
	} else if (last_name.empty()) {
		return first_name + " with unknown last name";
	} else {
		return first_name + " " + last_name;
	}
}

class Person {
public:
	void ChangeFirstName(const int &year1, const string &first_name) {
		if (year <= year1) {
			first_names[year1] = first_name;
		}
	}
	void ChangeLastName(const int &year1, const string &last_name) {
		if (year <= year1) {
			last_names[year1] = last_name;
		}
	}

	Person(const string &new_name, const string &new_surname,
			const int &birth_year) {
		name = new_name;
		surname = new_surname;
		year = birth_year;
		first_names[birth_year] = new_name;
		last_names[birth_year] = new_surname;
	}

	string GetFullName(const int &year1) const {
		if (year > year1) {
			return "No person";
		}
		// ����� ������� ��������� ����� � �������
		// � ������ ������ ��� �������, ��� ��� ��� ���������� ������ ��������� ��� � �������, �� ������ �� �� ������������ ������� �������?
		vector<string> first_names_history = FindFirstNamesHistory(year1);
		vector<string> last_names_history = FindLastNamesHistory(year1);

		// ���������� ������ ��� ������� BuildFullName: ������ ��������� ��� � ������� ��� ������� �� �������, ���� ��� ����������
		string first_name;
		string last_name;
		if (!first_names_history.empty()) {
			first_name = first_names_history.back();
		}
		if (!last_names_history.empty()) {
			last_name = last_names_history.back();
		}
		return BuildFullName(first_name, last_name);
	}

	string GetFullNameWithHistory(const int &year1) const {
		if (year > year1) {
			return "No person";
		}
		// ������� ������ ��� �� ���� ��������
		const string first_name = BuildJoinedName(FindFirstNamesHistory(year1));
		// ������� ������ ������� �� ���� ��������
		const string last_name = BuildJoinedName(FindLastNamesHistory(year1));
		// ��������� �� � ������� ������� �������
		return BuildFullName(first_name, last_name);
	}

private:
	vector<string> FindFirstNamesHistory(int year) const {
		return FindNamesHistory(first_names, year);
	}
	vector<string> FindLastNamesHistory(int year) const {
		return FindNamesHistory(last_names, year);
	}

	map<int, string> first_names;
	map<int, string> last_names;
	string name;
	string surname;
	int year;
};

int main() {
	Person person("-1_first", "-1_last", -1);

	int year = -3;
	person.ChangeFirstName(year, std::to_string(year) + "_first");
	person.ChangeLastName(year, std::to_string(year) + "_last");

	year = 7;
	std::cout << "year: " << year << '\n';
	std::cout << person.GetFullNameWithHistory(year) << '\n';
	std::cout << person.GetFullName(year) << '\n';

	return 0;
}
