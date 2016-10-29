#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int number;
	cout << "How many numbers do you want to read in?" << endl;
	cin >> number;

	vector<int> myvector(number);
	cout << "What are they?" << endl;
	generate(myvector.begin(), myvector.end(), []() { int val; cin >> val; return val; });

	int i = 0, count_max = 0, key;
	vector<int> mycount(number);
	generate(mycount.begin(), mycount.end(), [&]()
	{
		int mycount = count(myvector.begin(), myvector.end(), myvector[i]);
		i++;
		if (mycount > count_max)
		{
			count_max = mycount;
			key = i;
			return mycount;
		}
	});

	if (count_max > 1)
	{
		cout << "The mode is " << myvector[key] << "." << endl;
	}
	else
	{
		cout << "Cannot find the mode." << endl;
	}
	return 0;
}