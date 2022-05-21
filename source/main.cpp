#include <iostream>
#include <array>

#include "../include/csv_parser.hpp"
#include "../include/row.hpp"
#include "../include/character.hpp"
#include "../include/question.hpp"

/*	to compile
*	g++ -std=c++17 -pedantic -Wall -Wextra *.cpp
*/

template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, std::pair<T,U> p)
{
	os << "{"<< p.first << ", " << p.second << "}";
	return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> v)
{
	std::for_each(v.begin(), v.end(), [&os](T elem)
	{
		os << elem << "\t";
	});
	return os;
}


void erase_question(std::vector<Question> questions_vector)
{
	for(size_t i = 0; i < questions_vector.size(); i++)
		if (questions_vector[i]._already_asked == true)
			questions_vector.erase(questions_vector.begin() + i);
}

int main()
{	
	std::cout << "Program is starting." << std::endl;
	csv::Parser questions_parser = csv::Parser("content/questions.csv");
	csv::Parser characters_parser = csv::Parser("content/personnages.csv");

	int current_ans;
	std::vector<int> user_ans;

	/*Character vector init*/
	std::vector<Character> characters_vector;
	for(size_t i = 0; i<characters_parser.get_nrow(); i++) 
		characters_vector.push_back(Character(characters_parser[i]));

	/*Question init*/
	std::vector<Question> questions_vector;
	for(size_t i = 0; i<questions_parser.get_nrow(); i++) 
		questions_vector.push_back(Question(i, questions_parser[i], characters_vector));

	/*Answers aquisitions*/
	for(size_t i = 0; i<questions_parser.get_nrow(); i++)
	{
		/*Update question relevance*/
		for(size_t i = 0; i<questions_parser.get_nrow(); i++)
		{ 
				questions_vector[i].update_relevance(characters_vector);
				std::cout << questions_vector[i].get_relevance() << " ";
		}
		std::cout << std::endl;

		/*Sort the relevance from the answer*/
		std::sort(questions_vector.begin()+i, questions_vector.end(), 
			[](Question q1, Question q2)
			{
				if (q1.get_relevance() > q2.get_relevance()) return true;
				else return false;
			});

		/*Display the question*/
		std::cout << questions_vector << std::endl;
		std::cout << questions_vector[i] << "\t(réponse entre 0 et 5)" << std::endl;
		std::cin >> current_ans;
		user_ans.push_back(current_ans);

	}
		/*Update relevance*/

	/*Answers analysis*/

	return 0;
}
