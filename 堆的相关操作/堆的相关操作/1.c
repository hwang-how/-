# define _CRT_SECURE_NO_WARNINGS 1
# pragma warning(disable:6031)
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

//堆得结构体定义
typedef int ElementType;
typedef struct Hnode* Heap;
typedef Heap MaxHeap;
typedef Heap MinHeap;
struct Hnode
{
	ElementType* data;//存堆的数组
	int Capacity;//堆容量
	int Size;//当前存入的个数
};

//创建空的最大堆
#define MAXDATA 1000
MaxHeap CreatHeap(int MaxSize)
{
	//先给结构体开辟一个空间
	MaxHeap H = (MaxHeap)malloc(sizeof(struct Hnode));
	//开辟数组空间
	if (H)
	{
		H->data = (ElementType*)malloc((MaxSize + 1) * sizeof(ElementType));
		if(H->data)
			H->data[0] = MAXDATA;//给哨兵赋初始值
		H->Size = 0;
		H->Capacity = MaxSize;
	}
	return H;
}
//判断堆是否已经满了
bool IsFull(MaxHeap H)
{
	//if (H->Size == H->Capacity)
	//	return true;
	//else
	//	return false;
	return (H->Size == H->Capacity);
}
//判断是否为空
bool IsEmpty(MaxHeap H)
{
	//if (H->Size == 0)
	//	return true;
	//else
	//	return false;
	return (H->Size == 0);//成立就返回的是1，否则是0
}
//进行堆的插入
bool InSert(MaxHeap H,int x)//在堆中插入x
{
	if (!IsFull(H))
	{
		int i=H->Size+1;  //data[i]的位置就是新插入元素的位置，之后进行调整
		for (; H->data[i / 2] < x; i /= 2)
		{
			H->data[i] = H->data[i / 2];
		}
		H->data[i] = x;
		H->Size++;
		return true;
	}
	else
	{
		printf("堆已满!");
		return false;  //插入失败
	}
}


//版本1
//进行堆的删除，并返回被删除元素的值
#define ERROR -1
//void Swap(int* x, int* y);
//ElementType DeletMax(MaxHeap H)
//{
//	//首先检查堆是不是空的，空堆没必要继续进行
//	if (IsEmpty(H))
//	{
//		printf("当前堆已空！");
//		return ERROR;
//	}
//	int parents, child, Maxitem; //parents 最开始指向的是根结点，child用来指向parents两个孩子中较大的一个,ret用来存储最终的返回值
//	parents = 1;
//	Maxitem = H->data[parents];
//	H->data[parents] = H->data[H->Size];//最后一个元素替代根节点然后开始下坠
//	H->Size--;
//	if (H->Size == 0)//说明此时的堆只有一个结点，直接就删除完了
//	{
//		H = NULL;
//		free(H);//既然已经空了，就释放掉空间
//		return Maxitem;
//	}
//	else//说明不止是一个结点的堆
//	{
//		int flag = 1;//flag用于标记是否发生父子交换，如果没发生将flag置位0，跳出循环
//		while (flag)
//		{
//			child = parents * 2;
//			if ((child + 1) <= H->Size && H->data[child] < H->data[child + 1])//当右孩子存在而且右孩子比左孩子大的时候，让child指向右孩子
//				child++;
//			if (H->data[parents] < H->data[child])
//			{
//				Swap(&(H->data[parents]), &(H->data[child]));//感觉这里有点bug，如果只有两个元素的话，前面已经删除了，child好像越界访问了
//				parents = child;
//			}
//			else
//				flag = 0;//说明此轮没有发生交换，终止循环
//		}
//		return Maxitem;
//	}
//}
//交换函数
void Swap(int* x, int* y)
{
	int tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}





