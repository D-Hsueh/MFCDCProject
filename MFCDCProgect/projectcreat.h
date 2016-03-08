#pragma once

#include "stdafx.h"
#include "list.cpp"
using namespace std;

//全局变量声明 （宏定义）
#define Wall 1
#define Load_NotArrive 0
#define Start_Location 5
#define End_Location 6
#define Load_NotSure  2
#define Load_ArriveButFalse  3
#define Wall_BeDestroy  8
#define Load_ArriveAndTrue  9
#define ResultLogLocation "E:\\VisualStudioWorkSpace\\MazeWriteByXueDong\\MazeWriteByXueDong\\ResultLog.txt"
#define BugLogLocation  "E:\\VisualStudioWorkSpace\\MazeWriteByXueDong\\MazeWriteByXueDong\\BugLog.txt"


//实现框架

class MazeProject
{
	
private:
	int **maze;
	int maze_length;
	int maze_width;
	int size_length;
	int size_width;

public:
	//具体方法
	MazeProject(int length, int width, CWnd *pWnd);
	~MazeProject();
	bool MazeCreat();
	bool PathFind(CWnd *pWnd);
	//bool LoadShow(string data);

	//画迷宫的方法
	void DrawInCreat();
	void DrawInCreat(int x, int y);
	void DrawInFind();
	void DrawInFind(int x,int y);

	// 得到maze的方法
	int** getMaze();
	// 得到maze大小的方法
	int get_length() { return size_length; };
	int get_width() { return size_width; };
	
	//生成随机数的方法
	int RanBuild(int start, int end);

	//获取系统时间的方法
	//int**  GetTime();

	//int转string的方法
	string inttostring(int data);
	
	//输出结果以及BUG方法
	bool ResultPrint(string Str);
	bool BugPrint(string Str);

	//在此初始化画板
	CWnd *pWnd;
	CRect rect;
	CDC *pdc_Wall;
	CDC *pdc_Load;
	CDC *pdc_Load_True;
	CDC *pdc_Load_False;
	CDC *pdc_Start;
	CDC *pdc_End;
	CDC *pdc_Load_Not_Sure;
	void CreatPaint();
};
//清空文件内容
bool clearlog();
