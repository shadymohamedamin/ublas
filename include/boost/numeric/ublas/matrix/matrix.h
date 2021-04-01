using namespace std;
templete<class T>
typedef unsigned long long ll;
class Matrix{
  
  public:
  
  //pointer to a series of pointer 
  
  ll **matrix;
  
  Matrix();//constructor
  ~Matrix(); //deconstructor
  Matrix(ll r,ll c);
  
  //setsize method-- reisize the matrix 
  
  ll **setSize(ll r,ll c);
  
  //getMatrix setting
  
  ll *getMatrix();
  //getRow method -- will return the pointer of the begin of the array[x,0]
  ll *getRow(ll r);
  // getColumn method -- will return the pointer of the begin of the array[0,y]
  ll *getColumn(ll c);
  //destructor method -- will deallocate the memory used by matrix 
  
/*void zeros(unsigned r,unsigned c)
{
   unsigned matrix_[r+1][c+1];
   for(unsigned i=1;i<=r;i++)
   {
     for(unsigned i=1;i<=r;i++)
     {
     matrix_[i][j]=0;
     }
   }
}*/
  
  
  private:
  ll r,c;
  
  
};