//  版本2，教材版
ElementType DeletMax(MaxHeap H)
{
	//首先应该进行判断堆是否为空，如果是空的就没必要继续进行下去
	if (IsEmpty(H))
	{
		printf("当前堆已满\n");
		return ERROR;
	}
	int parents, child;
	ElementType Maxitem, tmp;//Maxitem用来存储待删除的最大值，tmp用来临时存储最后一个结点的值，方便下坠时候进行比较
	Maxitem = H->data[1];
	tmp = H->data[H->Size--];//这里已经将堆的长度减少了一个
	for (parents = 1; parents * 2 <= H->Size; parents = child)//如果最后一个节点的值比大孩子还大，就让parents下坠，parents也就是最后要存放最后一个结点的位置
	{
		child = parents * 2;
		if (!(child == H->Size) && H->data[child] < H->data[child + 1])
			child++;//当有右孩子的时候，让child指向大的孩子
		if (tmp > H->data[child])
			break;
		else
			H->data[parents] = H->data[child];//让大的孩子上位
	}
	H->data[parents] = tmp;
	return Maxitem;
}

//建堆方案2，先将有要构成堆的n个元素输入到数组中，形成初始的无序的堆
//然后从最后一个父节点开始调整堆，让小的元素下坠，大的上去
void PercDown(MaxHeap H, int i);
void BuildHeap(MaxHeap H)
{
	int i;
	for (i = H->Size / 2; i > 0; i--)
	{
		PercDown(H,i);
	}
}
//下坠函数
void PercDown(MaxHeap H,int i)
{
	int parent = i;
	int child = i * 2;
	if (child != H->Size && H->data[child] < H->data[child + 1])
		child++;
	if (child <= H->Size && H->data[parent] < H->data[child])
	{
		Swap(&(H->data[parent]), &(H->data[child]));
		PercDown(H, child);
	}
}

int main()
{


	//下坠法建堆开始
	int MaxSize, n, i, x;
	int j = 1;//j用来往数组中存入数据时使用
	MaxHeap H = NULL;
	printf("请输入初始堆容量：");
	scanf("%d", &MaxSize);//根据输入的堆最大容量来创建最大堆;实际创建的时候建的是MaxSize+1个容量，数组0用来存哨兵。
	if (MaxSize > 0)
	{
		H = CreatHeap(MaxSize);
	}
	else
	{
		printf("输入有误，请输入正整数\n");
	}
	//构建一个n个元素的最大堆
	printf("请输入要存入的元素个数：");
	scanf("%d", &n);
	if (n > H->Capacity)
	{
		printf("输入值超过堆的最大容量，无法建堆！\n");
		return 0;
	}
	printf("开始读入元素：\n");
	while (n)
	{
		scanf("%d", &x);
		//将数据插入到数组中
		H->data[j] = x;
		H->Size++;
		j++;
		n--;
	}
	BuildHeap(H);
	//将构建的结果打印出来看看
	if (!n)
	{
		for (i = 1; i <= H->Size; i++)
		{
			printf("%d ", H->data[i]);
		}
	}
	else
	{
		printf("建堆失败\n");
	}
	//下坠法建堆结束

}


////用插入的方法尝试构建一个最大堆
//int main()
//{
//
//
//	//插入法建堆开始
//	int MaxSize, n, i, x;
//	MaxHeap H = NULL;
//	scanf("%d", &MaxSize);//根据输入的堆最大容量来创建最大堆;实际创建的时候建的是MaxSize+1个容量，数组0用来存哨兵。
//	if (MaxSize > 0)
//	{
//		H = CreatHeap(MaxSize);
//	}
//	else
//	{
//		printf("输入有误，请输入正整数\n");
//	}
//	//构建一个四个元素的最大堆
//	scanf("%d", &n);
//	while (n)
//	{
//		scanf("%d", &x);
//		InSert(H, x);
//		n--;
//	}
//	//将构建的结果打印出来看看
//	if (!n)
//	{
//		for (i = 1; i <= H->Size; i++)
//		{
//			printf("%d ", H->data[i]);
//		}
//	}
//	else
//	{
//		printf("建堆失败\n");
//	}
//	//插入法建堆结束
//
//
//
//
//	int delet = DeletMax(H);
//	printf("delet=%d\n", delet);
//	//将删除后的结果打印出来看看
//	for (i = 1; i <= H->Size; i++)
//	{
//		printf("%d ", H->data[i]);
//	}
//	return 0;
//}
#define MaxSize 1000
typedef int SetType[MaxSize];
SetType s;