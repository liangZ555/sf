#include<stdio.h>

#define MaxSize 10

void Print(int(*m)[MaxSize], int n)
{
	for (int i = 1; i <= n; i++)
	{
		printf("%d\t", i);
	}
	for (int i = 1; i <= n; i++)
	{
		printf("\n%d：", i);
		for (int j = 1; j <= n; j++)
		{
			printf("%d\t", m[i][j]);
		}
	}
	printf("\n");
}


void MatrixChain(int n, int *p, int (*m)[MaxSize], int (*s)[MaxSize])
{
	for (int r = 2; r <= n; r++)
	{
		for (int i = 1; i <= n - r + 1; i++)
		{
			int j = i + r - 1;
			m[i][j] = m[i + 1][j] + p[i - 1] * p[i] * p[j];
			s[i][j] = i;
			for (int k = i + 1; k < j; k++)
			{
				int t = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (t < m[i][j])
				{
					m[i][j] = t;
					s[i][j] = k;
				}
			}
		}
	}
}

void TraceBack(int(*s)[MaxSize], int i, int j)
{
	if (i == j)
	{
	}
	else
	{
		TraceBack(s, i, s[i][j]);
		TraceBack(s, s[i][j] + 1, j);
		printf("Multiply (A%d and A%d)，断开位置是:%d\n",i, j,s[i][j]);
	}
	return;
}

int main()
{
	int start = 0, end = 0;
	int p[] = {30,35,15,5,10,20,25};
	int m[MaxSize][MaxSize] = {};
	int s[MaxSize][MaxSize] = {};
	int n = sizeof(p) / sizeof(p[0])-1;
	MatrixChain(n ,p, m, s);
	printf("打印m数组:\n   ");
	Print(m, n);
	printf("打印s数组:\n   ");
	Print(s, n);

	printf("请输入矩阵连乘的起始位置和终止位置：");
	scanf("%d %d",&start,&end);
	printf("矩阵连乘从%d开始，到%d结束：\n",start,end);
	TraceBack(s, start, end);

	return 0;

}
