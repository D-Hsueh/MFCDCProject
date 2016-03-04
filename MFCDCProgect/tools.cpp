#include "stdafx.h"
#include "tools.h"

// 得到maze的方法的实现
int** MazeProject::getMaze()
{
	return maze;
}

//生成随机数的实现
int MazeProject::RanBuild(int start, int end)
{
	return start + (rand()%(end-start+1));
}

// int 转 string 实现
string MazeProject::inttostring(int data)
{
	strstream ss;
	string s;
	ss << data;
	ss >> s;

	return s;
}

//实现向结果日志中输出
bool MazeProject::ResultPrint(string Str)
{
	ofstream resultPrint;
	resultPrint.open(ResultLogLocation,ios::app);
	if (resultPrint.is_open())
	{
		resultPrint << Str.c_str() << endl;
		resultPrint.close();
	}
	else return false;
}

//实现向BUG日志中输出
bool MazeProject::BugPrint(string Str)
{
	ofstream BugPrint;
	BugPrint.open(BugLogLocation, ios::app);
	if (BugPrint.is_open())
	{
		BugPrint << Str.c_str() << endl;
		BugPrint.close();
	}
	else return false;
}

//清空文件内容的实现
bool clearlog()
{
	ofstream logclear;
	logclear.open(ResultLogLocation, ios::trunc);
	logclear.close();
	logclear.open(BugLogLocation, ios::trunc);
	logclear.close();
	return true;
}

//实现Maze的构造
/*
迷宫实现思路解释：
将迷宫初始化为一个二维数组，初始状态时该迷宫为一个个独立的小方格，而创建随机迷宫的方法就是先采用等价类的思想
将两两格子联通，最后在二维数组中将联通的格子之间的墙“推倒”即可。
*/
MazeProject::MazeProject(int length, int width, CWnd *pWnd)
{
	//墙与空白都占用各自的位置方便渲染，所以最终的数组是2n+1的长度
	this->pWnd = pWnd;
	maze_length = length;
	maze_width = width;

	size_length = 2*length+1;
	size_width = 2*width+1;

	maze = new int*[size_width];
	for (int i = 0;i < size_width;i++)
	{
		maze[i] = new int[size_length];
	}


	for (int i = 0;i < size_width;i++)
	{
		for (int j = 0;j < size_length;j++)
		{
			//如果是空白那么就设为未经过的路
			if (i % 2 == 1 && j % 2 == 1)
			{
				maze[i][j] = Load_NotArrive;
			}
			//如果是墙就设为墙
			else
			{
				maze[i][j] = Wall;
			}
		}
	}
	maze[1][0] = Start_Location;
	maze[size_width-2][size_length-1] = End_Location;

}
MazeProject::~MazeProject()
{
	for (int i = 0;i < size_width;i++)
	{
		delete[]maze[i];
	}
	delete []maze;
	/*
	delete &maze_length;
	delete &maze_width;
	delete &size_length;
	delete &size_width;
	*/
}

void MazeProject::CreatPaint()
{
	//pWnd= GetDlgItem(Maze_Show);
	//CRect rect;
	pWnd->GetClientRect(&rect);


	pdc_Wall = pWnd->GetDC();
	pdc_Load = pWnd->GetDC();
	pdc_Load_True = pWnd->GetDC();
	pdc_Load_False = pWnd->GetDC();
	pdc_Start = pWnd->GetDC();
	pdc_End = pWnd->GetDC();
	pdc_Load_Not_Sure = pWnd->GetDC();

	int Wall_Color = RGB(0, 0, 0);
	int Load_Color = RGB(255, 255, 255);
	int Load_True_Color = RGB(0, 255, 0);
	int Load_False_Color = RGB(255, 0, 0);
	int Start_Color = RGB(0, 0, 255);
	int End_Color = RGB(160, 32, 240);
	int Load_Not_Sure_Color = RGB(255, 69, 0);

	CBrush Brush_Wall(Wall_Color);
	CBrush Brush_Load(Load_Color);
	CBrush Brush_Load_Ture(Load_True_Color);
	CBrush Brush_Load_False(Load_False_Color);
	CBrush Brush_Start(Start_Color);
	CBrush Brush_End(End_Color);
	CBrush Brush_Load_Not_Sure(Load_Not_Sure_Color);

	CPen pen_Wall(PS_SOLID, 1, Wall_Color);
	CPen Pen_Load(PS_SOLID, 1, Load_Color);
	CPen Pen_Load_True(PS_SOLID, 1, Load_True_Color);
	CPen Pen_Load_False(PS_SOLID, 1, Load_False_Color);
	CPen Pen_Start(PS_SOLID, 1, Start_Color);
	CPen Pen_End(PS_SOLID, 1, End_Color);
	CPen Pen_Load_Not_Sure(PS_SOLID, 1, Load_Not_Sure_Color);

	pdc_Wall->SelectObject(pen_Wall);
	pdc_Load->SelectObject(Pen_Load);
	pdc_Load_True->SelectObject(Pen_Load_True);
	pdc_Load_False->SelectObject(Pen_Load_False);
	pdc_Start->SelectObject(Pen_Start);
	pdc_End->SelectObject(Pen_End);
	pdc_Load_Not_Sure->SelectObject(Pen_Load_Not_Sure);

	pdc_Wall->SelectObject(&Brush_Wall);
	pdc_Load->SelectObject(&Brush_Load);
	pdc_Load_True->SelectObject(&Brush_Load_Ture);
	pdc_Load_False->SelectObject(&Brush_Load_False);
	pdc_Start->SelectObject(&Brush_Start);
	pdc_End->SelectObject(&Brush_End);
	pdc_Load_Not_Sure->SelectObject(&Brush_Load_Not_Sure);
}






