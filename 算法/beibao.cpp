#include <iostream>

#include <algorithm>

using namespace std;

 

const int maxNumber=1000000;

 

class Edge

{

public:

int weight;

int v1,v2;

};

 

bool cmp(Edge e1,Edge e2)

{

return e1.weight<e2.weight;

}

 

int Graph[30][30];

Edge edgeArr[900];

int countVertex[900];

int bestEdgeIndex[900];

int edgeNum;

int n;

 

void TravelMan(int k,int currCost,int &bestCost,int chosenEdgeNum,int* edgeIndex)//第k条边

{

if(k>=edgeNum)return;

if((edgeNum-k)<(n-chosenEdgeNum))return;

if(edgeArr[k].weight+currCost>bestCost)return;

 

while( (countVertex[edgeArr[k].v1]>1||countVertex[edgeArr[k].v2]>1) )

{

k++;

if( k==edgeNum || (edgeArr[k].weight+currCost>bestCost) )return;

}

 

TravelMan(k+1,currCost,bestCost,chosenEdgeNum,edgeIndex);

 

currCost+=edgeArr[k].weight;

countVertex[edgeArr[k].v1]++;

countVertex[edgeArr[k].v2]++;

edgeIndex[chosenEdgeNum]=k;

chosenEdgeNum++;

if(chosenEdgeNum==n)

{

if(currCost<bestCost)

{

bestCost=currCost;

for(int i=0;i<chosenEdgeNum;i++)

bestEdgeIndex[i]=edgeIndex[i];

}

countVertex[edgeArr[k].v1]--;

   countVertex[edgeArr[k].v2]--;

return;

}

 

TravelMan(k+1,currCost,bestCost,chosenEdgeNum,edgeIndex);

 

countVertex[edgeArr[k].v1]--;

countVertex[edgeArr[k].v2]--;

 

return ;

}

 

 

int main()

{

cin>>n;

for(int i=0;i<n;i++)

{

for(int j=0;j<n;j++)

cin>>Graph[i][j];

}

 

edgeNum=0;

for(int i=0;i<n;i++)

{

countVertex[i]=0;

for(int j=i+1;j<n;j++)

{

edgeArr[edgeNum].v1=i;

edgeArr[edgeNum].v2=j;

edgeArr[edgeNum].weight=Graph[i][j];

bestEdgeIndex[edgeNum]=-1;//入选哈夫谩回路的边的序号

edgeNum++;

}

}

 

sort(edgeArr,edgeArr+edgeNum,cmp);

 

int bestCost=maxNumber;

int edgeIndex[1000];

TravelMan(0,0,bestCost,0,edgeIndex);

 

cout<<"The min cost is:"<<bestCost<<endl;

for(int i=0;i<n;i++)

{

cout<<edgeArr[bestEdgeIndex[i]].v1<<" "<<edgeArr[bestEdgeIndex[i]].v2<<endl;

}

return 0;