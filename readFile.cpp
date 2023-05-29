#include <fstream>
#include <sstream>
#include <iostream>

std::string	readFile(const char *fileName)
{
	std::ifstream file;
	file.open(fileName);
	if (!file.is_open())
	{
		std::cerr << "Error opening " << fileName << std::endl;
		exit(EXIT_FAILURE);
	}
	std::stringstream temp;
	temp << file.rdbuf();
	std::string str = temp.str();
	file.close();
	return (str);
}

