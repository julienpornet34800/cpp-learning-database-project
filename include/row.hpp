/*Standart include*/
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <sstream>


#ifndef ROW_HPP
#define ROW_HPP

namespace csv
{
	class Row
	{
		friend std::ostream& operator<<(std::ostream& os, Row row);
		friend std::vector<int> get_answer(Row row); 
		friend class Character;

		public:
			Row(std::vector<std::string> header, std::stringstream ssline, char sep);
			Row(const Row& row) = default;
			virtual ~Row();

			std::string& operator[](int pos);
			std::string& operator[](std::string header_name);

			int length();
			bool add_column(std::string header_name);

		private:
			std::vector<std::string> _header;
			char _sep;

		protected:
			std::vector<std::string> _content;
	};
}

#endif