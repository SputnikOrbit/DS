#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

// 老规矩，险些思路
// 需要一个数组 is_intact 记录是否有孤立节点
// 考虑用邻接矩阵来简单解决这个题
// 深度和广度优先搜索中，节点编号从小到大输出，这要靠邻接矩阵
// 遍历来实现。从上往下遍历，找到最小的
// 管他呢，先生成个邻接矩阵看看！
int matrix[15][15];
int flag;
    int N, E ;

int is_intact[15];
void DFS(int cur_node)
{
    if (!flag)
    {
        printf("{ ");
        flag=1;
    }
    is_intact[cur_node]--;
    if(!is_intact[cur_node])
    printf("%d ",cur_node);
    int queue[15];
    int j = 0;
    for (int i = 0; i < N; i++)
    {
        if (matrix[cur_node][i]==1&&is_intact[i]==1)
        {
            queue[j++] = i;
        }
    }
    if(j==0)
    {
        return;
    }
    for (int i = 0; i < j; i++)
    {
        DFS(queue[i]);
    }
    return;
}

int BFS_queue[15];
    int q_front,q_rear; ;
void BFS(int cur_node)
{
    if (!flag)
    {
        BFS_queue[q_rear++] = cur_node;

        flag=1;
    }

    is_intact[cur_node] = 0;
    int j =0;
    int queue[15];
    for (int i = 0; i < N; i++)
    {
        if (matrix[cur_node][i]==1&&is_intact[i]==1)
        {
            queue[j++] = i;
            is_intact[i] = 0;
        }
    }
    if(j==0)
    {
        return;
    }
    for(int i = 0; i<j ;i++)
    {
        BFS_queue[q_rear++] = queue[i];
    }
    for (int i = q_front; i < q_rear; i++)
    {
        BFS(BFS_queue[i]);
        q_front++;
    }
    return;
}

int main()
{
    freopen("PAT_TSBASE.txt","r",stdin);
    scanf("%d %d", &N, &E);
    if(N==1)
        {
            printf("{ 0 }\n{ 0 }");
            return 0;
        }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = 0;
        }
    }
    
    int tag1 ,tag2;
    while (E--)
    {
        scanf("%d %d",&tag1, &tag2);
        matrix[tag1][tag2] = matrix[tag2][tag1] = 1;
    }
    // for (int i = 0; i < N; i++)
    // {
    //     for (int j = 0; j < N; j++)
    //     {
    //         printf("%d ",matrix[i][j]);
    //     }
    //     printf("\n");
    // }

    for(int i = 0;i<N;i++)
    {
        is_intact[i] = 1;
    }
            flag = 0;

    for (int i = 0; i < N; i++)
    {
        if (is_intact[i]==1)
        {

            DFS(i);
            printf("}\n");flag = 0;

        }
    }
    for (int i = 0; i < N; i++)
    {
        is_intact[i]=1;
    }
    flag = 0;
    q_front = q_rear = 0;
    for (int i = 0; i < N; i++)
    {
        if (is_intact[i]==1)
        {
                q_front = q_rear = 0;
        printf("{ ");

            BFS(i);

            for (int i = 0; i < q_rear; i++)
            {
                printf("%d ",BFS_queue[i]);
            }
            
            printf("}\n");flag = 0;


        }
    }
    //BFS(0);

    return 0;
}

// BFS写不动了。
// 首先，给定根节点，BFS的实现要求将根节点所有子节点推入
// 队列（在这之前先print），然后进行队列里每个子节点的BFS。
// 在这个过程中，如果子节点没有任何节点再与之联通，则可return。

// 给定一个有N个顶点和E条边的无向图，请用DFS和BFS分别列出其所有的连通集。假设顶点从0到N−1编号。进行搜索时，假设我们总是从编号最小的顶点出发，按编号递增的顺序访问邻接点。

// 输入格式:
// 输入第1行给出2个整数N(0<N≤10)和E，分别是图的顶点数和边数。随后E行，每行给出一条边的两个端点。每行中的数字之间用1空格分隔。

// 输入样例:
// 8 6
// 0 7
// 0 1
// 2 0
// 4 1
// 2 4
// 3 5