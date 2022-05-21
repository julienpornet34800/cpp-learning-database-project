#include <iostream>
#include <string>
#include <vector>

#include "../include/question.hpp"

Question::Question(int id, csv::Row row, std::vector<Character> character_vector) : _id(id), _statement(row[0]), _relevance(0), _already_asked(false)
{
	for(size_t i = 0; i < character_vector.size(); i++)
		_ans.push_back(character_vector[i][_id]);
}

Question::~Question()
{}

void Question::update_answer(std::vector<Character> character_vector)
{
	for(size_t i = 0; i < character_vector.size(); i++)
		
		if (character_vector[i]._next_in_line == true)
			_ans[i] = character_vector[i][_id];
		else 
			_ans[i] = 0; 
}

void Question::update_relevance(std::vector<Character> character_vector)
{
	update_answer(character_vector);

	_relevance = 0;
	for(size_t i = 1; i <_ans.size(); i++)
	{
		_relevance *= (_ans[i]+1) 
	}	
}

int Question::get_relevance()
{
	return _relevance;
}

std::ostream& operator<<(std::ostream& os, Question q)
{
	q._already_asked = true;
	os << q._statement;
	return os;
}