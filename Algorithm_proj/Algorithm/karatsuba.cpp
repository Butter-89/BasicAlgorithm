#include "problems.h"
#include <fstream>
#include <cmath>

void PrintVector(std::vector<int>& i_vector)
{
	for (int i = 0; i < i_vector.size(); i++)
	{
		std::cout << i_vector[i];
	}
	std::cout << "\n";
}

std::vector<int> ToVector(int i_integer)
{
	std::vector<int> temp_result;
	std::vector<int> result;

	int quotient = i_integer;
	while (quotient != 0)
	{
		temp_result.push_back(quotient % 10);
		quotient /= 10;
	}

	for (int i = 0; i < temp_result.size(); i++)
	{
		result.push_back(temp_result[temp_result.size() - 1 - i]);
		//std::cout << temp_result[temp_result.size() - 1 - i];
	}
	if (result.size() == 0)
	{
		result.push_back(0);
		//std::cout << result[0];
	}
	return result;
}

int ToInteger(std::vector<int>& i_vector)
{
	int value = 0;
	for (int i = 0; i < i_vector.size(); i++)
	{
		value += i_vector[i] * powf(10, i_vector.size() - 1 - i);
	}
	return value;
}

std::vector<int> SmallMultiply(std::vector<int>& i_lhs, std::vector<int>& i_rhs)
{
	std::vector<int> result;
	int lhs = ToInteger(i_lhs);
	int rhs = ToInteger(i_rhs);
	result = ToVector(lhs * rhs);

	return result;
}

// Vector-represented integer sum function - done. Still needs improvement
std::vector<int> ArraySum(std::vector<int>& i_lhs, std::vector<int>& i_rhs)
{
	int count = i_lhs.size() < i_rhs.size() ? i_lhs.size() : i_rhs.size(); // set the smaller one as the times of calculation loop
	int carry = 0;
	std::vector<int> temp_result;
	std::vector<int> result;	// the result to be returned should be inversed from the temp_result which uses push_back 

	if (i_lhs.size() <= i_rhs.size())
	{
		for (int i = 0; i < i_rhs.size(); i++)
		{
			int summed = 0;
			if (i <= i_lhs.size() - 1)
				summed = i_rhs[i_rhs.size() - i - 1] + i_lhs[i_lhs.size() - i - 1] + carry;
			else
				summed = i_rhs[i_rhs.size() - i - 1] + carry;
			carry = 0;

			if (summed > 9)
			{
				carry = summed / 10;
				summed -= 10 * carry;
			}

			temp_result.push_back(summed);
		}
		if (carry != 0)
			temp_result.push_back(carry);
	}
	else
	{
		for (int i = 0; i < i_lhs.size(); i++)
		{
			int summed = 0;
			if (i <= i_rhs.size() - 1)
				summed = i_lhs[i_lhs.size() - i - 1] + i_rhs[i_rhs.size() - i - 1] + carry;
			else
				summed = i_lhs[i_lhs.size() - i - 1] + carry;
			carry = 0;

			if (summed > 9)
			{
				carry = summed / 10;
				summed -= 10 * carry;
			}

			temp_result.push_back(summed);
		}


		if (carry != 0)
			temp_result.push_back(carry);
	}

	for (int i = temp_result.size() - 1; i >= 0; i--)
	{
		result.push_back(temp_result[i]);
		//std::cout << temp_result[i];
	}
	//PrintVector(result);
	return result;
}

std::vector<int> operator+(std::vector<int>& i_lhs, std::vector<int>& i_rhs)
{
	return ArraySum(i_lhs, i_rhs);
}


// A tweaked subtraction function just for this case, since the minuend should always be greater than the subtracted
std::vector<int> ArraySubtract(std::vector<int> i_minuend, std::vector<int> i_subtracted)
{
	int count = i_subtracted.size(); // set the size of subtracted as the times of calculation
	int carry = 0;
	std::vector<int> temp_result;
	std::vector<int> result;	// the result to be returned should be inversed from the temp_result which uses push_back 

	for (int i = 0; i < i_minuend.size(); i++)
	{
		int subtracted = 0;
		if (i <= i_subtracted.size() - 1)
			subtracted = i_minuend[i_minuend.size() - i - 1] - i_subtracted[i_subtracted.size() - i - 1] + carry;
		else
			subtracted = i_minuend[i_minuend.size() - i - 1] + carry;
		carry = 0;

		if (subtracted < 0)
		{
			carry = -1;
			subtracted += 10;
		}

		temp_result.push_back(subtracted);
	}

	bool first_zeros = true;
	for (int i = temp_result.size() - 1; i >= 0; i--)
	{
		if (temp_result[i] != 0)
			first_zeros = false;
		if (!first_zeros)
		{
			result.push_back(temp_result[i]);
			//std::cout << temp_result[i];
		}
	}
	if (result.size() == 0)
	{
		result.push_back(0);
		//std::cout << result[0];
	}
	//PrintVector(result);
	return result;
}
std::vector<int> operator-(std::vector<int>& i_minuend, std::vector<int>& i_subtracted)
{
	return ArraySubtract(i_minuend, i_subtracted);
}
// Tweaked multiplication for this, since it only needs to pad zeros
void ArrayMultiplication(std::vector<int>& i_base, int i_size)
{
	for (int i = 0; i < i_size; i++)
	{
		i_base.push_back(0);
	}
	//PrintVector(i_base);
}

