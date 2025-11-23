//【例5.5】的算法：求一个顺序表中最大元素。
#include <stdio.h>
#define MaxSize 50
typedef int ElemType; 
typedef struct 
{	
	ElemType data[MaxSize];		//存放顺序表元素
   	int length;					//存放顺序表的长度
} SqList;						//顺序表的类型

ElemType Max1(SqList L,int i)	//解法1：求顺序表L中最大元素
{	ElemType max;
	if (i==0) return L.data[0];
	else
	{	max=Max1(L,i-1);
		if (max<L.data[i]) return L.data[i];
		else return max;
	}
}

ElemType Max2(SqList L,int i,int j)  //解法2：求顺序表L中最大元素
{
	int mid;
	ElemType max,max1,max2;
	if (i==j) 
		max=L.data[i];				//递归出口
	else
	{	
		mid=(i+j)/2;
		max1=Max2(L,i,mid);			//递归调用1
		max2=Max2(L,mid+1,j); 		//递归调用2
		max=(max1>max2)?max1:max2;
	}
	return(max);
}
int main()
{
	int i;
	SqList L;
	ElemType a[]={3,1,5,8,0,2,4,7,9,6};
	for (i=0;i<10;i++)		//构造顺序表
		L.data[i]=a[i];
	L.length=10;
	printf("Max1:Max=%d\n",Max1(L,9));
	printf("Max2:Max=%d\n",Max2(L,0,9));
	return 1;
}
