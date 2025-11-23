//¡¾Àı5.1¡¿µÄËã·¨£ºÇón!µÄµİ¹éËã·¨
#include <stdio.h>
int fact(int n)					//Ö±½Óµİ¹éº¯Êı 
{
	if (n==1) 					//Óï¾ä1
		return 1;				//Óï¾ä2
	else 						//Óï¾ä3
		return fact(n-1)*n;		//Óï¾ä4
}
int fact1(int n,int ans)		//Î²µİ¹éº¯Êı
{
    if(n==1)
        return ans;
    else
        return fact1(n-1,n*ans);
}

int main()
{
	printf("5!=%d\n",fact(5));
	printf("5!=%d\n",fact1(5,1));
	return 1;
}

