#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

int network[1001][1001];
int visited[1001];
int N, M;

// void DFS(int root, int stage)
// {
//     visited[root] = 1;
//     if (stage==6)
//     {
//         return;
//     }
    
//     int queue[1001];
//     int top = 0;
//     for (int i = 0; i < N ; i++)
//     {
//         if(network[root][i]==1&&visited[i]!=1)
//             queue[top++] = i;
//     }
//     if(top==0)
//         return;
//     else
//         for (int i = 0; i <top; i++)
//         {
//             DFS(queue[i], stage+1);
//         }
    
// }
    int queue[7][100000];
    int in_queue[1001];

void DFS(int root)
{
    visited[root] = 1;
    int top[10] = {0};
    memset(queue, 0, sizeof(queue));
    memset(in_queue, 0, sizeof(in_queue));

    int m = 0;
    int flag = 0;
    while (m<=6)
    {
        if (flag==0)
        {
            flag = 1;
            visited[root] = 1;
            for (int i = 0; i < N ; i++)
            {
                if(network[root][i]==1&&visited[i]!=1)
                {
                    queue[m][top[m]++] = i;
                    in_queue[i] = 1;
                }
            }
            if (top[m]==0)
            {
                return;
            }
            
        }
        else
        {
            if(top[m-1]==0)
                    return;
            int sum = top[m-1];
            
            for (int i = 0; i < sum; i++)
            {
                if (in_queue[queue[m-1][i]]==1)
                {
                    root = queue[m-1][i];
                visited[root] = 1;
                for (int i = 0; i < N ; i++)
                {
                    if(network[root][i]==1&&visited[i]!=1)
                    {queue[m][top[m]++] = i;
                            in_queue[i] = 1;
                    }
                }
                    in_queue[queue[m-1][i]] = -1;
                }
                else if (in_queue[queue[m-1][i]]==-1)
                {
                    continue;
                }
            }
        }
        m++;
    }
}

int main()
{
    freopen("TESTBASE.txt","r",stdin);
    scanf("%d %d", &N, &M);
        memset(network, 0, sizeof(network));

    for (int i = 0; i < M; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        network[a-1][b-1] = 1;
        network[b-1][a-1] = 1;
    }
    // for(int i = 0; i < N; i++)
    //     {
    //         for (int j = 0; j < N; j++)
    //         printf("%d ", network[i][j]);
    //         printf("\n");
    //     }

    int count = 0;
    float percentage = 0.0;

    for (int i = 0; i < N; i++)
    {
        count = 0;
        printf("%d: ",i+1);
        memset(visited,0,sizeof(visited));
        visited[i] = 1;
        DFS(i);
        for (int j = 0; j < N; j++)
            if(visited[j])
                count++;
        percentage = ((float)count/(float)N)*100.0;
        printf("%.2f%%\n", percentage); 
    }
    
}

// 老规矩，先写思路
// 这个是图的层序遍历，唯一不同的是终止
// 条件要多加留心。终止条件有二：1、到达第六层
// 2、不够六层但已经循环完（小条件）
// 搜索的逻辑是打一个扔一个，用一个N长
// 数组记录节点在递归节点的过程中
// 是否已经被访问过，如果被访问过，则不再递归
// 如果没有，先标记访问过，再递归深入搜索。