#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

void count_word(string, int *);

void output_table(int *);

void count_word(string inStr, int * count)
{
	switch (inStr.length())
	{
	case 1:
		(*count)++;
		break;
	case 2:
		(*(count + 1))++;
		break;
	case 3:
		(*(count + 2))++;
		break;
	default:
		(*(count + 2))++;
		break;
	}
}

void output_table(int *count)
{
	const int total = *count + *(count + 1) + *(count + 2);
	cout << "The frequency of letters in given words:" << endl;
	cout << setiosflags(ios::fixed | ios::showpoint) << setprecision(2);
	cout << "1 letter words : " << *count << ", about " << float(*count) * 100 / total << "%" << endl;
	cout << "2 letter words : " << *(count + 1) << ", about " << float(*(count + 1)) * 100 / total << "%" << endl;
	cout << "3 letter words : " << *(count + 2) << ", about " << float(*(count + 2)) * 100 / total << "%" << endl;
	cout << "That's all, thanks" << endl;
}
void main()
{
	ifstream infile("input.txt");
	if (infile.fail())
	{
		cout << "File not accessable" << endl;
		return;
	}
	string tmp;
	int *count = new int[3]{ 0, 0, 0 };
	while (!infile.eof())
	{
		infile >> tmp;
		count_word(tmp, count);
	}
	output_table(count);
	return;
}