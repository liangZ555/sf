#include<stdio.h>
#define  V 100
int f[10][V];//ȫ�ֱ������Զ���ʼ��Ϊ0
int weight[10];
int value[10];
#define  max(x,y)   (x)>(y)?(x):(y)
int main()
{
    //��ʼ��
    int N,M;
    freopen("1.txt","r",stdin);
    scanf("%d%d",&N,&M);//N��Ʒ���� M��������
    for (int i=1;i<=N; i++)
    {
        scanf("%d%d",&weight[i],&value[i]);
    }
    //��̬�滮����
    for (int i=1; i<=N; i++)
        for (int j=1; j<=M; j++)
        {
            if (weight[i]<=j)
            {
                f[i][j]=max(f[i-1][j],f[i-1][j-weight[i]]+value[i]);
            }
            else
                f[i][j]=f[i-1][j];
        }
      printf("%d\n",f[N][M]);//������Ž�

     //���ѡ�����Ʒ
    int j = M;
    int x[V];
    for(int i=N; i>0; --i)
    {
        if(f[i][j] > f[i-1][j])
        {
            x[i-1] = 1;
            j = j - weight[i-1];//װ���i-1����ʯ�󱳰���װ��������ֻʣ��j - V[i-1]
        }
    }
    for(int i=0; i<N; ++i)
        printf("%d ", x[i]);

}
