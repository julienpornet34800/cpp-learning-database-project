#include <iostream>
#include <cmath> // for std::sqrt

#include <fstream>
#include <vector>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <sstream>
#include <unordered_map>


#ifndef ROW_HPP
#define ROW_HPP

namespace csv
{
	class Row
	{
		friend std::ostream& operator<<(std::ostream& os, Row row);
		//friend std::istream& operator>>(std::istream& is, Row row);
		//friend std::istream& operator>>(std::istream& is, std::vector<T> v);

		friend std::vector<int> get_answer(Row row); 
		friend class Character;

		public:
			Row(std::vector<std::string> header, std::stringstream ssline, char sep);
			~Row();

			std::string& operator[](int pos);
			std::string& operator[](std::string header_name);

			int length();
			bool add_column(std::string header_name);

		private:
			char _sep;
			std::vector<std::string> _content;
			std::vector<std::string> _header;
	};
}

#endif