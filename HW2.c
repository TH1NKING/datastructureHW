#include <stdio.h>
#include <stdlib.h>

#define MAXVEX 100 // 最大顶点数
#define OK 1
#define ERROR 0

typedef int Status;

// 边表结点
typedef struct EdgeNode {
    int adjvex; // 邻接点域
    struct EdgeNode *next; // 指向下一个邻接点
} EdgeNode;

// 顶点表结点
typedef struct VertexNode {
    char data; // 顶点信息
    EdgeNode *firstarc; // 指向第一个邻接点
} VertexNode, AdjList[MAXVEX];

// 图的邻接表结构
typedef struct {
    AdjList adjList;
    int numVertexes, numEdges; // 图的当前顶点数和边数
} GraphAdjList;

// 初始化栈结构
typedef struct {
    int data[MAXVEX];
    int top;
} Stack;

// 初始化栈
void InitStack(Stack *S) {
    S->top = -1;
}

// 判断栈是否为空
int StackEmpty(Stack *S) {
    return S->top == -1;
}

// 进栈
void Push(Stack *S, int elem) {
    S->data[++S->top] = elem;
}

// 出栈
void Pop(Stack *S, int *elem) {
    *elem = S->data[S->top--];
}

// 创建有向图的邻接表
void CreateGraph(GraphAdjList *G) {
    int i, j, k;
    EdgeNode *e;

    printf("请输入顶点数和边数（格式：顶点数 边数）：\n");
    scanf("%d %d", &G->numVertexes, &G->numEdges);

    getchar(); // 清空缓冲区

    // 输入顶点信息
    printf("请输入顶点信息（如A B C...）：\n");
    for (i = 0; i < G->numVertexes; i++) {
        scanf("%c", &G->adjList[i].data);
        G->adjList[i].firstarc = NULL;
        getchar(); // 清空缓冲区
    }

    // 输入边信息
    printf("请输入边的信息（格式：起点 终点）：\n");
    for (k = 0; k < G->numEdges; k++) {
        scanf("%d %d", &i, &j); // 输入起点和终点
        e = (EdgeNode *)malloc(sizeof(EdgeNode));
        e->adjvex = j;
        e->next = G->adjList[i].firstarc;
        G->adjList[i].firstarc = e;
    }
}

// 计算各顶点的入度
void FindInDegree(GraphAdjList G, int *indegree) {
    int i;
    EdgeNode *p;

    for (i = 0; i < G.numVertexes; i++) {
        indegree[i] = 0;
    }

    for (i = 0; i < G.numVertexes; i++) {
        p = G.adjList[i].firstarc;
        while (p) {
            indegree[p->adjvex]++;
            p = p->next;
        }
    }
}

// 拓扑排序
Status TopologicalSort(GraphAdjList G) {
    Stack S;
    int indegree[MAXVEX];
    int count = 0;
    int i, k;
    EdgeNode *p;

    // 计算入度
    FindInDegree(G, indegree);

    // 初始化栈
    InitStack(&S);

    // 将所有入度为0的顶点入栈
    for (i = 0; i < G.numVertexes; i++) {
        if (indegree[i] == 0) {
            Push(&S, i);
        }
    }

    printf("拓扑排序结果：\n");
    while (!StackEmpty(&S)) {
        Pop(&S, &i);
        printf("%c ", G.adjList[i].data);
        count++;

        // 对该顶点的每个邻接点入度减1
        for (p = G.adjList[i].firstarc; p; p = p->next) {
            k = p->adjvex;
            if (--indegree[k] == 0) {
                Push(&S, k);
            }
        }
    }
    printf("\n");

    // 判断是否有环
    if (count < G.numVertexes) {
        return ERROR; // 有环
    } else {
        return OK; // 无环
    }
}

int main() {
    GraphAdjList G;

    CreateGraph(&G);

    if (TopologicalSort(G) == ERROR) {
        printf("该有向图中存在环，无法进行拓扑排序。\n");
    } else {
        printf("拓扑排序完成。\n");
    }

    return 0;
}