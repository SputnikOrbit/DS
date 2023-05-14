#include<stdio.h>
int albat[100001];

int max_tri(int a, int b, int c)
{
    return a>b?(a>c?a:c):(b>c?b:c);
}

int msl(int left, int right)
{
    int cur_max = 0;
    int tmp_max = 0;
    for (int i = left; i <= right; i++)
    {
        
            tmp_max += albat[i];
        if (tmp_max<0)
        {
            tmp_max = 0;
        }

        if(tmp_max>cur_max)
            cur_max = tmp_max;
    }
    
    return cur_max;
    
}

int main()
{
    freopen("TESTBASE.txt", "r", stdin);
    int k;
    scanf("%d", &k);
    int has_pos = 0;
    for(int i = 0; i < k; i++)
    {
        scanf("%d",&albat[i]);
        if(albat[i]>=0)
            has_pos = 1;
    }
    if(has_pos)
        printf("%d", msl(0, k-1));
    else
        printf("0");
    return 0;
}


// README:
// 这道题我决定两种思路都学会
// 首先是分治，有三个要点：
// 1、将数组分为len/2部分，递归求其两侧最大值
// 2、广义展开， 求一次跨两翼最大值
// 3、终止条件和中间条件是什么？
// 伪代码
// Max_link_sum(int a[], int a_len){
//     if (a_len==0)
//     {
//         return a[i]
//     }
    
//     left = Max_link_sum(a_left)
//     right = Max_link_sum(a_right)

//     mid = find_wings_max(a_mid)

//     return max(left, right, min)

// }