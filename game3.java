import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.event.KeyEvent;
import javax.swing.ImageIcon;
import java.awt.event.KeyListener;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import java.awt.Rectangle;
import java.awt.Image;
import java.util.*;
import java.awt.Toolkit;
import java.awt.Color;


@SuppressWarnings("serial")
class game3 extends JPanel{


//ArrayList<Fruit> f = new ArrayList<Fruit>() ;
Fruit f = new Fruit(this) ;
Snake s = new Snake(this) ;
Grid grid = new Grid(this) ;

int x = 0 ;


public game3(){
              addKeyListener(new KeyListener(){
			      @Override
			      public void keyTyped(KeyEvent e)
					{}
			      public void keyReleased(KeyEvent e)
					{
					}
			      public void keyPressed(KeyEvent e)
					{ s.keyPressed(e);
					}
				});
		setFocusable(true);
                }
		                  

public void gameOver() {
           JOptionPane.showMessageDialog(this,"You lost the game!\nYour score is " + s.SCORE,"Game Over",JOptionPane.YES_NO_OPTION);
	   System.exit(ABORT);
			}
private void move()
  {
   s.move() ;
   
  }

@Override
	public void paint(Graphics g) {
		super.paint(g);
		Graphics2D g2d = (Graphics2D) g;
		    g2d.drawString("SCORE:"+s.SCORE,200,30);
		  grid.paint(g2d) ;
		f.paint(g2d) ;		
                s.paint(g2d) ;
	//	g2d.setStrokeStyle(2);
//                g2d.drawString("SCORE:"+s.SCORE,200,30);
		g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
				RenderingHints.VALUE_ANTIALIAS_ON);
		             
	}


public static void main(String[] args) throws InterruptedException{
		JFrame frame = new JFrame("SNAKE");
                game3 Game = new game3();
                frame.add(Game);
                frame.setSize(500,400);
                frame.setResizable(false);
                frame.setVisible(true);
                frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		while(true){
                    Game.move();
                    Game.x += 1 ;
                    if( Game.x == 500 ) Game.x = 0 ;
		    Game.repaint();
		    if( Game.f.eaten == 1 ) { Game.f.eaten = 0 ;
					      Game.f.Generate() ;
					}
		    Thread.sleep(70);
		   }
	}

}

class Grid{

   private game3 ga ;
   public Grid( game3 g )
	   {
	    ga = g ;
	   }
	
   public void paint(Graphics2D g )
	  {
	   for( int i = 0 ; i < 500 ; )
		{
		 for( int j = 0 ; j < 400 ; )
			{
			 g.setColor(Color.gray) ;
			 g.fillRect( i , j , 20 , 1 ) ;
			 j += 20 ;
			 
			}
		i += 20 ;
		}
	for( int i = 0 ; i < 500 ; )
                {
                 for( int j = 0 ; j < 400 ; )
                        {
			 g.setColor(Color.gray) ;
                         g.fillRect( i , j , 1 , 20 ) ;
                         j += 20 ;

                        }
                i += 20 ;
                }

	}
}		  



class Fruit {
	int x , y ;
	private game3 ga ;
	int eaten ;	

	public Fruit( game3 g )
		{
		 ga = g ;
		 x = 80 ;
		 y = 80 ;
		 eaten = 0 ;
		}

	public void Generate()
		{
			Random rn = new Random() ;
			x = rn.nextInt(500) ;
			y = rn.nextInt(400) ;
			x = (x/20) * 20 ;
			y = (y/20) * 20 ;
		//	System.out.println( x + " " + y ) ;
		}

	public void paint(Graphics2D g)
		{       
			g.setColor(Color.orange) ;
			g.fillOval( x , y , 20 , 20 ) ;
		}

	

	public Rectangle getBounds()
		{
			return new Rectangle( x , y , 20 , 20 ) ;
		}

	     }


class Pellet{

int x ;
int y ;
int id ;
int xa , ya ;
private game3 ga ;
public Pellet( int xs , int ys , int xas , int yas , game3 g , int ids)
	{
	 x = xs ;
	 y = ys ;
	 xa = xas ;
	 ya = yas ;
	 ga = g ;
	 id = ids ;
	}

public void move()
	{
	 x = x + xa ;
	 y = y + ya ;
	
	 if( x > 480 ) { x = 0 ; }
	 if( y > 380 ) { y = 0 ; }
	 if( x < 0 ) { x = 500 ; }
	 if( y < 0 ) { y = 400 ; }
	 if(  id == 0  && collision2() ) { ga.gameOver() ; }
	}


public boolean collisionfruit()
		{
			return ga.f.getBounds().intersects(getBounds()) ;
		}

public boolean collision2()
		{
		 for( int i = 0 ; i < ga.s.parts.size() ; i++)
			{
			  Pellet p = ga.s.parts.get(i) ;
			  if( id == p.id ) { continue ; }
			  if( i == ga.s.parts.size() - 1 && xa == p.xa && ya == p.ya ) continue ;
			  if( p.getBounds().intersects(getBounds()) ) { return true ; }
			}
		 return false ;
		}

public void paint(Graphics2D g)
	{
	  g.fillRect( x , y , 20 , 20 ) ;  
	}

public void paint2(Graphics2D g)
       {
          if( id % 4 == 0 ) { g.setColor(Color.red) ; }
          else if( id % 4 == 1 ) { g.setColor(Color.blue) ; }
          else if( id % 4 == 2 ) { g.setColor(Color.orange) ; }
          else g.setColor(Color.yellow) ;
       }

public Rectangle getBounds()
	{
	  return new Rectangle( x , y , 20 , 20 ) ; 
	
	} 


}

