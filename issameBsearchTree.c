#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

// 老规矩，先写思路
// 1. 读入数据，建立树，获得树的前序和后序遍历指纹
// 2. 循环新建树，比较指纹
// 3. 建树规则：第一个读入是头节点，此后插入，比当前节点数值大
// 的插入右子树，比当前节点数值小的插入左子树

typedef struct node{
    int data;
    int left_index;
    int right_index;
}node;

node A[12];
node B[12];
int A_count;

void DFS_post(node* tree, int cur_index, char line[][2])
{
   
    *(line[A_count]+0) = tree[cur_index].data;
        A_count++;

    if (tree[cur_index].left_index!=-1)
    {
        DFS_post(tree,tree[cur_index].left_index, line);//I'm confused about it here
    }
    if (tree[cur_index].right_index!=-1)
    {
        DFS_post(tree,tree[cur_index].right_index, line);//I'm confused about it here
    }
    if (tree[cur_index].left_index==-1&&tree[cur_index].right_index==-1)
    {
        return ;
    }
    return;
}
void DFS_mid(node* tree, int cur_index, char line[][2])
{
    if (tree[cur_index].left_index!=-1)
    {
        DFS_mid(tree,tree[cur_index].left_index, line);//I'm confused about it here
    }
    *(line[A_count]+1) = tree[cur_index].data;
        A_count++;

    if (tree[cur_index].right_index!=-1)
    {
        DFS_mid(tree,tree[cur_index].right_index, line);//I'm confused about it here
    }
    if (tree[cur_index].left_index==-1&&tree[cur_index].right_index==-1)
    {
        return ;
    }
    return;
}

void get_figpt(node* tree,char line[][2], int n)
{

    int num;
    int root = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &num);
        if (!root)//If the tree is empty, set the first num as root
        {
            tree->data = num;
            tree->left_index = -1;
            tree->right_index = -1;
            root = 1;
        }
        else
        {
            int cur = 0;
        while(1)//Switching and finding the right place
            if (num>(tree[cur].data))
            {
                if (tree[cur].right_index==-1)
                {
                    tree[cur].right_index = i;
                    break;
                }
                else    
                    cur = tree[cur].right_index;
            }
            else
            {
                if (tree[cur].left_index==-1)
                {
                    tree[cur].left_index = i;
                    break;
                }
                else
                    cur = tree[cur].left_index;
            }
                tree[i].data = num;//Set the num in the right place
                tree[i].left_index = -1;
                tree[i].right_index = -1;
        }
        
    }
    A_count = 0;
    DFS_post(tree, 0, line);
    A_count = 0;
    DFS_mid(tree, 0, line);
}

int main()
{
    freopen("Untra_base.txt", "r", stdin);
    int n ;
    scanf("%d", &n);
    while(n!=0)
    {
        int comp_time;
        scanf("%d", &comp_time);

        char A_fingerprint[14][2];
        char B_fingerprint[14][2];

        get_figpt(A,A_fingerprint, n);

        while(comp_time--)
        {
            get_figpt(B,B_fingerprint, n);
            int flag = 1;
        for(int j = 0; j<2; j++)
        {
            if (flag==0)
            {
                break;
            }
             for (int i = 0; i < n; i++)
            {
                if (A_fingerprint[i][j]!=B_fingerprint[i][j])
                {
                    flag = 0;
                    break;
                }
            }
            
        }
            if (flag)
            {
                printf("Yes\n");
            }
            else
            {
                printf("No\n");
            }
        }
        scanf("%d", &n);
    }
}

