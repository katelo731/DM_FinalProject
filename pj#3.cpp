#include <iostream>
using namespace std;

const int x=3500;
int v,i,j,k,count=1;
int m1[x][x]={};
int m2[x][x]={};
int m3[x][x]={};
int s[x][x]={};

void mul(int a[][x],int b[][x],int c[][x])
{
	for(i=0;i<v;i++)
	{
		for(j=0;j<v;j++)
		{
			for(k=0;k<v;k++)
			{
				c[i][j]+=a[i][k]*b[k][j];
			}	
		}
	}
} 

bool check(int m[][x])
{
	bool f=false;
	
	for(i=0;i<v;i++)
	{
		for(j=0;j<v;j++)
		{
			if(i!=j && m[i][j]==0)
			f=true;
		}
	}
	return f;
}

void find(int a[][x],int b[][x],int c[][x])
{
	if(!check(s))
		return;
	
	if(count%2==1)
	{
		if(count!=1)
		mul(a,c,b);
		
		count++;
		
		for(i=0;i<v;i++)
		{
			for(j=0;j<v;j++)
			{
				if(i!=j && s[i][j]==0 && b[i][j]!=0)
					s[i][j]=1;
			}
		}
	}
	else
	{
		mul(a,b,c);
		
		count++;
		
		for(i=0;i<v;i++)
		{
			for(j=0;j<v;j++)
			{
				if(i!=j && s[i][j]==0 && c[i][j]!=0)
					s[i][j]=1;
			}
		}	
	}
	
	find(a,b,c);
}

int main()
{
	int a,b,sum=0;
	bool flag=false;
	
	cin >> v;

	while(cin >> a >> b)
	{
		m1[a][b]=1;
		m1[b][a]=1;
		s[a][b]=1;
		s[b][a]=1;
	}
	
	mul(m1,m1,m2);
	mul(m1,m2,m3);
	
	for(i=0;i<v;i++)
	{
		sum+=m3[i][i];
	}
	
	cout << sum/6 << " ";
	
	find(m1,m2,m3);
	
	cout << count;
	
	system("pause");
	return 0;
 }