class Snake{


int length = 100;
int x = 180 ;
int SCORE = 0 ;
int y = 320 ;
int ya = 0 ;
int xa = 2 ;
int id = 0 ;

ArrayList<Pellet> parts = new ArrayList<Pellet>() ;

ArrayList<Integer> xchanges = new ArrayList<Integer>() ;
ArrayList<Integer> ychanges = new ArrayList<Integer>() ;
ArrayList<Integer> pos = new ArrayList<Integer>() ;
ArrayList<Integer> turn = new ArrayList<Integer>() ;


private game3 ga;

public Snake( game3 g )
  {
   ga = g ;
   for( int i = 0 ; i < 5 ; i++)
	{
	 Pellet p = new Pellet( x , y , 20 , 0 , g , id ) ;
	 parts.add( p ) ;
	 x -= 20 ;
	 id++ ;
	} 
  }

public void move()
      { 
	for( int i = 0 ; i < xchanges.size() ; i++)
	    {
		for( int j = pos.get(i) ; j < parts.size() ; j++ )
		    { 
                      
			Pellet p2 = parts.get( j ) ;
			if( xchanges.get(i) == p2.x && ychanges.get(i) == p2.y ) {  
										 if( turn.get( i ) == 1 ) {parts.get(j).xa = 20 ;
													     parts.get(j).ya = 0 ;
													    }
										else if( turn.get( i ) == -1 ) {parts.get(j).xa = -20 ;
													     parts.get(j).ya = 0 ;
														
													     }
										else	if( turn.get( i ) == 2 ) {parts.get(j).xa = 0 ;
													     parts.get(j).ya = 20 ;
													    }
										else {parts.get(j).xa = 0 ;
											parts.get(j).ya = -20 ;
										       }
										 if( j == parts.size() - 1 ) { xchanges.remove( i ) ;
														ychanges.remove( i ) ;
														turn.remove( i ) ;
														pos.remove( i ) ;
														i-- ;
														}
										 
										}
		   }
	  }
			
        for( int i = 0 ; i < parts.size() ; i++)
	   {
	     Pellet p = parts.get(i) ;
	     p.move() ;
	   }

        if( collision2() ) { ga.f.Generate() ; } 
	if( collision() ) { 
			    Pellet last = parts.get( parts.size() - 1 ) ;
			    Pellet pnew ;
			    if( last.xa == 20 ) { pnew = new Pellet( last.x - 20 , last.y , 20 , 0 , ga , id ) ; }
			    else if( last.xa == -20 ) { pnew = new Pellet( last.x + 20 , last.y , -20 , 0 , ga , id ) ; }
			    else if( last.ya == 20 ) { pnew = new Pellet( last.x , last.y - 20 , 0 , 20 , ga , id ) ; }
			    else { pnew = new Pellet( last.x , last.y + 20 , 0 , -20 , ga , id ) ; }
			    id++ ;
			    parts.add( pnew ) ;
			    SCORE += 1 ;
			    ga.f.eaten = 1 ; }
      }

public boolean collision()
		{
			return parts.get(0).collisionfruit() ;
		}

public boolean collision2()
		{
		 for( int i = 1 ; i < parts.size() ; i++)
			{
			 if( parts.get(i).collisionfruit() ) return true ;
			}
		 return false ;
		}

public void paint(Graphics2D g)
	{
	  //if( xa == 0 ) { g.fillRect( x , y , 5 , length ) ; }
	  //else g.fillRect( x , y , length , 5 ) ;
	  for( int i = 0 ; i < parts.size() ; i++)
		{
                  parts.get(i).paint2( g ) ;
		  parts.get(i).paint( g ) ;
		} 
	}

public Rectangle getBounds()
	{
	  if( xa == 0 )return new Rectangle( x , y , 20 , length ) ; 
	  else return new Rectangle( x, y , length , 20 ) ;
	} 


public void keyReleased( KeyEvent e )
	{
	 }

public void keyPressed( KeyEvent e )
	{
	 if( e.getKeyCode() == KeyEvent.VK_LEFT )
	      {
	       
		if( xa == 2 ) { } 
		else if( xa == -2 ) { }
		else { xa = -2 ;
		 	ya = 0 ;
		 xchanges.add( parts.get(0).x ) ;
		ychanges.add( parts.get(0).y ) ;
		pos.add( 0 ) ;
		turn.add( -1 ) ;
			}
		}
	if( e.getKeyCode() == KeyEvent.VK_RIGHT )
	      {
		 
		if( xa == 2 ) { } 
		else if( xa == -2 ) { }
		else { xa =  2 ;
		 	ya = 0 ;
			xchanges.add( parts.get(0).x ) ;
		ychanges.add( parts.get(0).y ) ;
		pos.add( 0 ) ;
		turn.add( 1 ) ;
			}
		}
	if( e.getKeyCode() == KeyEvent.VK_UP )
	      { 
		
		if( ya == 2 ) { } 
		else if( ya == -2 ) { }
		else { ya =  -2 ;
		 	xa = 0 ;
			 xchanges.add( parts.get(0).x ) ;
		ychanges.add( parts.get(0).y ) ;
		pos.add( 0 ) ;
		turn.add( -2 ) ;
			}
		}
	if( e.getKeyCode() == KeyEvent.VK_DOWN )
	      {
		
		if( ya == 2 ) { } 
		else if( ya == -2 ) { }
		else { ya = 2 ;
		 	xa = 0 ;
			 xchanges.add( parts.get(0).x ) ;
		ychanges.add( parts.get(0).y ) ;
		pos.add( 0 ) ;
		turn.add( 2 ) ;
			}
		}
	}
}










