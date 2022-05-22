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

	questions_parser.add_row("Votre personnage est-il chatain ?");
	characters_parser.add_row("JUL, 5, 1, 5, 0, 0, 4");

	characters_parser.add_column("test");

	std::cout << questions_parser << std::endl;
	std::cout << characters_parser << std::endl;

	questions_parser.sync();
	characters_parser.sync();
}