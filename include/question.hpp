/*Standart include*/
#include <iostream>
#include <vector>
#include <utility>

/*Personnal include*/
#include "row.hpp"
#include "character.hpp"

#ifndef QUESTION_HPP
#define QUESTION_HPP

/*Declaration of the different question number (0 to 5)*/ 
#define N_ANSWER 6 

class Question : public csv::Row
{
	friend std::ostream& operator<<(std::ostream& os, Question q);

	public:
		/*Constructor and destructor*/
		Question(int id, csv::Row row, std::vector<Character> character_vector);
		~Question();

		void update_answer(std::vector<Character> character_vector);
		/*Update question's answer, according if the answer's character is
		eliminated or not.
		@param  std::vector<Character> character_vector vector storing every character
		@result void
		*/
		void answer_mapping();
		/*Update the answers repartition
		@param  void
		@result void
		*/
		void update_relevance(std::vector<Character> character_vector);
		/*Update the question's relevance grade
		eliminated or not.
		@param  std::vector<Character> character_vector vector storing every character
		@result void
		*/

		/*Access member*/
		int get_ans(int pos) const;
		int get_relevance() const;
		int get_id() const;
	

	private:
		int _id;
		std::string _statement;
		int _relevance;
		bool _already_asked;
		int _user_ans;
		/*Answer of every character for the question*/
		std::vector<int> _ans;
		/*Repartition of the different answer for the question*/
		std::array<int, N_ANSWER> _rep_ans;
};

#endif