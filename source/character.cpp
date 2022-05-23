#include <iostream>
#include <vector>
#include <string>

#include "../include/row.hpp"
#include "../include/character.hpp"

template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> v)
{
	std::for_each(v.begin(), v.end(), [&os](T elem)
	{
		os << elem << "\t";
	});
	return os;
}

/*Friend function*/
std::ostream& operator<<(std::ostream& os, Character ch)
{
	os << ch._name;
	return os;
}

/*Operator*/

/*Constructor & destructor*/
Character::Character(Row row) : Row(row), _status(true), _grade(0), _name(_content[0])
{
	for(int i = 1; i < length(); i++)
	{	 
		_ans.push_back(stoi(_content[i]));
	}
	//std::cout << _ans << std::endl;
}
 
Character::~Character()
{}

/*Member function*/
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
		if(_status == true) std::cout << _name << " is eliminated !" << std::endl;
		
		_status = false;
	}
}

bool Character::get_status()
{
	return _status;	
} 

int Character::get_grade()
{
	return _grade;	
} 

int Character::get_ans(int pos)
{
	return _ans[pos];
}