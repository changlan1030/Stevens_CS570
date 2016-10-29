#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class node
{
public:
	int value = 0;
	shared_ptr<node> lc, rc;
	string code = "";
	char ch;
	node()
	{
		value = 0;
		code = "0";
		lc = nullptr;
		rc = nullptr;
	}
	static shared_ptr<node> copyNode(node origin)
	{
		shared_ptr<node> fork = make_shared<node>();
		fork->code = origin.code;
		fork->value = origin.value;
		fork->lc = origin.lc;
		fork->rc = origin.rc;
		fork->ch = origin.ch;
		return  fork;
	}
};

ifstream in;
ofstream out;

void printCharFrequency(const vector<node> frq)
{
	int j = 0;
	out << "Char : Frequency" << endl;
	for_each(frq.begin(), frq.end(), [&j](node x)
	{
		if (j < 26)
		{
			out << static_cast<char> (j + 65) << " : " << x.value << endl;
		}
		else if (j < 52)
		{
			out << static_cast<char> (j + 71) << " : " << x.value << endl;
		}
		else if (j < 62)
		{
			out << static_cast<char> (j - 4) << " : " << x.value << endl;
		}
		j++;
		return;
	});
	out << endl;
}

struct cmp
{
	bool operator() (const node& lhs, const node& rhs)
	{
		return lhs.value > rhs.value;
	}
};


shared_ptr<node> doHuffman(vector<node> & orifrq)
{
	shared_ptr<node> min1, min2, tmp;
	int count = 0;
	priority_queue<node, vector<node>, cmp> frq;
	for_each(orifrq.begin(), orifrq.end(), [&](node x)
	{
		if (x.value != 0)
		{
			frq.push(x);
		}
	});
	//make_heap(frq.begin(), frq.end(), [=](node i, node j) { return (i.value > j.value); });
	//push_heap(frq.begin(), frq.end(), [=](node i, node j) { return (i.value > j.value); });
	//sort_heap(frq.begin(), frq.end(), [=](node i, node j) { return (i.value > j.value); });
	count = frq.size();
	while (count != 1)
	{
		min1 = tmp->copyNode(frq.top());
		min1->code = "0";
		//pop_heap(frq.begin(), frq.end(), [=](node i, node j) { return (i.value > j.value); });
		frq.pop();
		min2 = tmp->copyNode(frq.top());
		min2->code = "1";
		frq.pop();
		tmp = make_shared<node>();
		tmp->value = min1->value + min2->value;
		tmp->lc = min1;
		tmp->rc = min2;
		frq.push(*tmp);
		//push_heap(frq.begin(), frq.end(), [=](node i, node j) { return (i.value > j.value); });
		count--;
	}
	return tmp;
}

void tranverse(vector<node> &res, shared_ptr<node> root, string seq)
{
	if (root->lc != nullptr)
	{
		tranverse(res, root->lc, seq + root->code);
	}
	if (root->rc != nullptr)
	{
		tranverse(res, root->rc, seq + root->code);
	}
	root->code = seq + root->code;
	if ((root->ch <= '9') && (root->ch >= '0'))
	{
		res[root->ch + 4] = *root;
	}
	else if ((root->ch <= 'Z') && (root->ch >= 'A'))
	{
		res[root->ch - 65] = *root;
	}
	else if ((root->ch <= 'z') && (root->ch >= 'a'))
	{
		res[root->ch - 71] = *root;
	}
	root.reset();
}

void printHuffCode(vector<node> &res)
{
	out << "Char : Huffman Code" << endl;
	for_each(res.begin(), res.end(), [=](node x)
	{
		if (x.value != 0)
		{
			out << x.ch << " : " << x.code << endl;
		}
	});
	out << endl;
}

void calcLength(vector<node> &res, string str)
{
	int total = 0;
	for (int i = 0; i < static_cast<int> (str.length()); i++)
		if ((str[i] <= '9') && (str[i] >= '0'))
		{
			total += res[str[i] + 4].code.length();
		}
		else if ((str[i] <= 'Z') && (str[i] >= 'A'))
		{
			total += res[str[i] - 65].code.length();
		}
		else if ((str[i] <= 'z') && (str[i] >= 'a'))
		{
			total += res[str[i] - 71].code.length();
		}
		out << "Total length of bits after Huffman encoding is " << total << endl;
}

int main()
{
	vector<node> frq(62);
	shared_ptr<node> root;
	in.open("infile.dat", ios::in);
	out.open("outfile.dat", ios::out);
	string tmp, raw = "";
	while (!in.eof())
	{
		in >> tmp;
		for (int i = 0; i < static_cast<int> (tmp.length()); i++)
		{
			if ((tmp[i] <= '9') && (tmp[i] >= '0'))
			{
				frq[tmp[i] + 4].value++;
				frq[tmp[i] + 4].ch = static_cast<char> (tmp[i]);
			}
			else if ((tmp[i] <= 'Z') && (tmp[i] >= 'A'))
			{
				frq[tmp[i] - 65].value++;
				frq[tmp[i] - 65].ch = static_cast<char> (tmp[i]);
			}
			else if ((tmp[i] <= 'z') && (tmp[i] >= 'a'))
			{
				frq[tmp[i] - 71].value++;
				frq[tmp[i] - 71].ch = static_cast<char> (tmp[i]);
			}
		}
		raw += tmp;
	}
	printCharFrequency(frq);
	vector<node> frqdup = frq;
	root = doHuffman(frqdup);
	vector<node> res(62);
	tranverse(res, root, "");
	printHuffCode(res);
	calcLength(res, raw);
	out.close();
	in.close();
	return 0;
}