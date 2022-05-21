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

template<typename T, size_t N>
std::ostream& operator<<(std::ostream& os, std::array<T, N> a)
{
	std::for_each(std::begin(a), std::end(a), [&os](T elem)
	{
		os << elem << "\t";
	});
	return os;
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
	for(size_t i = 0; i<5; i++)
	{
		/*Update question relevance*/
		for(size_t j = 0; j<questions_parser.get_nrow(); j++)
		{ 
				//std::cout << questions_vector[i];
				questions_vector[j].update_relevance(characters_vector);
				//std::cout << "_rep_ans = " << questions_vector[i].get_rep_ans() << std::endl;
				//std::cout << "relevance = " << questions_vector[i].get_relevance() << std::endl;
		}
		//std::cout << std::endl;

		/*Sort the relevance from the answer*/
		std::sort(questions_vector.begin()+i, questions_vector.end(), 
			[](Question q1, Question q2)
			{
				if (q1.get_relevance() > q2.get_relevance()) return true;
				else return false;
			});

		std::cout << questions_vector << std::endl << std::endl;

		/*Display the question*/
		std::cout << questions_vector[i] << "\t(réponse entre 0 et 5)" << std::endl;
		std::cin >> current_ans;
		user_ans.push_back(current_ans);
		
		for(size_t j = 0; j<characters_vector.size(); j++)
		{ 
			characters_vector[j].update_status(current_ans, questions_vector[i][j]);
		}

	}
		/*Update relevance*/

	/*Answers analysis*/

	return 0;
}
