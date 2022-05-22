#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

#include "row.hpp"

#ifndef CSV_PARSER_HPP
#define CSV_PARSER_HPP

namespace csv
{
	class Parser
    {
    	friend std::ostream& operator<<(std::ostream& os, Parser parser);

	    public:
	        Parser(const std::string&, char sep = ',');
	        ~Parser();

	        size_t get_nrow() const;
	        size_t get_ncolumn() const;

	        Row operator[](int pos);

	        bool delete_row(unsigned int row);
        	bool add_row(std::string str);
        	bool add_column(std::string header_name);
        	bool modif_value(std::string new_value, int row, int pos);
        	void sync(void) const;

	    private:
	    	std::string _path;
	    	char _sep;
	    	std::vector<std::string> _file;
	    	int _ncolumn;
	    	std::vector<std::string> _header;
	    	std::vector<Row> _content;
    };
}

#endif