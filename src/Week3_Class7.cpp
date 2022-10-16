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
	// перебираем всю историю в хронологическом пор€дке
	for (const auto &item : names_by_year) {
		// если очередное им€ не относитс€ к будущему и отличаетс€ от предыдущего,
		if (item.first <= year
				&& (names.empty() || names.back() != item.second)) {
			// добавл€ем его в историю
			names.push_back(item.second);
		}
	}
	return names;
}

string BuildJoinedName(vector<string> names) {
	// нет истории Ч им€ неизвестно
	if (names.empty()) {
		return "";
	}
	// мен€ем пр€мой хронологический пор€док на обратный
	reverse(begin(names), end(names));

	// начинаем строить полное им€ с самого последнего
	string joined_name = names[0];

	// перебираем все последующие имена
	for (size_t i = 1; i < names.size(); ++i) {
		if (i == 1) {
			// если это первое Ђисторическоеї им€, отдел€ем его от последнего скобкой
			joined_name += " (";
		} else {
			// если это не первое им€, отдел€ем от предыдущего зап€той
			joined_name += ", ";
		}
		// и добавл€ем очередное им€
		joined_name += names[i];
	}

	// если в истории было больше одного имени, мы открывали скобку Ч закроем еЄ
	if (names.size() > 1) {
		joined_name += ")";
	}
	// им€ со всей историей готово
	return joined_name;
}

// см. решение предыдущей задачи
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
		// найдЄм историю изменений имени и фамилии
		// в данном случае это излишне, так как нам достаточно узнать последние им€ и фамилию, но почему бы не использовать готовые функции?
		vector<string> first_names_history = FindFirstNamesHistory(year1);
		vector<string> last_names_history = FindLastNamesHistory(year1);

		// подготовим данные дл€ функции BuildFullName: возьмЄм последние им€ и фамилию или оставим их пустыми, если они неизвестны
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
		// получим полное им€ со всей историей
		const string first_name = BuildJoinedName(FindFirstNamesHistory(year1));
		// получим полную фамилию со всей историей
		const string last_name = BuildJoinedName(FindLastNamesHistory(year1));
		// объединим их с помощью готовой функции
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
