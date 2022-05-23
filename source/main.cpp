#include <iostream>
#include <array>

#include "../include/csv_parser.hpp"
#include "../include/row.hpp"
#include "../include/character.hpp"
#include "../include/question.hpp"

template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, std::pair<T,U> p)
{
	os << p.first << ", " << p.second;
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
	for(size_t i = 0; i<questions_parser.get_nrow()-1; i++) 
		questions_vector.push_back(Question(i, questions_parser[i], characters_vector));

	/*Answers aquisitions*/
	for(size_t i = 0; i<5; i++)
	{
		/*Update question relevance*/
		for(int j = 0; j < static_cast<int>(questions_parser.get_nrow())-2; j++) //try to resolve
		{ 
			questions_vector[j].update_relevance(characters_vector);
			//std::cout << "_rep_ans = " << questions_vector[i].get_rep_ans() << std::endl;
			//std::cout << "relevance = " << questions_vector[i].get_relevance() << std::endl;
		}
		std::cout << std::endl;

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
	/*Answers analysis*/
	for(size_t j = 0; j<characters_vector.size(); j++)
	{ 
		characters_vector[j].update_diff(user_ans);
	}

	std::sort(characters_vector.begin(), characters_vector.end(), [](Character c1, Character c2)
	{
		if(c1.get_grade() > c2.get_grade()) return false;
		else return true;
	});

	std::cout << characters_vector << std::endl; 
	
	return 0;
}

/*
	std::cout << "Program is starting." << std::endl;
	csv::Parser questions_parser = csv::Parser("content/questions.csv");
	csv::Parser characters_parser = csv::Parser("content/personnages.csv");

	questions_parser.add_row("Votre personnage est-il chatain ?");
	characters_parser.add_row("JUL, 5, 1, 5, 0, 0, 4");

	characters_parser.add_column("test");

	characters_parser.modif_value("300", 1, 1);

	std::cout << questions_parser << std::endl;
	std::cout << characters_parser << std::endl;

	questions_parser.sync();
	characters_parser.sync();
*/