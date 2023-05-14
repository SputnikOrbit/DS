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

git

```sh
git clone ... #这个是把版本仓库复制下来
git init #创建本地版本仓库
git config --global user.name ...
git config --global user.email ...

git add . #装弹,装填整个文件夹下所有东西
git add <file.name> #装填特定文件，可以用于不装填部分未完成的文件
git commit -m "I love U" #向当前所在的分支提交备份并
git commit main.py -m "I completed func 2" #commit 也有类似功能
git log #查看版本库
git branch <...> | git checkout <...> #创建并移动到分支
git checkout -b <...> #跟上面那个等价
git merge main  git rebase main  #这两个区别我还没搞清楚

git checkout bugFix #如果这个是commit 的名字（hash）就detach HEAD , 如果是分支的名字就移动到分支上 bugFix*
git checkout main^ #移动HEAD到main 的parent 节点
git checkout main^^ #移动两次
git checkout HEAD~3 #移动多次,不能写节点名，要写HEAD指向或者具体分支名，分支名后不能跟~3
git branch -f main HEAD~3 #强制移动分支位置
#你注意， HEAD就是这个分支里你的操作位置，是唯一且最重要的

git reset HEAD^ #这个是针对本地的
git revert HEAD #这个针对远端，会再原有节点上新建一个退化节点出来
git cherry_pick C3 C4 C7 #在HEAD停留的分支上创建副本，会长出来C3'，C4', C7'三个副本节点并按先后排列
git rebase -i HEAD~3 #交互式调整节点顺序
```

