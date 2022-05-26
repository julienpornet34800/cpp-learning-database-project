/*Standart include*/
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <sstream>
/*Personnal include*/
#include "row.hpp"

#ifndef CSV_PARSER_HPP
#define CSV_PARSER_HPP

namespace csv
{
	class Parser
    {
    	friend std::ostream& operator<<(std::ostream& os, Parser const parser);

	    public:
	    	/*Constructor ans destructor*/
	        Parser(const std::string&, char sep = ',');
	        ~Parser();

	        /*Return respectively the number of row and column*/
	        size_t get_nrow() const;
	        size_t get_ncolumn() const;

	        /*Access operator*/
	        Row operator[](int nline);
	        /*Return the associated row to nline
	        @param int nline row's line number
	        @return row associated row to nline  
	        */

	        bool delete_row(unsigned int nline);
	        /*Delete the associated row to nline
	        @param int nline row's line number
	        @return bool equal to true if the row is well deleted
	        */
        	bool add_row(std::string str);
        	/*Add a row
        	@param std::string str string representing the row content
        	@return bool equal to true if the row is well added
        	*/
        	bool add_column(std::string header_name);
        	/*Add a colomn to the associated header_name
        	@param std::string header_name string
        	@return bool equal to true if the row is well added
        	*/
        	bool modif_value(std::string new_value, int nline, int ncol);
        	/*Set a new value to a specific row and colomn
        	@param int nline row's line number
        	@param int ncol column's number
        	@return bool equal to true if the row is well added
        	*/
        	void sync(void) const;
        	/*Synchronise the content inside the parser's content and the file
			@param void
			@return void
        	*/

	    private:
	    	/*Path to the csv file*/
	    	std::string _path;
	    	/*Separator column used on the csv file*/
	    	char _sep;
	    	/*Number of column*/
	    	int _ncolumn;
	    	/*Store the csv's header*/
	    	std::vector<std::string> _header;
	    	/*Raw content of the file registred directly by 
	 		the parser line by line*/
	    	std::vector<std::string> _file;
	    	/*Content of the file registred row by row by the parser
	    	uisng row objects*/
	    	std::vector<Row> _content;
    };
}

#endif