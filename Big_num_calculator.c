#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

// 老规矩，先写思路
// 数据的组织形势：结构体，包含：字符串数组（倒序），len，符号位
// 比较数据的大小：先比较符号位，再比较len，再比较字符串数组
// 加法实现：需要符号相同

typedef struct big_num{
    int len;
    char data[100];
    int sign;
}big_num;

void rev_str(char* str)
{
    int len = strlen(str);
    char temp;
    for(int i=0;i<len/2;i++)
    {
        temp = str[i];
        str[i] = str[len-i-1];
        str[len-i-1] = temp;
    }
    return;
}

void plus(big_num A, big_num B);
void minus(big_num A, big_num B);


int main()
{
    //freopen("PAT_TSBASE.txt","r",stdin);    
    big_num A;
    big_num B;

    //data initialization
    fgets(A.data,100,stdin);
    fgets(B.data,100,stdin);
    if(*A.data=='-')
    {
        A.sign = -1;
        A.len = strlen(A.data)-1;
        for(int i=0;i<A.len;i++)
        {
            A.data[i] = A.data[i+1];
        }
        A.data[A.len] = '\0';
    }
    else
    {
        A.sign = 1;
        A.len = strlen(A.data);
    }

    if (!isdigit(A.data[A.len-1]))
    {
        A.len--;
        A.data[A.len] = '\0';
    }
    rev_str(A.data);
    if(*B.data=='-')
    {
        B.sign = -1;
        B.len = strlen(B.data)-1;
        for(int i=0;i<B.len;i++)
        {
            B.data[i] = B.data[i+1];
        }
        B.data[B.len] = '\0';
    }
    else
    {
        B.sign = 1;
        B.len = strlen(B.data);
    }
    if (!isdigit(B.data[B.len-1]))
    {
        B.len--;
        B.data[B.len] = '\0';
    }
    rev_str(B.data);

    //addition
    //plus(A,B);
    minus(A,B);

}

