/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AllInOneFile.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:31:51 by ivotints          #+#    #+#             */
/*   Updated: 2024/10/02 19:58:48 by ivotints         ###   ########.fr       */
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
#include <unistd.h>

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
		static t_index	ford_johnson_algorithm(t_index to_sort, int &compar_num);
		typedef std::vector<int>::iterator iterator;
		static iterator binary_search(iterator begin, iterator end, int &val, int &compar_num);

	public:
		static int	merge_insertion_sort(std::vector<int>::iterator begin, std::vector<int>::iterator end);
		static int	merge_insertion_worst_case_bound(int array_size);

};

int	PmergeMe::merge_insertion_sort(iterator begin, iterator end)
{
	t_index to_sort;
	to_sort.vector.assign(begin, end);
	int size = to_sort.vector.size();
	for (int i = 0; i < size; ++i)
		to_sort.index.push_back(i);

	int number_of_comparisons_made = 0;
	t_index result = ford_johnson_algorithm(to_sort, number_of_comparisons_made);
	std::copy(result.vector.begin(), result.vector.end(), begin);
	return (number_of_comparisons_made);
}

//0 1 1 3 5 11 21 43 85 171 341 683 1365 2731 5461 10923 21845 43691
int jacobsthal(int n) // 1
{
	if (n == 0)
		return (0);

	int dp[n + 1];
	dp[0] = 0;
	dp[1] = 1;

	for (int i = 2; i <= n; i++)
		dp[i] = dp[i - 1] + 2 * dp[i - 2];


	return dp[n];
}

int jacobsthal_modified(int n)
{
	return (jacobsthal(n + 2) - 1);
}




































t_index PmergeMe::ford_johnson_algorithm(t_index to_sort, int &compar_num)
{
	int size = to_sort.vector.size();
	if (size == 1)
		return (to_sort);
	t_index main_sequence;
	t_index sub_sequence;
	iterator it_vect = to_sort.vector.begin();
	iterator it_indx = to_sort.index.begin();
	while (it_vect != to_sort.vector.end())
	{
		if (it_vect + 1 != to_sort.vector.end())
		{
			++compar_num;
			if (*(it_vect + 1) < *it_vect)
			{
				std::swap(*it_vect, *(it_vect + 1));
				std::swap(*it_indx, *(it_indx + 1));
			}
			main_sequence.vector.push_back(*(it_vect + 1));
			main_sequence.index.push_back(*(it_indx + 1));
			sub_sequence.vector.push_back(*it_vect);
			sub_sequence.index.push_back(*it_indx);
		}
		else
		{
			sub_sequence.vector.push_back(*it_vect);
			sub_sequence.index.push_back(*it_indx);
			break;
		}
		it_vect += 2;
		it_indx += 2;
	}
	t_index sorted;
	sorted.vector.reserve(size);
	sorted.index.reserve(size);
	sorted = ford_johnson_algorithm(main_sequence, compar_num);
	t_index sorted_sub;
	sorted_sub.vector.reserve((size + 1) / 2);
	sorted_sub.index.reserve((size + 1) / 2);
	//restore subsequence position
	for (int i = 0; i < size / 2; ++i)
	{
		int j = 0;
		while (sorted.index[i] != main_sequence.index[j])
			++j;
		sorted_sub.vector.push_back(sub_sequence.vector[j]);
		sorted_sub.index.push_back(sub_sequence.index[j]);
	}
	if (size % 2 == 1)
	{
		sorted_sub.vector.push_back(sub_sequence.vector[size / 2]);
		sorted_sub.index.push_back(sub_sequence.index[size / 2]);
	}
	int k = 0;
	int last_k;
	for (int i = 0; i < sorted_sub.vector.size(); ++i)
	{
		if (i == 0)
		{
			sorted.vector.insert(sorted.vector.begin(), sorted_sub.vector.front());
			sorted.index.insert(sorted.index.begin(), sorted_sub.index.front());
			continue;
		}
		last_k = jacobsthal_modified(i - 1); // 0
		k = jacobsthal_modified(i);          // 2
		while (k > last_k)
		{
			if ((size + 1) / 2 > k)
			{
 				iterator insert_pos = binary_search(sorted.vector.begin(), sorted.vector.begin() + k + 1 + last_k, *(sorted_sub.vector.begin() + k), compar_num);
				int pos = 0;
				iterator pos_it = sorted.vector.begin();
				while (insert_pos != pos_it)
				{
					++pos;
					++pos_it;
					//write(1, "DD", 2);
				}
				sorted.vector.insert(insert_pos, *(sorted_sub.vector.begin() + k));
				sorted.index.insert(sorted.index.begin() + pos, *(sorted_sub.index.begin() + k));
			}
			--k;
		}
	}
	return (sorted);
}
//     2 4 10 20 42
//0 1 1 3 5 11 21 43 85 171 341 683 1365 2731 5461 10923 21845 43691
/////////////////////////////////////////////////////1               end        2
PmergeMe::iterator PmergeMe::binary_search(iterator begin, iterator end, int &val, int &compar_num)
{
	iterator first = begin;
	iterator last = end;
	iterator middle;

	while (first < last)
	{
		middle = first + (last - first) / 2;
		++compar_num;
		if (*middle < val)
			first = middle + 1;
		else
			last = middle;
	}
	return (first);
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











/* int main(int ac, char **av)
{
	std::vector<int> vec;

	int N = 10;
	for (int i = 0; i < N; ++i)
		vec.push_back(N - i);
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
	return (0);
} */














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



