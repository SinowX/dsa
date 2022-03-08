#include "vector.h"
#include <iostream>

int main()
{
	Vector vec;
	vec.push_back(123);
	vec.push_back(12);
	vec.push_back(3);
	vec.push_back(1);
	vec.push_back(23);
	
	vec.push_back(12);
	vec.push_back(3);
	vec.push_back(1);
	vec.push_back(23);
	vec.push_back(12);
	vec.push_back(3);
	vec.push_back(1);
	vec.push_back(23);
	
	while(!vec.empty())
	{
		std::cout<<vec.pop_back()<<std::endl;
	}
}
