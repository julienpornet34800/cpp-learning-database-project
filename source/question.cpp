#include <iostream>
#include <string>
#include <vector>
#include <array>

#include "../include/question.hpp"

/*Constructor & Destructor*/
Question::Question(int id, csv::Row row, std::vector<Character> character_vector) : _id(id), _statement(row[0]), _relevance(1), _already_asked(false)
{
	for(size_t i = 0; i < character_vector.size(); i++)
		_ans.push_back(character_vector[i].get_ans(_id));

	for(size_t i = 1; i < N_ANSWER; i++)
		_rep_ans[i] = 0;
}

Question::~Question()
{}

/*Member operator*/
int Question::operator[](int pos)
{
	return _ans[pos];
}

std::ostream& operator<<(std::ostream& os, Question q)
{
	q._already_asked = true;
	os << q._statement;
	return os;
}

/*Member function*/
void Question::update_answer(std::vector<Character> character_vector)
{
	
	for(size_t i = 0; i < character_vector.size(); i++)
	{	
		if (character_vector[i].get_status() == true)
		{
			std::cout << "_ans[" << i << "] = character_vector[" << i << "].get_ans(" <<_id <<")" << std::endl; 
			_ans[i] = character_vector[i].get_ans(_id);
			std::cout << "_ans[" << i << "] = " << _ans[i] << std::endl;
		}

		//else 
			//_ans[i] = 0;
	} 
}

void Question::answer_mapping()
{
	for(size_t i = 0; i < _ans.size(); i++)
		_rep_ans[_ans[i]] += 1;
}

void Question::update_relevance(std::vector<Character> character_vector)
{
	update_answer(character_vector);
	answer_mapping();

	for(int i = 1; i < N_ANSWER; i++)
	{
		_relevance *= (_rep_ans[i] + 1); 
	}	
}

int Question::get_relevance()
{
	return _relevance;
}

std::array<int, N_ANSWER> Question::get_rep_ans()
{
	return _rep_ans;
}