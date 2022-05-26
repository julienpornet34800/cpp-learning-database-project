#include "../include/csv_parser.hpp"

template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> v)
{
	std::for_each(v.begin(), v.end(), [&os](T value)
	{
		os << value << std::endl;
	});

	return os;
}

namespace csv
{	
	/*Friend operator*/
	template<typename T>
	std::ostream& operator<<(std::ostream& os, std::vector<T> v)
	{
		std::for_each(v.begin(), v.end(),
			[&os](T elem)
			{
				os << elem << std::endl;
			});

		return os;
	}

	std::ostream& operator<<(std::ostream& os, Parser const parser)
	{
		os << parser._content;
		return os;
	}

	/*Constructor & Destructor*/
	Parser::Parser(const std::string& path, char sep):_path(path), _sep(sep)
	{
		//file opening
	    std::fstream fs;
	    fs.open(path, std::ios::in); //read mode
	    //make sure that the file exists
	    if (!fs.good())
	    {
	        std::perror("File did not open correctly.");
	        throw;
	    }
	    //storage of the file line per line inside a vector
	    for (std::string line; std::getline(fs, line, '\n'); ) 
    	{
        	_file.push_back(line);
    	}
    	//storage of the header inside the _header vector
    	std::stringstream ss(_file[0]);
    	std::string item;
      	while (std::getline(ss, item, _sep)) _header.push_back(item);
      	//storage of the row inside the content vector
      	for(size_t i = 1; i < _file.size(); i++)
      	{
      		_content.push_back(Row(_header, static_cast<std::stringstream>(_file[i]), _sep));
      	}
      	fs.close();
	}

	Parser::~Parser()
	{
		std::cout << "Parser end of use." << std::endl;
	}

	/*Member operator*/
	Row Parser::operator[](int nline)
	{
		return _content[nline];
	}

	/*Member function*/
	size_t Parser::get_nrow() const
	{
		return _content.size();
	}

	size_t Parser::get_ncolumn() const
	{
		return _header.size();
	}

	bool Parser::delete_row(unsigned int nline)
	{
		if (nline > _header.size())
		{
			std::perror("Unexisting row.");
			return false;
		}
		_content.erase(_content.begin()+nline);
		return true;
	}

	bool Parser::add_row(std::string str)
	{
		Row row(_header, static_cast<std::stringstream>(str), _sep);
		if (static_cast<long unsigned int>(row.get_length()) != _header.size())
		{
			std::perror("Format error");
			return false;
		}
		else
		{
			_content.push_back(row);
			return true;
		}
	}

	bool Parser::add_column(std::string header_name)
	{
		_header.push_back(header_name);

		for(size_t i = 0; i < _content.size(); i++) _content[i].add_column(header_name);

		return true;
	}

	bool Parser::modif_value(std::string new_value, int nline, int ncol)
	{
		_content[nline][ncol] = new_value;
		return true;
	}

	void Parser::sync(void) const
	{
		unsigned int i = 0;

		std::fstream fs;
	    fs.open(_path, std::ios::out); //read mode
	    //make sure that the file exists
	    if (!fs.good())
	    {
	        std::perror("File did not open correctly.");
	        throw;
	    }
	    //write Row by Row inside the file	
		for (auto it = _header.begin(); it != _header.end(); it++)
		{
			fs << *it;
			if (i < _header.size() - 1)
				fs << _sep;
			else
				fs << std::endl;
			i++;
		}
     
		for (auto it = _content.begin(); it != _content.end(); it++)
			fs << *it << std::endl;

      	fs.close();
	}
}