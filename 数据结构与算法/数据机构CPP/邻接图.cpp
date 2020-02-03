#include<iostream>
#include<stdlib.h>
#define MaxVertexNum 100
using namespace std;
typedef struct GNode* PtrToGNode;
typedef PtrToGNode MGraph;//以邻接矩阵存储的图类型
typedef int Vertex;//用顶点下标表示顶点，为整型
typedef struct ENode* PtrToENode;
typedef PtrToENode Edge;
struct ENode {
	Vertex V1, V2;//有向边<V1,V2>
	int Weight;//权重
};
struct GNode
{
	int Nv;//顶点数
	int Ne;//边数
	int G[MaxVertexNum][MaxVertexNum];
	int Data[MaxVertexNum];//存顶点的数据
};
MGraph CreateGraph(int VertexNum) {
	MGraph Graph;
	Graph = new GNode;
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	Vertex V = 0, W = 0;
	for (V = 0; V < Graph->Nv; V++) {
		for (W = 0; W < Graph->Nv; W++) {
			Graph->G[V][W] = 0;
		}
	}
	return Graph;
}
void InsertEdge(MGraph Graph, Edge E) {
	Graph->G[E->V1][E->V2] = E->Weight;
	//若是无向图，还要插入<V2,V1>
	Graph->G[E->V2][E->V1] = E->Weight;
}
MGraph BuildGraph() {
	MGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;
	cin >> Nv;
	Graph = CreateGraph(Nv);
	cin >> Graph->Ne;
	if (Graph->Ne != 0) {
		E = new ENode;
		for (i = 0; i < Graph->Ne; i++) {
			cin >> E->V1 >> E->V2 >> E->Weight;
			InsertEdge(Graph, E);
		}
	}
	for (V = 0; V < Graph->Nv; V++) {
		cin >> Graph->Data[V];
	}
	return Graph;
}
void EasyBuild() {
	int i, j, v1, v2, w, Nv, Ne;
	cin >> Nv;
	int G[100][100];
	for (i = 0; i < Nv; i++) {
		for (j = 0; j < Nv; j++) {
			G[i][j] = 0;
		}
	}
	cin >> Ne;
	for (i = 0; i < Ne; i++) {
		cin >> v1 >> v2 >> w;
		G[v1][v2] = w;
		G[v2][v1] = w;
	}
}
int main() {
	MGraph Graph = BuildGraph();
	return 0;
}