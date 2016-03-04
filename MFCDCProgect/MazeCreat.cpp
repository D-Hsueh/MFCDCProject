#include "stdafx.h"
#include "MazeCreat.h"


//��CPP�ļ���Ҫʵ����������õȼ���ķ�������һ���Թ�
/*
�õ������ݽṹ��һά���飬��ά���飬��ջ,����
*/
bool MazeProject::MazeCreat()
{
	//�������������
	srand(unsigned(time(0)));

	//��������
	pWnd->GetClientRect(&rect);

	//��������
	pdc_Wall = pWnd->GetDC();
	pdc_Load = pWnd->GetDC();
	pdc_Start = pWnd->GetDC();
	pdc_End = pWnd->GetDC();

	int Wall_Color = RGB(0, 0, 0);
	int Load_Color = RGB(255, 255, 255);
	int Start_Color = RGB(0, 0, 255);
	int End_Color = RGB(160, 32, 240);

	CBrush Brush_Wall(Wall_Color);
	CBrush Brush_Load(Load_Color);
	CBrush Brush_Start(Start_Color);
	CBrush Brush_End(End_Color);

	CPen pen_Wall(PS_SOLID, 1, Wall_Color);
	CPen Pen_Load(PS_SOLID, 1, Load_Color);
	CPen Pen_Start(PS_SOLID, 1, Start_Color);
	CPen Pen_End(PS_SOLID, 1, End_Color);

	pdc_Wall->SelectObject(pen_Wall);
	pdc_Load->SelectObject(Pen_Load);
	pdc_Start->SelectObject(Pen_Start);
	pdc_End->SelectObject(Pen_End);

	pdc_Wall->SelectObject(&Brush_Wall);
	pdc_Load->SelectObject(&Brush_Load);
	pdc_Start->SelectObject(&Brush_Start);
	pdc_End->SelectObject(&Brush_End);

	//���ȼ�����ȼ���ĸ���
	int MaxNum = maze_length*maze_width;
	int *p=new int[MaxNum];
	for (int i = 1;i <= MaxNum;i++)
	{
		p[i] = i;
	}
	//�����е�ǽ���ȥ
	list *l = new list();

	for (int i = 1;i < MaxNum;i++)
	{
		if (i%maze_length != 0)
		{
			l->add(i, i + 1);
		}
	}

	for (int i = 1;i < MaxNum - maze_length;i++)
	{
		l->add(i, i + maze_length);
	}
	while (l->size > 0)
	{
		int r = l->size;
		int ran = RanBuild(1, r);
		BugPrint(inttostring(ran));
		Node *temp = l->find(ran);
		int x = temp->first;
		int y = temp->last;
		if (p[x] != p[y])
		{
			int tempnum = p[x];
			for (int i = 1;i < MaxNum;i++)
			{
				if (p[i] == tempnum)
				{
					p[i] = p[y];
				}
			}

			//���Թ����Ƶ�ǽ
			int lo_x;
			int lo_y;
			if (x%maze_length == 0)
			{
				lo_y = maze_length;
				lo_x = x / maze_length;
			}
			else
			{
				lo_y = x%maze_length;
				lo_x = x / maze_length + 1;
			}
			lo_y = 1 + 2 * (lo_y - 1);
			lo_x = 1 + 2 * (lo_x - 1);

			if (y - x == 1)
			{
				maze[lo_x][lo_y + 1] = 0;
			}
			else if (y - x == maze_length)
			{
				maze[lo_x + 1][lo_y] = 0;
			}
			else
			{
				BugPrint("Error:Destory the wall is fail by MazeCreat");
			}
			l->del(ran);
			DrawInCreat();
			//Sleep(50);
		}
		else
		{
			l->del(ran);
			//DrawInCreat(pWnd);
		}
	}
		
	return true;
}

