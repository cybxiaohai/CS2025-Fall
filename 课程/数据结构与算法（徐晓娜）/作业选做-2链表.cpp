/*
第二章选做作业


2.假设有一个学生文件student.txt，每个学生记录包括学号、姓名、高等数学成绩、线性代数成绩、大学英语成绩、体育成绩。设计一个程序，完成以下功能：

(1) 建立一个带头结点的单链表L，从student.txt文件中读出学生记录，并将记录存放在单链表L中。

(2) 显示所有学生记录。

(3) 将学生记录按平均分降序排序，并显示数据。

(4) 插入学生记录，并能使记录还按平均分降序排序。

(5) 修改某个学生某门课的分数，并能使记录还按平均分降序排序。

（6）将单链表L中的所有记录存回到student.txt文件中。




*/

#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<locale.h>
#include<wchar.h>
#include<windows.h>
typedef struct {
	int ID;					//学号
	char name[10];			//姓名
	float gaoshu;			//高等数学成绩
	float xiandai;			//线性代数成绩
	float yingyu;			//大学英语成绩
	float tiyu;				//体育成绩
	float ave_score;		//平均分

} ElemType;

typedef struct LNode {
	ElemType data;
	struct LNode *next;
} LinkNode;

void LinkCreate(LinkNode *&L, ElemType a[], int n);
void LinkDisplay(LinkNode *&L);
void LinkInsert(LinkNode *&L, ElemType &e);
void LinkChange(LinkNode *&L);
int TxtRead(FILE *T, ElemType a[]);
void ElemDisplay(ElemType &e);
void ElemAve(ElemType &e);
LinkNode* LinkSort(LinkNode *&L);
void TxtWrite(FILE* T, LinkNode *&L);



int main() {
	/*————————————中文编码测试一————————————*/
//	printf("当前区域设置: %s\n", setlocale(LC_ALL, NULL));
//	setlocale(LC_ALL, "zh_CN.UTF-8");
//	printf("设置后区域: %s\n", setlocale(LC_ALL, NULL));
//
//	// 测试输出中文
//	printf("测试中文输出\n");

	/*—————————————中文编码测试二————————————*/
//	const char* locales[] = {
//		"zh_CN.UTF-8", "zh_CN.utf8", "zh_CN.gbk",
//		"Chinese_China.936", "C.UTF-8", "en_US.UTF-8"
//	};
//
//	for (int i = 0; i < sizeof(locales) / sizeof(locales[0]); i++) {
//		if (setlocale(LC_ALL, locales[i]) != NULL) {
//			printf("成功设置区域: %s\n", locales[i]);
//			break;
//		}
//	}
//
//	// 如果都不行，设置为空字符串使用系统默认
//	if (setlocale(LC_ALL, "") == NULL) {
//		setlocale(LC_ALL, "C");
//	}
//
//	printf("最终区域设置: %s\n", setlocale(LC_ALL, NULL));
//	printf("测试中文输出\n");
//	_setmode(_fileno(stdout), _O_U16TEXT);
	setlocale(LC_ALL, "zh_CN.UTF-8");

	wprintf(L"当前区域设置: %hs\n", setlocale(LC_ALL, NULL));
	wprintf(L"测试中文输出\n");

// 1) 读取文件并将记录存放在单链表L中
	ElemType a[100] ;
	LinkNode *L = NULL;
	int n = 0;
//	FILE *fp = _wfopen(FileName, L"r+");
	FILE *fp = fopen("student.txt", "r+");
	n = TxtRead(fp, a);
	LinkCreate(L, a, n);

// 2）显示记录
	LinkDisplay(L);
//
	// 3) 按均分降序排序并显示
	LinkSort(L);
	LinkDisplay(L);

	// 4) 插入记录并排序
	ElemType e;
	printf("\n--- 插入新学生记录 ---\n");
	printf("输入学号: ");
	scanf("%d", &e.ID);
	printf("输入姓名: ");
	scanf("%s", e.name);
	printf("输入高数成绩: ");
	scanf("%f", &e.gaoshu);
	printf("输入线代成绩: ");
	scanf("%f", &e.xiandai);
	printf("输入英语成绩: ");
	scanf("%f", &e.yingyu);
	printf("输入体育成绩: ");
	scanf("%f", &e.tiyu);
	ElemAve(e);
	LinkNode *X;
	LinkInsert(L, e);
	X = LinkSort(L);
	LinkDisplay(X);

	// 5) 修改分数并排序
	LinkChange(X);
	LinkDisplay(X);

	// 6) 记录存回文件
	TxtWrite(fp, X);

	fclose(fp);
	return 0;

}

//尾插法创建单链表
void LinkCreate(LinkNode *&L, ElemType a[], int n) {
	L = (LinkNode*)malloc(sizeof(LinkNode));
	L->next = NULL;
	LinkNode* s = NULL,*r = L;
	for (int i = 0; i < n; i++) {
		s = (LinkNode*)malloc(sizeof(LinkNode));
		s->data = a[i];
		r->next = s;
		r = s;
	}
	r->next = NULL;
}

//展示单链表信息
void LinkDisplay(LinkNode *&L) {
	printf("L:\n");
	LinkNode*p = L->next;
	while (p != NULL) {
		ElemDisplay(p->data);
		p = p->next;
	}
}

