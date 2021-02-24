# define _CRT_SECURE_NO_WARNINGS 1
# pragma warning(disable:6031)
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

//�ѵýṹ�嶨��
typedef int ElementType;
typedef struct Hnode* Heap;
typedef Heap MaxHeap;
typedef Heap MinHeap;
struct Hnode
{
	ElementType* data;//��ѵ�����
	int Capacity;//������
	int Size;//��ǰ����ĸ���
};

//�����յ�����
#define MAXDATA 1000
MaxHeap CreatHeap(int MaxSize)
{
	//�ȸ��ṹ�忪��һ���ռ�
	MaxHeap H = (MaxHeap)malloc(sizeof(struct Hnode));
	//��������ռ�
	if (H)
	{
		H->data = (ElementType*)malloc((MaxSize + 1) * sizeof(ElementType));
		if(H->data)
			H->data[0] = MAXDATA;//���ڱ�����ʼֵ
		H->Size = 0;
		H->Capacity = MaxSize;
	}
	return H;
}
//�ж϶��Ƿ��Ѿ�����
bool IsFull(MaxHeap H)
{
	//if (H->Size == H->Capacity)
	//	return true;
	//else
	//	return false;
	return (H->Size == H->Capacity);
}
//�ж��Ƿ�Ϊ��
bool IsEmpty(MaxHeap H)
{
	//if (H->Size == 0)
	//	return true;
	//else
	//	return false;
	return (H->Size == 0);//�����ͷ��ص���1��������0
}
//���жѵĲ���
bool InSert(MaxHeap H,int x)//�ڶ��в���x
{
	if (!IsFull(H))
	{
		int i=H->Size+1;  //data[i]��λ�þ����²���Ԫ�ص�λ�ã�֮����е���
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
		printf("������!");
		return false;  //����ʧ��
	}
}


//�汾1
//���жѵ�ɾ���������ر�ɾ��Ԫ�ص�ֵ
#define ERROR -1
//void Swap(int* x, int* y);
//ElementType DeletMax(MaxHeap H)
//{
//	//���ȼ����ǲ��ǿյģ��ն�û��Ҫ��������
//	if (IsEmpty(H))
//	{
//		printf("��ǰ���ѿգ�");
//		return ERROR;
//	}
//	int parents, child, Maxitem; //parents �ʼָ����Ǹ���㣬child����ָ��parents���������нϴ��һ��,ret�����洢���յķ���ֵ
//	parents = 1;
//	Maxitem = H->data[parents];
//	H->data[parents] = H->data[H->Size];//���һ��Ԫ��������ڵ�Ȼ��ʼ��׹
//	H->Size--;
//	if (H->Size == 0)//˵����ʱ�Ķ�ֻ��һ����㣬ֱ�Ӿ�ɾ������
//	{
//		H = NULL;
//		free(H);//��Ȼ�Ѿ����ˣ����ͷŵ��ռ�
//		return Maxitem;
//	}
//	else//˵����ֹ��һ�����Ķ�
//	{
//		int flag = 1;//flag���ڱ���Ƿ������ӽ��������û������flag��λ0������ѭ��
//		while (flag)
//		{
//			child = parents * 2;
//			if ((child + 1) <= H->Size && H->data[child] < H->data[child + 1])//���Һ��Ӵ��ڶ����Һ��ӱ����Ӵ��ʱ����childָ���Һ���
//				child++;
//			if (H->data[parents] < H->data[child])
//			{
//				Swap(&(H->data[parents]), &(H->data[child]));//�о������е�bug�����ֻ������Ԫ�صĻ���ǰ���Ѿ�ɾ���ˣ�child����Խ�������
//				parents = child;
//			}
//			else
//				flag = 0;//˵������û�з�����������ֹѭ��
//		}
//		return Maxitem;
//	}
//}
//��������
void Swap(int* x, int* y)
{
	int tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}





