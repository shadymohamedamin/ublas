#include<bits/stdc++.h>
using namespace std;
int A[3][2],B[3][2],C[3][2];
/*void intialise_matrix(int A[],int r,int c)
{
  int A[3][2],B[3][2];
for(int i=0;i<3;i++)
{
  for(int j=0;j<2;j++)
  {
 A[i][j]=0;   
  }
}*/
  return 
}
int main()
{
int r=3,c=2;
int A[3][2],B[3][2],C1[3][2],C2[3][2],C3[3][2],C4[3][2],C5[3][2],C6[3][2];
for(int i=0;i<3;i++)
{
  for(int j=0;j<2;j++)
  {
 A[i][j]=0;   
  }
}
for(int i=0;i<3;i++)
{ 
  for(int j=0;j<2;j++)
  {
 B[i][j]=0;   
  }
}
  for(int i=0;i<3;i++)
{
  for(int j=0;j<2;j++)
  {
 C1[i][j]=A[i][j]+B[i][j];   
  }
}
  for(int i=0;i<3;i++)
{
  for(int j=0;j<2;j++)
  {
 C2[i][j]=2*A[i][j];   
  }
}

for(int i=0;i<3;i++)
{
  for(int j=0;j<2;j++)
  {
 C3[i][j]=2*A[i][j];   
  }
}
  

for(int i=0;i<3;i++)
{
  for(int j=0;j<2;j++)
  {
 C4[i][j]=A[i][j]*B[i][j];   
  }
}
  
  for(int i=0;i<3;i++)
{
  for(int j=0;j<2;j++)
  {
 C5[i][j]=A[j][i];   
  }
}
  
  int s=0;
  
  for(int i=0;i<3;i++)
{
  for(int j=0;j<2;j++)
  {
    if(A[i][j]==B[i][j])
      s++;
 //C3[i][j]=2*A[i][j];   
  }
}
  
  int y=A[2][1];
  
   for(int i=0;i<3;i++)
{
  for(int j=0;j<2;j++)
  {
    if(A[i][j]>=1&&A[i][j]<=3)
       C6[i][j]=A[i][j];
    else C6[i][j]=0;
 
  }
}
   tuple<int,int,int>t1;
  t1=make_tuple(1,2,3);
  tie(f1,f2,f3)=t1;
  cout<<f1<<endl;
  cout<<f2<<endl;
  cout<<f3<<endl;
  
  
  

return 0;
}