//尾插法插入记录
void LinkInsert(LinkNode *&L, ElemType &e) {
	LinkNode*s = (LinkNode*)malloc(sizeof(LinkNode));
	s->data = e;
	s->next = NULL;
	if (L->next == NULL) {
		L->next = s;
		return;
	}

	// 寻找插入位置（按学号顺序或其他逻辑）
	LinkNode *prev = L;
	LinkNode *current = L->next;

	// 这里简单地在链表尾部插入
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = s;
}

//改变链表中某一学生成绩
void LinkChange(LinkNode *&L) {
	LinkNode*p = L->next;
	int ID, num, score;
	bool flag = false;
	do {
		printf("\n输入待改成绩的学生学号：(输入0可取消修改)");
		scanf("%d", &ID);
		if (ID == 0) {
			return;
		}
		while (p != NULL) {
			if (p->data.ID == ID) {
				flag = true;
				break;
			}
			p = p->next;
		}
		if (flag) {
			break;
		}
		printf("\n学号不存在。");

	} while (!flag);

	do {
		printf("\n输入待改科目（高数：1 线代：2 英语 3 体育 4，仅需输入序号）：");
		scanf("%d", &num);
	} while (num != 1 && num != 2 && num != 3 && num != 4);

	printf("\n输入正确成绩：");
	scanf("%d", &score);
	switch (num) {
		case 1:
			p->data.gaoshu = score;

			break;
		case 2:
			p->data.xiandai = score; //TODO
			break;
		case 3:
			p->data.yingyu = score;
			break;
		case 4:
			p->data.tiyu = score;
			break;
		default:
			//TODO
			break;

	}
	//刷新均分
	ElemAve(p->data);



}

int TxtRead(FILE *T, ElemType a[]) {
	setlocale(LC_ALL, "zh_CN.UTF-8");
	char line[100];
	int n = 0;
	char *slice = NULL;
	while (fscanf(T, "%d,%[^,],%f,%f,%f,%f", &a[n].ID, &a[n].name, &a[n].gaoshu, &a[n].xiandai, &a[n].yingyu, &a[n].tiyu) == 6) {
		ElemAve(a[n]);
		n++;
	}


//	while (fgets(line, 100, T) != NULL && n < 100) {
//
//		//获取ID
//		slice = strtok(line, ",\n\t");
//		//跳过空行
//		if (slice == NULL) {
//			continue;
//		}
//		a[n].ID = atoi(slice);
//
//		//获取姓名
//		slice = strtok(NULL, ",\n\t");
//
//		strcpy(a[n].name, slice);
//
//		//高数成绩
//		slice = strtok(NULL, ",\n\t");
//		a[n].gaoshu = atof(slice);
//
//		//xiandai
//		slice = strtok(NULL, ",\n\t");
//		a[n].xiandai = atof(slice);
//
//		//yingyu
//		slice = strtok(NULL, ",\n\t");
//		a[n].yingyu = atof(slice);
//
//		//tiyu
//		slice = strtok(NULL, ",\n\t");
//		a[n].tiyu = atof(slice);
//
//
//		ElemAve(a[n]);
//		n++;
//	}
	return n;

}

//展示学生信息
//若有均分则展示，无均分则不展示
void ElemDisplay(ElemType &e) {
	wprintf(L"学号：%d\t姓名：%s\t成绩：\t高数 %.1f、\t线代 %.1f、\t英语 %.1f、\t体育 %.1f", e.ID, e.name, e.gaoshu, e.xiandai, e.yingyu, e.tiyu);
	if (e.ave_score) {
		wprintf(L"、\t均分 %.1f", e.ave_score);

	}
	wprintf(L"\n");
}

void ElemAve(ElemType &e) {
	e.ave_score = (e.gaoshu + e.xiandai + e.yingyu + e.tiyu) / 4;
}


LinkNode* LinkSort(LinkNode *&L) {
	if (L == NULL || L->next == NULL || L->next->next == NULL) {
		return L;
	}
	LinkNode *r = L->next,*rnext = r->next;
	LinkNode *head = (LinkNode*)malloc(sizeof(LinkNode));
	head->next = NULL;

	LinkNode *pre = head,*p = head->next;
	ElemAve(r->data);
	head->next = r;											//添加L的第一个节点

	while (r != NULL) {
		rnext = r->next;

		pre = head;
		p = head->next;

		while (r->data.ave_score < p->data.ave_score && p != NULL) {
			pre = p;
			p = p->next;
		}
		r->next = p;
		pre->next = r;

		r = rnext;
	}
	free(L);
	L = head;
	return head;

}


void TxtWrite(FILE* T, LinkNode *&L) {
	fclose(T);
	T = fopen("student.txt", "w");
	if (T == NULL) {
		printf("文件打开失败\n");
		return;
	}
	LinkNode* p = L->next;
	while (p != NULL) {
		fprintf(T, "%d,%s,%.1f,%.1f,%.1f,%.1f\n",
		        p->data.ID, p->data.name,
		        p->data.gaoshu, p->data.xiandai,
		        p->data.yingyu, p->data.tiyu);
		p = p->next;
	}
	printf("成功保存 %d 条记录到文件\n", 8); // 简单统计
	fclose(T);
}





