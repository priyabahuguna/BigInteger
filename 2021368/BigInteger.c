#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "BigInteger.h"
void insert(struct node**head,int data)
{
    struct node*temp=(struct node*)malloc(sizeof(struct node));
    temp->data=data;
    temp->next=NULL;
    if(*head==NULL)
    {
        *head=temp;
    }
    else
    {
        struct node*itr=*head;
        while(itr->next!=NULL)
        {
            itr=itr->next;
        }
        itr->next=temp;
    }
}
struct BigInteger initialize(char *s)
{
    struct BigInteger big;
    big.L=NULL;
    big.length=strlen(s);
    int i=0;
    for(i=big.length-1;i>=0;i--)
    {
        insert(&big.L,s[i]-'0');
    }
    return big;
}
struct BigInteger reverse1(struct BigInteger b)
{
    struct BigInteger rev;
    rev.L=NULL;
    rev.length=b.length;
    struct node *j=b.L;
    while(j!=NULL)
    {
        insert(&rev.L,j->data);
        j=j->next;
    }
    struct node *itr=rev.L, *prev=NULL,*next=NULL;
    while(itr!=NULL)
    {
        next=itr->next;
        itr->next=prev;
        prev=itr;
        itr=next;
    }
    rev.L=prev;
    return rev;
}

void display(struct BigInteger b)
{
    struct BigInteger rev=reverse1(b);
    struct node*itr=rev.L;
    while(itr!=NULL)
    {
        printf("%d",itr->data);
        itr=itr->next;
    }
}
int Compare(struct BigInteger a,struct BigInteger b)
{
    if(a.length>b.length)
    {
        return 1;
    }
    else if(a.length<b.length)
    {
        return -1;
    }
    else
    {
        int f=0;
        struct node*itr1=a.L;
        struct node*itr2=b.L;
        while(itr1!=NULL)
        {
            if(itr1->data>itr2->data)
            {
                f=1;
            }
            else if(itr1->data<itr2->data)
            {
                f=-1;
            }
            itr1=itr1->next;
            itr2=itr2->next;
        }
        return f;
    }
}

struct BigInteger add(struct BigInteger a,struct BigInteger b)
{
    struct BigInteger c;
    c.L=NULL;
    c.length=0;
    int carry=0;
    struct node*itr1=a.L,*itr2=b.L;
    while(itr1!=NULL||itr2!=NULL)
    {
        int sum=carry;
        if(itr1!=NULL)
        {
            sum=sum+itr1->data;
            itr1=itr1->next;
        }
        if(itr2!=NULL)
        {
            sum+=itr2->data;
            itr2=itr2->next;
        }
        carry=sum/10;
        sum=sum%10;
        insert(&c.L,sum);
        c.length++;
    }
    if(carry!=0)
    {
        insert(&c.L,carry);
        c.length++;
    }    
    return c;
}

struct BigInteger sub(struct BigInteger a,struct BigInteger b)
{
	int borrow=0;
    struct BigInteger c;
    c.L=NULL;
    c.length=0;
    if(Compare(a,b)==-1)
    {
        struct BigInteger temp=a;
        a=b;
        b=temp;
    }
    struct node*itr1=a.L,*itr2=b.L;
    while(itr1!=NULL||itr2!=NULL)
    {
        int sub=borrow;
        if(itr1!=NULL)
        {
            sub+=itr1->data;
            itr1=itr1->next;
        }
        if(itr2!=NULL)
        {
            sub-=itr2->data;
            itr2=itr2->next;
        }
        if(sub<0)
        {
            sub+=10;
            borrow=-1;
        }
        else
        {
            borrow=0;
        }
        insert(&c.L,sub);
        c.length++;
    }
    return c;
}

struct BigInteger mul(struct BigInteger a,struct BigInteger b)
{
    struct BigInteger c=initialize("0");
    c.L=NULL;
    c.length=0;
    struct node*itr1=a.L,*itr2=b.L;
    int count=0,i;
    while(itr2)
    {
        struct BigInteger temp;
        temp.L=NULL;
        temp.length=0;
        int carry=0;
        for( i=0;i<count;i++)
        {
            insert(&temp.L,0);
            temp.length++;
        }
        itr1=a.L; 
        while(itr1)
        {
            int m=itr1->data*itr2->data+carry;
            carry=m/10;
            m=m%10;
            insert(&temp.L,m);
            temp.length++;
            itr1=itr1->next;
        }
        if(carry!=0)
        {
            insert(&temp.L,carry);
            temp.length++;
        }
        c=add(c,temp);
        count++;
        itr2=itr2->next;
    }
    return c;
}
struct BigInteger mod(struct BigInteger a,struct BigInteger b)
{
    struct BigInteger temp=initialize("0");
    struct BigInteger quotient=initialize("0");
    struct BigInteger one = initialize("1");
    while(Compare(a,temp)!=-1)
    {
        temp=add(temp,b);
        quotient=add(quotient,one);
    }
    temp=sub(temp,b);
    quotient=sub(quotient,one);
    return sub(a,temp);
}
struct BigInteger div1(struct BigInteger a,struct BigInteger b)
{
    struct BigInteger temp=initialize("0");
    struct BigInteger quotient=initialize("0");
    struct BigInteger one = initialize("1");
    while(Compare(a,temp)!=-1)
    {
        temp=add(temp,b);
        quotient=add(quotient,one);
    }
    temp=sub(temp,b);
    quotient=sub(quotient,one);
    return quotient;
}
