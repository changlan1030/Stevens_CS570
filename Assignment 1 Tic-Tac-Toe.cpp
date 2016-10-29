#include <iostream>
#include <vector>

using namespace std;

void display()
{
	cout << "A tic-tac-toe game" << endl;
	cout << "  1   2   3" << endl;
	cout << "1   |   |" << endl;
	cout << " ---+---+---" << endl;
	cout << "2   |   |" << endl;
	cout << " ---+---+---" << endl;
	cout << "3   |   |" << endl;
}

char askPiece()
{
	char choice;
	do
	{
		cout << "Choose a (X/O) as player one's symbol: ";
		cin >> choice;
	} while (choice != 'X' && choice != 'O');
	return choice;
}

int askPosition()
{
	int position, row, column;
	do
	{
		cout << "Row number: ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> row;
		if (row > 3 || row < 1)
		{
			cout << "Wrong row number! Try another position." << endl;
		}
	} while (row > 3 || row < 1);
	do
	{
		cout << "Column number: ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> column;
		if (column > 3 || column < 1)
		{
			cout << "Wrong column number! Try another position." << endl;
		}
	} while (column > 3 || column < 1);
	position = (row - 1) * 3 + column - 1;
	return position;
}

void result(const vector<char>& position)
{
	cout << endl << endl;
	cout << "  1   2   3" << endl;
	cout << "1 " << position[0] << " | " << position[1] << " | " << position[2] << endl;
	cout << " ---+---+---" << endl;
	cout << "2 " << position[3] << " | " << position[4] << " | " << position[5] << endl;
	cout << " ---+---+---" << endl;
	cout << "3 " << position[6] << " | " << position[7] << " | " << position[8] << endl;
}

int win(const vector<char>& position, char choiceOne, char choiceTwo)
{
	if (position[0] == 'X' && position[1] == 'X' && position[2] == 'X' ||
		position[3] == 'X' && position[4] == 'X' && position[5] == 'X' ||
		position[6] == 'X' && position[7] == 'X' && position[8] == 'X' ||
		position[0] == 'X' && position[3] == 'X' && position[6] == 'X' ||
		position[1] == 'X' && position[4] == 'X' && position[7] == 'X' ||
		position[2] == 'X' && position[5] == 'X' && position[8] == 'X' ||
		position[0] == 'X' && position[4] == 'X' && position[8] == 'X' ||
		position[2] == 'X' && position[4] == 'X' && position[6] == 'X')
	{
		if (choiceOne == 'X')
		{
			cout << "Congratulations! Player one wins." << endl;
		}
		else
		{
			cout << "Congratulations! Player two wins." << endl;
		}
		return 0;
	}
	if (position[0] == 'O' && position[1] == 'O' && position[2] == 'O' ||
		position[3] == 'O' && position[4] == 'O' && position[5] == 'O' ||
		position[6] == 'O' && position[7] == 'O' && position[8] == 'O' ||
		position[0] == 'O' && position[3] == 'O' && position[6] == 'O' ||
		position[1] == 'O' && position[4] == 'O' && position[7] == 'O' ||
		position[2] == 'O' && position[5] == 'O' && position[8] == 'O' ||
		position[0] == 'O' && position[4] == 'O' && position[8] == 'O' ||
		position[2] == 'O' && position[4] == 'O' && position[6] == 'O')
	{
		if (choiceOne == 'O')
		{
			cout << "Congratulations! Player one wins." << endl;
		}
		else
		{
			cout << "Congratulations! Player two wins." << endl;
		}
		return 0;
	}
	if (position[0] != ' ' && position[1] != ' ' && position[2] != ' ' &&
		position[3] != ' ' && position[4] != ' ' && position[5] != ' ' &&
		position[6] != ' ' && position[7] != ' ' && position[8] != ' ')
	{
		cout << "It's a tie. No one wins." << endl;
		return 0;
	}
	return 1;
}

int main()
{
	int count;
	vector<char> position(9, ' ');

	display();

	char choiceOne = askPiece();
	char choiceTwo;
	if (choiceOne == 'X')
	{
		choiceTwo = 'O';
	}
	else
	{
		choiceTwo = 'X';
	}
	cout << "Player one chooses: " << choiceOne << endl;
	cout << "Player two chooses: " << choiceTwo << endl;

	char turn = choiceOne;
	while (win(position, choiceOne, choiceTwo))
	{
		if (turn == choiceOne)
		{
			cout << "It's player one's turn, please input the position:" << endl;
			count = askPosition();
			while (position[count] != ' ')
			{
				cout << "Wrong position! Try another position." << endl;
				count = askPosition();
			}
			position[count] = choiceOne;
			turn = choiceTwo;
		}
		else if (turn == choiceTwo)
		{
			cout << "It's player two's turn, please input the position:" << endl;
			count = askPosition();
			while (position[count] != ' ')
			{
				cout << "Wrong position! Try another position." << endl;
				count = askPosition();
			}
			position[count] = choiceTwo;
			turn = choiceOne;
		}
		result(position);
	}
}