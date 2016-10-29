#include<iostream>
#include<vector>

using namespace std;

vector<int> initInput();
int initQuery();
bool binarySearch(vector<int>, int);

vector<int> initInput()
{
	vector<int> inputSeq;
	int len, tmp;
	cout << "Please input the length of your sequence:";
	cin >> len;
	cout << "Please input a descending sequence:";
	while (len--)
	{
		cin >> tmp;
		inputSeq.push_back(tmp);
	}
	cin.ignore(256, '\n');
	//cin.clear();
	//fflush(stdin);
	return inputSeq;
}


int initQuery()
{
	int queryNum;
	cout << "Please input the number to search in sequence:";
	cin >> queryNum;
	return queryNum;
}

bool binarySearch(vector<int> s, int num)
{
	int  mid, head = 0, tail = s.size()-1;
	while (head <= tail)
	{
		mid = (head + tail) / 2;
		if (s[mid] > num)
		{
			head = mid + 1;
			continue;
		}
		else if (s[mid] < num)
		{
			tail = mid - 1;
			continue;
		}
		else
			return true;
	}
	return false;
}

int main()
{
	vector<int> seq = initInput();
	int query = initQuery();
	bool res = binarySearch(seq, query);
	if (res)
		cout << "True. The num is in the sequence" << endl;
	else
		cout << "False. The num is not in the sequence" << endl;
	return 0;
}