void ReadInput(std::vector<int>& i_lhs, std::vector<int>& i_rhs)
{
	// Read the input from a .txt file
	std::fstream ifs;
	ifs.open("Input.txt", std::fstream::in);
	char char_lhs[100] = {};
	char char_rhs[100] = {};

	ifs.getline(char_lhs, 100);
	ifs.getline(char_rhs, 100);

	// Now convert the char into int numbers
	int i = 0;	// counter
	while (char_lhs[i] != '\0')
	{
		int value = (int)(char_lhs[i] - '0');
		i_lhs.push_back(value);
		i++;
	}

	i = 0;
	while (char_rhs[i] != '\0')
	{
		int value = (int)(char_rhs[i] - '0');
		i_rhs.push_back(value);
		i++;
	}
}

void SubDivide(std::vector<int>& i_vector, std::vector<int>& o_lhs, std::vector<int>& o_rhs, float i_size)
{
	if (i_size / 2 < i_vector.size())
	{
		for (int i = i_vector.size() - i_size / 2; i < i_vector.size(); i++)
		{
			o_rhs.push_back(i_vector[i]);	// divide the first half part into a/c
		}
		for (int i = 0; i < i_vector.size() - i_size / 2; i++)
		{
			o_lhs.push_back(i_vector[i]);  // divide the second half part into b/d
		}
	}
	else
	{
		o_lhs.push_back(0);
		for (int i = 0; i < i_vector.size(); i++)
		{
			o_rhs.push_back(i_vector[i]);
		}
	}
	
}

std::vector<int> Sum(std::vector<int>& i_lhs, std::vector<int>& i_rhs)
{
	long int value_lhs = 0;
	long int value_rhs = 0;
	long int sum = 0;

	for (int i = 0; i < i_lhs.size(); i++)
	{
		value_lhs += i_lhs[i] * powf(10, i_lhs.size() - 1 - i);
	}
	for (int i = 0; i < i_rhs.size(); i++)
	{
		value_rhs += i_rhs[i] * powf(10, i_rhs.size() - 1 - i);
	}

	sum = value_lhs + value_rhs;
	//std::cout << "Sum is: " << sum << "\n";

	std::vector<int> sum_vector;
	sum_vector.push_back(sum);
	return sum_vector;
}

// Cases of odd bit numbers like 12345 * 1234 are not considered yet
std::vector<int> KaratsubaMul(std::vector<int>& i_lhs, std::vector<int>& i_rhs)
{
	int max_size = i_lhs.size() <= i_rhs.size() ? i_rhs.size() : i_lhs.size();
	if (max_size % 2 != 0)
		max_size += 1;
	std::vector<int> ac;
	std::vector<int> bd;
	std::vector<int> combination; // (a+b)(c+d)
	std::vector<int> ad_bc; // ad + bc
	std::vector<int> result;

	if (i_lhs.size() >= 2 && i_rhs.size() >= 2)
	{
		std::vector<int> a;
		std::vector<int> b;
		std::vector<int> c;
		std::vector<int> d;
		std::vector<int> sum_ab;	// a+b
		std::vector<int> sum_cd;	// c+d

		int padded_size = i_lhs.size() <= i_rhs.size() ? i_rhs.size() : i_lhs.size();
		if (padded_size % 2 != 0)
			padded_size++;

		SubDivide(i_lhs, a, b, padded_size);
		SubDivide(i_rhs, c, d, padded_size);

		// Compute (a+b)(c+d)
		sum_ab = ArraySum(a, b);
		sum_cd = ArraySum(c, d);
		combination = KaratsubaMul(sum_ab, sum_cd);

		// compute a*c and b*d
		ac = KaratsubaMul(a, c);
		bd = KaratsubaMul(b, d);

		ad_bc = combination - ac;
		ad_bc = ad_bc - bd;
	}
	else
	{
		// The case with only one number multiplied with one number
		result = SmallMultiply(i_lhs, i_rhs);
		return result; //ToVector(i_lhs[0] * i_rhs[0]);
	}
	
	ArrayMultiplication(ac, max_size);
	ArrayMultiplication(ad_bc, max_size / 2);
	// Stupid operations!
	result = (ac + ad_bc);
	result = result + bd;
	return result;
}

void Karatsuba()
{
	std::cout << "This is the karatsuba multiplication sample.\n";
	std::vector<int> lhs;
	std::vector<int> rhs;
	std::vector<int> result;
	ReadInput(lhs, rhs);

	result = KaratsubaMul(lhs, rhs);
	PrintVector(result);

}

