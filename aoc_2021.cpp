#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void day_1()
{
	std::ifstream MyReadFile("day1.txt");
	std::string input;

	int result = 0;
	std::vector<int>ints{};

	while (std::getline(MyReadFile, input)) {
		int x = std::stoi(input);
		ints.push_back(x);
	}

	std::vector<int>sums{};
	for(int i=0;i<ints.size()-2;++i)
	{
		int sum = ints.at(i) + ints.at(i + 1) + ints.at(i + 2);
		sums.push_back(sum);
		std::cout << sum << "\n";
	}

	for (int i = 1; i < sums.size(); ++i)
	{
		if (sums.at(i) > sums.at(i - 1))result++;
	}

	std::cout << result;
}

void day_2()
{
	std::ifstream MyReadFile("day2.txt");
	std::string input;
	int down{ 0 }, horizontal{ 0 },aim{0};

	while (std::getline(MyReadFile, input)) {
		std::string command=input.substr(0, input.find(' '));
		int x = std::stoi(input.substr(input.find(' '), input.length() - input.find(' ')));
		if (command == "forward"){
			horizontal += x;
			down += x * aim;
		}
		if (command == "down")aim += x;
		if (command == "up")aim -= x;
	}
	std::cout << down*horizontal;
}

int convert(long long n) {
	int dec = 0, i = 0, rem;

	while (n != 0) {
		rem = n % 10;
		n /= 10;
		dec += rem * pow(2, i);
		++i;
	}

	return dec;
}

void day_3()
{
	std::ifstream MyReadFile("day3.txt");
	std::string input;
	std::vector<std::string>binary{};

	while (std::getline(MyReadFile, input)) {
		binary.push_back(input);
	}
	long digits = input.length();
	long long gamma_rate = 0,epsilon_rate{0};
	for(unsigned int i=0;i<input.length();++i)
	{
		int ones{ 0 };
		for(unsigned int j=0;j<binary.size();j++)
		{
			std::string binary_val = binary.at(j);
			char digit = binary_val.at(digits-i-1);
			ones += (digit=='1'?1:0);
		}
		gamma_rate += ((long long)std::pow(10, i)) * (ones > binary.size() / 2 ? 1 : 0);
		epsilon_rate += ((long long)std::pow(10, i)) * (ones > binary.size() / 2 ? 0 : 1);
	}
	std::cout << gamma_rate << " " << epsilon_rate << " ";
	std::cout << convert(gamma_rate)*convert(epsilon_rate);
}

void day_3_2()
{
	std::ifstream MyReadFile("day3.txt");
	std::string input;
	std::vector<std::string>binary{};

	while (std::getline(MyReadFile, input)) {
		binary.push_back(input);
	}

	char common_bit;
	std::vector<std::string>oxygen{binary};
	for (unsigned int i = 0; i < input.length()&&oxygen.size()>1; ++i)
	{
		if (oxygen.size() == 1)continue;
		std::vector<std::string>oxygen_tmp{};

		int ones{ 0 };
		for (unsigned int j = 0; j < oxygen.size(); j++)
		{
			char digit = oxygen.at(j).at(i);
			ones += (digit == '1' ? 1 : 0);
		}
		common_bit = (ones > (oxygen.size() / 2) ? '1' : '0');
		if (oxygen.size() % 2 == 0 && oxygen.size() / 2 == ones)common_bit = '1';

		for (unsigned int j = 0; j < oxygen.size(); j++)
		{
			char digit = oxygen.at(j).at(i);
			if (digit == common_bit)
				oxygen_tmp.push_back(oxygen.at(j));
		}

		oxygen = oxygen_tmp;
	}
	std::cout << oxygen.front() << " " << std::stoi(oxygen.front(), nullptr, 2) << "\n";

	std::vector<std::string>co2{ binary };
	for (unsigned int i = 0; i < input.length() && co2.size()>1; ++i)
	{
		if (co2.size() == 1)continue;
		std::vector<std::string>co2_tmp{};

		int ones{ 0 };
		for (unsigned int j = 0; j < co2.size(); j++)
		{
			char digit = co2.at(j).at(i);
			ones += (digit == '1' ? 1 : 0);
		}
		common_bit = (ones > (co2.size() / 2) ? '1' : '0');
		if (co2.size() % 2 == 0 && co2.size() / 2 == ones)common_bit = '1';

		for (unsigned int j = 0; j < co2.size(); j++)
		{
			char digit = co2.at(j).at(i);
			if (digit != common_bit)
				co2_tmp.push_back(co2.at(j));
		}

		co2 = co2_tmp;
	}
	if (oxygen.empty() || co2.empty())return;
	std::cout  << co2.front() << " " << std::stoi(co2.front(), nullptr, 2) << "\n";

	std::cout << std::stoi(oxygen.front(), nullptr, 2) * std::stoi(co2.front(), nullptr, 2);
}

int main()
{
	day_3_2();
}

