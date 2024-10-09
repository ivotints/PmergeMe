/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:31:51 by ivotints          #+#    #+#             */
/*   Updated: 2024/10/09 14:11:57 by ivotints         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

//0 1 1 3 5 11 21 43 85 171 341 683 1365 2731 5461 10923 21845 43691
int jacobsthal(int n)
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

// 3 3 7 7 15 15 15 15 15 15
int PmergeMe::add_end_of_search(int i, int size)
{
	int pos = std::pow(2, i + 1) - 1;
	return (pos > size ? size : pos);
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

// It is almost perfecrt, but number of comparisons can be decreased if you will find out how to easly decrease return value of add_end_of_search() function when it is needed. For example, if number was inserted in the end of sequence, we can decrease end of serach on 1 for all next numbers which are before current. I am tired and I hope that you are the one, who will understand my code, and improve it.
t_index PmergeMe::ford_johnson_algorithm(t_index to_sort, int &compar_num)
{
	int size = to_sort.vector.size();
	if (size == 1)
		return (to_sort);
	t_index main_sequence;
	t_index sub_sequence;
	iterator it_vect = to_sort.vector.begin();
	iterator it_indx = to_sort.index.begin();
	// sort in pairs
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
	//reverse sorting of main sequence
	t_index sorted = ford_johnson_algorithm(main_sequence, compar_num);
	t_index sorted_sub;
	//restore subsequence positions
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
	// insert from sub_sequance to the main
	sorted.vector.insert(sorted.vector.begin(), sorted_sub.vector.front());
	sorted.index.insert(sorted.index.begin(), sorted_sub.index.front());
	for (int i = 1; std::pow(2, i) - 1 < size; ++i)
	{
		int last_k = jacobsthal_modified(i - 1);
		int k = jacobsthal_modified(i);
		while (k > last_k)
		{
			if ((size + 1) / 2 > k)
			{
 				iterator insert_pos = binary_search(sorted.vector.begin(), sorted.vector.begin() + add_end_of_search(i, sorted.vector.size()), *(sorted_sub.vector.begin() + k), compar_num);
				int pos = 0;
				iterator pos_it = sorted.vector.begin();
				while (insert_pos != pos_it)
				{
					++pos;
					++pos_it;
				}
				sorted.vector.insert(insert_pos, *(sorted_sub.vector.begin() + k));
				sorted.index.insert(sorted.index.begin() + pos, *(sorted_sub.index.begin() + k));
			}
			--k;
		}
	}
	return (sorted);
}

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

//////////////////////////////////And same for deque////////////////////////////

int	PmergeMe::merge_insertion_sort(iterator_deq begin, iterator_deq end)
{
	t_index_deq to_sort;
	to_sort.deque.assign(begin, end);
	int size = to_sort.deque.size();
	for (int i = 0; i < size; ++i)
		to_sort.index.push_back(i);
	int number_of_comparisons_made = 0;
	t_index_deq result = ford_johnson_algorithm(to_sort, number_of_comparisons_made);
	std::copy(result.deque.begin(), result.deque.end(), begin);
	return (number_of_comparisons_made);
}

t_index_deq PmergeMe::ford_johnson_algorithm(t_index_deq to_sort, int &compar_num)
{
	int size = to_sort.deque.size();
	if (size == 1)
		return (to_sort);
	t_index_deq main_sequence;
	t_index_deq sub_sequence;
	iterator_deq it_vect = to_sort.deque.begin();
	iterator_deq it_indx = to_sort.index.begin();
	while (it_vect != to_sort.deque.end())
	{
		if (it_vect + 1 != to_sort.deque.end())
		{
			++compar_num;
			if (*(it_vect + 1) < *it_vect)
			{
				std::swap(*it_vect, *(it_vect + 1));
				std::swap(*it_indx, *(it_indx + 1));
			}
			main_sequence.deque.push_back(*(it_vect + 1));
			main_sequence.index.push_back(*(it_indx + 1));
			sub_sequence.deque.push_back(*it_vect);
			sub_sequence.index.push_back(*it_indx);
		}
		else
		{
			sub_sequence.deque.push_back(*it_vect);
			sub_sequence.index.push_back(*it_indx);
			break;
		}
		it_vect += 2;
		it_indx += 2;
	}
	t_index_deq sorted = ford_johnson_algorithm(main_sequence, compar_num);
	t_index_deq sorted_sub;
	//restore subsequence position
	for (int i = 0; i < size / 2; ++i)
	{
		int j = 0;
		while (sorted.index[i] != main_sequence.index[j])
			++j;
		sorted_sub.deque.push_back(sub_sequence.deque[j]);
		sorted_sub.index.push_back(sub_sequence.index[j]);
	}
	if (size % 2 == 1)
	{
		sorted_sub.deque.push_back(sub_sequence.deque[size / 2]);
		sorted_sub.index.push_back(sub_sequence.index[size / 2]);
	}
	// insert from sub_sequance to the main
	sorted.deque.insert(sorted.deque.begin(), sorted_sub.deque.front());
	sorted.index.insert(sorted.index.begin(), sorted_sub.index.front());
	for (int i = 1; std::pow(2, i) - 1 < size; ++i)
	{
		int last_k = jacobsthal_modified(i - 1);
		int k = jacobsthal_modified(i);
		while (k > last_k)
		{
			if ((size + 1) / 2 > k)
			{
 				iterator_deq insert_pos = binary_search(sorted.deque.begin(), sorted.deque.begin() + add_end_of_search(i, sorted.deque.size()), *(sorted_sub.deque.begin() + k), compar_num);
				int pos = 0;
				iterator_deq pos_it = sorted.deque.begin();
				while (insert_pos != pos_it)
				{
					++pos;
					++pos_it;
				}
				sorted.deque.insert(insert_pos, *(sorted_sub.deque.begin() + k));
				sorted.index.insert(sorted.index.begin() + pos, *(sorted_sub.index.begin() + k));
			}
			--k;
		}
	}
	return (sorted);
}

PmergeMe::iterator_deq PmergeMe::binary_search(iterator_deq begin, iterator_deq end, int &val, int &compar_num)
{
	iterator_deq first = begin;
	iterator_deq last = end;
	iterator_deq middle;

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
