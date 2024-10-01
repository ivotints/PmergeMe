/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AllInOneFile.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:31:51 by ivotints          #+#    #+#             */
/*   Updated: 2024/10/01 19:11:39 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_index
{
	std::vector<int> vector;
	std::vector<int> index;
} t_index;

class PmergeMe
{
	private:
		PmergeMe() {}
		PmergeMe(const PmergeMe &) {}
		PmergeMe operator=(const PmergeMe &) { return *this;}
		~PmergeMe() {}
		static double	log2(double x);
		static t_index	ford_johnson_algorithm(std::vector<int>& to_sort, int &compar_num);
		typedef std::vector<int>::iterator iterator;
		static iterator binary_search(iterator begin, iterator end, int &num);

	public:
		static int	merge_insertion_sort(std::vector<int>::iterator begin, std::vector<int>::iterator end);
		static int	merge_insertion_worst_case_bound(int array_size);

};

int	PmergeMe::merge_insertion_sort(iterator begin, iterator end)
{
	std::vector<int> to_sort(begin, end);
	int number_of_comparisons_made = 0;
	t_index result = ford_johnson_algorithm(to_sort, number_of_comparisons_made);
	std::copy(result.vector.begin(), result.vector.end(), begin);
	return (number_of_comparisons_made);
}

//0 1 1 3 5 11 21 43 85 171 341 683 1365 2731 5461 10923 21845 43691
int jacobsthal(int n)
{
	int dp[n + 1];

	dp[0] = 0;
	dp[1] = 1;

	for (int i = 2; i <= n; i++)
		dp[i] = dp[i - 1] + 2 * dp[i - 2];

	return dp[n];
}







































t_index PmergeMe::ford_johnson_algorithm(std::vector<int>& to_sort, int &compar_num)
{
	t_index result;
	result.vector = to_sort;
	int size = result.vector.size();
	for (int i = 0; i < size; ++i)
		result.index.push_back(i);
	if (size == 1)
		return (result);
	std::vector<int> main_sequence;
	std::vector<int> sub_sequence;
	iterator it_vect = result.vector.begin();
	iterator it_indx = result.index.begin();
	while (it_vect != result.vector.end())
	{
		if (it_vect + 1 != result.vector.end())
		{
			++compar_num;
			if (*(it_vect + 1) < *it_vect)
			{
				std::swap(*it_vect, *(it_vect + 1));
				std::swap(*it_indx, *(it_indx + 1));
			}
			main_sequence.push_back(*(it_vect + 1));
			sub_sequence.push_back(*it_vect);;
		}
		else
		{
			sub_sequence.push_back(*it_vect);;
		}
		it_vect += 2;
		it_indx += 2;
	}
	t_index sorted = ford_johnson_algorithm(main_sequence, compar_num); // vector:     index:
	for (int i = 0; i < size / 2; ++i)
	{
		std::swap(sub_sequence[i], sub_sequence[sorted.index[i]]);
	}
	int k;
	for (int i = 0; i < sub_sequence.size(); ++i)
	{
		if (i == 0)
		{
			sorted.vector.insert(sorted.vector.begin(), sub_sequence.front());
			continue;
		}
		k = jacobsthal(i); // 2
		sorted.vector.insert(binary_search(sorted.vector.begin(), sorted.vector.begin() + k, *(sub_sequence.begin() + k)), *(sub_sequence.begin() + k));

	}
	return (sorted);
}
//2
//0 1 1 3 5 11 21 43 85 171 341 683 1365 2731 5461 10923 21845 43691

PmergeMe::iterator PmergeMe::binary_search(iterator begin, iterator end, int &num)
{


}
















































// Function to calculate log base 2 of a number
double PmergeMe::log2(double x)
{
	return std::log(x) / std::log(2);
}

// Function to calculate the worst-case comparison bound for merge-insertion sort
// Return total comparisons max possible
int PmergeMe::merge_insertion_worst_case_bound(int array_size)
{
	int total_comparisons = 0;
	for (int i = 1; i <= array_size; ++i)
		total_comparisons += static_cast<int>(ceil(log2((3.0 / 4.0) * static_cast<double>(i))));
	return (total_comparisons);
}













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

	{
		clock_t start = clock();
		int number_of_comparisons_made = PmergeMe::merge_insertion_sort(vec.begin(), vec.end());
		clock_t end = clock();
		for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout << *it << ((it + 1 != vec.end()) ? " " : "\n");
		std::cout << std::fixed << "Time to process a range of " << vec.size() << " elements with std::vector : " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " us\n";
		std::cout << "Number of comparisons made: " << number_of_comparisons_made << "\n";
		std::cout << "Maximum number of comparisons possible by Ford-Jonson algorithm: " << PmergeMe::merge_insertion_worst_case_bound(vec.size()) << "\n";

	}


	}
	catch(const std::exception& e)
	{
		return (std::cerr << e.what() << std::endl, 1);
	}
	return (0);
}