//  �汾2���̲İ�
ElementType DeletMax(MaxHeap H)
{
	//����Ӧ�ý����ж϶��Ƿ�Ϊ�գ�����ǿյľ�û��Ҫ����������ȥ
	if (IsEmpty(H))
	{
		printf("��ǰ������\n");
		return ERROR;
	}
	int parents, child;
	ElementType Maxitem, tmp;//Maxitem�����洢��ɾ�������ֵ��tmp������ʱ�洢���һ������ֵ��������׹ʱ����бȽ�
	Maxitem = H->data[1];
	tmp = H->data[H->Size--];//�����Ѿ����ѵĳ��ȼ�����һ��
	for (parents = 1; parents * 2 <= H->Size; parents = child)//������һ���ڵ��ֵ�ȴ��ӻ��󣬾���parents��׹��parentsҲ�������Ҫ������һ������λ��
	{
		child = parents * 2;
		if (!(child == H->Size) && H->data[child] < H->data[child + 1])
			child++;//�����Һ��ӵ�ʱ����childָ���ĺ���
		if (tmp > H->data[child])
			break;
		else
			H->data[parents] = H->data[child];//�ô�ĺ�����λ
	}
	H->data[parents] = tmp;
	return Maxitem;
}

//���ѷ���2���Ƚ���Ҫ���ɶѵ�n��Ԫ�����뵽�����У��γɳ�ʼ������Ķ�
//Ȼ������һ�����ڵ㿪ʼ�����ѣ���С��Ԫ����׹�������ȥ
void PercDown(MaxHeap H, int i);
void BuildHeap(MaxHeap H)
{
	int i;
	for (i = H->Size / 2; i > 0; i--)
	{
		PercDown(H,i);
	}
}
//��׹����
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


	//��׹�����ѿ�ʼ
	int MaxSize, n, i, x;
	int j = 1;//j�����������д�������ʱʹ��
	MaxHeap H = NULL;
	printf("�������ʼ��������");
	scanf("%d", &MaxSize);//��������Ķ������������������;ʵ�ʴ�����ʱ�򽨵���MaxSize+1������������0�������ڱ���
	if (MaxSize > 0)
	{
		H = CreatHeap(MaxSize);
	}
	else
	{
		printf("��������������������\n");
	}
	//����һ��n��Ԫ�ص�����
	printf("������Ҫ�����Ԫ�ظ�����");
	scanf("%d", &n);
	if (n > H->Capacity)
	{
		printf("����ֵ�����ѵ�����������޷����ѣ�\n");
		return 0;
	}
	printf("��ʼ����Ԫ�أ�\n");
	while (n)
	{
		scanf("%d", &x);
		//�����ݲ��뵽������
		H->data[j] = x;
		H->Size++;
		j++;
		n--;
	}
	BuildHeap(H);
	//�������Ľ����ӡ��������
	if (!n)
	{
		for (i = 1; i <= H->Size; i++)
		{
			printf("%d ", H->data[i]);
		}
	}
	else
	{
		printf("����ʧ��\n");
	}
	//��׹�����ѽ���

}


////�ò���ķ������Թ���һ������
//int main()
//{
//
//
//	//���뷨���ѿ�ʼ
//	int MaxSize, n, i, x;
//	MaxHeap H = NULL;
//	scanf("%d", &MaxSize);//��������Ķ������������������;ʵ�ʴ�����ʱ�򽨵���MaxSize+1������������0�������ڱ���
//	if (MaxSize > 0)
//	{
//		H = CreatHeap(MaxSize);
//	}
//	else
//	{
//		printf("��������������������\n");
//	}
//	//����һ���ĸ�Ԫ�ص�����
//	scanf("%d", &n);
//	while (n)
//	{
//		scanf("%d", &x);
//		InSert(H, x);
//		n--;
//	}
//	//�������Ľ����ӡ��������
//	if (!n)
//	{
//		for (i = 1; i <= H->Size; i++)
//		{
//			printf("%d ", H->data[i]);
//		}
//	}
//	else
//	{
//		printf("����ʧ��\n");
//	}
//	//���뷨���ѽ���
//
//
//
//
//	int delet = DeletMax(H);
//	printf("delet=%d\n", delet);
//	//��ɾ����Ľ����ӡ��������
//	for (i = 1; i <= H->Size; i++)
//	{
//		printf("%d ", H->data[i]);
//	}
//	return 0;
//}
#define MaxSize 1000
typedef int SetType[MaxSize];
SetType s;