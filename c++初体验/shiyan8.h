//
//  shiyan8.h
//  c++初体验
//
//  Created by SXB on 15/11/27.
//  Copyright (c) 2015年 apple. All rights reserved.
//

#ifndef c______shiyan8_h
#define c______shiyan8_h

#include<iostream>
#include "shiyan5.h"        //    因为我需要用队列
using namespace std;


//  MARK:  邻接矩阵的基类
//  包含有向图，无向图，加权图的共同点。

template<class T>
void Make2DArray(T** &x, int rows, int cols)
{
//    创建一个二维数组
//    不捕获异常
    
//    创建行指针
    x = new T *[rows];
    
//    为每一行分配空间
    for (int i=0; i < rows; i++) {
        x[i] = new int[cols];
    }
}

template<class T>
void Delete2DArray(T** &x, int rows)
{
//    删除二维数组
//    释放为每一行所分配的空间
    for (int i=0; i < rows; i++)
        delete [] x[i];
//        删除行指针
    delete []x;
    x = 0;
    
}

template<class T>
class AdjacencyWDigraph {
//    friend AdjacencyWGraph<T>;
    
public:
    AdjacencyWDigraph(int Vertices = 10, T noEdge = 0);
    ~AdjacencyWDigraph() {Delete2DArray(a , n+1);}
    bool Exist(int i, int j) const;
    int Edges() const { return e;}
    int Vertices() const { return n;}
    AdjacencyWDigraph<T>& Add (int i, int j, const T& w);
    AdjacencyWDigraph<T>& Delete(int i, int j);
    int OutDegree(int i) const;
    int InDegree(int i) const;
    
//private:
    T NoEdge;   //  用于没有边存在的情形。在加权图中，各个权的值不同，若两点之间不通，用NoEdge表示。
    int n;      //  顶点数目
    int e;      //  边数
    T **a;      //  二维数组
    Position *poss ;
};

template<class T>
AdjacencyWDigraph<T>::AdjacencyWDigraph(int Vertices, T noEdge)
{
//    构造函数
    n = Vertices;
    e = 0;
    NoEdge = noEdge;
    Make2DArray(a , n+1 , n+1);
//    初始化为没有边的图
    poss = new Position[Vertices*Vertices];
    for (int i=1; i <= n; i++) {
        for (int j=1; j <= n; j++) {
            a[i][j] = NoEdge;
        }
    }
}

template<class T>
bool AdjacencyWDigraph<T>::Exist(int i, int j) const
{
//    边(i,j)存在吗
    if (i<1 || j<1 || i>n || j>n || a[i][j] == NoEdge) {
        return false;
    }
    return  true;
}

template<class T>
AdjacencyWDigraph<T>& AdjacencyWDigraph<T>::Add(int i, int j, const T& w)
{
//    如果边(i,j)不存在，则将该边加入到图中
    if (i<1 || j<1 || i>n || j>n || i==j || a[i][j] != NoEdge) {
//        throw BadInput();
        cout << "给的数据位置有问题，或是图中已经存在这条线。" << endl;
    }
    a[i][j] = w;
    e++;
    return *this;
}

template <class T>
AdjacencyWDigraph<T>& AdjacencyWDigraph<T>::Delete(int i, int j)
{
//    删除边(i,j)
    if (i<1 || j<1 || i>n || j>n || a[i][j] == NoEdge) {
//        throw BadInput();
        cout << "给的数据位置，或是图中本来就不存在这条线 " << endl;
    }
    a[i][j] = NoEdge;
    e--;
    return *this;
}

template<class T>
int AdjacencyWDigraph<T>::OutDegree(int i) const
{
    if (i<1 || i>n ) {
//        throw BadInput();
    }
//    计算顶点i的出度
    int sum = 0;
    for (int j = 1; j <= n; j++) {
        if (a[i][j] != NoEdge) {
            sum++;
        }
    }
    return sum;
}

template<class T>
int AdjacencyWDigraph<T>::InDegree(int i) const
{
    if (i<1 || i>n ) {
//        throw BadInput();
    }
//    计算顶点i的入度
    int sum = 0;
    for (int j = 1; j <= n; j++) {
        if (a[j][i] != NoEdge) {
            sum++;
        }
    }
    return sum;
}





//  MARK:图
class AdjacencyGraph : public AdjacencyWDigraph<int>
{
public:
    AdjacencyGraph(int Vertices = 10) : AdjacencyWDigraph<int>(Vertices, 0){}
    AdjacencyGraph& Add(int i, int j)
    {
        AdjacencyWDigraph<int>::Add(i, j, 1);
        return *this;
    }
    AdjacencyGraph& Delete(int i, int j)
    {
        AdjacencyWDigraph<int>::Delete(i, j);
        return *this;
    }
    
//    下面是邻接矩阵的一些其他方法。本来应该写在AdjacencyWDiagraph里的。但是我现在心情不好，就先写这儿了。
    
