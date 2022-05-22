#include <iostream>
#include <cmath> // for std::sqrt

#include <fstream>
#include <vector>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include "../include/row.hpp"

namespace csv
{
	/*Friend operator*/	
	std::ostream& operator<<(std::ostream& os, csv::Row row)
	{

		for(size_t i = 0; i < row._content.size(); i++)
		{
			if (i != row._content.size()-1) os << row[i] << row._sep;
			else os << " " << row[i];
		}
		//os << row[static_cast<int>(row._content.size())];
		return os;
	}
	/*
	template<typename T>
	std::istream& operator>>(std::istream& is, std::vector<T> v)
	{
		int count = 0;

		while (std::getline(is, item, _sep))
      	{	 
      		count++;
      		if (count > _header.size()) throw;
      	}
      	while (std::getline(is, item, _sep))
      	{	 
      		v.push_back(item);
      	}

		return is;
	}*/
	/*
	std::istream& operator>>(std::istream& is, Row row)
	{
		is >> row._content;
		return is;
	}*/

	/*Friend function*/
	std::vector<int> get_answer(Row row)
	{
		std::vector<int> vec;
		
		std::transform(row._content.begin() + 1, row._content.end(), std::back_inserter(vec),
        [&](std::string s) {
            return stoi(s);
        });

		return vec;
	}

	/*Constructor and destructor*/
	Row::Row(std::vector<std::string> header, std::stringstream ssline, char sep) : _sep(sep), _header(header)
	{
    	std::string item;
    	size_t count = 0;

    	//convert string line in vector
      	while (std::getline(ssline, item, sep))
      	{	 
      		_content.push_back(item);
      		count++;
      		if (count > _header.size()) throw;
      	}
	}

	Row::~Row()
	{}

	std::string& Row::operator[](int pos)
	{
		return _content[pos];
	}

	std::string& Row::operator[](std::string header_name)
	{
		size_t pos = 0;
		bool key = false;
		
		for(size_t i = 0; i < _header.size(); i++)
		{	
				if (_header[pos] != header_name && key == false)
					pos++;
				else
					key = true;
		};
		
		if (pos > _header.size())
			throw;
		
		return _content[static_cast<int>(pos)];
	}

	int Row::length()
	{
		return _header.size();
	}

	bool Row::add_column(std::string header_name)
	{
		_header.push_back(header_name);
		_content.push_back("0"); 
		return true;
	}

}


