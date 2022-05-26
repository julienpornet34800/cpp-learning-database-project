#include <iostream>
#include <string>
#include <vector>
#include <array>

#include "../include/question.hpp"

/*Constructor & Destructor*/
Question::Question(int id, csv::Row row, std::vector<Character> character_vector) :Row(row), _id(id), _statement(row[0]), _relevance(1), _already_asked(false), _user_ans(0)
{
	/*Fill the answer array from the character answer*/
	for(size_t i = 0; i < character_vector.size(); i++)
		_ans.push_back(character_vector[i].get_ans(_id));
}

Question::~Question()
{}

/*Member operator*/
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
		/*Only consider the character who are not eliminated.*/
		if (character_vector[i].get_status() == true) 
		{
			_ans[i] = character_vector[i].get_ans(_id);
		}
		/*If a character is eliminated is answer is consider as unknow.*/
		else _ans[i] = 0; 
	} 
}

void Question::answer_mapping()
{
	/*Repartition is made from the answer array for each caracter*/
	for(size_t i = 0; i < _ans.size(); i++)
		_rep_ans[_ans[i]] += 1;
}

void Question::update_relevance(std::vector<Character> character_vector)
{
	/*First, answers are updated according the eliminated character*/
	update_answer(character_vector);
	/*Second, the answer repartition is updated*/
	answer_mapping();
	/*Third, the relvance is calculated, without considering the unknow answers*/
	for(int i = 1; i < N_ANSWER; i++)
		_relevance *= (_rep_ans[i] + 1); 	
}

int Question::get_ans(int pos) const
{
	return _ans[pos];
}

int Question::get_relevance() const
{
	return _relevance;
}

int Question::get_id() const
{
	return _id;
}