void MazeProject::DrawInCreat()
{
	//�ڴ���ʾ�������Թ�
	/*
	CRect rect;
	pWnd->GetClientRect(&rect);

	//��������
	CDC *pdc_Wall = pWnd->GetDC();
	CDC *pdc_Load = pWnd->GetDC();
	CDC *pdc_Start = pWnd->GetDC();
	CDC *pdc_End = pWnd->GetDC();
	
	int Wall_Color = RGB(0, 0, 0);
	int Load_Color = RGB(255, 255, 255);
	int Start_Color = RGB(0, 0, 255);
	int End_Color = RGB(160, 32, 240);

	CBrush Brush_Wall(Wall_Color);
	CBrush Brush_Load(Load_Color);
	CBrush Brush_Start(Start_Color);
	CBrush Brush_End(End_Color);

	CPen pen_Wall(PS_SOLID, 1, Wall_Color);
	CPen Pen_Load(PS_SOLID, 1, Load_Color);
	CPen Pen_Start(PS_SOLID, 1, Start_Color);
	CPen Pen_End(PS_SOLID, 1, End_Color);

	pdc_Wall->SelectObject(pen_Wall);
	pdc_Load->SelectObject(Pen_Load);
	pdc_Start->SelectObject(Pen_Start);
	pdc_End->SelectObject(Pen_End);

	pdc_Wall->SelectObject(&Brush_Wall);
	pdc_Load->SelectObject(&Brush_Load);
	pdc_Start->SelectObject(&Brush_Start);
	pdc_End->SelectObject(&Brush_End);
	*/
	//int **maze = maze;
	int length = size_length;
	int width = size_width;

	//����߳�
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
			else if (maze[i][j] == Start_Location)
			{
				pdc_Start->Rectangle(&recttemp);
			}
			else if (maze[i][j] == End_Location)
			{
				pdc_End->Rectangle(&recttemp);
			}
		}
	}
	//Sleep(50);

}

//��һ�ε�˼·
/*
int **p;
//�ִ�ĵȼ���ĸ���
int TheNum = maze_length*maze_width;
int MaxNum = TheNum;

//��ʼ���ȼ���
for (int i = 1;i <= TheNum;i++)
{
p[i][0] = i;
//��ѡ���˼���
p[i][1] = 0;
}

//�Ըõȼ�����в��������õȼ�����û��δ��ѡ�еĸ��ӵ�ʱ��ֹͣ

bool NotDone = true;
while (NotDone)
{
int ran = RanBuild(1, TheNum);
int North = -1;
int South = -1;
int West = -1;
int East = -1;
int count = 0;

//��ѡ�е�һ���������ܽ��в���,������������ֵ��������������-1
if (ran%maze_width + 1 < maze_length && ran%maze_width + 1 != 1)
{
East = ran + 1;
if (p[East][0] != p[ran][0])
{
count++;
}
else {
East = -1;
}
}
if (ran%maze_width - 1 > 0)
{
West = ran - 1;
if (p[West][0] != p[ran][0])
{
count++;
}
else {
West = -1;
}
}
if (ran - maze_length > 0)
{
North = ran - maze_length;
if (p[North][0] != p[ran][0])
{
count++;
}
else {
North = -1;
}
}
if (ran + maze_length < MaxNum)
{
South = ran + maze_length;
if (p[South][0] != p[ran][0])
{
count++;
}
else {
South = -1;
}
}

//���ѡ�����ܿ�ѡ���һ��
int ranf = RanBuild(1, count);
int WeChoose = -1;
//���û���򲻽��н������Ĳ���
if (ranf == 0)
{
continue;
}
else if (ranf == 1)
{
if (North != -1)
WeChoose = North;
else if (East != -1)
WeChoose = East;
else if (South != -1)
WeChoose = South;
else if (West != -1)
WeChoose = West;
}
else if (ranf == 2)
{
if (East != -1)
WeChoose = East;
else if (South != -1)
WeChoose = South;
else if (West != -1)
WeChoose = West;
else if (North != -1)
WeChoose = North;
}
else if (ranf == 3)
{
if (South != -1)
WeChoose = South;
else if (West != -1)
WeChoose = West;
else if (North != -1)
WeChoose = North;
else if (East != -1)
WeChoose = East;
}
else if (ranf == 4)
{
if (West != -1)
WeChoose = West;
else if (North != -1)
WeChoose = North;
else if (East != -1)
WeChoose = East;
else if (South != -1)
WeChoose = South;
}

//���û�и�ֵ�ɹ�����ô������󱨸�
if (WeChoose == -1)
{
BugPrint("Error : In the Wechoose By the MazeCreat.cpp");
}
else {
//����ͬһ�ȼ���
int temp = p[WeChoose][0];
for (int i = 1;i <= MaxNum;i++)
{
if (p[i][0] == temp)
p[i][0] == p[ran][0];
}
p[ran][1]++;
p[WeChoose][1]++;
}



}
*/