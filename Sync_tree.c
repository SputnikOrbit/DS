#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

typedef struct node{
    char data;
    int left_index;
    int right_index;
}node; 

void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int len;
 node A[12];
    node B[12];
int is_sync(int tmp1, int tmp2)
{
    if (tmp1==-1&&tmp2==-1)
    {
        return 1;
    }
    else if (A[tmp1].data!=B[tmp2].data)
    {
        return 0;
    }
    
    int ans = 2;
    if(A[A[tmp1].left_index].data!=B[B[tmp2].left_index].data)
    {
        swap(&A[tmp1].left_index, &A[tmp1].right_index);
        if(A[A[tmp1].left_index].data!=B[B[tmp2].left_index].data||A[A[tmp1].right_index].data!=B[B[tmp2].right_index].data)
        {
            ans =  0;
        }
        else
        {
            ans =  1;
        }
    }
    else 
    {
        if (A[A[tmp1].right_index].data==B[B[tmp2].right_index].data)
        {
            ans =  1;
        }
        else
        {
            ans =  0;
        }
    }
    if (ans)
    {
        return is_sync(A[tmp1].left_index, B[tmp2].left_index)&&is_sync(A[tmp1].right_index, B[tmp2].right_index);
    }
    else
    return 0;
        
}

int main()
{
    freopen("Untra_base.txt", "r", stdin);
    int k;
    int check1[12] = {0};
    int check2[12] = {0};
    int root1, root2;

    scanf("%d", &k);
    if (k==0)
    {
        len = 0;
    }
    else
    for (int i = 0; i < k; i++)
    {
        char tmp;
        scanf("\n%c %c %c", &tmp, &A[i].left_index, &A[i].right_index);
        A[i].data = tmp;
        if (A[i].left_index=='-')
        {
            A[i].left_index = -1;
        }
        else
        {
            A[i].left_index -= '0';
            check1[A[i].left_index] = 1;
        }
        if (A[i].right_index=='-')
        {
            A[i].right_index = -1;
        }
        else
        {
            A[i].right_index -= '0';
            check1[A[i].right_index] = 1;
        }
    }
    for (int i = 0; i < k; i++)
    {
        if (check1[i]==0)
        {
            root1 = i;
            break;
        }
    }
    len = k;

    
    scanf("%d", &k);
    if (len!=k)
    {
        printf("No");
        return 0;
    }
    else if (k==0)
    {
        printf("Yes");
        return 0;
    }
    else
    for (int i = 0; i < k; i++)
    {
        char tmp;
        scanf("\n%c %c %c", &tmp, &B[i].left_index, &B[i].right_index);
        B[i].data = tmp;
        if (B[i].left_index=='-')
        {
            B[i].left_index = -1;
        }
        else
        {
            B[i].left_index -= '0';
            check2[B[i].left_index] = 1;
        }
        if (B[i].right_index=='-')
        {
            B[i].right_index = -1;
        }
        else
        {
            B[i].right_index -= '0';
            check2[B[i].right_index] = 1;
        }
    }
    for (int i = 0; i < k; i++)
    {
        if (check2[i]==0)
        {
            root2 = i;
            break;
        }
    }

    int bool = is_sync(root1, root2);
    if (bool)
    {
        printf("Yes");
    }
    else
    {
        printf("No");
    }
    return 0;
}

// README.md
// 老规矩，先落实思路
// 1、先用数组构成树两棵
// 2、再递归判断是否同构，依据为A树按照
// B树修改左右节点，如果所有节点都听话，说明同构
// 如果出现无法通过交换左右节点来同构的情况，说明不同构