void plus(big_num A, big_num B)
{
    if (A.sign==B.sign)
    {
        char result[200] = {0};
        if(A.sign==1)
        {
            int carry = 0;
            int i=0;
            for(;i<A.len&&i<B.len;i++)
            {
                result[i] = (A.data[i]-'0'+B.data[i]-'0'+carry)%10+'0';
                carry = (A.data[i]-'0'+B.data[i]-'0'+carry)/10;
            }
            for(;i<A.len;i++)
            {
                result[i] = (A.data[i]-'0'+carry)%10+'0';
                carry = (A.data[i]-'0'+carry)/10;
            }
            for(;i<B.len;i++)
            {
                result[i] = (B.data[i]-'0'+carry)%10+'0';
                carry = (B.data[i]-'0'+carry)/10;
            }
            if(carry!=0)
            {
                result[i] = carry+'0';
                i++;
            }
            result[i] = '\0';
            rev_str(result);
            printf("%s",result);
        }
        else
        {
            int carry = 0;
            int i=0;
            for(;i<A.len&&i<B.len;i++)
            {
                result[i] = (A.data[i]-'0'+B.data[i]-'0'+carry)%10+'0';
                carry = (A.data[i]-'0'+B.data[i]-'0'+carry)/10;
            }
            for(;i<A.len;i++)
            {
                result[i] = (A.data[i]-'0'+carry)%10+'0';
                carry = (A.data[i]-'0'+carry)/10;
            }
            for(;i<B.len;i++)
            {
                result[i] = (B.data[i]-'0'+carry)%10+'0';
                carry = (B.data[i]-'0'+carry)/10;
            }
            if(carry!=0)
            {
                result[i] = carry+'0';
                i++;
            }
            result[i] = '\0';
            rev_str(result);
            printf("-%s",result);
        }
    }
    else
    {
        if (A.sign==-1)
        {
            A.sign = 1;
            minus(B,A);
            A.sign = -1;
        }
        else
        {
            B.sign = 1;
            minus(A,B);
            B.sign = -1;
        }
    }
    
}
void minus(big_num A, big_num B)//to verify result, opt = comp*(A.sign -)
{
    char result[200] = {0};
    if (A.sign==B.sign)
    {
        if (A.len>B.len)
        {
            int len = A.len;
            int carry = 0;
            int i=0;
            for(;i<B.len;i++)
            {
                if(A.data[i]-'0'-carry>=B.data[i]-'0')
                {
                    result[i] = A.data[i]-carry-B.data[i]+'0';
                    carry = 0;
                }
                else
                {
                    result[i] = A.data[i]-carry-B.data[i]+'0'+10;
                    carry = 1;
                }
            }
            for(;i<A.len;i++)
            {
                if(A.data[i]-'0'-carry>=0)
                {
                    result[i] = A.data[i]-carry;
                    carry = 0;
                }
                else
                {
                    result[i] = A.data[i]-carry+10;
                    carry = 1;
                }
            }

            result[i] = '\0';
            for (int i = strlen(result)-1; result[i]=='0'; i--)
            {
                result[i] = '\0';
            }
            rev_str(result);
            
            if (A.sign==1)
        {
            printf("%s",result);
        }
        else
        {
            printf("-%s",result);
        }
        }
        else if (A.len<B.len)
        {
            int len = B.len;
            int carry = 0;
            int i=0;
            for(;i<A.len;i++)
            {
                if(B.data[i]-'0'-carry>=A.data[i]-'0')
                {
                    result[i] = B.data[i]-carry-A.data[i]+'0';
                    carry = 0;
                }
                else
                {
                    result[i] = B.data[i]-carry-A.data[i]+'0'+10;
                    carry = 1;
                }
            }
            for(;i<B.len;i++)
            {
                if(B.data[i]-'0'-carry>=0)
                {
                    result[i] = B.data[i]-carry;
                    carry = 0;
                }
                else
                {
                    result[i] = B.data[i]-carry+10;
                    carry = 1;
                }
            }
            result[i] = '\0';
            for (int i = strlen(result)-1; result[i]=='0'; i--)
            {
                result[i] = '\0';
            }
            rev_str(result);
            if (B.sign==-1)
        {
            printf("%s",result);
        }
        else
        {
            printf("-%s",result);
        }
        }
        else//A.len==B.len
        {
            int len = A.len;
            int comp = '\0';
            int i = 0;
            for (int i = len; i >=0; i--)
            {
                if (A.data[i]>B.data[i])
                {
                    comp = 1;
                    break;
                }
                else if (A.data[i]<B.data[i])
                {
                    comp = -1;
                    break;
                }
                else
                {
                    continue;
                }                
            }
            
            if (comp == 1)//abs(A) is bigger
            {
                int j =0;
                for (j = 0; j <len; j++)
                {
                    result[j] = A.data[j]-B.data[j]+'0';
                    if (result[j]<'0')
                    {
                        result[j] = result[j]+10;
                        A.data[j-1] = A.data[j-1]-1;
                    }
                }
            result[j] = '\0';

                for (int i = len-1; A.data[i]=='0'; i--)
                {
                    result[i] = '\0';
                }
                rev_str(result);                
            }
            else if (comp == -1)//abs(B) is bigger
            {
                int j = 0;
                for(j = 0; j<len; j++)
                {
                    result[j] = B.data[j]-A.data[j]+'0';
                    if (result[j]<'0')
                    {
                        result[j] = result[j]+10;
                        B.data[j-1] = B.data[j-1]-1;
                    }
                }
            result[j] = '\0';

                for (int i = len-1; B.data[i]=='0'; i--)
                {
                    result[i] = '\0';
                }
                rev_str(result);
            }
            
            //Might be zero...
            if(comp==1)
            {
                printf("%s",result);
            }
            else if(comp==-1)
            {
                printf("-%s",result);
            }
            else
            {
                printf("0");
            }
        }
        
       
        
        
    }
    else
    {
        if(B.sign==-1)//A.sign==1
        {
            B.sign = 1;
            plus(A,B);
            B.sign = -1;
        }
        else//A.sign==-1, B.sign==1
        {
            B.sign = -1;
            plus(A,B);
            B.sign = 1;
        }
    }
}
