#pragma once

#include "stdafx.h"
#include "list.cpp"
using namespace std;

//ȫ�ֱ������� ���궨�壩
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


//ʵ�ֿ��

class MazeProject
{
	
private:
	int **maze;
	int maze_length;
	int maze_width;
	int size_length;
	int size_width;

public:
	//���巽��
	MazeProject(int length, int width, CWnd *pWnd);
	~MazeProject();
	bool MazeCreat();
	bool PathFind(CWnd *pWnd);
	//bool LoadShow(string data);

	//���Թ��ķ���
	void DrawInCreat();
	void DrawInCreat(int x, int y);
	void DrawInFind();
	void DrawInFind(int x,int y);

	// �õ�maze�ķ���
	int** getMaze();
	// �õ�maze��С�ķ���
	int get_length() { return size_length; };
	int get_width() { return size_width; };
	
	//����������ķ���
	int RanBuild(int start, int end);

	//��ȡϵͳʱ��ķ���
	//int**  GetTime();

	//intתstring�ķ���
	string inttostring(int data);
	
	//�������Լ�BUG����
	bool ResultPrint(string Str);
	bool BugPrint(string Str);

	//�ڴ˳�ʼ������
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
//����ļ�����
bool clearlog();
