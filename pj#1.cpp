#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <set>
#define M 10
#define N 10
using namespace std;

int sudoku[M][N]={};		// real sudoku 
int rec[M][N]={};		// record the initial value
int order[81][2]={};
int row[M][N]={}; 		// row[i][num] means the row i has appeared # num
int col[M][N]={};
int sqr[M][N]={};
int c=0;
bool flag=false;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int DFS(int cell)
{
	int a,b,x;
	a=cell/9+1;  // row
	b=cell%9+1;  // col
	x=((a-1)/3)*3+(b-1)/3+1;
	
	if(c>80)
	{
		flag=true;
		return 0;
	} 
	
	if(sudoku[a][b]!=0)
	{
		c++;
		DFS(order[c][0]);
	}
	else
	{
		for(int val=9;val>=1;val--)
		{
			if(row[a][val]==1 || col[b][val]==1 || sqr[x][val]==1)
				continue;
			
			int tmp=c;
			sudoku[a][b]=val;
			row[a][val]=1;
			col[b][val]=1;
			sqr[x][val]=1;
			
			c++;
			DFS(order[c][0]);
			
			if(!flag)
			{
				c=tmp;
				sudoku[a][b]=0;
				row[a][val]=0;
				col[b][val]=0;
				sqr[x][val]=0;
				order[c][1]--;
			}
			else
				return 0;
		} 
	}
}
// DFS find the next cell ,if the outcome is false,then return the upper result

int Cmp(const void *lhs, const void *rhs) 
{
    return ((const int *)rhs)[1]-((const int *)lhs)[1];
}

int main()
{
	ifstream fin("pj#1_test_data.txt");
	string inputstr;
	set<int> sn;
	int a,b,color;
	int count[M][N]={};   // count the degree of the cell
	
	while(getline(fin,inputstr))
	{
		a = inputstr[0]-'0';
		b = inputstr[2]-'0';
		color = inputstr[4]-'0';;
		
		sudoku[a][b]=color;    	
		rec[a][b]++;
	}
	// coloring
	
	for(int i=1;i<M;i++)
	{
		for(int j=1;j<N;j++)
		{
			int w,t;
			w=(i-1)/3;
			t=(j-1)/3;
			
			if(sudoku[i][j]!=0)
			{
				int num=sudoku[i][j];
				int x=w*3+t+1;
				row[i][num]=1;
				col[j][num]=1;
				sqr[x][num]=1;
				
				continue;
			}
			
			for(int k=1;k<M;k++)
			{
				if(k!=i)
					sn.insert(sudoku[k][j]);
				if(k!=j)
					sn.insert(sudoku[i][k]);
			}
				
			for(int k=w*3+1;k<=(w+1)*3;k++)
			{
				for(int l=t*3+1;l<=(t+1)*3;l++)
				{
					if(k!=i && l!=j)
						sn.insert(sudoku[k][l]);
				}
			}
			
			count[i][j]=sn.size()-1;
			sn.clear();
		}
	}
	// record each cell's degree
	// record used color
	
	for(int i=0;i<81;i++)
	{
		order[i][0]=i;
	}
	
	for(int i=1;i<M;i++)
	{
		for(int j=1;j<N;j++)
		{
			order[(i-1)*9+j-1][1]=count[i][j];
		}
	}
	// order[81][2] records each cell's degree.
	
	qsort(order,81,sizeof(order[0]),Cmp);
	// descending order order[81][2]
	
	DFS(order[c][0]);
	
	cout << endl;

	for(int i=1;i<M;i++)
	{
		for(int j=1;j<N;j++)
		{
			if(i==1 && j==1) 
			{
				SetConsoleTextAttribute(hConsole, 15);
				cout << " ------------------------- " << endl;
			}	
				
			if(j==1) 
			{
				SetConsoleTextAttribute(hConsole, 15);
				cout << " | ";
			}	
			
			if(rec[i][j]==0)
			{
				SetConsoleTextAttribute(hConsole, 10);
				cout << sudoku[i][j] << " ";
			}
			else
			{
				SetConsoleTextAttribute(hConsole, 15);
				cout << sudoku[i][j] << " ";
			}
			if(j%3==0) 
			{
				SetConsoleTextAttribute(hConsole, 15);
				cout << "| " ;
			}
			if(i%3==0 && j==9) 
			{
				SetConsoleTextAttribute(hConsole, 15);
				cout << endl << " ------------------------- " << endl;
			}
			else if(j==9) cout << endl;
		}
	}
	
	cout << endl;

	system("pause");
	return 0;
 }
