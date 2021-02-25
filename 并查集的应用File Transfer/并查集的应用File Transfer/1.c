# define _CRT_SECURE_NO_WARNINGS 1
# pragma warning(disable:6031)
# include <stdio.h>

//��Ŀ˵����
//ͨ������һЩ������ı�������������ϵļ��������������һ��
//����ͨ��������������ж���̨������Ƿ�����ͨ��

//�����������
//input1:
//5    ��ʾ�ܹ���5̨�����
// c 3 2  ���3��2֮���Ƿ�����ͨ�� ->  no
// I 3 2  ��3 2��������
// C 1 5  -> no
// I 4 5 
// I 2 4
// C 3 5  -> yes
// S  ��ʾ�������

//�������֮������жϿ����м�����ͨ����
//������  There are 2 components


//input2:
//5    ��ʾ�ܹ���5̨�����
// c 3 2  ���3��2֮���Ƿ�����ͨ�� ->  no
// I 3 2  ��3 2��������
// C 1 5  -> no
// I 4 5 
// I 2 4
// C 3 5  -> yes
// I 1 3
// C 1 5  -> yes
// S  ��ʾ�������

//  The network is connected

#define MAXN 1000
typedef int ElementType;
typedef ElementType SetName;  //���ϵ���������������ʾ��Ҳ�������ĸ��ڵ���±�
typedef int SetType[MAXN];   //typedef�������÷���SetType s  �ͱ�ʾ����һ��int�͵�Ԫ�ظ�����1000�ļ���s��1000��
//˵����
//1.������±�ͼ������Ӧ�ı���Ǻ�
//2.��ʼʱ�����ÿ��ֵ��Ӧ����Ϊ-1����ʾ��ʼʱ���ǵ�����㣬���Ǹ����
//3.�ϲ�֮����ڵ�ĸ�ֵ��ʾ������ϵ�Ԫ�ظ���


//���ϵĻ���������
//1.���Ҽ��ϵ�����Ҳ���Ǹ����:
SetName Find(SetType S, ElementType X)
{
	for (; S[X] >= 0; X = S[X]);
	return X;
}

// Find�������Ż�   ·��ѹ��
SetName Find(SetType S, ElementType X)
{
	if (S[X] < 0)
		return X;
	else
		return S[X] = Find(S, S[X]);//������һֱ�����ڵ������ң����Ұ�·���ϵĽ���ָ��ȫ��ָ�����յĸ���㣬�൱�ڰ�·���ϵĺܶ���Ĳ���·�������
}

//2.���������Ͻ��кϲ�,���Һϲ�ʱ�����Ż�����ֹ�����Ĺ���
void Union(SetType S, SetName root1, SetName root2)
{
	if (S[root1] < S[root2])//˵��root1����Ԫ�ض࣬��root2���ӵ�root1��ȥ
	{
		S[root1] += S[root2];
		S[root2] = root1;
	}
	else
	{
		S[root2] += S[root1];
		S[root1] = root2;
	}
}


void Initialization(SetType S, int n);
void Check(SetType S, SetName root1, SetName root2);
void Isconnected(SetType S, int n);
void Input_connection(SetType S, SetName root1, SetName root2);
//��������ܴ
int main()
{
	int n;//��ʼʱ����ļ����̨��
	ElementType x, y;//һ���Ҫ�����жϵ���̨�����
	SetType S;//������ʼ����
	char ch;
	scanf("%d", &n);
	rewind(stdin);//!!!!!!!!!!!!!!!!!!!!!!!!!!!�ǳ��ؼ���һ����������Ȼ\n�ڻ������лᱻ�����Ǹ��ַ���scanfֱ�ӽ��մӶ�����scanf��ִ�У���
	Initialization(S,n);//��ʼ������,��n��Ԫ�ص�λ����λ-1��
	do
	{
		scanf("%c", &ch);
		rewind(stdin);
		switch (ch)
		{
		case 'I':
			scanf("%d %d", &x, &y);
			rewind(stdin);
			Input_connection(S,Find(S,x), Find(S,y));//����̨������������������ֻ��Ҫ�ҵ����Ǹ��Եĸ��ڵ�Ȼ��������Ӽ��ɣ�
			break;
		case 'c':
			scanf("%d %d", &x, &y);
			rewind(stdin);
			Check(S, Find(S, x), Find(S, y));//�����̨�����Ƿ���ͨ��ͬ��Ҳֻ��Ҫ�ҵ����ǵĸ��ڵ㣬�Ƚ��Ƿ���ͬ������ͬ��������ͨ��
			break;
		case 'S':
			Isconnected(S,n);//�ж������м�����ͨ����ͨ��ɨ���������ϣ������м����Ǹ����ģ��м����Ǹ��������м������ڵ㣬���м�����ͨ��
			break;
		default:
			printf("������������������\n");
			break;
		}
	} while (ch != 'S');
	return 0;
}

//��ʼ������
void Initialization(SetType S, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		S[i] = -1;
	}
}
//�������Ӻ���
void Input_connection(SetType S, SetName root1, SetName root2)
{
	if (root1 != root2)
		Union(S, root1, root2);
}
//����Ƿ���ͨ����
void Check(SetType S, SetName root1, SetName root2)
{
	if (root1 == root2)
		printf("yes\n");
	else
		printf("no\n");
}
//�ж���ͨ���ĸ���
void Isconnected(SetType S,int n)
{
	int count=0;
	int i;
	for (i = 0; i < n; i++)
	{
		if (S[i] < 0)
			count++;
	}
	if (count == 1)
		printf("The network is connected\n");
	else
		printf("There are %d components\n", count);

}