#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <iomanip>
#include <vector>
#pragma warning(disable: 4996)

using namespace std;

int main()
{
	// Initialize the vector for saving the primary names and synonym names
	vector<vector<string> > company(10);
	for (int i = 0; i < 10; i++)
	{
		company[i].resize(10);
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			company[i][j] = ".";
		}
	}

	// Input the companies.dat
	ifstream infile1("companies.dat");
	string companyLine;
	int row = 0; // Number of company primary names
	while (getline(infile1, companyLine))
	{
		int col = 0;
		char* pcompanyLine = &companyLine[0];
		char* pch = strtok(pcompanyLine, "'\t'"); // Separate the names by using strtok
		while (pch != NULL)
		{
			company[row][col] = pch;
			col++;
			pch = strtok(NULL, "'\t'");
		}
		row++;
	}
	infile1.close();

	// Exclude some symbols in the name
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			string filter(",.");
			string::size_type pos = 0;
			while ((pos = company[i][j].find_first_of(filter, pos)) != string::npos)
			{
				company[i][j].erase(pos, 1);
			}
		}
	}

	cout << "Number of companies: " << row << endl;
	for (int i = 0; i < row; i++)
	{
		cout << company[i][0] << endl;
	}
	cout << endl;

	// Input the article.dat
	vector<string> article(1000);
	ifstream infile2("article.dat");
	string articleLine;
	int wordNumber = 0; // Number of words
	while (getline(infile2, articleLine))
	{
		char* particleLine = &articleLine[0];
		char* pch1 = strtok(particleLine, "' ',.'-_=+[]{}:;<>/?|!#$%^*()"); // Exclude some symbols in the article
		while (pch1 != NULL)
		{
			article[wordNumber] = pch1;
			pch1 = strtok(NULL, "' ',.'-_=+[]{}:;<>/?|!#$%^*()");
			wordNumber++;
		}
	}
	infile2.close();

	int totalNumber = wordNumber; // number of words after matching
	cout << "Number of words in the article: " << totalNumber << endl << endl;
	
	// Initialize the vector for saving the number of names in the article
	vector<int> companyNumber(row);
	cout << "Match:" << endl;
	for (int i = 0; i < row; i++)
	{
		companyNumber[i] = 0;
	}

	// Match
	for (int i = 0; i < wordNumber; i++)
	{
		// Exclude some words
		if (article[i] == "the" || article[i] == "a" || article[i] == "an" || article[i] == "and" || article[i] == "or" || article[i] == "but")
		{
			totalNumber = totalNumber - 1;
		}
		string blank = " ";
		string twoWord = article[i] + blank + article[i + 1]; // Some names have two words
		string threeWord = article[i] + blank + article[i + 1] + blank + article[i + 2]; // Some names have three words
		for (int j = 4; j >= 0; j--)
		{
			for (int k = 4; k >= 0; k--)
			{
				if (threeWord == company[j][k])
				{
					cout << threeWord << "--" << company[j][0] << endl;
					companyNumber[j]++;
					totalNumber = totalNumber - 2;
					break;
				}
				if (twoWord == company[j][k])
				{
					cout << twoWord << "--" << company[j][0] << endl;
					companyNumber[j]++;
					totalNumber = totalNumber - 1;
					break;
				}
				if (article[i] == company[j][k])
				{
					cout << article[i] << "--" << company[j][0] << endl;
					companyNumber[j]++;
				}
			}
		}
	}

	cout << endl << "Relevance:" << endl;

	for (int i = 0; i < row; i++)
	{
		cout << company[i][0] << ": " << companyNumber[i] << "/" << totalNumber << endl;
	}
	
	return 0;
}