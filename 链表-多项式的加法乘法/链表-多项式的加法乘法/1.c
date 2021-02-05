# define _CRT_SECURE_NO_WARNINGS 1
# pragma warning(disable:6031)
# include <stdio.h>
# include <stdlib.h>

//多项式节点
struct PolyNode
{
	int coef;//系数
	int expon;//指数
	struct PolyNode* Next;
};
typedef struct PolyNode* Polynomial;
//链表的生成函数，需要传入系数，指数，还要修改链表，需要链表的尾指针
void Attach(int coef, int expon, Polynomial* rear)
{
	//申请空节点
	Polynomial P;
	P = (Polynomial)malloc(sizeof(struct PolyNode));
	if (P)
	{
		P->coef = coef;
		P->expon = expon;
		P->Next = NULL;
		(*rear)->Next = P;
		(*rear) = P;
	}
}
Polynomial ReadPloy()
{
	//先申请一个头节点来接收输入进来的字符
	int num = 0; //num表示输入的多项式的总项数；
	int coef = 0; 
	int expon = 0; 
	Polynomial L, rear;
	L = (Polynomial)malloc(sizeof(struct PolyNode));
	if (L)
	{
		rear = L;
		rear->Next = NULL;
		scanf("%d", &num);
		while (num--)
		{
			scanf("%d %d", &coef, &expon);
			Attach(coef, expon, &rear);
		}
		Polynomial tmp;
		tmp = L->Next;
		L->Next = NULL;
		free(L);
		L = tmp;
		return L;
	}
}
//系数比较函数
int Compare(int x, int y)
{
	if (x > y)
		return 1;
	else if (x < y)
		return -1;
	else
		return 0;
}
Polynomial PolyAdd(Polynomial p1, Polynomial p2)
{
	//新建一个链表来存储相加后的结果
	Polynomial front, rear, tmp;
	int sum = 0;
	front = (Polynomial)malloc(sizeof(struct PolyNode));
	if (front)
	{
		rear = front;
		while (p1 && p2)
		{
			switch (Compare(p1->expon, p2->expon))
			{
			case 1://p1的指数大，将p1节点插入到结果链表中，p1指针后移动
				Attach(p1->coef, p1->expon, &rear);
				p1 = p1->Next;
				break;
			case -1://p2的指数大，将p2节点插入到结果链表中，p2指针后移动
				Attach(p2->coef, p2->expon, &rear);
				p2 = p2->Next;
				break;
			case 0://指数相同，系数相加
				sum = p1->coef + p2->coef;
				//如果系数不等于0
				if (sum)
					Attach(sum, p2->expon, &rear);
				p1 = p1->Next;
				p2 = p2->Next;
				break;
			}
		}
		//跳出循环是仍然有一个多项式没有遍历完
		//如果是p1
		for (; p1; p1 = p1->Next)
		{
			Attach(p1->coef, p1->expon, &rear);
		}
		//如果是p2
		for (; p2; p2 = p2->Next)
		{
			Attach(p2->coef, p2->expon, &rear);
		}
		//处理完毕，释放最开始申请的空的头节点
		rear->Next = NULL;
		tmp = front->Next;
		front->Next = NULL;
		free(front);
		front = tmp;
		return front;
	}
}
//实现打印运算结果
void PolyPrint(Polynomial L)
{
	while (L)
	{
		printf("%d %d", L->coef, L->expon);
		printf("  ");
		L = L->Next;
	}
}
//多项式的加法main函数框架
int main()
{
	Polynomial p1, p2,L1;
	//读入字符串1，存入到链表中,并返回链表头指针，输入格式，4 23 45 23 第一个代表一共的个数   先系数再指数
	p1 = ReadPloy();
	//输入字符串2
	p2 = ReadPloy();
	//进行多项式的加法运算
	L1 = PolyAdd(p1, p2);
	//打印结果1；
	PolyPrint(L1);
	//进行多项式的乘法运算
	//L2 = PolyMult(p1, p2);
	////打印结果2；
	//PolyPrint(L2);
	return 0;
}