#include<iostream>
#include<stdlib.h>
#define MaxVertexNum 100
using namespace std;
typedef int Vertex;
typedef int Vertextype;
typedef struct AdjList adjlist;

typedef struct ENode* PtrToENode;
typedef PtrToENode Edge;
struct ENode {
	Vertex V1, V2;//有向边<V1,V2>
	int Weight;//权重
};

//边表节点
typedef struct AdjVNode* PtrToAdjVNode;
struct AdjVNode {
	Vertex AdjV;/* 邻接点下标*/
	int Weight;  /* 边权重*/
	PtrToAdjVNode Next;
};
//顶点表节点
typedef struct Vnode {
	PtrToAdjVNode FirstEdge;
	int Data;/* 存顶点的数据*/
};

typedef struct GNode* PtrToGNode;
struct GNode {
	int Nv;    /* 顶点数*/
	int Ne;    /* 边数*/
	Vnode G[MaxVertexNum]; /* AdjList是邻接表类型,定义邻接表*/
};
typedef PtrToGNode LGraph;


LGraph CreateGraph(int VertexNum) {
	Vertex V, W;
	LGraph Graph;
	Graph = (LGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	/* 注意：这里默认顶点编号从0开始，到(Graph->Nv-1) */
	for (V = 0; V < Graph->Nv; V++)
		Graph->G[V].FirstEdge = NULL;
	return Graph;
}
void InsertEdge(LGraph Graph, Edge E) {
	PtrToAdjVNode NewNode;
	/***************** 插入边<V1, V2> ****************/
	/* 为V2建立新的邻接点*/
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V2;
	NewNode->Weight = E->Weight;
	/* 将V2插入V1的表头*/
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;
	/********** 若是无向图，还要插入边<V2, V1> **********/
	/* 为V1建立新的邻接点*/
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V1; NewNode->Weight = E->Weight;
	/* 将V1插入V2的表头*/
	NewNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V2].FirstEdge = NewNode;
}
LGraph BuildGraph() {
	LGraph Graph;
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
		cin >> Graph->G->Data;
	}
	return Graph;
}
int main() {
	return 0;
}