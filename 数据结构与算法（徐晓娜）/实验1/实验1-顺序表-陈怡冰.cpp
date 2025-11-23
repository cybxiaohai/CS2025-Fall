#include<stdio.h>
#include<malloc.h>
#define MaxSize 10

typedef int ElemType;
typedef struct {
	ElemType data[MaxSize];
	int length;
} SqList;

void InitList(SqList *&L) {
	L = (SqList*)malloc(sizeof(SqList));
	L->length = 0;
}

void CreateList(SqList *&L, ElemType a[], int n) {
	L = (SqList*)malloc(sizeof(SqList));
	for (int i = 0; i < n; i++) {
		L->data[i] = a[i];

	}
	L->length = n;

}

void PrintList(SqList*&L) {
	for (int i = 0; i < L->length; i++) {
		printf("%d ", L->data[i]);
	}
	printf("\nlength=%d\n\n", L->length);
}

bool InsertList(SqList *&L, int j, ElemType &e) {
	bool flag = true;
	if (L->length >= MaxSize) {
		flag = false;
	} else {
		for (int i = L->length - 1; i >= j; i--) {
			L->data[i + 1] = L->data[i];
		}
		L->data[j] = e;
		L->length += 1;
		flag = true;
	}

	return flag;
}

bool DeleteList(SqList *&L, int j) {
	bool flag = true;
	if (L->length <= j) {
		flag = false;
	} else {
		for (int i = j; i < L->length; i++) {
			L->data[i] = L->data[i + 1];
		}

		L->length -= 1;
		flag = true;
	}

	return flag;
}

bool FindList(SqList *&L, ElemType &e) {
	bool flag = false;
	for (int i = 0; i < L->length; i++) {
		if (L->data[i] == e) {
			flag = true;
			break;
		}
	}
	return flag;
}

bool AddList(SqList *&L, SqList*&L_add) {
	bool flag = true;
	int j;
	if (L->length + L_add->length > MaxSize) {
		printf("Add Error\n");
		flag = false;
	} else {
		for (int i = 0; i < L_add->length; i++) {
			j = L->length + i;
			L->data[j] = L_add->data[i];
		}
		L->length = L->length + L_add->length;
	}
	return flag;
}

void ClearList(SqList *&L) {
	L->length = 0;
}


int main() {
	SqList* L, *LA, *LB, *LC;
	ElemType a[8] = {0, 1, 2, 3, 5, 6, 9, 9};
	ElemType la[8] = {2, 7, 6, 9, 8, 3, 0, 1};
	ElemType lb[8] = {1, 4, 5, 6, 9, 3, 0, 7};
	int n = 8;
	ElemType e = 4;
	CreateList(L, a, n);
	CreateList(LA, la, n);
	CreateList(LB, lb, n);
	InitList(LC);
	printf("L:");
	PrintList(L);
	printf("LA:");
	PrintList(LA);
	printf("LB:");
	PrintList(LB);
	printf("LC:");
	PrintList(LC);


	int j = 0;
	for (int i = 0; i < L->length; i++) {
		if (L->data[i] < e) {
			j = i + 1;
		} else {
			j = i;
			break;
		}
	}
	InsertList(L, j, e);
	printf("1.插入元素e=4\n");
	printf("L:");
	PrintList(L);

	j = 0;
	while (j < L->length - 1) {
		if (L->data[j] == L->data[j + 1]) {
			DeleteList(L, j);
		} else {
			j++;
		}
	}
	printf("2.删除重复元素\n");
	printf("L:");
	PrintList(L);

	AddList(LC, LA);
	for (int i = 0; i < LB->length; i++) {
		if (!FindList(LC, LB->data[i])) {
			InsertList(LC, LC->length, LB->data[i]);
		}
	}
	printf("3.求LA,LB并集\nLC:");
	PrintList(LC);

	ClearList(LC);
	for (int i = 0; i < LB->length; i++) {
		if (FindList(LA, LB->data[i])) {
			InsertList(LC, LC->length, LB->data[i]);
		}
	}
	printf("4.求LA,LB交集\nLC:");
	PrintList(LC);

	ClearList(LC);
	for (int i = 0; i < LA->length; i++) {
		if (!FindList(LB, LA->data[i])) {
			InsertList(LC, LC->length, LA->data[i]);
		}
	}
	printf("5.求LA,LB差集\nLC:");
	PrintList(LC);

	return 0;

}