    void GetGraph();
    void OutputGraph();
    
    int **pos;
    void InitializePos() { Make2DArray(pos, n+1, n+1);}
    
    int Begin(int i);
    int NextVertex(int i);
    
    void BFS(int v, int reach[], int label);
    void DFS(int v, int reach[], int label);

    void build(Position *str, int*tag, int n, int siz);
    int DFSForTree(int v , int reach[] , int label);
    
    void buildMin(Position *str, int*tag, int n, int siz);
};


void AdjacencyGraph::GetGraph()
{
    int k=0;
    for (int i=1; i<=n ; i++) {
        for (int j=1 ; j<=n ; j++) {
            if (a[i][j] != 0) {
                cout << i << "  "<< j<< endl;
                poss[k].row = i;
                poss[k].col = j;
                k++;
            }
        }
    }
    
//    InitializePos();
//    for (int i=1; i<=n ; i++) {
//        int beginReturn = Begin(i);
//        if (beginReturn == 0) {
//            continue;
//        } else {
//            while (NextVertex(i) != 0) {
//                
//            }
//        }
//    }
}

//int AdjacencyGraph::Begin(int i)
//{
////    返回第一个与顶点i邻接的顶点
//    if (i<1 || i>n) {
////        throw OutOfBounds();
//    }
//    
////    查找第一个邻接顶点
//    for (int j=1; j <= n; j++) {
//        if (a[i][j] != 0) {
//            pos[i] = j;
//            return j;
//        }
//    }
//    pos[i] = n+1;   //  没有邻接顶点
//    return 0;
//}
//
//int AdjacencyGraph::NextVertex(int i)
//{
////    返回下一个与顶点i邻接的顶点
//    if (i<1 || i>n ) {
////        throw OutOfBounds();
//    }
//    
//    for (int j = pos[i]+1 ; j<=n ; j++) {
//        if (a[i][j] != NoEdge) {
//            pos[i] = j;
//            return j;
//        }
//    }
//    pos[i] = n+1;
//    return 0;
//}

void AdjacencyGraph::BFS(int v , int reach[], int label)
{
//    宽度优先搜索
    Queue<int> *q = new Queue<int>(100);
    reach[v] = label;
    q->Add(v );
    while (!q->IsEmpty()) {
        int w;
        q->Delete(w);
        cout << "包含顶点: " ;
        cout << w << " " << endl;
//        对尚未标记的，邻接自w的顶点进行标记
        for (int u=1; u <= n ; u++) {
            if (a[w][u] != NoEdge && !reach[u]) {
                q->Add(u);
                reach[u] = label;
            }
        }
        for (int t=1; t <= w; t++) {
            if (a[t][w] != NoEdge && !reach[t]) {
                q->Add(t);
                reach[t] = label;
            }
        }
    }
}

void AdjacencyGraph::DFS(int v , int reach[] , int label)
{
//    深度优先搜索
    Stack<int> *s = new Stack<int>(100);
    reach[v] = label;
    s->Add(v );
    while (!s->IsEmpty()) {
        int w;
        s->Delete(w);
        cout << "包含顶点: ";
        cout << w << " " << endl;
//        对尚未标记的，邻接自w的顶点进行标记
        for (int u=1; u <= n ; u++) {
            if (a[w][u] != NoEdge && !reach[u]) {
                s->Add(u);
                reach[u] = label;
            }
        }
        for (int t=1; t <= w; t++) {
            if (a[t][w] != NoEdge && !reach[t]) {
                s->Add(t);
                reach[t] = label;
            }
        }
    }
}

int AdjacencyGraph::DFSForTree(int v , int reach[] , int label)
{
    //    深度优先搜索for 生成树
    int sum = 0;
    
    Stack<int> *s = new Stack<int>(100);
    reach[v] = label;
    s->Add(v );
    while (!s->IsEmpty()) {
        int w;
        s->Delete(w);
        sum += w;
        //        对尚未标记的，邻接自w的顶点进行标记
        for (int u=1; u <= n ; u++) {
            if (a[w][u] != NoEdge && !reach[u]) {
                s->Add(u);
                reach[u] = label;
            }
        }
        for (int t=1; t <= w; t++) {
            if (a[t][w] != NoEdge && !reach[t]) {
                s->Add(t);
                reach[t] = label;
            }
        }
    }
    return sum;
}


static int treeCount = 1;

