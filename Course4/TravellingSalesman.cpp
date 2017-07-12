#include <bits/stdc++.h>
#define MIN(a,b) a<b?a:b
using namespace std;
unsigned long long fun1(unsigned long long x)
{

  unsigned long long r;
  unsigned long long n;
  unsigned long long rp;
  unsigned long long next = 0;

  if(x)
  {
    r = x & -(signed long)x;
    n = x + r;
    rp = x ^ n;
    rp = (rp)/r;
    rp >>= 2;
    next = n | rp;
  }

  return next;
}
void fun2(char *a, float *v1, float *v2)
{
     int i,j;
     char ab[10];
     for(j=0, i=0; a[i]!=' '; i++,j++) 
     ab[j]=a[i];
     ab[j]='\0';
     *v1=atof(ab);
     for(j=0, i++; a[i]!='\n'; i++,j++)
     ab[j]=a[i];
     ab[j]='\0';
     *v2=atof(ab);
}
long long fun3(int n, int m)
{
     long long num=1, d=1;
     if(n==m) return 1;
     for(int i=0; i<m; i++) num*=(n-i);
     for(int i=1; i<=m; i++) d*=i;
     return num/d;
}
int main(int argc, char *argv[])
{
    struct node
    {
       long s;
       float *a;
       node *next;
    };
    char line[30];
    int num_cities;
    FILE *f=fopen("/Users/shashankmishra/Desktop/tsp.txt","r");
    fgets(line,30,f);
    num_cities=atoi(line);
    float **g=new float*[num_cities+1];
    float **c=new float*[num_cities+1];
    for(int i=1; i<=num_cities; i++)
    {
            c[i]=new float[2];
            fgets(line,30,f);
            float x,y;
            fun2(line,&x,&y);
            c[i][0]=x; c[i][1]=y;
    }
    fclose(f);
    g[0]=new float[num_cities+1];
    for(int i=1; i<=num_cities; i++)
            g[i]=new float[num_cities+1];

    for(int i=1; i<=num_cities; i++)
    {
            g[i][i]=0;
            for(int j=i+1; j<=num_cities; j++)
                    {
                           g[i][j]=sqrt(pow(c[i][0]-c[j][0],2)+pow(c[i][1]-c[j][1],2));
                           g[j][i]=g[i][j];
                    }
    }
    delete c;

    node **arr=new node*[num_cities+1];
    for(int i=0; i<=num_cities; i++) arr[i]=NULL;
    for(int h=1; h<=num_cities; h++)
    {
            long s=1<<(h-1);
            long index=s%num_cities;
            if(arr[index]==NULL)
            {
                arr[index]=new node;
                arr[index]->next=NULL;
                arr[index]->s=s;
                arr[index]->a=new float[num_cities+1];
                arr[index]->a[num_cities]=99999;
                if(s==1) arr[index]->a[num_cities]=0;
            }
            else
            {
                node *temp=arr[index];
                while(temp->next!=NULL) temp=temp->next;
                node *newnode=new node;
                newnode->next=NULL;
                newnode->s=s;
                newnode->a=new float[num_cities+1];
                newnode->a[num_cities]=99999;
                temp->next=newnode;
            }
    }

    long long S=1<<num_cities;
    long count=num_cities, lcount;
    long long newSize=count, lsize;
    node **curr_arr;

    for(int m=2; m<=num_cities; m++)
    {
            lcount=count; count=0;
            lsize=newSize;
            int tempm=m;
            if(m>(num_cities/2))
            {
                tempm=num_cities-m+1;
                if(num_cities%2==1 && m==((num_cities/2)+1)) tempm=m;
            }
            newSize=fun3(num_cities-1,tempm-1);
            curr_arr=new node*[newSize+1];
            for(long long i=0; i<=newSize; i++) curr_arr[i]=NULL;
            long long s=0;
            for(int i=0; i<m; i++)
            s+=(long long)(((long long)1)<<i);
            while(s<S)
            {
                    ++count;
                    node *newnode=new node;
                    newnode->next=NULL;
                    newnode->s=s;
                    newnode->a=new float[num_cities+1];
                    for(int p=0; p<=num_cities; p++) newnode->a[p]=99999;
                    for(int j=num_cities-1; j>0; j--)
                    {
                            if((s&(1<<(num_cities-j))))
                            {
                                    long long ttemp=s&~(1<<(num_cities-j));
                                    newnode->a[j]=99999;
                                    for(int k=num_cities; k>0; k--)
                                    {
                                            if((s&(1<<(num_cities-k))) && k!=j)
                                            {
                                            long long indexx=ttemp%lsize;
                                            node *old=arr[indexx];
                                            while(old!=NULL && (old->s)!=ttemp) old=old->next;
                                            float val=99999;
                                            if(old!=NULL) val=old->a[k];
                                            if(newnode->a[j]>(val+g[num_cities-k+1][num_cities-j+1]))
                                                    newnode->a[j]=val+g[num_cities-k+1][num_cities-j+1];
                                            }
                                    }

                            }
                    }
                    unsigned long long index=s%newSize;
                    if(curr_arr[index]!=NULL)
                    {
                        node *temp=curr_arr[index];
                        while(temp->next!=NULL) temp=temp->next;
                        temp->next=newnode;
                    }
                    else curr_arr[index]=newnode;
                    s=s>>1;
                    s=(signed)fun1(s);
                    s=(s<<1)+1;
            }
            delete arr;
            arr=curr_arr;
            curr_arr=NULL;
    }

    float min=99999;
    count=(S-1)%newSize;
    for(int j=1; j<num_cities; j++)
        if(((arr[count]->a[j])+g[num_cities-j+1][1])<min)
            min=(arr[count]->a[j])+g[num_cities-j+1][1];
    delete arr,curr_arr,g;
    cout<<"Mininum Cost Travelling Salesman Tour: "<<(int)min<<endl;
    return 0;
}
