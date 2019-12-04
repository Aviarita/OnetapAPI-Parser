// APIParser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

std::vector<std::string> split(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

bool replace(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

int main(int argc, const char * argv[]) {
	std::ifstream inputFile("API.txt");
	std::ofstream outputFile("javascript.json");
	outputFile << "{\n";

	std::string line;
	int i = 0;
	while (std::getline(inputFile, line)) {
		std::istringstream lineStream(line);
		if (i % 2) { // Main
			outputFile << "\t\t\"description\": \"" << line << "\"\n";
			outputFile << "\t},\n";
		}
		else { // Body 
			auto info = split(line, ' ');
			auto Header = split(split(line, '(').at(0), ' ');
			replace(Header.at(1), ".", "");

			outputFile << "\t\"" << Header.at(1) << "\":{\n";
			line = line.substr(line.find_first_of(" \t") + 1);
			outputFile << "\t\t\"prefix\": " << std::quoted(line) << ",\n";
			outputFile << "\t\t\"body\": " << std::quoted(line) << ",\n";
		}
		i++;
	}
	outputFile << "}\n";
	outputFile.close();

	return 0;
}
