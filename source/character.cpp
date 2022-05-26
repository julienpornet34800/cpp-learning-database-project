#include <iostream>
#include <vector>
#include <string>

#include "../include/row.hpp"
#include "../include/character.hpp"

#ifndef CHARACTER_C
#define CHARACTER_C

/*Friend function*/
std::ostream& operator<<(std::ostream& os, Character const ch) 
{
	os << ch._name;
	return os;
}

/*Operator*/

/*Constructor & destructor*/
Character::Character(Row row) : Row(row), _status(true), _grade(0), _name(_content[0])
{
	for(int i = 1; i < get_length(); i++)
		_ans.push_back(stoi(_content[i]));
}
 
Character::~Character()
{}

/*Member function*/
void Character::update_status(int current_ans, int expected_ans)
{
	/*Check if :
	- values are enouch far
	- expected answer is know, if unknow the character may not be elminated
	- character is already eliminated, may be eliminated just one time
	*/
	if (abs(current_ans-expected_ans) > 2 && expected_ans != 0 && _status == true)
	{ 	
		_status = false;
	}
}

bool Character::get_status() const
{
	return _status;	
} 

int Character::get_grade() const
{
	return _grade;	
} 

int Character::get_ans(int pos) const
{
	return _ans[pos];
}

std::string Character::get_name() const
{
	return _name;
}

#endif