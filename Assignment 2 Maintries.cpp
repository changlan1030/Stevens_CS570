#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;


class syno {
public:
	char synoName;
	vector<int> primaryNameNum;
	shared_ptr<syno> child, brother;
	syno(char name, int num) {
		synoName = name;
		primaryNameNum.push_back(num);
	}
};

class dictEntry {
public:
	string primaryName;
	int count = 0;
	dictEntry(string name) {
		primaryName = name;
	}
};

/* check if it is the end of std input */
bool isEOF(string str)
{
	int i = 0;
	if (str == "")
		return false;
	while (i < str.length()) {
		if (str[i] != '.')
			break;
		i++;
	}
	if (i == str.length())
		return true;
	else
		return false;
	
}

/* normalize every name*/
string checkSymbols(string str)
{
	int i = 0;
	string synoNewName = "";

	for (; i < str.length(); i++) {
		if ((str[i] <= 'z' && str[i] >= 'a') || (str[i] >= 'A' &&str[i] <= 'Z') || str[i] == ' ')
			synoNewName += str[i];
	}
	return synoNewName;
}

/* insert into tries structure */
void insertToTries(string synoName, int primaryNum, shared_ptr<syno> root)
{
	shared_ptr<syno> synoEntry, synoNew;
	int depth = 0;
	bool setFlag = false; /* check whether there is a child node for current synoEntry */

	synoEntry = root;
	synoName = checkSymbols(synoName);

	while (depth < synoName.length()) {
		if (synoEntry->synoName == synoName[depth]) {
			depth++;
			if (depth == synoName.length())
				break;
			if (synoEntry->child == nullptr) {
				synoNew = static_cast<shared_ptr<syno>> (new syno(synoName[depth], -1));
				synoEntry->child = synoNew;
				setFlag = true;
				if (depth == synoName.length() - 1)
					break;
			}
			else
				setFlag = false;
			synoEntry = synoEntry->child;
		}
		else {
			if (synoEntry->brother == nullptr) {
				synoNew = static_cast<shared_ptr<syno>> (new syno(synoName[depth], -1));
				synoEntry->brother = synoNew;
				setFlag = false;
			}
			else
				setFlag = false;
			synoEntry = synoEntry->brother;
		}
	}
	if (setFlag)
		synoEntry = synoEntry->child;
	synoEntry->primaryNameNum.push_back(primaryNum);
}

/* return the number of maximum words in a name */
int checkWordsAmount(string str)
{
	int amount = 1;

	for (int i = 0; i < str.length(); i++)
		if (str[i] == ' ')
			amount++;
	return amount;
}

void disposeDictEntry(vector<dictEntry> &dName, string line, int order, shared_ptr<syno> root, int &maxLen)
{
	int pos, len;
	shared_ptr<dictEntry> dEntry;
	bool endFlag = false;
	string name, syno, tmp, pattern = "	";

	pos = line.find(pattern, 0);
	if (pos != -1) {
		name = line.substr(0, pos);
		syno = line.substr(pos + 1, line.length()-1);
	}

	/* read the primary name */
	dEntry = static_cast<shared_ptr<dictEntry>> (new dictEntry(name));
	dName.push_back(*dEntry);
	name = checkSymbols(name);
	insertToTries(name, order, root);
	len = checkWordsAmount(name);
	if (len > maxLen)
		maxLen = len;
	
	/* read every synonym */
	pattern = "	";
	pos = syno.find(pattern, 0);
	while (pos != -1) {
		tmp = syno.substr(0, pos);
		insertToTries(tmp, order, root);
		len = checkWordsAmount(tmp);
		if (len > maxLen)
			maxLen = len;
		syno = syno.substr(pos + 1, syno.length());
		pos = syno.find(pattern, 0);
	}
	/* handle the last synonym */
	tmp = syno;
	insertToTries(tmp, order, root);
}

/* this function used for finding a specific name in tries */
vector<int> matchSyno(string word, shared_ptr<syno> root)
{
	shared_ptr<syno> synoEntry, synoLast;
	int depth = 0;

	synoEntry = root;
	while (synoEntry != nullptr) {
		if (synoEntry->synoName == word[depth]) {
			depth++;
			synoLast = synoEntry;
			synoEntry = synoEntry->child;
		}
		else {
			synoEntry = synoEntry->brother;
		}
	}
	if (depth == word.length()) {
		return synoLast->primaryNameNum;
	}
	else
		return vector<int> {-1};

}

int main()
{
	ifstream infile;
	string inStr, outStr="";
	vector<dictEntry> dictName;
	vector<int> res;
	vector<string> allWords;
	shared_ptr<syno> root;
	char inChr;
	char * countConvert = new char[255];
	bool overFlowFLag;
	int i=0, count=0, currPos=0, maxLen = 1, j;


	root = static_cast<shared_ptr<syno>> (new syno('\n', -1));
	infile.open("companies.dat", ios::in);
	while (getline(infile, inStr)) {
		disposeDictEntry(dictName, static_cast<string> (inStr), i, root, maxLen);
		i++;
	};

	inStr = "";

	while (cin.get(inChr)) {
		if (inChr != ' ' && inChr != '\n' && inChr != '\r') {
			inStr += inChr;
			continue;
		}
		else
			if (inChr == '\n' || inChr == '\r') {
				if (isEOF(inStr))
					break;
				else
					continue;	
			}



		if (inStr != "a" && inStr != "an" && inStr != "the" && inStr != "and" && inStr != "or" && inStr != "but")
			count++;
		allWords.push_back(inStr);

		inStr = "";
		/* this loop used for counting synonyms with multiple words*/
		for (i = 1; i <= maxLen; i++) {
			overFlowFLag = false;
			for (j = 0; j < i; j++)
				if (inStr != "") {
					if ((static_cast<int>(allWords.size()) - j - 1) < 0) {
						overFlowFLag = true;
						break;
					}
					inStr = allWords[allWords.size() - j - 1] + ' ' + inStr;
				}
				else
					inStr = allWords[allWords.size() - j - 1] + inStr;
			if (overFlowFLag)
				break;
			res = matchSyno(inStr, root);
			for_each(res.begin(), res.end(), [&](int x) {
				if (x != -1)
					/* counting by the actual words (i) in a synonym */
					dictName[x].count += i;
			});
			inStr = "";
		}
		inStr = "";
		
	}

	/* output part */
	for_each(dictName.begin(), dictName.end(), [&](dictEntry dEntry) {
		outStr += dEntry.primaryName;
		outStr += "  ";
		sprintf_s(countConvert, 255, "Relevance: %d%%", dEntry.count * 100 / count );
		outStr += static_cast<string>(countConvert);
		outStr += "\n";
	});
	cout << outStr;
	return 0;
}