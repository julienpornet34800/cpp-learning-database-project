/*Standart include*/
#include <iostream>
#include <vector>
#include <utility>

/*Personnal include*/
#include "row.hpp"

#ifndef CHARACTER_H
#define CHARACTER_H

class Character : public csv::Row
{
	friend std::ostream& operator<<(std::ostream& os, Character const ch);

	public:
		/*Constructor & destructor*/
		Character(Row row);
		~Character();

		void update_status(int current_ans, int expected_ans);
		/*Update character's status, according if the character is
		eliminated or not.
		@param int current_ans current answer of the user
		@param int expected_ans character answer 
		@result void
		*/
		template<size_t N>
		void update_grade(std::array<int, N>& user_ans);
		/*Update character's grade
		@param std::array<int, N> user_ans user answer array 
		@result void
		*/

		/*Access method*/
		bool get_status() const;
		int get_grade() const;
		int get_ans(int pos) const;
		std::string get_name() const;

	private:
		/*_status = false => character is eliminated.*/
		bool _status;
		/*Quantify how close the character is to the user answer.*/
		int _grade;
		std::string _name;
		/*Character answer for every question asked*/
		std::vector<int> _ans;
};

#include "../source/character.icpp"
#endif