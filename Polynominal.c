#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

typedef struct polyNode{
    struct polyNode* next;
    int exp;
    int coef;
}polyNode;
typedef polyNode* polyPtr;

polyPtr create_polynominal( int exp_, int coef_)
{
    polyPtr a = (polyPtr)malloc(sizeof(polyNode));
    a->coef = coef_;
    a->exp = exp_;
    a->next = NULL;
    return a;
}
polyPtr cl ;
void insert(polyPtr c, int coef_num, int exp_num)
{
    polyPtr ctmp = c;
    
    while (ctmp->next!=NULL&&ctmp->next->exp>exp_num)
        ctmp = ctmp->next;

    if (ctmp->next == NULL)
    {
        //polyNode a = {NULL, exp_num, coef_num};
        polyPtr ai = create_polynominal(exp_num, coef_num);
        ctmp->next = ai;
    }
    else if (ctmp->next->exp == exp_num)
    {
        ctmp->next->coef+=coef_num;
    }
    else if (ctmp->next->exp < exp_num)
    {
        polyPtr ai = create_polynominal(exp_num, coef_num);
        ai->next = ctmp->next;
        ctmp->next = ai;
    }
}
void multi(polyPtr a, polyPtr b)
{
    polyPtr aPtr = a->next;
    polyPtr bPtr = b->next;
    while (aPtr!=NULL)
    {
        while (bPtr !=  NULL)
        {
            int exp = aPtr->exp+bPtr->exp;
            int coef = aPtr->coef*bPtr->coef;

            insert(cl,coef, exp);

            bPtr  = bPtr->next;
        }
        bPtr = b->next;
        aPtr  = aPtr->next;
    }
    polyPtr ctmp = cl->next;
    while (ctmp!=NULL)
    {
        if (ctmp->coef!=0)
        {
            printf("%d %d ",ctmp->coef, ctmp->exp);
        }
        ctmp = ctmp->next;
    }
    printf("\n");
    
}

void add(polyPtr a, polyPtr b)
{
    polyPtr btmp = b->next;
    while (btmp!=NULL)
    {
        insert(a, btmp->coef, btmp->exp);
        btmp = btmp->next;
    }
    polyPtr atmp = a->next;
    int all_zeros = 1;
    while (atmp!=NULL)
    {
        if (atmp->coef!=0)
        {
            all_zeros = 0;
            break;
        }
        atmp = atmp->next;
    }
    if (all_zeros)
    {
        printf("0 0");
    }
    else
    {
        atmp = a->next;
        while (atmp!=NULL)
    {
        if (atmp->coef!=0)
            printf("%d %d ", atmp->coef, atmp->exp);
        atmp = atmp->next;
    }
    }        
    
}

int main()
{
    freopen("TESTBASE.txt", "r",stdin);
    polyPtr a = create_polynominal(10000, 10000);
    polyPtr b = create_polynominal(10000, 10000);
    cl = create_polynominal(10000, 10000);

    //next we intake the polynominal
    int k ;
    scanf("%d", &k);
    int coef, exp;
    while (k--)
    {
        scanf("%d %d", &coef,&exp);
        polyPtr tmp = a;
        while (tmp->next!=NULL)
            tmp = tmp->next;
        tmp->next = create_polynominal(exp ,coef);            
        
    }

        scanf("%d", &k);
        while (k--)
    {
        scanf("%d %d", &coef,&exp);
        polyPtr tmp = b;
        while (tmp->next!=NULL)
            tmp = tmp->next;
        tmp->next = create_polynominal(exp ,coef);   
    }
    multi(a, b);

    add(a, b);

    return 0;
}

// 这道题我决定采用链表构造多项式，创造虚拟头节点的同时
// 要设计方法：初始化、插入
// 和多项式部分，直接将a的每一项插入到b中合适位置即可
// 求积的话也不难，将a的每一位多项式逐个乘b，创造一新栈c，将这些多项式逐个
// 插入c中合适位置。因为要保留a b 原始数据，所以
// 不能直接在a b上操作。
//注意最后有一个输出 0 0 的规则

// 伪代码
// 注意是输出就完了

// void multi(a, b )
// {
//     polyPtr c = create_polynominal(10000, 10000);
//     polyPtr aPtr = a;
//     polyPtr bPtr = b;
//     while (aPtr!=NULL)
//     {
//         while (bPtr !=  NULL)
//         {
//             exp = bPtr.exp+aPtr.exp;
//             coef = bPtr.coef*aPtr.coef;

//             insert(coef, exp);

//             bPtr  = bPtr->next;
//         }

//         bPtr = b;
//         aPtr  = aPtr->next;
        
//     }

//     int all_zero = 1;
//     ptr ctmp = c;
//     while (ctmp!=NULL)
//     {
//         if()
//     }
//     if (all_zeros)
//     {
//         printf("0 0\n");
//     }
//     else
//     {
//         ctmp = c;
//         while (ctmp!=NULL)
//         {
//             prf coef exp

//         }

        
//     }
    
    
    
// }