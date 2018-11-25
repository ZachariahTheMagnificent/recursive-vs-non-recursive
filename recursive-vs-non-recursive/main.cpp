#include <iostream>
#include <chrono>
#include <vector>
#include <random>

using namespace std::chrono_literals;
using int_array = std::vector<int>;

struct range
{
	int_array::iterator begin;
	int_array::iterator end;
};
using range_array = std::vector<range>;

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

	auto ranges_to_sort = range_array{};

	ranges_to_sort.reserve(1000);
	const auto start_point = std::chrono::steady_clock::now();

	if(array.size() > 1)
	{
		ranges_to_sort.push_back(range{array.begin(), array.end()});

		while(!ranges_to_sort.empty())
		{
			const auto element = ranges_to_sort.back();

			const auto lower_range_begin = element.begin;
			const auto upper_range_end = element.end;
			const auto median = *lower_range_begin;

			auto lower_range_end = lower_range_begin + 1;
			for(auto it = lower_range_end; it != element.end; ++it)
			{
				const auto value = *it;
				if(value <= median)
				{
					*it = *lower_range_end;
					*lower_range_end = value;
					++lower_range_end;
				}
			}
			const auto lower_range_last = lower_range_end - 1;
			const auto upper_range_begin = lower_range_end;

			*lower_range_begin = *lower_range_last;
			*lower_range_last = median;

			ranges_to_sort.pop_back();

			if(upper_range_begin != upper_range_end)
			{
				ranges_to_sort.push_back(range{upper_range_begin, upper_range_end});
			}
			if(lower_range_begin != lower_range_last)
			{
				ranges_to_sort.push_back(range{lower_range_begin, lower_range_last});
			}
		}
	}

	const auto end_point = std::chrono::steady_clock::now();

	const auto duration_in_seconds = std::chrono::duration<long double>(end_point - start_point).count();
	
	std::cout << "Time taken: " << duration_in_seconds << '\n';

	return EXIT_SUCCESS;
}