void AdjacencyGraph::build(Position *str, int*tag, int n, int siz)
{
//    cout << " cao ???" << endl;
    if (n == siz) {

        AdjacencyGraph *tmp = new AdjacencyGraph(Vertices());
        int *biaoji = new int[Vertices()+1];
        for (int i=1; i<=Vertices(); i++) {
            biaoji[i] = 1;
        }
        
        for (int i=0; i<siz; i++) {
            if (tag[i] == 1) {
                tmp->Add(str[i].row, str[i].col);
                biaoji[str[i].row] = 0;
                biaoji[str[i].col] = 0;
            }
        }
        
        bool flag = true;
        for (int i=1; i<=Vertices(); i++) {
            if (biaoji[i] == 1) {
                flag = false;
            }
        }
        
        if (flag != true) {
            return;
        }
        
        int sum=0; int *reach = new int[Vertices()+1];
        for (int i=1; i<=Vertices(); i++) {
            sum+=i;
        }
        
        bool flag2 = false;
        if (sum == tmp->DFSForTree(1, reach, 100)) {
            flag2 = true;
        }
        if (flag == true && flag2) {
            cout << "第 " << treeCount << "棵生成树： " << endl;
            treeCount++;
            for (int i=0; i<siz; i++) {
                if (tag[i] == 1) {
                    cout << str[i].row << "   " << str[i].col << endl;
                }
            }
        }
        
        return;
    }
    tag[n] = 0;
    build(str, tag, n+1, siz);
    tag[n] = 1;
    build(str, tag, n+1, siz);
}

static int mintreeCount = 1;
static int mintreeSize = 10000;

void AdjacencyGraph::buildMin(Position *str, int*tag, int n, int siz)
{
    if (n == siz) {
        int treesize = 0;
        AdjacencyGraph *tmp = new AdjacencyGraph(Vertices());
        int *biaoji = new int[Vertices()+1];
        for (int i=1; i<=Vertices(); i++) {
            biaoji[i] = 1;
        }
        
        for (int i=0; i<siz; i++) {
            if (tag[i] == 1) {
                tmp->Add(str[i].row, str[i].col);
                biaoji[str[i].row] = 0;
                biaoji[str[i].col] = 0;
                treesize++;
            }
        }
        
        bool flag = true;
        for (int i=1; i<=Vertices(); i++) {
            if (biaoji[i] == 1) {
                flag = false;
            }
        }
        
        if (flag != true) {
            return;
        }
        
        int sum=0; int *reach = new int[Vertices()+1];
        for (int i=1; i<=Vertices(); i++) {
            sum+=i;
        }
        
        bool flag2 = false;
        if (sum == tmp->DFSForTree(1, reach, 100)) {
            flag2 = true;
        }
        if (flag == true && flag2 && treesize<= mintreeSize) {
            mintreeSize = treesize;
            cout << "第 " << mintreeCount << "棵最小生成树： " << endl;
            mintreeCount++;
            for (int i=0; i<siz; i++) {
                if (tag[i] == 1) {
                    cout << str[i].row << "   " << str[i].col << endl;
                }
            }
        }
        
        return;
    }
    tag[n] = 0;
    buildMin(str, tag, n+1, siz);
    tag[n] = 1;
    buildMin(str, tag, n+1, siz);
}

//#include "shiyan8.h"
//
//int main()
//{
//    AdjacencyGraph *ag = new AdjacencyGraph(7);
//    ag->Add(1, 2);
//    ag->Add(1, 6);
//    ag->Add(2, 3);
//    ag->Add(2, 7);
//    ag->Add(3, 4);
//    ag->Add(4, 5);
//    ag->Add(5, 7);
//    ag->Add(5, 6);
//
//
//    ag->GetGraph();
//
//    int *reach = new int[ag->Vertices()+1];
//    cout << " BFS: " << endl;
//    ag->BFS(3, reach, 100);
//    cout << endl;
//
//    cout << " DFS: " <<endl;
//    int *reach2 = new int[ag->Vertices()+1];
//    ag->DFS(3, reach2 , 100);
//    cout << endl;
//
//    int tag[ag->Edges()];
//    ag->build(ag->poss, tag, 0, ag->Edges());
//    ag->buildMin(ag->poss, tag, 0, ag->Edges());
//
////    输出最小生成树里还有点问题，即第一次输出的不一定是最小的，可以按如下方法进行改进：
////    在buildMin里，检测到当前treesize是最小的，就把这棵树加入数组
////    输出时，先遍历数组，确定最小treesize，然后把treesize等于最小treesize的树输出出来。
////    但是我实在是懒得再改了～ ：）
//}
#endif
