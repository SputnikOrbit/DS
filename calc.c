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
        return 3;
    default:
        return 0;
    }
}

int calc();

int main()
{
    freopen("Untra_base.txt", "r", stdin);
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
            int new_hie = hieracy(line[i]);
            while (top!=-1&&new_hie < hieracy(stack[top]))
            {
                if(line[i]==')'&&stack[top]=='(')
                {
                    top--;
                    break;
                }
                else if (stack[top]=='(')
                {
                    if (line[i]=='=')
                    {
                        while (top!=-1)
                        {
                            fomula[j].num = 0;
                            fomula[j++].op = stack[top--];
                        }
                    }
                    break;
                }

                fomula[j].num = 0;
                fomula[j++].op = stack[top--];
                //stack[top] = '\0';
                if (top==-1)
                {
                    break;
                }
            }
            if(!(line[i]==')'))
            {
                top++;
                stack[top] = line[i];
            }
            
        }
    }
    for (int i = 0; i < j; i++)
    {
        if (fomula[i].op)
            printf("%c ",fomula[i].op);
        else
            printf("%d ",fomula[i].num);
    }
        
    return 0;
    
}

// 写一下规则：
// 1、先用clean函数清理空格
// 2、如果是数字，组成多位数字后，直接入总队
// 3、如果是符号：1.1 低位弹高位 +：1 *：2 ）：0 （：3
//             1.2 遇左括号直接入栈
//             1.3 遇到右括号，出栈知道赶走第一个左括号，出了的东西到总线里 