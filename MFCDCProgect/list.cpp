//前两个为自写的链表
#include "stdafx.h"

class Node
{
public :
	int first;
	int last;
	Node *next;
};

class list
{
public :
	int size;
	Node *head;

	list()
	{
		size = 0;
	}

	void add(int x, int y)
	{
		Node *temp=new Node();
		temp->first = x;
		temp->last = y;
		if (!head)
		{
			head = temp;
			size++;
		}
		else
		{
			Node *pso = head;
			while (pso->next)
			{
				pso = pso->next;
			}
			pso->next = temp;
			size++;
		}
	}

	Node* find(int num)
	{
		Node *pso = head;
		while (--num>0)
		{
			pso = pso->next;
		}
		return pso;
	}

	void del(int data)
	{
		if (data == 1)
		{
			head = head->next;
			size--;
		}
		else
		{
			Node *pso = head;
			Node *temp = pso;
			while (--data>0)
			{
				temp = pso;
				pso = pso->next;
			}
				temp->next = pso->next;
			size--;
		}
	}
};

//构建走迷宫时的位置

class loc
{
public:
	int x;
	int y;
};
