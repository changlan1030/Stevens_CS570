#include <iostream>
#include <vector>

using namespace std;

vector<int> getVector(int size)
{
	vector<int> number(size);
	for (int i = 0; i < size; i++)
		cin >> number[i];
	return number;
}

void bubbleSort(vector<int> &A)
{
	auto size = A.size();
	if (size <= 1)
		return;
	int pass = 0;
	int swapCount, below, above;
	do {
		swapCount = 0;
		for (below = size - 1, above = size - 2; above >= pass; below--, above--)
		{
			if (A[below] > A[above])
			{
				swap(A[below], A[above]);
				swapCount++;
			}
		}
		pass++;
	} while (swapCount > 0 && pass < size - 1);
}

bool binarySearch(vector<int> const &A, int tarVal)
{
	int first = 0, last = A.size() - 1, mid;
	while (first <= last)
	{
		mid = (first + last) / 2;
		if (tarVal > A[mid])
			last = mid - 1;
		else if (tarVal < A[mid])
			first = mid + 1;
		else
			return true;
	}
	return false;
}

int main()
{
	int n, m;
	cout << "How many numbers? " << endl;
	cin >> n;
	cout << "What are they? " << endl;
	auto number = getVector(n);
	cout << "The number to be searched: " << endl;
	cin >> m;
	bubbleSort(number);
	cout << "The " << n << " numbers after bubble sort: " << endl;
	for (int i = 0; i < number.size(); i++)
		cout << number[i] << " ";
	cout << endl;
	if (binarySearch(number, m))
		cout << "The number can be found." << endl;
	else
		cout << "The number can't be found." << endl;
}