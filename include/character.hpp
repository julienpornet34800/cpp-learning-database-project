/*Standart include*/
#include <iostream>
#include <vector>

/*Personnal include*/
#include "row.hpp"
#include "csv_parser.hpp"

#ifndef CHARACTER_H
#define CHARACTER_H

class Character : public csv::Row
{
	friend std::ostream& operator<<(std::ostream& os, Character ch);

	public:
		Character(Row row);
		~Character();

		void update_status(int current_ans, int expected_ans);
		void update_diff(std::vector<int> user_ans);

		bool get_status();
		int get_grade();
		int get_ans(int pos);

	private:
		bool _status;
		int _grade;
		std::string _name;
		std::vector<int> _ans;
};

#endif