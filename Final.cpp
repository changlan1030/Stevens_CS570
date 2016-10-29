#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <iomanip>
#include <vector>
#include <stack>
#pragma warning(disable: 4996)

using namespace std;

int main()
{
	// input graph.dat
	vector<vector<int> > data(100);
	for (int i = 0; i < 100; i++)
	{
		data[i].resize(100);
	}
	vector<int> colNum(100);
	for (int i = 0; i < 100; i++)
	{
		colNum[i] = 0;
	}
	ifstream in("graph.dat");
	string line;
	int count = 0;
	int row = 0;
	while (getline(in, line))
	{
		int col = 0;
		char* pline = &line[0];
		char* pch = strtok(pline, " "); // separate the numbers by using strtok
		while (pch != NULL)
		{
			int temp = atoi(pch);
			data[row][col] = temp;
			count++;
			col++;
			pch = strtok(NULL, " ");
		}
		colNum[row] = col;
		row++;
	}
	in.close();

	cout << count << endl;

	// create adjacency matrix
	cout << "processing..." << endl;
	vector<vector<int> > matrix(10000);
	for (int i = 0; i < 10000; i++)
	{
		matrix[i].resize(10000);
	}
	int maxPoint = 1; // the biggest number of point
	for (int i = 0; i < row; i++)
	{
		int souPoint = data[i][0]; // the starting point
		if (maxPoint < souPoint)
		{
			maxPoint = souPoint;
		}
		for (int j = 1; j < colNum[i]; j = j + 2)
		{
			int desPoint = data[i][j]; // the ending point
			if (maxPoint < desPoint)
			{
				maxPoint = desPoint;
			}
			matrix[souPoint - 1][desPoint - 1] = data[i][j + 1]; // save the weight
		}
	}

	// calculate in-degree and out-degree
	vector<vector<int> > degree(maxPoint);
	for (int i = 0; i < maxPoint; i++)
	{
		degree[i].resize(5);
	}
	for (int i = 0; i < maxPoint; i++)
	{
		degree[i][0] = i + 1; // the No. of the point
		degree[i][1] = 0; // the out-degree
		degree[i][2] = 0; // the in-degree
		degree[i][4] = 0; // count the degree
	}
	for (int i = 0; i < maxPoint; i++)
	{
		for (int j = 0; j < maxPoint; j++)
		{
			if (matrix[i][j] != 0)
			{
				degree[i][1]++;
			}
		}
	}
	for (int j = 0; j < maxPoint; j++)
	{
		for (int i = 0; i < maxPoint; i++)
		{
			if (matrix[i][j] != 0)
			{
				degree[j][2]++;
			}
		}
	}
	for (int i = 0; i < maxPoint; i++)
	{
		degree[i][3] = degree[i][1] + degree[i][2]; // out-degree + in-degree
	}

	// bubble sort by degree
	int i, j;
	for (i = 0; i < maxPoint; i++)
	{
		for (j = 0; i + j < maxPoint - 1; j++)
		{
			if (degree[j][3] < degree[j + 1][3])
			{
				int temp0 = degree[j][0];
				degree[j][0] = degree[j + 1][0];
				degree[j + 1][0] = temp0;
				int temp1 = degree[j][1];
				degree[j][1] = degree[j + 1][1];
				degree[j + 1][1] = temp1;
				int temp2 = degree[j][2];
				degree[j][2] = degree[j + 1][2];
				degree[j + 1][2] = temp2;
				int temp3 = degree[j][3];
				degree[j][3] = degree[j + 1][3];
				degree[j + 1][3] = temp3;
			}
		}
	}

	// calculate the number of nodes
	int pointNum = 0;
	for (int i = 0; i < maxPoint; i++)
	{
		if (degree[i][3] != 0)
		{
			pointNum++;
		}
	}

	// calculate the number of lines
	int lineNum = 0;
	for (int i = 0; i < maxPoint; i++)
	{
		for (int j = 0; j < maxPoint; j++)
			if (matrix[i][j] != 0)
			{
				lineNum++;
			}
	}
	
	// bubble sort by node
	vector<int> degree2(maxPoint);
	for (int i = 0; i < pointNum; i++)
	{
		degree2[i] = degree[i][0];
	}
	int p, q;
	for (p = 0; p < pointNum; p++)
	{
		for (q = 0; p + q < pointNum - 1; q++)
		{
			if (degree2[q] > degree2[q + 1])
			{
				int temp0 = degree2[q];
				degree2[q] = degree2[q + 1];
				degree2[q + 1] = temp0;
			}
		}
	}

	// initialize output chart
	vector<vector<int> > chart(pointNum);
	for (int i = 0; i < pointNum; i++)
	{
		chart[i].resize(pointNum);
	}
	for (int i = 0; i < pointNum; i++)
	{
		for (int j = 0; j < pointNum; j++)
		{
			int x = degree2[i] - 1;
			int y = degree2[j] - 1;
			if (x == y)
			{
				chart[i][j] = 0; // the distance between point A and point A
			}
			else if (matrix[x][y] == 0)
			{
				chart[i][j] = INT_MAX; // the distance between the points that have no direct path
			}
			else
			{
				chart[i][j] = matrix[x][y];
			}
		}
	}

	// initialize output graph
	int width = lineNum * 8 + 17;
	int height = pointNum * 8;
	vector<vector<string> > graph(height);
	for (int i = 0; i < height; i++)
	{
		graph[i].resize(width);
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			graph[i][j] = " ";
		}
	}

	// draw the nodes in the graph
	for (int i = 0; i < pointNum; i++)
	{
		int pos_X = i * 8 + 3;
		int a = degree[i][0]; // the No. of the node
		int a0 = a / 1000;
		int a1 = (a - a0 * 1000) / 100;
		int a2 = (a - a0 * 1000 - a1 * 100) / 10;
		int a3 = a - a0 * 1000 - a1 * 100 - a2 * 10;
		char b0[2];
		char b1[2];
		char b2[2];
		char b3[2];
		itoa(a0, b0, 10);
		itoa(a1, b1, 10);
		itoa(a2, b2, 10);
		itoa(a3, b3, 10);
		graph[pos_X][0] = "+";
		graph[pos_X][1] = "-";
		graph[pos_X][2] = "-";
		graph[pos_X][3] = "[";
		if (a <= 9)
		{
			graph[pos_X][4] = b3;
			graph[pos_X][5] = "]";
			graph[pos_X][6] = "-";
			graph[pos_X][7] = "-";
			graph[pos_X][8] = "-";
		}
		if (a >= 10 && a <= 99)
		{
			graph[pos_X][4] = b2;
			graph[pos_X][5] = b3;
			graph[pos_X][6] = "]";
			graph[pos_X][7] = "-";
			graph[pos_X][8] = "-";
		}
		if (a >= 100 && a <= 999)
		{
			graph[pos_X][4] = b1;
			graph[pos_X][5] = b2;
			graph[pos_X][6] = b3;
			graph[pos_X][7] = "]";
			graph[pos_X][8] = "-";
		}
		if (a >= 1000 && a <= 9999)
		{
			graph[pos_X][4] = b0;
			graph[pos_X][5] = b1;
			graph[pos_X][6] = b2;
			graph[pos_X][7] = b3;
			graph[pos_X][8] = "]";
		}
		graph[pos_X][9] = "-";
		graph[pos_X][10] = "-";
		graph[pos_X][11] = " ";
		graph[pos_X][12] = " ";
		graph[pos_X][13] = " ";
		graph[pos_X][14] = " ";
		graph[pos_X - 3][4] = "+";
		graph[pos_X - 2][4] = "|";
		graph[pos_X - 1][4] = "|";
		graph[pos_X + 1][4] = "|";
		graph[pos_X + 2][4] = "|";
		graph[pos_X + 3][4] = "+";
		graph[pos_X + 4][4] = "-";
		graph[pos_X + 4][0] = "+";
		graph[pos_X + 4][1] = "-";
		graph[pos_X + 4][2] = "-";
		graph[pos_X + 4][3] = "-";
		graph[pos_X + 4][4] = "-";
		graph[pos_X + 4][5] = "-";
		graph[pos_X + 4][6] = "-";
		graph[pos_X + 4][7] = "-";
		graph[pos_X + 4][8] = "-";
		graph[pos_X + 4][9] = "-";
		graph[pos_X + 4][10] = "-";
		graph[pos_X + 4][11] = " ";
		graph[pos_X + 4][12] = " ";
		graph[pos_X + 4][13] = " ";
		graph[pos_X + 4][14] = " ";
		graph[pos_X + 3][5] = "-";
		graph[pos_X + 3][6] = "-";
		graph[pos_X + 3][7] = "-";
		graph[pos_X + 3][8] = "-";
		graph[pos_X + 3][9] = "-";
		graph[pos_X + 3][10] = "-";
		graph[pos_X + 3][11] = " ";
		graph[pos_X + 3][12] = " ";
		graph[pos_X + 3][13] = " ";
		graph[pos_X + 3][14] = " ";
		graph[pos_X - 3][5] = "-";
		graph[pos_X - 3][6] = "-";
		graph[pos_X - 3][7] = "-";
		graph[pos_X - 3][8] = "-";
		graph[pos_X - 3][9] = "-";
		graph[pos_X - 3][10] = "-";
		graph[pos_X - 3][11] = " ";
		graph[pos_X - 3][12] = " ";
		graph[pos_X - 3][13] = " ";
		graph[pos_X - 3][14] = " ";
		graph[pos_X + 1][0] = "|";
		graph[pos_X + 2][0] = "|";
		graph[pos_X + 3][0] = "|";
	}

	// draw the arrows and weight in the graph
	int lineCount = 0;
	for (int i = 0; i < pointNum; i++)
	{
		for (int j = 0; j < pointNum; j++)
		{
			int point1 = degree[i][0]; // the starting node
			int point2 = degree[j][0]; // the ending node
			int point1_X = i * 8 + 3;
			int point2_X = j * 8 + 3;
			int num1 = degree[point1 - 1][4]; // count the degree
			int num2 = degree[point2 - 1][4]; // count the degree
			int d0 = matrix[point1 - 1][point2 - 1];
			int d1, d2;
			if (num1 == 0)
			{
				d1 = 0;
			}
			if (num1 == 1)
			{
				d1 = 3;
			}
			if (num1 == 2)
			{
				d1 = 6;
			}
			if (num1 == 3)
			{
				d1 = 7;
			}
			if (num2 == 0)
			{
				d2 = 0;
			}
			if (num2 == 1)
			{
				d2 = 3;
			}
			if (num2 == 2)
			{
				d2 = 6;
			}
			if (num2 == 3)
			{
				d2 = 7;
			}
			if (d0 != 0)
			{
				if (d2 == 0)
				{
					graph[point2_X - 1][4] = "V";
				}
				if (d2 == 3)
				{
					if (graph[point2_X][5] == "]")
					{
						graph[point2_X][6] = "<";
					}
					if (graph[point2_X][6] == "]")
					{
						graph[point2_X][7] = "<";
					}
					if (graph[point2_X][7] == "]")
					{
						graph[point2_X][8] = "<";
					}
					if (graph[point2_X][8] == "]")
					{
						graph[point2_X][9] = "<";
					}
				}
				if (d2 == 6)
				{
					graph[point2_X + 1][4] = "^";
				}
				if (d2 == 7)
				{
					graph[point2_X][2] = ">";
				}
				graph[point1_X - 3 + d1][17 + lineCount * 2] = "+";
				graph[point2_X - 3 + d2][17 + lineCount * 2] = "+";
				int t = d0;
				int t0 = t / 1000;
				int t1 = (t - t0 * 1000) / 100;
				int t2 = (t - t0 * 1000 - t1 * 100) / 10;
				int t3 = t - t0 * 1000 - t1 * 100 - t2 * 10;
				char s0[2];
				char s1[2];
				char s2[2];
				char s3[2];
				itoa(t0, s0, 10);
				itoa(t1, s1, 10);
				itoa(t2, s2, 10);
				itoa(t3, s3, 10);
				if (d0 <= 9)
				{
					graph[point1_X - 3 + d1][11] = s3;
					graph[point1_X - 3 + d1][12] = "-";
					graph[point1_X - 3 + d1][13] = "-";
					graph[point1_X - 3 + d1][14] = "-";
				}
				if (d0 >= 10 && d0 <= 99)
				{
					graph[point1_X - 3 + d1][11] = s2;
					graph[point1_X - 3 + d1][12] = s3;
					graph[point1_X - 3 + d1][13] = "-";
					graph[point1_X - 3 + d1][14] = "-";
				}
				if (d0 >= 100 && d0 <= 999)
				{
					graph[point1_X - 3 + d1][11] = s1;
					graph[point1_X - 3 + d1][12] = s2;
					graph[point1_X - 3 + d1][13] = s3;
					graph[point1_X - 3 + d1][14] = "-";
				}
				if (d0 >= 1000 && d0 <= 9999)
				{
					graph[point1_X - 3 + d1][11] = s0;
					graph[point1_X - 3 + d1][12] = s1;
					graph[point1_X - 3 + d1][13] = s2;
					graph[point1_X - 3 + d1][14] = s3;
				}
				graph[point1_X - 3 + d1][15] = "-";
				graph[point1_X - 3 + d1][16] = "-";
				graph[point2_X - 3 + d2][11] = "-";
				graph[point2_X - 3 + d2][12] = "-";
				graph[point2_X - 3 + d2][13] = "-";
				graph[point2_X - 3 + d2][14] = "-";
				graph[point2_X - 3 + d2][15] = "-";
				graph[point2_X - 3 + d2][16] = "-";
				degree[point1 - 1][4]++;
				degree[point2 - 1][4]++;
				lineCount++;
				matrix[point1 - 1][point2 - 1] = 0;
			}
		}
	}

	// initialize vector to save the position of bends
	vector<vector<int> > bend(lineNum);
	for (int i = 0; i < lineNum; i++)
	{
		bend[i].resize(4);
	}
	for (int i = 0; i < lineNum; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			bend[i][j] = 0;
		}
	}
	int l1 = 0;
	for (int j = 17; j < 17 + lineNum * 2; j = j + 2)
	{
		int l2 = 0;
		for (int i = 0; i < height; i++)
		{
			if (graph[i][j] == "+")
			{
				bend[l1][l2] = i;
				bend[l1][l2 + 1] = j;
				l2 = l2 + 2;
			}
		}
		l1++;
	}

	// draw the vertical lines
	for (int i = 0; i < lineNum; i++)
	{
		int sou_X = bend[i][0];
		int sou_Y = bend[i][1];
		int des_X = bend[i][2];
		for (int j = sou_X + 1; j < des_X; j++)
		{
			graph[j][sou_Y] = "|";
		}
	}

	// draw the horizontal lines
	for (int i = 0; i < lineNum; i++)
	{
		int sou_X = bend[i][0];
		int sou_Y = bend[i][1];
		int des_X = bend[i][2];
		for (int j = 17; j < sou_Y; j++)
		{
			if (graph[sou_X][j] == "|")
			{
				graph[sou_X][j] = "=";
			}
			if (graph[sou_X][j] == " ")
			{
				graph[sou_X][j] = "-";
			}
			if (graph[des_X][j] == "|")
			{
				graph[des_X][j] = "=";
			}
			if (graph[des_X][j] == " ")
			{
				graph[des_X][j] = "-";
			}
		}
	}

	// remove the unnecessary lines
	for (int i = 0; i < pointNum; i++)
	{
		int pointA = i * 8;
		int pointB = i * 8 + 3;
		int pointC = i * 8 + 6;
		int pointD = i * 8 + 7;
		if (graph[pointA][11] == " ")
		{
			graph[pointA + 2][4] = " ";
			graph[pointA + 1][4] = " ";
			graph[pointA][4] = " ";
			graph[pointA][5] = " ";
			graph[pointA][6] = " ";
			graph[pointA][7] = " ";
			graph[pointA][8] = " ";
			graph[pointA][9] = " ";
			graph[pointA][10] = " ";
		}
		if (graph[pointB][11] == " ")
		{
			if (graph[pointB][5] == "]")
			{
				graph[pointB][6] = " ";
				graph[pointB][7] = " ";
				graph[pointB][8] = " ";
				graph[pointB][9] = " ";
			}
			if (graph[pointB][6] == "]")
			{
				graph[pointB][7] = " ";
				graph[pointB][8] = " ";
				graph[pointB][9] = " ";
			}
			if (graph[pointB][7] == "]")
			{
				graph[pointB][8] = " ";
				graph[pointB][9] = " ";
			}
			if (graph[pointB][8] == "]")
			{
				graph[pointB][9] = " ";
			}
			graph[pointB][10] = " ";
		}
		if (graph[pointC][11] == " ")
		{
			graph[pointC - 2][4] = " ";
			graph[pointC - 1][4] = " ";
			graph[pointC][4] = " ";
			graph[pointC][5] = " ";
			graph[pointC][6] = " ";
			graph[pointC][7] = " ";
			graph[pointC][8] = " ";
			graph[pointC][9] = " ";
			graph[pointC][10] = " ";
		}
		if (graph[pointD][11] == " ")
		{
			graph[pointD - 4][2] = " ";
			graph[pointD - 4][1] = " ";
			graph[pointD - 4][0] = " ";
			graph[pointD - 3][0] = " ";
			graph[pointD - 2][0] = " ";
			graph[pointD - 1][0] = " ";
			graph[pointD][0] = " ";
			graph[pointD][1] = " ";
			graph[pointD][2] = " ";
			graph[pointD][3] = " ";
			graph[pointD][4] = " ";
			graph[pointD][5] = " ";
			graph[pointD][6] = " ";
			graph[pointD][7] = " ";
			graph[pointD][8] = " ";
			graph[pointD][9] = " ";
			graph[pointD][10] = " ";
		}
	}

	// optimize
	vector<int> print(height);
	for (int i = 0; i < height; i++)
	{
		print[i] = 0;
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (graph[i][j] == " " || graph[i][j] == "|")
			{
				print[i]++;
			}
		}
	}

	//output the graph
	for (int i = 0; i < height - 1; i++)
	{
		if (print[i] == width && print[i + 1] == width)
		{
		continue;
		}
		else
		{
		for (int j = 0; j < width; j++)
		{
			cout << graph[i][j];
		}
		cout << endl;
		}
	}

	// dijkstra and output the chart
	cout << "From       To     Distance     Path" << endl;
	vector<int> distance(pointNum); // the distance
	vector<int> preNode(pointNum); // the previous node
	for (int k = 0; k < pointNum; ++k)
	{
		vector<bool> isInS; // whether the node is in the set
		isInS.reserve(0);
		isInS.assign(pointNum, false);
		for (int i = 0; i < pointNum; ++i)
		{
			distance[i] = chart[k][i];
			if (chart[k][i] < INT_MAX)
			{
				preNode[i] = k;
			}
			else
			{
				preNode[i] = -1;
			}
		}
		preNode[k] = -1;
		// greedy algorithm
		isInS[k] = true; // put the first node in the set
		int u = k;
		for (int i = 1; i < pointNum; i++)
		{
			int nextVertex = u;
			int tempDistance = INT_MAX;
			for (int j = 0; j < pointNum; ++j)
			{
				if ((isInS[j] == false) && (distance[j] < tempDistance)) // find the node with the shortest distance that is not in the set
				{
					nextVertex = j;
					tempDistance = distance[j];
				}
			}
			isInS[nextVertex] = true;  // put the node in the set
			u = nextVertex; // the nest node
			// update the distance
			for (int j = 0; j < pointNum; j++)
			{
				if (isInS[j] == false && chart[u][j] < INT_MAX)
				{
					int temp = distance[u] + chart[u][j];
					if (temp < distance[j])
					{
						distance[j] = temp;
						preNode[j] = u;
					}
				}
			}
		}
		for (int j = 0; j < pointNum; ++j)
		{
			int sou = k;
			cout << setw(4) << degree2[sou] << "     ";
			int index = j;
			stack<int> trace;
			while (preNode[index] != -1)
			{
				trace.push(preNode[index]);
				index = preNode[index];
			}
			int des = j;
			cout << setw(4) << degree2[des] << "     ";

			if (distance[j] < INT_MAX)
			{
				cout << setw(8) << distance[j] << "     ";
			}
			else
			{
				cout << "     inf" << "     ";
			}
			int cou = 0;
			while (!trace.empty())
			{
				int node = trace.top();
				cout << degree2[node] << "-->";
				trace.pop();
				cou++;
			}
			if (cou != 0)
			{
				cout << degree2[des] << endl;
			}
			else
			{
				cout << " -- " << endl;
			}
		}
		cout << endl;
	}

	return 0;
}