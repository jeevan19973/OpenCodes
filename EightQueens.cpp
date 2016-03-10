#include<iostream>

using namespace std ;

void eightqueen( char chess[][8] , int num );

void same( char dup[][8] , char chess[][8] ) ;


int count = 0 ;
int main()
   {

     char chess[8][8] ;
     for( int i = 0 ; i < 8 ; i++)
	{
	 for( int j = 0 ; j < 8 ; j++)
	    {
	     chess[i][j] = '.' ;
	    }
	}
     
    eightqueen( chess , 0 ) ;


     return 0 ;
   }


void same( char dup[][8] , char chess[][8] ) 
    {
     for( int i = 0 ; i < 8 ; i++)
	{
	for( int j = 0 ; j < 8 ; j++)
	  {
	   dup[i][j] = chess[i][j] ;
	  }
	}
    }
    


void eightqueen( char chess[][8] , int num )
    { 
      char dup[8][8] ;
      if( num == 8 ) { for( int i = 0 ; i < 8 ; i++)
			  {
			   for( int j = 0 ; j < 8 ; j++)
				{
				 cout << chess[i][j] << " ";
				}
                           cout << endl ;
			  } 
                       cout << endl << endl ;
                      // cout << ++count << endl ;
                        return ;
		     }

      for( int j = 0 ; j < 8 ; j++)
	 {
          same( dup , chess ) ;
	  if( dup[num][j] == '.') dup[num][j] = 'Q';
          else continue ;
          for( int k = 0 ; k < 8 ; k++)
	     {
	      if( k != j ) dup[num][k] = 'o';
             }
          for( int k = 0 ; k < 8 ; k++)
	     {
	      if( k != num ) dup[k][j] = 'o';
	     }
	  for( int k = -7 ; k < 8 ; k++)
	    {
	     if( (num + k >= 0) && (num + k <= 7) && ( j + k >= 0 ) && ( j + k <= 7 ) && k != 0 ) dup[num + k][j + k] = 'o' ;
             if( (num + k >= 0) && (num + k <= 7) && ( j - k >= 0 ) && ( j - k <= 7 ) && k != 0 ) dup[num + k][j - k] = 'o' ;
	    }
	  eightqueen( dup , num + 1 ) ;
	   }
	return ;
      }
