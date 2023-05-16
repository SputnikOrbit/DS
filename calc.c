#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

typedef struct node{
    int num;
    int op;
    struct node* left;
    struct node* right;
}node;
char stack[100];
int top;
int isopt(char c){
    return c=='+'||c=='-'||c=='*'||c=='/'||c=='('||c==')'||c=='=';
}

void clean(char* line){
    char* a = line;
    int index = 0;
    while (*a != '\0'&&*a!='\n')
    {
        char tmp = *a;
        if (isopt(tmp))
        {
            line[index++] = *a;
        }
        else if(isdigit(tmp))
        {
            line[index++] = *a;
        }
        a++;
    }
    line[++index] = '\0';
}

int hieracy(char opt)
{
    switch (opt)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '=':
        return -1;
    case '(':
        return 0;
    default:
        return 0;
    }
}

int postfix_calc(node* root)
{
    if (root->op==0)
    {
        return root->num;
    }
    
    int a = postfix_calc(root->left);
    int b = postfix_calc(root->right);

    
    switch (root->op)
    {
    case '+':
    return a+b;
    case '-':
        return a-b;
    case '*':
        return a*b;

    case '/':
    return a/b;
    break;
    }
    
}

int main()
{
    //freopen("Untra_base.txt", "r", stdin);
    node fomula[200];
    char line[500];
    fgets(line, 500, stdin);
    clean(line);

    int len = 0;
    while (line[len]!=' '&&line[len]!='='&&line[len]!='\0'){
        len++;
    }
    len++;
    
    int j = 0;
    top = -1;//init the stack;
    for (int i = 0; i < len; i++)
    {
        if (isdigit(line[i]))
        {
            int sum = 0;
            while (isdigit(line[i]))
            {
                sum*=10;sum+=line[i]-'0';
                i++;
            }

            fomula[j].num = sum;
            fomula[j++].op = 0; 
        }
        if (isopt(line[i]))
        {

            if (line[i]==')')
            {
                 while (stack[top]!='(')
                    {
                        fomula[j].num = 0;
                        fomula[j].op = stack[top--];
                        j++;
                    }
                    top--;
            }
            else if (line[i]=='(')
            {
                top++;
                stack[top] = line[i];
            }
            else
            {
                if (line[i]=='=')
                {
                    while (top!=-1)
                    {
                        fomula[j].num = 0;
                        fomula[j].op = stack[top--];
                        j++;
                    }
                    
                }
                else
                {
                    int new_hie = hieracy(line[i]);
                    while (top!=-1&&(hieracy(stack[top]) >= new_hie))
                    {
                        fomula[j].num = 0;
                        fomula[j].op = stack[top--];
                        j++;
                    }   
                        top++;
                        stack[top] = line[i];
                }
                
            }
            
        }
    }
    // for (int i = 0; i <j; i++)
    // {
    //     if (fomula[i].op)
    //         printf("%c ",fomula[i].op);
    //     else
    //         printf("%d ",fomula[i].num);
    // }
    node* trees[200];
    for (int i = 0; i < j; i++)
    {
        trees[i] = (node*)malloc(sizeof(node));
        int ch  = fomula[i].op;
        int num = fomula[i].num;
        trees[i]->num = num;
        trees[i]->op = ch;
        trees[i]->left = NULL;
        trees[i]->right = NULL;
    }
    node* trees_stack[150];
    int ptr_top = -1;

    for (int i = 0; i < j; i++)
    {
        if (trees[i]->op)
        {
            node* T2 = trees_stack[ptr_top--];
            node* T1 = trees_stack[ptr_top--];
            trees[i]->left = T1;
            trees[i]->right = T2;
        }
        ptr_top++;
        trees_stack[ptr_top] = trees[i];
    }
    
    
    
    //printf("%c %c %c\n", trees_stack[0]->op, trees_stack[0]->left->op, trees_stack[0]->right->op);
    node* root = trees_stack[0];
    printf("%c",root->op);
    if (root->left!=NULL)
    if (root->left->op)
    {
    printf(" %c",root->left->op);
        
    }
    else 
    {
    printf(" %d",root->left->num);

    }
    if (root->right!=NULL)
    if (root->right->op)
    {
    printf(" %c",root->right->op);
        
    }
    else 
    {
    printf(" %d",root->right->num);

    }
    printf("\n");

    
printf("%d", postfix_calc(root));    return 0;
    
}

// 写一下规则：
// 1、先用clean函数清理空格
// 2、如果是数字，组成多位数字后，直接入总队
// 3、如果是符号：1.1 低位弹高位 +：1 *：2 ）：0 （：3
//             1.2 遇左括号直接入栈
//             1.3 遇到右括号，出栈知道赶走第一个左括号，出了的东西到总线里 
