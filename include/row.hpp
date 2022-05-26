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

		public:
			/*Construtor and destructor*/
			Row(std::vector<std::string> header, std::stringstream ssline, char sep);
			Row(const Row& row) = default;
			virtual ~Row();

			/*Access operator*/
			std::string& operator[](int pos);
			std::string& operator[](std::string header_name);
			
			/*Access member*/
			int get_length();

			/*Member function*/
			bool add_column(std::string header_name);

		protected:
			std::vector<std::string> _content;

		private:
			std::vector<std::string> _header;
			char _sep;
	};
}

#endif