/*Standart include*/
#include <iostream>
#include <vector>
#include <utility>

/*Personnal include*/
#include "row.hpp"
#include "character.hpp"

#ifndef QUESTION_HPP
#define QUESTION_HPP

#define N_ANSWER 6

class Question : public csv::Row
{
	friend std::ostream& operator<<(std::ostream& os, Question q);

	public:
		Question(int id, csv::Row row, std::vector<Character> character_vector);
		~Question();

		void update_answer(std::vector<Character> character_vector);
		void update_relevance(std::vector<Character> character_vector);
		void answer_mapping();

		int get_ans(int pos);
		int get_relevance();
		std::array<int, N_ANSWER> get_rep_ans();

	private:
		int _id;
		std::string _statement;
		int _relevance;
		bool _already_asked;
		std::vector<int> _ans;
		std::array<int, N_ANSWER> _rep_ans;
};

#endif