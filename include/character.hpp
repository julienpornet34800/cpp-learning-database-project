#include <iostream>
#include <vector>

#include "row.hpp"

#ifndef CHARACTER_H
#define CHARACTER_H

class Character 
{
	friend std::ostream& operator<<(std::ostream& os, Character ch);

	public:
		Character(csv::Row row);
		~Character();

		void update_status(std::vector<int> user_ans);

		int operator[](int pos);

	private:
		bool _next_in_line;
		int _grade;
		std::string _name;
		std::vector<int> _ans;
};

#endif