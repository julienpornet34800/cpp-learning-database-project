#include <iostream>
#include <vector>
#include <string>

#include "../include/row.hpp"
#include "../include/character.hpp"

/*Friend function*/
std::ostream& operator<<(std::ostream& os, Character ch)
{
	os << ch._name;
	return os;
}

/*Operator*/
int Character::operator[](int pos)
{
	return _ans[pos];
}

/*Constructor & destructor*/
Character::Character(csv::Row row) : _status(true), _grade(0), _name(row["Name"])
{
	for(int i = 1; i < row.length(); i++)
	{	 
		_ans.push_back(stoi(row[i]));
	}
}

Character::~Character()
{}

/*Method*/
void Character::update_diff(std::vector<int> user_ans)
{
	std::vector<int> diff_ans;

	std::transform(_ans.begin(), _ans.end(), user_ans.begin(), std::back_inserter(diff_ans),
	[this](int elem1, int elem2)
	{
		return abs(elem1-elem2);
	});
	
	_grade = std::accumulate(diff_ans.begin(), diff_ans.end(), 0);
}

void Character::update_status(int current_ans, int expected_ans)
{
	if (abs(current_ans-expected_ans) <= 2 || expected_ans == 0)
	{ 
		_status = true;
	}
	else 
	{
		_status = false;
		std::cout << _name << "is eliminated !" << std::endl;
	}
}

bool Character::get_status()
{
	return _status;	
} 