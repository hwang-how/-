# define _CRT_SECURE_NO_WARNINGS 1
# pragma warning(disable:6031)
# include <stdio.h>

//题目说明：
//通过输入一些计算机的编号来将两个集合的计算机进行连接在一起
//或者通过输入的数据来判断两台计算机是否是连通的

//输入输出样例
//input1:
//5    表示总共有5台计算机
// c 3 2  检查3和2之间是否是连通的 ->  no
// I 3 2  将3 2进行连接
// C 1 5  -> no
// I 4 5 
// I 2 4
// C 3 5  -> yes
// S  表示输入结束

//输入结束之后进行判断看看有几个连通集合
//最后输出  There are 2 components


//input2:
//5    表示总共有5台计算机
// c 3 2  检查3和2之间是否是连通的 ->  no
// I 3 2  将3 2进行连接
// C 1 5  -> no
// I 4 5 
// I 2 4
// C 3 5  -> yes
// I 1 3
// C 1 5  -> yes
// S  表示输入结束

//  The network is connected

#define MAXN 1000
typedef int ElementType;
typedef ElementType SetName;  //集合的名字用整数来表示，也就是树的根节点的下标
typedef int SetType[MAXN];   //typedef的特殊用法，SetType s  就表示创建一个int型的元素个数是1000的集合s【1000】
//说明：
//1.数组的下标和计算机对应的编号吻合
//2.初始时数组的每个值对应设置为-1，表示初始时都是单个结点，都是根结点
//3.合并之后根节点的负值表示这个集合的元素个数


//集合的基本操作：
//1.查找集合的所属也就是根结点:
SetName Find(SetType S, ElementType X)
{
	for (; S[X] >= 0; X = S[X]);
	return X;
}

// Find函数的优化   路径压缩
SetName Find(SetType S, ElementType X)
{
	if (S[X] < 0)
		return X;
	else
		return S[X] = Find(S, S[X]);//从下面一直往根节点上面找，并且把路径上的结点的指针全部指向最终的跟结点，相当于把路径上的很多结点的查找路径变短了
}

//2.将两个集合进行合并,并且合并时进行优化，防止树长的过高
void Union(SetType S, SetName root1, SetName root2)
{
	if (S[root1] < S[root2])//说明root1的树元素多，将root2连接到root1上去
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
//主函数框架搭建
int main()
{
	int n;//初始时输入的计算机台数
	ElementType x, y;//一会儿要进行判断的两台计算机
	SetType S;//创建初始数组
	char ch;
	scanf("%d", &n);
	rewind(stdin);//!!!!!!!!!!!!!!!!!!!!!!!!!!!非常关键的一个东西，不然\n在缓冲区中会被下面那个字符的scanf直接接收从而跳过scanf的执行！！
	Initialization(S,n);//初始化数组,将n个元素的位置置位-1；
	do
	{
		scanf("%c", &ch);
		rewind(stdin);
		switch (ch)
		{
		case 'I':
			scanf("%d %d", &x, &y);
			rewind(stdin);
			Input_connection(S,Find(S,x), Find(S,y));//将两台电脑连接起来，这是只需要找到他们各自的根节点然后进行连接即可；
			break;
		case 'c':
			scanf("%d %d", &x, &y);
			rewind(stdin);
			Check(S, Find(S, x), Find(S, y));//检查两台电脑是否连通，同样也只需要找到他们的根节点，比较是否相同，若相同，则是连通的
			break;
		case 'S':
			Isconnected(S,n);//判断整个有几个连通集，通过扫描整个集合，看看有几个是负数的，有几个是负数代表有几个根节点，就有几个连通集
			break;
		default:
			printf("输入有误，请重新输入\n");
			break;
		}
	} while (ch != 'S');
	return 0;
}

//初始化函数
void Initialization(SetType S, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		S[i] = -1;
	}
}
//建立连接函数
void Input_connection(SetType S, SetName root1, SetName root2)
{
	if (root1 != root2)
		Union(S, root1, root2);
}
//检查是否连通函数
void Check(SetType S, SetName root1, SetName root2)
{
	if (root1 == root2)
		printf("yes\n");
	else
		printf("no\n");
}
//判断连通集的个数
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