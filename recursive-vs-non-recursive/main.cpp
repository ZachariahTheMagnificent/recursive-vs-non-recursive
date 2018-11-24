#include <iostream>
#include <chrono>
#include <vector>
#include <random>

using namespace std::chrono_literals;
using int_array = std::vector<int>;

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

	const auto end_point = std::chrono::steady_clock::now();

	const auto duration_in_seconds = std::chrono::duration<long double>(end_point - start_point).count();
	
	std::cout << "Time taken: " << duration_in_seconds << '\n';

	return EXIT_SUCCESS;
}