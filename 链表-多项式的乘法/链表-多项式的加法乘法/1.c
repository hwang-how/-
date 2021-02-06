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
//尾插法链表的生成函数，需要传入系数，指数，还要修改链表，需要链表的尾指针
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

// 乘法的实现
Polynomial PolyMult(Polynomial p1, Polynomial p2)
{
	//大致实现思路：t1,t2分别指向p1和p2链表，初始时用t1的第一项乘t2的每一项构造初始的结果链表
	//然后t1后移再乘上t2的每一项，算出指数和系数，这里的关键是插入操作，设置一个tmp指针用来遍历当前的结果链表
	//找到合适的位置插入
	//验证p1,p2的合法性
	if (!p1 || !p2)
		return NULL;
	Polynomial front, rear, tmp,pretmp,t1,t2;
	int sum = 0;
	int c = 0;//记录系数相乘的结果
	int e = 0;//记录指数相乘的结果
	t1 = p1;
	t2 = p2;
	front = (Polynomial)malloc(sizeof(struct PolyNode));
	if (front)
	{
		rear = front;
		//实现初始结果表
		while (t2)
		{
			Attach(t1->coef * t2->coef, t1->expon + t2->expon, &rear);
			t2 = t2->Next;
		}
		t1 = t1->Next;
		while (t1)
		{
			t2 = p2;
			while (t2)
			{
				tmp = front->Next;//tmp用来遍历生成链表，以寻找合适的插入位置
				pretmp = front;
				c = t1->coef * t2->coef;
				e = t1->expon + t2->expon;
				while (tmp)
				{
					//如果当前乘积的结果指数是比tmp的指数大，则插入tmp的前面，那么需要一个指针来记录tmp之前的位置
					if (e > tmp->expon)
					{
						Polynomial S = (Polynomial)malloc(sizeof(struct PolyNode));
						if (S)
						{
							S->coef = c;
							S->expon = e;
							S->Next = tmp;
							pretmp->Next = S;
						}
						break;
					}
					//如果当前乘积的结果指数比tmp的指数小，则tmp后移，继续找
					else if (e < tmp->expon)
					{
						tmp = tmp->Next;
						pretmp = pretmp->Next;
					}
					//如果两个相等的话，就直接修改当前tmp的系数，指数不变，系数相加进行合并
					//相加后的结果如果是0的话就删除tmp节点
					else
					{
						sum = c + tmp->coef;
						if (sum)
							tmp->coef = sum;
						else
						{
							pretmp->Next = tmp->Next;
							tmp->Next = NULL;
							free(tmp);
						}
						break;
					}
				}
				//如果循环结束的时候tmp指向了NULL，说明前面的指数都比当前的乘积结果指数要大，那么就在结果链表尾巴上用Attach函数插入
				if (!tmp)
					Attach(c, e, &rear);
				t2 = t2->Next;
			}
			t1 = t1->Next;
		}
		//收尾工作
		tmp = front;
		front = front->Next;
		tmp->Next = NULL;
		free(tmp);
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
	printf("\n");
}
//多项式的加法main函数框架
int main()
{
	Polynomial p1, p2,L1,L2;
	//读入字符串1，存入到链表中,并返回链表头指针，输入格式，4 23 45 23 第一个代表一共的个数   先系数再指数
	p1 = ReadPloy();
	//输入字符串2
	p2 = ReadPloy();
	//进行多项式的加法运算
	L1 = PolyAdd(p1, p2);
	//打印结果1；
	PolyPrint(L1);
	//进行多项式的乘法运算
	L2 = PolyMult(p1, p2);
	//打印结果2；
	PolyPrint(L2);
	return 0;
}