1、最大子列和问题max_sum_link.c

这道题有两个好方法：1、分治

分治要注意边界条件，我们开启了一种新方法

1.1、调试边界条件：用一个简单的铅笔橡皮，找张白纸，不管什么strlen或者从0开始的下标，标号然后找闭区间规律（开区间不好找就算啦）

1.2、 调试递归终止条件：自底向上，从最小的人能够处理的最优结构开始，检查结果正确性。递归其实很好写的！

```c
int max_tri(int a, int b, int c)
{
	return a>b?(a>c?a:c):(b>c?b:c);
}
int albat[100001];
int msl(int left, int right)
{
    if (left==right)
    {
        return albat[left];
    }
    int mid = left-(left-right)/2;

    int max_left = msl(left, mid);
    int max_right = msl(mid+1, right);
    int max_mid = 0;
    int max_mid_tmp1 = 0;
    int max_mid_tmp2 = 0;
    for (int i = mid; i >=left ; i--)
    {
        max_mid_tmp1+=albat[i];
        if (max_mid_tmp1>max_mid)
            max_mid = max_mid_tmp1;
    }
    max_mid_tmp1 = 0;
       for (int i = mid+1; i <=right ; i++)
    {
        max_mid_tmp2+=albat[i];
        if (max_mid_tmp2>max_mid_tmp1)
            max_mid_tmp1 = max_mid_tmp2;
    }
    max_mid+=max_mid_tmp1;
    //printf("cross[%d, %d] :%d left %d right %d\n",left, right, max_mid, max_left, max_right);
    return max_tri(max_left, max_mid, max_right);   
}
```

2、滑动窗口，不知道是动态规划还是什么

```c
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
```

2、一元多项式的加法于乘法

这让我想到了超大多位数加法、减法这些让我吃亏的东西

