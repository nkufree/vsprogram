#include<iostream>
#include<ctime>
#include<random>
#include<queue>
#include<cmath>
#include<stack>
#include<vector>
using namespace std;

#define VCOUNT 50 //顶点个数n
#define TIMECOUNT 20 //图G的个数b
#define MAXDIS 3 //可以存在边的距离
#define MAXDIS2 9 //距离的平方
#define STARTV 2 //起始的顶点s
#define ENDV 46 //终止的顶点t
#define PAI 3.1415926 //常数pai
#define K 100 //改变路径的代价

struct Point{
	float x;
	float y;
};

struct Graph {
	Point vert[VCOUNT]; //图G_i的顶点坐标
	bool edge[VCOUNT][VCOUNT]; //图G_i的边
};

struct HelpGraph {
	bool edge[VCOUNT][VCOUNT]; //图G(i,j)的边
};

Graph graphs[TIMECOUNT] = {}; //G_i
HelpGraph helpGraphs[TIMECOUNT][TIMECOUNT] = {}; //G(i,j)
int helpEdges[TIMECOUNT][TIMECOUNT] = {}; //l(i,j)
int OPT[TIMECOUNT] = {}; //子问题划分
int lastChange[TIMECOUNT] = {};
stack<int> changePoint;
vector<stack<int>> path;

//模拟第i个图
void simulateGraph(int i)
{
	/*
	default_random_engine e(time(0)+i);
	uniform_real_distribution<float> u(-MOVE, MOVE);
	for (int j = 0; j < VCOUNT; j++)
	{
		graphs[i].vert[j].x = graphs[i - 1].vert[j].x + u(e);
		graphs[i].vert[j].y = graphs[i - 1].vert[j].y + u(e);
	}*/
	
	default_random_engine e1(time(0) + i);
	uniform_real_distribution<float> u1(-MAXDIS, MAXDIS);
	default_random_engine e2(time(0) + i);
	uniform_real_distribution<float> u2(-PAI, PAI);
	graphs[i].vert[0].x = u1(e1) * u2(e2);
	graphs[i].vert[0].y = u1(e1) * u2(e2);
	float theta = u2(e2);
	for (int j = 1; j < VCOUNT; j++)
	{
		graphs[i].vert[j].x = graphs[i].vert[j - 1].x + u1(e1) * cos(theta);
		graphs[i].vert[j].y = graphs[i].vert[j - 1].y + u1(e1) * sin(theta);
	}

}

//计算第i个图中的边
void calcEdge(int i)
{
	for (int j = 0; j < VCOUNT; j++)
	{
		for (int k = 0; k < VCOUNT; k++)
		{
			float dx = graphs[i].vert[j].x - graphs[i].vert[k].x;
			float dy = graphs[i].vert[j].y - graphs[i].vert[k].y;
			float tempDis2 = dx * dx + dy * dy;
			if (tempDis2 < MAXDIS2 && j != k)
				graphs[i].edge[j][k] = 1;
		}
	}
}

//初始化图
void initGraph()
{
	/*
	for (int i = 0; i < VCOUNT; i++)
	{
		graphs[0].vert[i].x = i % INITSQUARE;
		graphs[0].vert[i].y = i / INITSQUARE;
	}*/
	for (int i = 0; i < TIMECOUNT; i++)
		simulateGraph(i);
	for (int i = 0; i < TIMECOUNT; i++)
		calcEdge(i);
}

//计算G(i,j)
void calcHelpGraphs()
{
	for (int i = 0; i < TIMECOUNT; i++)
	{
		for (int j = 0; j < VCOUNT; j++)
			for (int k = 0; k < VCOUNT; k++)
				helpGraphs[i][i].edge[j][k] = graphs[i].edge[j][k];
				
		for (int j = i + 1; j < TIMECOUNT; j++)
		{
			for (int k = 0; k < VCOUNT; k++)
			{
				for (int h = 0; h < VCOUNT; h++)
				{
					if (helpGraphs[i][j - 1].edge[k][h] && graphs[j].edge[k][h])
						helpGraphs[i][j].edge[k][h] = 1;
				}
			}
		}
	}
}

int graphBFS(int index, int v1, int v2)
{
	queue<int> verts;//记录需要遍历的顶点
	bool isVisited[VCOUNT] = {};
	verts.push(v1);
	verts.push(-1);
	int deep = 1;
	isVisited[v1] = true;
	while (verts.size() != 0)
	{
		int temp = verts.front();
		if (temp == -1)
		{
			deep++;
			verts.push(-1);
			verts.pop();
			temp = verts.front();
			if (temp == -1)
				break;
		}
		verts.pop();
		for (int i = 0; i < VCOUNT; i++)
		{
			if (graphs[index].edge[temp][i] && (!isVisited[i]))
			{
				if (i == v2)
					return deep;
				else
				{
					verts.push(i);
					isVisited[i] = true;
				}
			}
		}
	}
	cout << "这两个顶点不相连 在图G(" << index << ")" << endl;
	return -1;
}

