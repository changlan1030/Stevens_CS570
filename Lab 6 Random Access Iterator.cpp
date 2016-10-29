#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

template <typename T, typename S>
class MyIterator
{
private:
	int index;
	T a;
public:
	MyIterator(T& vec, S num)
	{
		this->index = num;
		this->a = vec;
	}

	S& operator*()
	{
		return a[index];
	}

	bool operator==(MyIterator<T, S>& other)
	{
		return index == other.getIndex();
	}

	bool operator!=(MyIterator<T, S>& other)
	{
		return index != other.getIndex();
	}

	int getIndex()
	{
		return index;
	}

	MyIterator<T, S>& operator++(int)
	{
		index++;
		return *this;
	}

	MyIterator<T, S>& operator=(int x)
	{
		index = x;
		return *this;
	}

	MyIterator<T, S>& operator--(int)
	{
		index--;
		return *this;
	}
};

int main()
{
	vector<int> vec(2);
	vec = { 1, 2, 4, 3, 6, 5, 1, 1 };
	MyIterator<vector<int>, int> ptr(vec, 0), ptr1(vec, 7), ptr2(vec, 8), ptr3(vec, -1);

	for (; !(ptr == ptr2); ptr++)
	{
		cout << *ptr << endl;
	}
	cout << endl;

	for (; ptr3 != ptr1; ptr1--)
	{
		cout << *ptr1 << endl;
	}
	cout << endl;

	return 0;
}