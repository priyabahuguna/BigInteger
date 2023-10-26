#ifndef f1
#define f1 1
struct node 
{
    int data;
    struct node *next;
};
struct BigInteger
{
    struct node*L;
    int length;
};
struct BigInteger initialize(char *s);
struct BigInteger add(struct BigInteger,struct BigInteger);
struct BigInteger sub(struct BigInteger,struct BigInteger);
struct BigInteger mul(struct BigInteger,struct BigInteger);
struct BigInteger div1(struct BigInteger,struct BigInteger);
struct BigInteger mod(struct BigInteger,struct BigInteger);
struct BigInteger reverse1(struct BigInteger);
void display(struct BigInteger);
void insert(struct node**,int);
int Compare(struct BigInteger,struct BigInteger);
#endif
