/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:31:51 by ivotints          #+#    #+#             */
/*   Updated: 2024/10/09 13:50:32 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

//valgrind ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "` | ./checker
//valgrind ./PmergeMe `shuf -i 1-100000 -n $RANDOM | tr "\n" " "`

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

typedef struct s_index_deq
{
	std::deque<int> deque;
	std::deque<int> index;
} t_index_deq;

class PmergeMe
{
	private:
		PmergeMe() {}
		PmergeMe(const PmergeMe &) {}
		PmergeMe operator=(const PmergeMe &) { return *this;}
		~PmergeMe() {}
		static double	log2(double x);
		static t_index	ford_johnson_algorithm(t_index to_sort, int &compar_num);
		static t_index_deq ford_johnson_algorithm(t_index_deq to_sort, int &compar_num);
		typedef std::vector<int>::iterator iterator;
		typedef std::deque<int>::iterator iterator_deq;
		static iterator binary_search(iterator begin, iterator end, int &val, int &compar_num);
 		static iterator_deq binary_search(iterator_deq begin, iterator_deq end, int &val, int &compar_num);
		static int add_end_of_search(int i, int size);

	public:
		static int	merge_insertion_sort(iterator begin, iterator end);
		static int	merge_insertion_sort(iterator_deq begin, iterator_deq end);
		static int	merge_insertion_worst_case_bound(int array_size);
};
