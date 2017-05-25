// BoostRegex.cpp : Defines the entry point for the console application.
//

#include <boost/regex.hpp>
#include <iostream>
#include <string>

int main()
{
	std::string line = "Subjext: Re: You have installed boost successfully.";
	boost::regex pat("^Subject: (Re: |Aw: )*(.*)"); \
		boost::smatch matches;
	if (boost::regex_match(line, matches, pat))
		std::cout << matches[2] << std::endl;
	return 0;
}

