#include <iostream>
#include <string>
#include <vector>
#include "../include/question.hpp"

Question::Question(int id, csv::Row row, std::vector<Character> character_vector) : _id(id), _statement(row[0]), _relevance(0)
{
	for(size_t i = 0; i < character_vector.size(); i++)
		_ans.push_back(character_vector[i][_id]);
}

Question::~Question()
{}

void Question::update_answer(std::vector<Character> character_vector)
{
	for(size_t i = 0; i < character_vector.size(); i++)
		_ans[i] = character_vector[i][_id];
}