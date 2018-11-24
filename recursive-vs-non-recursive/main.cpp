#include <iostream>
#include <chrono>
#include <vector>
#include <random>

using namespace std::chrono_literals;
using int_array = std::vector<int>;

void quick_sort(const int_array::iterator begin, const int_array::iterator end)
{
	if(end - begin > 1)
	{
		const auto median = *begin;

		const auto lower_bound_begin = begin;
		const auto upper_bound_end = end;

		auto lower_bound_end = lower_bound_begin + 1;

		for(auto it = lower_bound_end; it != end; ++it)
		{
			const auto value = *it;
			if(value <= median)
			{
				*it = *lower_bound_end;
				*lower_bound_end = value;
				++lower_bound_end;
			}
		}
		const auto lower_bound_last = lower_bound_end - 1;
		*begin = *lower_bound_last;
		*lower_bound_last = median;

		quick_sort(lower_bound_begin, lower_bound_last);
		quick_sort(lower_bound_end, upper_bound_end);
	}
}

void quick_sort(int_array& array)
{
	quick_sort(array.begin(), array.end());
}

int main()
{
	constexpr auto num_elements = 8'000'000;
	constexpr auto seed = 490u;
	
	auto rng = std::mt19937{seed};
	auto random_int = std::uniform_int_distribution<int>{};

	auto array = int_array{};
	array.resize(num_elements);

	for(auto& element : array)
	{
		element = random_int(rng);
	}

	const auto start_point = std::chrono::steady_clock::now();

	quick_sort(array);

	const auto end_point = std::chrono::steady_clock::now();

	const auto duration_in_seconds = std::chrono::duration<long double>(end_point - start_point).count();
	
	std::cout << "Time taken: " << duration_in_seconds << '\n';

	return EXIT_SUCCESS;
}