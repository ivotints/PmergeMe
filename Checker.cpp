#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <ctype.h>
#include <cstdlib>
#include <vector>
#include <deque>
#include <cctype>
#include <limits>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <unistd.h>


/*
	It will take first 2 lines from standart input:
	Before:  5 9 10 6 2 8 3 1 7 4
	After:   1 2 3 4 5 6 7 8 9 10

	, sort first line and compare to second. Prints Yes in case of success.
 */
int main()
{
	std::vector<std::string> tokens_not_sorted;
	{
		std::string input;
		std::getline(std::cin, input);
		std::stringstream ss(input);
		std::string token;
		std::getline(ss, token, ' ');
		while (std::getline(ss, token, ' '))
		{
			if (!token.empty())
				tokens_not_sorted.push_back(token);
		}
	}
	std::vector<std::string> tokens_sorted;
	{
		std::string input;
		std::getline(std::cin, input);
		std::stringstream ss(input);
		std::string token;
		std::getline(ss, token, ' ');
		while (std::getline(ss, token, ' '))
		{
			if (!token.empty())
				tokens_sorted.push_back(token);
		}
	}

	std::vector<int> not_sorted;
	std::vector<int> sorted;

	for (unsigned int i = 0; i < tokens_not_sorted.size(); ++i)
		not_sorted.push_back(std::atoi(tokens_not_sorted[i].c_str()));

	for (unsigned int i = 0; i < tokens_sorted.size(); ++i)
		sorted.push_back(std::atoi(tokens_sorted[i].c_str()));

	for (std::size_t i = 0; i < not_sorted.size(); ++i)
		std::cout << not_sorted[i] << " ";
	std::cout << std::endl;

	for (std::size_t i = 0; i < sorted.size(); ++i)
		std::cout << sorted[i] << " ";
	std::cout << std::endl;

	std::sort(not_sorted.begin(), not_sorted.end());

	std::cout << "Is it sorted? " << ((not_sorted == sorted) ? "Yes.\n" : "No.\n");

}
