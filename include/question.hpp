#include <iostream>
#include <vector>

#include "row.hpp"
#include "character.hpp"


#ifndef QUESTION_HPP
#define QUESTION_HPP

class Question
{
	public:
		Question(int id, csv::Row row, std::vector<Character> character_vector);
		~Question();

		void update_answer(std::vector<Character> character_vector);
		void update_relevance();

	private:
		int _id;
		std::string _statement;
		int _relevance;
		std::vector<int> _ans;
};

#endif