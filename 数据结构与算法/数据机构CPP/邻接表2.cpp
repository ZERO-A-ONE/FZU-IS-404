#include <iostream>
using namespace std;

#define MAXVERTEX 100   //最大顶点数
typedef char vertextype;    //定义顶点的存储类型
typedef int arctype;    //定义边的权值类型

typedef struct ArcNode  //边表节点
{
    int adjvex; //邻接点域，存储该顶点对应的下标
    arctype wigth;  //用于存储权值
    struct ArcNode* next; //链域，指向下一个邻接点
}ArcNode;

typedef struct VertexNode   //顶点表节点
{
    vertextype data;    //存储顶点数据的信息
    ArcNode* firstarc;  //边表头指针
}VertexNode, AdjList[MAXVERTEX];

typedef struct
{
    AdjList adjlist;    //定义邻接表
    int numvertex;  //当前邻接表的顶点数
    int numarc; //当前邻接表的边数
}GraphAdjList;

//建立图的邻接表
void CreateAdjListGraph(GraphAdjList& G)
{
    ArcNode* e;
    cin >> G.numvertex; //输入当前图的顶点数
    cin >> G.numarc;    //输入当前图的边数
    for (int i = 0; i < G.numvertex; i++)    //建立顶点表
    {
        cin >> G.adjlist[i].data;   //输入顶点信息
        G.adjlist[i].firstarc = NULL;   //将表边指针置为空
    }
    for (int k = 0; k < G.numarc; k++)
    {
        int i, j, w;
        cin >> i >> j >> w; //输入边两边的顶点和边上的权重
        e = new ArcNode;   //创建一个表边节点指针
        e->adjvex = j;
        e->wigth = w;
        e->next = G.adjlist[i].firstarc;
        G.adjlist[i].firstarc = e;
        //因为是无向图，彼此相对称
        e = new ArcNode;   //创建一个表边节点指针
        e->adjvex = i;
        e->wigth = w;
        e->next = G.adjlist[j].firstarc;
        G.adjlist[j].firstarc = e;
    }
}

//打印邻接表
void PrintfGraphAdjList(GraphAdjList G)
{
    for (int i = 0; i < G.numvertex; i++)
    {
        ArcNode* p = G.adjlist[i].firstarc;
        cout << G.adjlist[i].data << '\t';
        while (p)
        {
            cout << p->adjvex << ' ' << p->wigth << '\t';
            p = p->next;
        }
        cout << endl;
    }
}
int main()
{
    GraphAdjList G;
    CreateAdjListGraph(G);
    PrintfGraphAdjList(G);
    return 0;
}