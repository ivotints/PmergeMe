/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:31:51 by ivotints          #+#    #+#             */
/*   Updated: 2024/10/09 13:50:35 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "PmergeMe.hpp"

int main(int ac, char **av)
{
	if (ac == 1)
		return (std::cerr << "Error: No arguments provided. Example:\n./PmergeMe `shuf -i 1-100000 -n 3000 | tr \"\\n\" \" \"`\n./PmergeMe `shuf -i 1-200000 -n 140000 | tr \"\\n\" \" \"`\n", 1);
	std::vector<int> vec;
	std::deque<int> deq;
	try
	{
		for (int i = 1; i < ac; ++i)
		{
			for (int j = 0; av[i][j]; ++j)
				if (!isdigit(av[i][j]))
					throw std::invalid_argument(std::string("") + "Error: '" + av[i][j] + "' is not a digit.");
			if (std::string(av[i]).size() > 10)
				throw std::invalid_argument(std::string("") + "Error: \"" + av[i] + "\" is too long.");
			if (std::string(av[i]).size() == 0)
				throw std::invalid_argument(std::string("") + "Error: \"" + av[i] + "\" is empty.");
			long num = std::atol(av[i]);
			if (num > 2147483647)
				throw std::invalid_argument(std::string("") + "Error: \"" + av[i] + "\" is too big.");
			vec.push_back(num);
			deq.push_back(num);
		}
	std::cout << "Before:  ";
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		std::cout << *it << ((it + 1 != vec.end()) ? " " : "\n");
	std::cout << "After:   ";
	///////////////vector
		clock_t start = clock();
		int number_of_comparisons_made = PmergeMe::merge_insertion_sort(vec.begin(), vec.end());
		clock_t end = clock();
		for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout << *it << ((it + 1 != vec.end()) ? " " : "\n");
		std::cout << std::fixed << "Time to process a range of " << vec.size() << " elements with std::vector : " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " us\n";
	//////////
	//////////deque
		start = clock();
		PmergeMe::merge_insertion_sort(deq.begin(), deq.end());
		end = clock();
		std::cout << std::fixed << "Time to process a range of " << deq.size() << " elements with std::deque  : " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " us\n";
	//////////
		std::cout << "Number of comparisons made: " << number_of_comparisons_made << "\n";
		std::cout << "Maximum number of comparisons possible by Ford-Jonson algorithm: " << PmergeMe::merge_insertion_worst_case_bound(vec.size()) << "\n";
	}
	catch(const std::exception& e)
	{
		return (std::cerr << e.what() << std::endl, 1);
	}
	return (0);
}
