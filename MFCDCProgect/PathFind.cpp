#include "stdafx.h"
#include "PathFind.h"

bool MazeProject::PathFind(CWnd *pWnd)
{
	//重置画笔

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
	int Load_Not_Sure_Color = RGB(0, 255, 255);

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

	//定义起点坐标和终点坐标
	int StartLocationX = 1;
	int StartLocationY = 0;
	int EndLocationX = size_width - 2;
	int EndLocationY = size_length - 1;

	//定义路径栈
	stack<loc*> load;

	//将起点坐标压入栈

	loc *temp = new loc();
	temp->x = StartLocationX;
	temp->y = StartLocationY+1;
	load.push(temp);

	//定义当前路标，进入循环求解

	int NowLocationX = StartLocationX;
	int NowLocationY = StartLocationY+1;

	while (1)
	{
		if (maze[NowLocationX][NowLocationY + 1] == End_Location)
		{
			maze[NowLocationX][NowLocationY] = Load_NotSure;
			break;
		}
		
		//找到当前位置的四个点	
		int	SouthX = NowLocationX + 1;
		int	SouthY = NowLocationY;
		
		
		int	NorthX = NowLocationX - 1;
		int	NorthY = NowLocationY;
		
		
		int	EastX = NowLocationX;
		int	EastY = NowLocationY + 1;
		
		
		int	WestX = NowLocationX;
		int	WestY = NowLocationY - 1;
		

		//按照东南西北的顺序进行寻找

		if (maze[EastX][EastY] == Load_NotArrive)
		{
			maze[NowLocationX][NowLocationY] = Load_NotSure;
			NowLocationX = EastX;
			NowLocationY = EastY;
			loc *step = new loc();
			step->x = NowLocationX;
			step->y = NowLocationY;
			load.push(step);
		}
		
		else if (maze[SouthX][SouthY] == Load_NotArrive)
		{
			maze[NowLocationX][NowLocationY] = Load_NotSure;
			NowLocationX = SouthX;
			NowLocationY = SouthY;
			loc *step = new loc();
			step->x = NowLocationX;
			step->y = NowLocationY;
			load.push(step);
		}
		
		else if (maze[WestX][WestY] == Load_NotArrive)
		{
			maze[NowLocationX][NowLocationY] = Load_NotSure;
			NowLocationX = WestX;
			NowLocationY = WestY;
			loc *step = new loc();
			step->x = NowLocationX;
			step->y = NowLocationY;
			load.push(step);
		}
		
		else if (maze[NorthX][NorthY] == Load_NotArrive)
		{
			maze[NowLocationX][NowLocationY] = Load_NotSure;
			NowLocationX = NorthX;
			NowLocationY = NorthY;
			loc *step = new loc();
			step->x = NowLocationX;
			step->y = NowLocationY;
			load.push(step);
		}
		
		else
		{
			maze[NowLocationX][NowLocationY] = Load_ArriveButFalse;
			load.pop();
			loc *step = new loc();
			step = load.top();
			NowLocationX = step->x;
			NowLocationY = step->y;
		}
		
		DrawInFind(pWnd);
	
	}
	//查询结束，对路径进行重置
	stack<loc*> FinalLoad;

	while (!load.empty())
	{
		FinalLoad.push(load.top());
		load.pop();
	}
	//修改正确路径
	while (!FinalLoad.empty())
	{
		loc *temp = new loc();
		temp = FinalLoad.top();
		int tempX = temp->x;
		int tempY = temp->y;
		maze[tempX][tempY] = Load_ArriveAndTrue;
		DrawInFind(pWnd);
		FinalLoad.pop();
	}
	return true;
}

void MazeProject::DrawInFind(CWnd *pWnd)
{
	//画出路径
	/*
	CRect rect;
	pWnd->GetClientRect(&rect);


	CDC *pdc_Wall = pWnd->GetDC();
	CDC *pdc_Load = pWnd->GetDC();
	CDC *pdc_Load_True = pWnd->GetDC();
	CDC *pdc_Load_False = pWnd->GetDC();
	CDC *pdc_Start = pWnd->GetDC();
	CDC *pdc_End = pWnd->GetDC();
	CDC *pdc_Load_Not_Sure = pWnd->GetDC();

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

	*/
	//UpdateData(TRUE);

	//int **maze = m->getMaze();
	int length = size_length;
	int width = size_width;

	//计算边长
	int bianchang = rect.Width() / width;
	int chushiweizhi = (rect.Width() - bianchang*width) / 2;


	for (int i = 0;i < width;i++)
	{
		for (int j = 0;j < length;j++)
		{
			CRect recttemp(chushiweizhi + j * bianchang, chushiweizhi + i * bianchang, chushiweizhi + j * bianchang + bianchang, chushiweizhi + i * bianchang + bianchang);
			if (maze[i][j] == Load_NotArrive)
			{
				pdc_Load->Rectangle(&recttemp);
			}
			else if (maze[i][j] == Wall)
			{
				pdc_Wall->Rectangle(&recttemp);
			}
			else if (maze[i][j] == Load_ArriveAndTrue)
			{
				pdc_Load_True->Rectangle(&recttemp);
			}
			else if (maze[i][j] == Load_ArriveButFalse)
			{
				pdc_Load_False->Rectangle(&recttemp);
			}
			else if (maze[i][j] == Start_Location)
			{
				pdc_Start->Rectangle(&recttemp);
			}
			else if (maze[i][j] == End_Location)
			{
				pdc_End->Rectangle(&recttemp);
			}
			else if (maze[i][j] == Load_NotSure)
			{
				pdc_Load_Not_Sure->Rectangle(&recttemp);
			}
		}
	}
	Sleep(10);
}