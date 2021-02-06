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
//β�巨��������ɺ�������Ҫ����ϵ����ָ������Ҫ�޸�������Ҫ�����βָ��
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

// �˷���ʵ��
Polynomial PolyMult(Polynomial p1, Polynomial p2)
{
	//����ʵ��˼·��t1,t2�ֱ�ָ��p1��p2������ʼʱ��t1�ĵ�һ���t2��ÿһ����ʼ�Ľ������
	//Ȼ��t1�����ٳ���t2��ÿһ����ָ����ϵ��������Ĺؼ��ǲ������������һ��tmpָ������������ǰ�Ľ������
	//�ҵ����ʵ�λ�ò���
	//��֤p1,p2�ĺϷ���
	if (!p1 || !p2)
		return NULL;
	Polynomial front, rear, tmp,pretmp,t1,t2;
	int sum = 0;
	int c = 0;//��¼ϵ����˵Ľ��
	int e = 0;//��¼ָ����˵Ľ��
	t1 = p1;
	t2 = p2;
	front = (Polynomial)malloc(sizeof(struct PolyNode));
	if (front)
	{
		rear = front;
		//ʵ�ֳ�ʼ�����
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
				tmp = front->Next;//tmp������������������Ѱ�Һ��ʵĲ���λ��
				pretmp = front;
				c = t1->coef * t2->coef;
				e = t1->expon + t2->expon;
				while (tmp)
				{
					//�����ǰ�˻��Ľ��ָ���Ǳ�tmp��ָ���������tmp��ǰ�棬��ô��Ҫһ��ָ������¼tmp֮ǰ��λ��
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
					//�����ǰ�˻��Ľ��ָ����tmp��ָ��С����tmp���ƣ�������
					else if (e < tmp->expon)
					{
						tmp = tmp->Next;
						pretmp = pretmp->Next;
					}
					//���������ȵĻ�����ֱ���޸ĵ�ǰtmp��ϵ����ָ�����䣬ϵ����ӽ��кϲ�
					//��Ӻ�Ľ�������0�Ļ���ɾ��tmp�ڵ�
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
				//���ѭ��������ʱ��tmpָ����NULL��˵��ǰ���ָ�����ȵ�ǰ�ĳ˻����ָ��Ҫ����ô���ڽ������β������Attach��������
				if (!tmp)
					Attach(c, e, &rear);
				t2 = t2->Next;
			}
			t1 = t1->Next;
		}
		//��β����
		tmp = front;
		front = front->Next;
		tmp->Next = NULL;
		free(tmp);
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
	printf("\n");
}
//����ʽ�ļӷ�main�������
int main()
{
	Polynomial p1, p2,L1,L2;
	//�����ַ���1�����뵽������,����������ͷָ�룬�����ʽ��4 23 45 23 ��һ������һ���ĸ���   ��ϵ����ָ��
	p1 = ReadPloy();
	//�����ַ���2
	p2 = ReadPloy();
	//���ж���ʽ�ļӷ�����
	L1 = PolyAdd(p1, p2);
	//��ӡ���1��
	PolyPrint(L1);
	//���ж���ʽ�ĳ˷�����
	L2 = PolyMult(p1, p2);
	//��ӡ���2��
	PolyPrint(L2);
	return 0;
}