#include <iostream>
#include <vector>
#include <map>

#include "row.hpp"

#ifndef CHARACTER_H
#define CHARACTER_H

class Character 
{
	friend std::ostream& operator<<(std::ostream& os, Character ch);

	public:
		Character(csv::Row row);
		~Character();

		void update_status(int current_ans, int expected_ans);
		void update_diff(std::vector<int> user_ans);

		bool get_status();

		int operator[](int pos);

	private:
		bool _status;
		int _grade;
		std::string _name;
		std::vector<int> _ans;
};

#endif