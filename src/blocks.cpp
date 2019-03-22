#include <iostream>
#include <array>
#include <memory>
#include <type_traits>
#include <fstream>

#include <block.hpp>
#include <bml.hpp>

constexpr int add(int l, int r)
{
	return l + r;
}

constexpr int minus(int l, int r)
{
	return l - r;
}

constexpr int divide(int l, int r)
{
	return l / r;
}

constexpr int mult(int l, int r)
{
	return l * r;
}

int main()
{
	block<50> memory;
	block<50> funcs;

	block_manager<block<50>> func_manager(funcs);
	auto iter = func_manager.store(&add);
	auto minus = func_manager.read<decltype(&add)>(iter);

	block_manager<block<50>> data_manager(funcs);

	auto iter12 = data_manager.store(12);
	auto iter4 = data_manager.store(4);

	auto res = minus(
			data_manager.read<int>(iter12),
			data_manager.read<int>(iter4));

	auto iterres = data_manager.store(res);

	std::cout << data_manager.read<int>(iterres) << std::endl;
	std::cout << sizeof(std::fstream) << std::endl;

}