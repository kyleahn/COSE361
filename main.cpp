#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define N 6
#define M 7
#define CONNECT 4

int w[M],cnt,a[N][M];

int top_stone(int);
void put_stone(int,int);
void remove_stone(int);
int end_check();
void print_map();
int my_turn();
int enemy_turn();

int main()
{
    int i,max,p,end;
    srand(time(NULL));
    while(cnt<N*M)
    {
        //my turn
        cnt++;
        put_stone(my_turn(),1);
        print_map();

        //enemy's turn
        cnt++;
        put_stone(enemy_turn(),2);
        print_map();

        //winner check
        end=end_check();
        if(end!=0)
        {
            printf("\nPlayer%d Wins!\n",end);
            return 0;
        }
    }
    printf("\nDraw!\n",end);
    return 0;
}
int my_turn()
{
    int i,max,p;
    for(i=0;i<M;i++)
        w[i]=0;
    for(i=0;i<M;i++)
    {
        //row i is not full
        if(a[0][i]==0)
        {
            //top_stone is enemy's
            if(top_stone(i)==2)
                w[i]=10;
            //pass here -> lose
            put_stone(i,2);
            if(end_check()==2)
                w[i]=99998;
            remove_stone(i);
            //put here -> win
            put_stone(i,1);
            if(end_check()==1)
                w[i]=99999;
            remove_stone(i);
        }
        else
            w[i]=-99999;
    }
    max=p=-100000;
    for(i=0;i<M;i++)
    {
        if(max<w[i])
        {
            max=w[i];
            p=i;
        }
    }
    return p;
}
int enemy_turn()
{
    int p;
    do
    {
        p=rand()%M;
    }while(a[0][p]!=0);
    return p;
}

void put_stone(int col, int team)
{
    int i;
    for(i=N-1;i>=0;i--)
    {
        if(a[i][col]==0)
        {
            a[i][col]=team;
            return;
        }
    }
    assert(1);
}
void remove_stone(int col)
{
    int i;
    for(i=0;i<N;i++)
    {
        if(a[i][col]!=0)
        {
            a[i][col]=0;
            return;
        }
    }
    assert(1);
}
int top_stone(int col)
{
    int i;
    for(i=0;i<N;i++)
    {
        if(a[i][col]!=0)
            return a[i][col];
    }
    assert(1);
}
void print_map()
{
    int i,j;
    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            if(a[i][j]==0)
                printf("- ");
            else if(a[i][j]==1)
                printf("@ ");
            else
                printf("# ");
        }
        printf("\n");
    }
    printf("\n");
}
int end_check()
{
    int i,j,k,l;
    int xx[]={-1,-1,-1,0,0,1,1,1};
    int yy[]={-1,0,1,-1,1,-1,0,1};
    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            for(k=0;k<8;k++)
            {
                for(l=1;l<=CONNECT-1;l++)
                {
                    if(!(0<=i+xx[k]*l && i+xx[k]*l<N && 0<=j+yy[k]*l && j+yy[k]*l<M && a[i][j]==a[i+xx[k]*l][j+yy[k]*l]))
                        break;
                }
                if(l==CONNECT)
                    return a[i][j];
            }
        }
    }
    return 0;
}