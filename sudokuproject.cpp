#include<iostream>

using namespace std;
int f=1;
int rows[9][9]={0};
int coloums[9][9]={0};
int quad[9][9]={0};
int arr[9][9];
int check[9][9]={0};
void set_rows_coloums_quad();
int checksudoku();
int findno(int,int);
void sudoku(int,int);
void set_rows_coloums_quad()
{
    int i,j,t,t1;
    for(i=0;i<9;i++)
    {
        t1=i/3;
        t1=t1*3;
        for(j=0;j<9;j++)
        {
            if(arr[i][j])
            {
                t=arr[i][j];
                rows[i][t-1]++;
                coloums[t-1][j]++;
                quad[t1+(j/3)][t-1]++;
            } 
            else
            {
                check[i][j]=1;
            }
            
        }
    }
}
int checksudoku()
{
    int i,j,f=0;
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            if(rows[i][j]>1||coloums[i][j]>1||quad[i][j]>1)
            return -1;
            if(!rows[i][j]||!coloums[i][j]||!quad[i][j])
            f=1;
        }
    }
    if(f==0)
    return 0;
    return 1;
}
int findno(int i,int j)
{
    int k,q,t;
    q=i/3;
    q=q*3;
    q+=(j/3);
    t=arr[i][j];
    if(t)
    {
        rows[i][t-1]=0;
        coloums[t-1][j]=0;
        quad[q][t-1]=0;
    }
    for(k=t+1;k<10;k++)
    {
            if(!rows[i][k-1]&&!coloums[k-1][j]&&!quad[q][k-1])
            {
                arr[i][j]=k;
                rows[i][k-1]++;
                coloums[k-1][j]++;
                quad[q][k-1]++;
                return k;
            }
    }
    return 0;
}

void sudoku(int i,int j)
{
    if(check[i][j])
    {
        if(j<8)
        {
            if(findno(i,j))
                sudoku(i,j+1); 
            else
            {
                arr[i][j]=0;
                return;
            }
            if(f)
                sudoku(i,j);
            return;
        }
        if(j==8)
        {
            if(i<8)
            {
                if(findno(i,j))
                    sudoku(i+1,0);
                else
                {
                    arr[i][j]=0;
                    return;    
                }
                if(f)
                    sudoku(i,j);
                return;
            }
            else
            {
                f=0;
                findno(i,j);
                return;
            }          
        }    
    }
    if(j<8)
    {
        sudoku(i,j+1);
    } 
    if(j==8)
    {
        if(i<8)
            sudoku(i+1,0);
        else
            f=0;
    }
}
int main()
{
    int i,j;
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        cin>>arr[i][j];
    }
    set_rows_coloums_quad();
    cout<<"\n";
    int check=checksudoku();
    if(check==-1)
        cout<<"Invalid Sudoku\n";
    else if(check==0)
        cout<<"Sudoku Already Completed\n";
    else
    {
        sudoku(0,0);
        for(i=0;i<9;i++)
        {
        for(j=0;j<9;j++)
        cout<<arr[i][j]<<" ";
        cout<<"\n";
        }
    }
    return 0; 
}
