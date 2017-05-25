// BoostTest.cpp : Defines the entry point for the console application.
// Source        : http://www.boost.org/doc/libs/1_64_0/more/getting_started/windows.html

#include <boost/regex.hpp>
#include <iostream>
#include <string>

int main()
{
	// lambda example:
/*	using namespace boost::lambda;
	typedef std::istream_iterator<int> in;

	std::for_each(
		in(std::cin), in(), std::cout << (_1 * 3) << " ");
*/
	// regex example:
	std::string line;
	boost::regex pat("^Subject: (Re: |Aw: )*(.*)");

	while (std::cin)
	{
		std::getline(std::cin, line);
		boost::smatch matches;
		if (boost::regex_match(line, matches, pat))
			std::cout << matches[2] << std::endl;
	}

	return 0;
}

