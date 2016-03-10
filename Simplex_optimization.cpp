
#include<iostream>

using namespace std ;

int isbasic( int i , int basic[], int Constraints)                          // To find whether (i + 1)th variable is Basic 
	{
	 for( int j = 0 ; j < Constraints ; j++)
	    {
		if( i == basic[j] ) return j ;
	   }
	 return -1 ;
        }

int notallpositive( double ZCdiff[] , int Constraints )                    // To check whether all Zj - Cj are non-negative
    {
     for( int i = 0 ; i < Constraints ; i++)
	 {
	  if( ZCdiff[i] < 0 ) return 1 ;
	 } 
      return 0 ;
    }

int zeroZC( double ZCdiff[] , int num)                                      // To check the count of number of Zj - Cj = 0 ( for multiple solutions)
	{
          int count = 0 ;
	  for( int i =  0 ; i < num ; i++)
	     {
		if( ZCdiff[i] == 0 ) count++ ;
	      }
	   return count ; 
         } 


int main()
   {
     int Var ;
     int Constraints ;
     double MIN = 9999999 ;
     int MINpos = 0 ;
     cout << "Number of Variables:";
     cin >> Var ;
     cout << "Number of Constraints:";
     cin >> Constraints;
     cout << "Give the cost vectors:\n";
     double cost[Var + Constraints];                                          //The cost of each variable in finding max
     double constr[Constraints][Var + Constraints];                           //The constraints 
     double required[Constraints];                                            //The required variables ex: <= 4, here 4 is the required variable
     int basic[Constraints];                                                  //The position of all basic variables
     double Xbasic[Constraints];                                              //The value of the basic variables
     double MRR[Constraints];                                                 //The MRR values required to fill the next table
     double minMRR = 9999999 ;                                                //To find the min MRR
     int MRRpos = 0 ;                                                         //To find the leaving variable
     double zmax = 0 ;                                                        //To store the max value of Z
     double ZCdiff[Var + Constraints] ;                                       //To store Zj - Cj
     cout << "Max z = ";
     for( int i = 1 ; i <= Var ; i++)
       { 
        cout << "__ x" << i ;
        if( i != Var ) cout << " + " ;
       }
     cout << endl ;

     for( int i = 0 ; i < Var ; i++)
        {
         cin >> cost[i] ;
        }
     for( int i = Var ; i < Var + Constraints ; i++)
	{ cost[i] = 0 ; }
    
     cout << "Give the Constraints:";
       for( int i = 1 ; i <= Var ; i++)
       {
        cout << "__ x" << i ;
        if( i != Var ) cout << " + " ;
       }
     cout << " <= __" << endl ;
     for( int i = 0 ; i < Constraints ; i++)
	{ int k = i + 1 ;
         cout << "Constraint " << k << endl ;
	
	for( int j = 0 ; j <= Var + Constraints ; j++)
	   {
            if( j < Var )cin >> constr[i][j];
            else if( j == Var + Constraints ) cin >> required[i] ;
            else { if( j - Var == i ) constr[i][j] = 1 ;
		   else constr[i][j] = 0 ;
		}
           }
        }
	

     for( int i = 0 ; i < Constraints ; i++)
	 {
	  basic[i] = i + Var ;
          Xbasic[i] = required[i];
         }

     for( int i = 0 ; i < Var + Constraints ; i++)
	{
         double x = 0 ;
         if( isbasic( i , basic, Constraints ) != -1 ) { ZCdiff[i] = 0 ;
				                   continue ;
				                 }
	 for( int j = 0 ; j < Constraints ; j++)                                     //Finding Zj - Cj where Zj =sum(cost[basic[j]] * Yj) 
	    {
	     x += cost[basic[j]] * constr[j][i];
            }
          ZCdiff[i] = x - cost[i];
          
          if( ZCdiff[i] < MIN ) {MIN = ZCdiff[i] ;
				 MINpos = i ;
				}
         }
     
     MIN = 9999999;
      while( notallpositive(ZCdiff,Constraints) )
	{
          minMRR = 9999999;
          for( int i = 0 ; i < Constraints ; i++)
	 {
	 if( constr[i][MINpos] != 0 ){MRR[i] = ( Xbasic[i] ) / constr[i][MINpos];
                                      if( MRR[i] < 0 ) MRR[i] = -9;
				      if( MRR[i] < minMRR && MRR[i] > 0 ) {minMRR = MRR[i] ;
                                                                           MRRpos = i;}
                                     }
	 else MRR[i] = -9;
         }
      if( minMRR == 9999999 ) { cout << "The solution is unbounded( feasible )" << endl ;
				return 0 ;
			      }
         basic[MRRpos] = MINpos ;
         for( int i = 0 ; i < Constraints ; i++)
	    {
	     if( i == MRRpos ) continue ;
             double mult = constr[i][MINpos];
             for( int j = 0 ; j < Var + Constraints ; j++)                                    //Finding Yj for next table( by row transformation)
		{
		 constr[i][j] = constr[i][j] - ((mult * constr[MRRpos][j])/constr[MRRpos][MINpos]);
                }
             Xbasic[i] = Xbasic[i] - ((mult * Xbasic[MRRpos])/constr[MRRpos][MINpos]);
            }
         Xbasic[MRRpos] = minMRR ;
            double div = constr[MRRpos][MINpos] ;
            for( int j = 0 ; j < Var + Constraints ; j++)
		{
		 constr[MRRpos][j] = constr[MRRpos][j]/div;
               
                }
       
          for( int i = 0 ; i < Var + Constraints ; i++)
	{
         
         if( isbasic( i , basic, Constraints ) != -1) { ZCdiff[i] = 0 ;
				                   continue ;
				                 }
         ZCdiff[i] = 0 ;
	 for( int j = 0 ; j < Constraints ; j++)
            {
	     float t = cost[basic[j]] * constr[j][i];
             ZCdiff[i] += t ;
            }
          ZCdiff[i] = ZCdiff[i] - cost[i];
          if( ZCdiff[i] < MIN ) {MIN = ZCdiff[i] ;
				 MINpos = i ;
				}
         }
         double z = 0 ;
         for( int i = 0 ; i < Constraints ; i++)
	    {
	     z += cost[basic[i]] * Xbasic[i] ;
	    }
         if( z > zmax ) zmax = z ;
    
          }
         cout << "Z* = " << zmax << endl ;
        if( zeroZC(ZCdiff , Var + Constraints ) > Constraints ) cout << "Solution 1:\n" ;
        for( int i = 0 ; i < Var ; i++)
	   {
            int t = i + 1 ;
            int pos ;
	    if( (pos = isbasic( i , basic , Constraints )) != -1 ) cout << "x" << t << "* = " << Xbasic[pos] << endl ;
            else cout << "x" << t << "* = 0" << endl ;
           }
        if( zeroZC( ZCdiff, Var + Constraints) > Constraints ) { for( int i = 0 ; i < Var + Constraints ; i++)
								     {
									if( ZCdiff[i] == 0 && isbasic( i , basic , Constraints) == -1) {
         										 cout << i << endl ;
											 minMRR = 9999999;
          MINpos = i;
          for( int i = 0 ; i < Constraints ; i++)
	 {
	 if( constr[i][MINpos] != 0 ){MRR[i] = ( Xbasic[i] ) / constr[i][MINpos];
                                      if( MRR[i] < 0 ) MRR[i] = -9;
				      if( MRR[i] < minMRR && MRR[i] > 0 ) {minMRR = MRR[i] ;
                                                                           MRRpos = i;}
                                     }
	 else MRR[i] = -9;
         }
      if( minMRR == 9999999 ) { cout << "The solution is unbounded( feasible )" << endl ;
				return 0 ;
			      }
         basic[MRRpos] = MINpos ;
         for( int i = 0 ; i < Constraints ; i++)
	    {
	     if( i == MRRpos ) continue ;
             double mult = constr[i][MINpos];
             for( int j = 0 ; j < Var + Constraints ; j++)
		{
		 constr[i][j] = constr[i][j] - ((mult * constr[MRRpos][j])/constr[MRRpos][MINpos]);
                }
             Xbasic[i] = Xbasic[i] - ((mult * Xbasic[MRRpos])/constr[MRRpos][MINpos]);
            }
         Xbasic[MRRpos] = minMRR ;
         cout << "Solution 2:\n" ;
   for( int i = 0 ; i < Var ; i++)
	   {
            int t = i + 1 ;
            int pos ;
	    if( (pos = isbasic( i , basic , Constraints )) != -1 ) cout << "x" << t << "* = " << Xbasic[pos] << endl ;
            else cout << "x" << t << "* = 0" << endl ;
           }
      cout << "There are infinte solutions for the variables with Z* = " << zmax << endl ;
		}
        
       } 
       
     } 
          



     return 0 ;
    }