void calcHelpEdge(int indexi,int indexj,int v1,int v2)
{
	queue<int> verts;//记录需要遍历的顶点
	bool isVisited[VCOUNT] = {};
	verts.push(v1);
	verts.push(-1);
	int deep = 1;
	isVisited[v1] = true;
	while (verts.size() != 0)
	{
		int temp = verts.front();
		if (temp == -1)
		{
			deep++;
			verts.push(-1);
			verts.pop();
			temp = verts.front();
			if (temp == -1)
				break;
		}
		verts.pop();
		for (int i = 0; i < VCOUNT; i++)
		{
			if (helpGraphs[indexi][indexj].edge[temp][i] && (!isVisited[i]))
			{
				if (i == v2)
				{
					helpEdges[indexi][indexj] = deep;
					return;
				}
				else
				{
					verts.push(i);
					isVisited[temp] = true;
				}
				
			}
		}
	}
	cout << "这两个顶点不相连 在图G(" << indexi << "," << indexj << ")" << endl;
	return;
}

//计算l(i,j)，起始点为v1，终止点为v2
void calcHelpEdges(int v1, int v2)
{
	for (int i = 0; i < TIMECOUNT; i++)
	{
		for (int j = i; j < TIMECOUNT; j++)
		{
			calcHelpEdge(i, j, v1, v2);
		}
	}
}

//动态规划求解
void DynamicProgram()
{
	OPT[0] = helpEdges[0][0];
	lastChange[0] = 0;
	for (int i = 1; i < TIMECOUNT; i++)
	{
		int minLength = 9999999;
		int index = -1;
		for (int j = 1; j < i; j++)
		{
			int temp = OPT[j] + (i - j) * helpEdges[j + 1][i] + K;
			if (temp < minLength)
			{
				minLength = temp;
				index = j;
			}
		}
		if (minLength < (i + 1) * helpEdges[0][i])
		{
			lastChange[i] = index;
		}
		else
		{
			minLength = (i + 1) * helpEdges[0][i];
			lastChange[i] = 0;
		}
		OPT[i] = minLength;
	}
}

//DFS算法
bool helpDFS(int i, int j,int curr, int deep,bool* isVisited)
{
	if (deep > helpEdges[i][j])
		return false;
	if (curr == ENDV)
	{
		path.front().push(ENDV);
		return true;
	}
	for (int k = 0; k < VCOUNT; k++)
	{
		if (helpGraphs[i][j].edge[curr][k] && (!isVisited[k]))
		{
			isVisited[k] = true;
			if (helpDFS(i, j, k, deep + 1, isVisited))
			{
				path.front().push(curr);
				return true;
			}
			isVisited[k] = false;
			
		}
	}
	return false;
}

void helpGraphDFS(int i,int j)
{
	stack<int> temp;
	path.insert(path.begin(), temp);
	bool isVisited[VCOUNT] = {};
	isVisited[STARTV] = true;
	helpDFS(i, j, STARTV, 0, isVisited);
}

//寻找改变点
void findChanges()
{
	int curr = TIMECOUNT - 1;
	changePoint.push(curr);
	while (lastChange[curr] != 0)
	{
		changePoint.push(lastChange[curr]);
		curr = lastChange[curr];
	}
	changePoint.push(-1);
}

//求解每条路径
void generatePath()
{
	stack<int> help(changePoint);
	int currEnd = TIMECOUNT - 1;
	int currStart = -1;
	while (help.size() != 1)
	{
		currStart = help.top() + 1;
		help.pop();
		currEnd = help.top();
		helpGraphDFS(currStart, currEnd);
	}
}

//检验答案是否正确
void checkAnswer()
{
	int sum = 0;
	for (int i = 0; i < path.size(); i++)
	{
		int temp = changePoint.top() + 1;
		cout << "起止区间为" << temp << "->";
		changePoint.pop();
		cout << changePoint.top() << "，路径长度为" << helpEdges[temp][changePoint.top()] << endl;
		sum += helpEdges[temp][changePoint.top()] * (changePoint.top() - temp + 1);
		while (path[i].size() != 1)
		{
			cout << path[i].top() << "->";
			path[i].pop();
		}
		cout << path[i].top() << endl;
	}
	sum += (path.size() - 1) * K;
	cout << "检验得到的路径长度为" << sum << endl;
}

int main()
{
	initGraph();
	for (int i = 0; i < TIMECOUNT; i++)
	{
		for (int j = 0; j < VCOUNT; j++)
		{
			cout << graphs[i].vert[j].x << " " << graphs[i].vert[j].y << endl;
		}
		cout << endl;
	}
	calcHelpGraphs();
	calcHelpEdges(STARTV, ENDV);
	DynamicProgram();
	findChanges();
	generatePath();
	cout << "最小代价为" << OPT[TIMECOUNT - 1] << endl;
	checkAnswer();
	
	return 0;
} 