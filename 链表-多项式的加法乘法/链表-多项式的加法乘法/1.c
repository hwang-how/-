# define _CRT_SECURE_NO_WARNINGS 1
# pragma warning(disable:6031)
# include <stdio.h>
# include <stdlib.h>

//����ʽ�ڵ�
struct PolyNode
{
	int coef;//ϵ��
	int expon;//ָ��
	struct PolyNode* Next;
};
typedef struct PolyNode* Polynomial;
//��������ɺ�������Ҫ����ϵ����ָ������Ҫ�޸�������Ҫ�����βָ��
void Attach(int coef, int expon, Polynomial* rear)
{
	//����սڵ�
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
	//������һ��ͷ�ڵ�����������������ַ�
	int num = 0; //num��ʾ����Ķ���ʽ����������
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
//ϵ���ȽϺ���
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
	//�½�һ���������洢��Ӻ�Ľ��
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
			case 1://p1��ָ���󣬽�p1�ڵ���뵽��������У�p1ָ����ƶ�
				Attach(p1->coef, p1->expon, &rear);
				p1 = p1->Next;
				break;
			case -1://p2��ָ���󣬽�p2�ڵ���뵽��������У�p2ָ����ƶ�
				Attach(p2->coef, p2->expon, &rear);
				p2 = p2->Next;
				break;
			case 0://ָ����ͬ��ϵ�����
				sum = p1->coef + p2->coef;
				//���ϵ��������0
				if (sum)
					Attach(sum, p2->expon, &rear);
				p1 = p1->Next;
				p2 = p2->Next;
				break;
			}
		}
		//����ѭ������Ȼ��һ������ʽû�б�����
		//�����p1
		for (; p1; p1 = p1->Next)
		{
			Attach(p1->coef, p1->expon, &rear);
		}
		//�����p2
		for (; p2; p2 = p2->Next)
		{
			Attach(p2->coef, p2->expon, &rear);
		}
		//������ϣ��ͷ��ʼ����Ŀյ�ͷ�ڵ�
		rear->Next = NULL;
		tmp = front->Next;
		front->Next = NULL;
		free(front);
		front = tmp;
		return front;
	}
}
//ʵ�ִ�ӡ������
void PolyPrint(Polynomial L)
{
	while (L)
	{
		printf("%d %d", L->coef, L->expon);
		printf("  ");
		L = L->Next;
	}
}
//����ʽ�ļӷ�main�������
int main()
{
	Polynomial p1, p2,L1;
	//�����ַ���1�����뵽������,����������ͷָ�룬�����ʽ��4 23 45 23 ��һ������һ���ĸ���   ��ϵ����ָ��
	p1 = ReadPloy();
	//�����ַ���2
	p2 = ReadPloy();
	//���ж���ʽ�ļӷ�����
	L1 = PolyAdd(p1, p2);
	//��ӡ���1��
	PolyPrint(L1);
	//���ж���ʽ�ĳ˷�����
	//L2 = PolyMult(p1, p2);
	////��ӡ���2��
	//PolyPrint(L2);
	return 0;
}