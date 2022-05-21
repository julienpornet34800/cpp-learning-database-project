#include <iostream>
#include <vector>

#include "row.hpp"
#include "character.hpp"


#ifndef QUESTION_HPP
#define QUESTION_HPP

class Question
{
	friend std::ostream& operator<<(std::ostream& os, Question q);

	friend void erase_question(std::vector<Question> questions_vector);
	
	public:
		Question(int id, csv::Row row, std::vector<Character> character_vector);
		~Question();

		void update_answer(std::vector<Character> character_vector);
		void update_relevance(std::vector<Character> character_vector);

		int get_relevance();

	private:
		int _id;
		std::string _statement;
		int _relevance;
		bool _already_asked;
		std::vector<int> _ans;
};

#endif