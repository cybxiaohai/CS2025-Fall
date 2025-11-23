/*
/*本次作业起，增加如下规定：

1. 自己写的函数的所有形参都必须包含学号的最后两位，假如学号为24010012，则定义为fun1（int a12mn,char bk12[10],……）,形参中要包含该同学的学号最后两位12

2. 假如运行结果中有输出字符串的语句，也要包含学号的最后两位，printf（“hello12”）;

3. 从本章作业开始，可以随意调用任何函数。

4.从本章作业开始，不再写实验报告，提交内容为cpp文件和运行结果截图


作业内容

编写算法实现串的置换操作Replace( S, T, R), 即将串S中所有与串T相等的子串置换为串R。
*/
/*陈怡冰 24012022*/

#include <stdio.h>
#define MaxSize 100

typedef struct {
	char data[MaxSize];
	int length;			//串长
} SqString;

//顺序串基本操作
void StrAssign(SqString &s, char cstr[]) {	//字符串常量赋给串s
	int i;
	for (i = 0; cstr[i] != '\0'; i++)
		s.data[i] = cstr[i];
	s.length = i;
}

void StrCopy(SqString &s, SqString t) {	//串复制
	int i;
	for (i = 0; i < t.length; i++)
		s.data[i] = t.data[i];
	s.length = t.length;
}

bool StrEqual(SqString s, SqString t) {	//判断串相等
	bool same = true;
	int i;
	if (s.length != t.length)				//长度不相等时返回0
		same = false;
	else
		for (i = 0; i < s.length; i++)
			if (s.data[i] != t.data[i]) {	//有一个对应字符不同时返回0
				same = false;
				break;
			}
	return same;
}

int StrLength(SqString s) {	//求串长
	return s.length;
}

SqString Concat(SqString s, SqString t) {	//串连接
	SqString str;
	int i;
	str.length = s.length + t.length;
	for (i = 0; i < s.length; i++)	//将s.data[0..s.length-1]复制到str
		str.data[i] = s.data[i];
	for (i = 0; i < t.length; i++)	//将t.data[0..t.length-1]复制到str
		str.data[s.length + i] = t.data[i];
	return str;
}

SqString SubStr(SqString s, int i22, int j22) {	//求子串
	SqString str;
	int k;
	str.length = 0;
	if (i22 <= 0 || i22 > s.length || j22 < 0 || i22 + j22 - 1 > s.length)
		return str;					//参数不正确时返回空串
	for (k = i22 - 1; k < i22 + j22 - 1; k++)  		//将s.data[i..i+j]复制到str
		str.data[k - i22 + 1] = s.data[k];
	str.length = j22;
	return str;
}

void DispStr(SqString s) {	//输出串s
	int i;
	if (s.length > 0) {
		for (i = 0; i < s.length; i++)
			printf("%c", s.data[i]);
		printf("\n");
	}
}

//BF算法查找子串位置
int BFIndex(SqString s22, SqString t22) {
	int i22 = 0, j22 = 0;
	while (i22 < s22.length && j22 < t22.length) {
		if (s22.data[i22] == t22.data[j22]) {	//继续匹配下一个字符
			i22++;				//主串和子串依次匹配下一个字符
			j22++;
		} else {        			//主串、子串指针回溯重新开始下一次匹配
			i22 = i22 - j22 + 1;		//主串从下一个位置开始匹配
			j22 = 0; 				//子串从头开始匹配
		}
	}
	if (j22 >= t22.length)
		return (i22 - t22.length);  	//返回匹配的第一个字符的下标
	else
		return (-1);        		//模式匹配不成功
}

//串替换函数
SqString Replace(SqString S22, SqString T22, SqString R22) {
	SqString result22;
	result22.length = 0; // 初始化结果串为空

	if (T22.length == 0) {
		// 如果目标串为空，直接返回原串
		StrCopy(result22, S22);
		return result22;
	}

	int i22 = 0;
	while (i22 < S22.length) {
		// 查找从当前位置开始的子串是否匹配T22
		bool match22 = true;
		if (i22 + T22.length > S22.length) {
			match22 = false;
		} else {
			for (int j22 = 0; j22 < T22.length; j22++) {
				if (S22.data[i22 + j22] != T22.data[j22]) {
					match22 = false;
					break;
				}
			}
		}

		if (match22) {
			// 匹配成功，将R22添加到结果中
			for (int k22 = 0; k22 < R22.length; k22++) {
				if (result22.length < MaxSize) {
					result22.data[result22.length++] = R22.data[k22];
				}
			}
			i22 += T22.length; // 跳过T22的长度
		} else {
			// 不匹配，将当前字符添加到结果中
			if (result22.length < MaxSize) {
				result22.data[result22.length++] = S22.data[i22++];
			}
		}
	}
	return result22;
}

int main() {
	SqString S22, T22, R22, result22;

	printf("=== 串替换操作演示22 ===\n");

	// 测试用例1
	StrAssign(S22, "ababcabcacbab22");
	StrAssign(T22, "abc");
	StrAssign(R22, "XYZ22");

	printf("测试用例122:\n");
	printf("原始串S22: ");
	DispStr(S22);
	printf("目标串T22: ");
	DispStr(T22);
	printf("替换串R22: ");
	DispStr(R22);

	result22 = Replace(S22, T22, R22);
	printf("替换结果22: ");
	DispStr(result22);
	printf("\n");

	// 测试用例2
	StrAssign(S22, "hello world hello22");
	StrAssign(T22, "hello");
	StrAssign(R22, "hi22");

	printf("测试用例222:\n");
	printf("原始串S22: ");
	DispStr(S22);
	printf("目标串T22: ");
	DispStr(T22);
	printf("替换串R22: ");
	DispStr(R22);

	result22 = Replace(S22, T22, R22);
	printf("替换结果22: ");
	DispStr(result22);
	printf("\n");

	// 测试用例3 - 没有匹配的情况
	StrAssign(S22, "abcdefg22");
	StrAssign(T22, "xyz");
	StrAssign(R22, "12322");

	printf("测试用例322:\n");
	printf("原始串S22: ");
	DispStr(S22);
	printf("目标串T22: ");
	DispStr(T22);
	printf("替换串R22: ");
	DispStr(R22);

	result22 = Replace(S22, T22, R22);
	printf("替换结果22: ");
	DispStr(result22);

	return 0;
}
