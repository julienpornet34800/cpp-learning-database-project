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

	/*Constructor and destructor*/
	Row::Row(std::vector<std::string> header, std::stringstream ssline, char sep) : _header(header), _sep(sep)
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

	/*Member operator*/
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

	/*Member function*/
	int Row::get_length()
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


