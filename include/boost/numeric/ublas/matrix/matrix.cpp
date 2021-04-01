#include<bits/stdc++.h>
#include "matrix.h"

using namepsace std;
typedef unsigned long long ll;
int main()
{
 Matrix::Matrix()
 {
  matrix=alloc(0,0);
 }
 Matrix::Matrix(ll r,ll c)
 {
  matrix=alloc(r,c);
 }
void Matrix::dealloc()
{
for(ll i=0;i<rows;i++)
{
delete[] matrix[i];
}
 delete[]matrix;


}
ll **Matrix::alloc(ll rows,ll columns)
{
 r=rows;
 c=columns;
 
 ll **new_matrix=new ll*[rows];
 for(ll i=0;i<rows;i++)
 {
  new_matrix[i]=new ll[columns];
 }
 return new_matrix;
}
Matrix::MAtrix(){dealloc();}
 
 ll **Matrix::setSize(ll rows,ll columns)
 {
  if(rows>r&&columns>c)
  {
 ll **new_matrix=alloc(rows,columns); 
   for(ll i=0;i<rows;i++)
   {
    new_matrix[i]=matrix[i];
   }
   delloac();
   return new_matrix;
  }
  else 
  {
   return matrix;
  }
  
 }
 
 ll *Matrix::getMatrix(){
  ll *start=matrix[0];
  return start;
 }
 ll *Matrix::getRow(ll rows){
  if(rows>r)
  {
   cout<<"error in the index";
  }
  else 
  {
    ll *rowStart=matrix[rows];
  
  return rowStart;
  }
 
 }
 ll *Matrix::getColumns(ll columns){
  if(columns>c)
  {
   cout<<"error in the index";
  }
  else 
  {
    ll *columnsStart=&matrix[0][columns];
  
  return columnsStart;
  }
 
 }
 
  return 0;
}
