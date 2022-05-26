#include <iostream>
#include <array>
#include <utility>

#include "../include/csv_parser.hpp"
#include "../include/row.hpp"
#include "../include/character.hpp"
#include "../include/question.hpp"

#define NQUESTION 6 

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

bool add_question(csv::Parser* questions_parser, csv::Parser* characters_parser, std::string statement)
{
	questions_parser->add_row(statement);
	characters_parser->add_column("new");
	return true;
}

bool add_character(csv::Parser* characters_parser, std::string name)
{
	std::string str = name;
	for (int i = 0; i < static_cast<int>(characters_parser->get_ncolumn())-1; i++)
		str += ", 0";
	std::cout << str << std::endl;
	characters_parser->add_row(str);
	return true;
}


int main()
{
	/*1. Reading of the question and character files---------------------------------------------------------------------------------------*/
	csv::Parser questions_parser = csv::Parser("content/questions.csv");
	csv::Parser characters_parser = csv::Parser("content/personnages.csv");
	/*2. Character and question vector init------------------------------------------------------------------------------------------------*/
	std::vector<Character> characters_vector; std::vector<Question> questions_vector;

	for(size_t i = 0; i<characters_parser.get_nrow(); i++) 
		characters_vector.push_back(Character(characters_parser[i]));
	for(size_t i = 0; i<questions_parser.get_nrow(); i++) 
		questions_vector.push_back(Question(i, questions_parser[i], characters_vector));
	
	/*3. Answers aquisitions---------------------------------------------------------------------------------------------------------------*/	
	add_character(&characters_parser, "JUL");
	std::cout << characters_parser << std::endl;
	add_question(&questions_parser, &characters_parser, "Qui est le plus bg ?");
	std::cout << questions_parser << std::endl;
	characters_parser.sync();
	questions_parser.sync();

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