
//  HuffTree
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct HfTreeNode *HfTree;
typedef struct HNode *Heap;
struct HNode    {
    HfTree *Data;
    int Size;
    int Capacity;
};
struct HfTreeNode   {
    char ch;
    int weight;
    HfTree Left;
    HfTree Right;
};

void PrintCode(HfTree root,int *arr,int top);
void PrintArr(int *arr,int top);

HfTree DeleteMin( Heap H );
Heap CreateHeap(int size);
void Adjust(Heap H, int p);
void BuildHeap(Heap H);


Heap Read(void);


HfTree Huffman(Heap heap);
int main(int argc, const char * argv[]) {
    int arr[100]={0},top=0;
    HfTree Root;
    Heap heap;
    heap=Read();
    Root=Huffman(heap);
    PrintCode(Root, arr, top);
    return 0;
    }
Heap Read(void)  {
    int num=0,dataNum=1;
    int frequency[58]={0};//用于统计次数的数组
    Heap heap;

    char c;
    while((c=getchar())!='\n')  {
        frequency[c-65]++;
    }
    for (int i=0; i<58; i++) {
        if(frequency[i]!=0)
            num++;
    }//找出输入的有效字母数量

    heap=CreateHeap(num);//建堆

    for (int i=0; i<58; i++) {
        //找到有效字母
        if(frequency[i]!=0) {
            //放入节点的过程
            HfTree p=(HfTree)malloc(sizeof(struct HfTreeNode));
            p->Left=NULL;
            p->Right=NULL;
            p->weight=frequency[i];
            p->ch=i+65;
            heap->Data[dataNum++]=p;
            heap->Size++;
        }
    }
    return heap;
}
Heap CreateHeap(int MaxSize)   {
    HfTree p=(HfTree)malloc(sizeof(struct HfTreeNode));
    p->Left=NULL;
    p->Right=NULL;
    p->weight=-1;
    /*
     设置哨兵
     */
    Heap H = (Heap)malloc(sizeof(struct HNode));
    H->Data = (HfTree *)malloc((MaxSize+1)*sizeof(struct HfTreeNode));//data存储的是指向HfTree的指针
    H->Size = 0;//初始化堆的大小为0
    H->Capacity = MaxSize;//设定堆的容量
    /*
     将除data的指针全设为NULL
     */
    for(int i=0;i<=MaxSize;i++)
        H->Data[i]=NULL;
    H->Data[0]=p;//设置哨兵
    return H;
}



void Insert( Heap H, HfTree X ) {
    int i=++H->Size;
    for (; H->Data[i/2]->weight>X->weight; i/=2 )
        H->Data[i] = H->Data[i/2];
    H->Data[i] = X;
}
HfTree Huffman(Heap heap)   {
    BuildHeap(heap);
    HfTree p;
    for (int i=1; i<heap->Capacity; i++) {
        p=(HfTree)malloc(sizeof(struct HfTreeNode));
        p->Left=DeleteMin(heap);
        p->Right=DeleteMin(heap);
        p->weight=p->Left->weight+p->Right->weight;
        Insert(heap, p);
    }
    p=DeleteMin(heap);
    return p;
}
void Adjust(Heap H, int p)    {
    int Parent, Child;
    HfTree X;
    X = H->Data[p];
    for( Parent=p; Parent*2<=H->Size; Parent=Child ) {
        Child = Parent * 2;
        if( (Child!=H->Size) && (H->Data[Child]->weight>H->Data[Child+1]->weight) )
            Child++;
        if( X->weight <= H->Data[Child]->weight ) break;
        else
            H->Data[Parent]= H->Data[Child];
    }
    H->Data[Parent] = X;
}
void BuildHeap( Heap H )    {
    /*
     从最后一个节点的父节点开始将一个子单元调整成堆，不断循环直到所有都调成堆
     */
    for(int i = H->Size/2; i>0; i-- )
        Adjust(H, i);
}
HfTree DeleteMin(Heap H)  {
    int Parent, Child;
    HfTree MinItem, X;
    MinItem = H->Data[1];
    X = H->Data[H->Size--];
    for( Parent=1; Parent*2<=H->Size; Parent=Child ) {
        Child = Parent * 2;
        if( (Child!=H->Size) && (H->Data[Child]->weight>H->Data[Child+1]->weight) )
            Child++;
        if( X->weight <= H->Data[Child]->weight ) break;
        else
            H->Data[Parent]= H->Data[Child];
    }
    H->Data[Parent] = X;

    return MinItem;
}



void PrintCode(HfTree tree,int *arr,int top)    {
    if (tree->Left) {
        arr[top] = 0;
        PrintCode(tree->Left, arr, top + 1);
    }
    if (tree->Right) {
        arr[top] = 1;
        PrintCode(tree->Right, arr ,top + 1);
    }
    // 如果是叶节点就打印
    if (tree->Left==NULL&&tree->Right==NULL) {
        printf("%c:", tree->ch);
        PrintArr(arr, top);
    }
}
void PrintArr(int *arr,int top) {
    for (int i = 0; i < top; ++i)
        printf("%d", arr[i]);
    printf("\n");
}
