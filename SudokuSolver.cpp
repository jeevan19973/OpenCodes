#include<iostream>

using namespace std ;

void same( int dup[][9] , int sudoku[][9] ) ;

void solution( int sudoku[][9]) ;

int isfull( int sudoku[][9] ) ;

void print( int dup[][9] ) 
      {
        for( int i = 0 ; i < 9 ; i++)
	   {
	   for( int j = 0 ; j < 9 ; j++)
		{
		  cout << dup[i][j] << " " ;
                  if( (j + 1) % 3 == 0 ) cout << "| " ;
                }
           if( (i + 1) % 3 == 0 ) 
				cout << endl << "________________________";
           cout << endl ;
           }
       cout << endl << endl ;
      }    

int isbox( int sudoku[][9] , int num , int x , int y )
       {
        int pro3x = x / 3 ;
        int pro3y = y / 3 ;
        for( int i = 3 * pro3x ; i < 3 * ( pro3x + 1 ) ; i++)
	   {
	    for( int j = 3 * pro3y ; j < 3 * ( pro3y + 1 ) ; j++)
	       {
		if( sudoku[i][j] == num) return -1 ;
               }
           }
        return 1 ;
       }

int ispossible( int sudoku[][9] , int num , int x , int y )
	{
	  for( int j = 0 ; j < 9 ; j++)
	     {
	      if( sudoku[x][j] == num ) return -1 ;
             }
          for( int i = 0 ; i < 9 ; i++)
             {
              if( sudoku[i][y] == num ) return -1 ;
             }
         if( isbox( sudoku , num , x , y ) != 1) return -1 ;
          return 1 ;
       }



int main()
   {
    int ar[9][9] ;
    for( int i = 0 ; i < 9 ; i++)
	{
	for( int j = 0 ; j < 9 ; j++)
	    {
	      ar[i][j] = 0 ;
            }
        }

    cout << "Give Input" << endl ;
   /* bool flag = false ;
    while( !flag )
	{
	 cout << "Give x position and y position ( 0 - 8 )" << endl ;
         int x , y ;
         cin >> x >> y ;
         int c ;
         cout << "Give the number between 1 and 9 " << endl ;
         cin >> c ;
         if( c >= 1 && c <= 9 ) { ar[x][y] = c ; }
	 else { cout << "Please give a valid number " << endl ; }
         cout << "Exit(e) or Continue(c)" << endl ;
         char inp ;
         cin >> inp ;
         if( inp == 'e' ) { break ; }
         else continue ;
        }
    */
    for( int i = 0 ; i < 9 ; i++)
	{
	 for( int j = 0 ; j < 9 ; j++)
	    {
		 cin >> ar[i][j] ;
            }
       }
    cout << endl ;
        solution( ar ) ;


   return 0 ;
     }


void same( int dup[][9] , int sudoku[][9])
    {
     for( int i = 0 ; i < 9 ; i++)
	{
	 for( int j = 0 ; j < 9 ; j++)
	    {
		dup[i][j] = sudoku[i][j] ;
	    }
	}
      return ;
    }         

int isfull( int sudoku[][9] )
    {
     for( int i = 0 ; i < 9 ; i++)
	{
	for( int j = 0 ; j < 9 ; j++)
	   {
	    if( sudoku[i][j] == 0 ) return -1 ;
	   }
	}
	return 1 ;
    }

void solution( int ar[][9] )
     {
       int dup[9][9] ;
      same( dup , ar ) ;
       int flag = 0 ;
       if(isfull( dup ) == 1 ) { print( dup ) ;
                                 return  ;
                               }
       int xpos = 0 , ypos = 0 ;
       for(int i = 0 ; i < 9 ; i++)
	  {
	   for(int j = 0 ; j < 9 ; j++)
	      {
		if( dup[i][j] == 0 ) { xpos = i ; ypos = j ;
                                         break ;
					}
                else continue ;
                
	      }
         }
                for( int k = 1 ; k <= 9 ; k++)
		   {
		    if(ispossible( dup , k , xpos , ypos ) == 1 ) { flag = 1 ;
                                                         dup[xpos][ypos] = k ;
                                                             solution( dup ) ;
						            }
                   }
            
    //    cout << "not possible" << endl ;    
        return ;
    }

