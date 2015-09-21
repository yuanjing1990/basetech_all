import java.lang.*;
import java.awt.*;
import javax.swing.*;
public class BoundBall
{
	public static void main(String args[])
	{
		int input = 0;
		System.out.println("Begin");
		ChessBoard cb = new BoundChessBoard();
	}
}

abstract class ChessBoard extends JFrame
{
	public abstract boolean Init();
	public abstract void Draw();
	public abstract int GetInput();
	public abstract boolean Next(int input);
	public abstract boolean MoveFocus(int row,int col);
}
class BoundChessBoard extends ChessBoard
{
	public BoundChessBoard()
	{
		m_level = 1;
		m_curnum = m_level * 3;
		m_currow = m_curcol = 1;
		m_chessman = new ChessMan[64];
		Init();
	}
	public boolean Init()
	{
		if(m_chessman.length < 64)
			return false;
		setLayout(new GridLayout(8,8));
		for(int x = 0; x < 8; ++x)
			for(int y = 0; y <8; ++y)
			{
				m_chessman[x+8*y] = new ChessMan(x,y);
			//	add(m_chessman[x+8*y]);
			}
		int n = m_curnum;
		setSize(640,640);
		setVisible(true);
		
		return true;
	}
	public void Draw()
	{
	}
	public int GetInput()
	{
		//BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int key = 0;
		while(true)
		{
			try{
				key = System.in.read();
				switch(key)
				{
					case 'a':
					case 'w':
					case 'd':
					case 's':
						return key;
					case 'q':
						System.exit(0);
					case 37:
						return 5;
					case 38:
						return 6;
					case 39:
						return 7;
					case 40:
						return 8;
					default:
						;
				}
			}
			catch(Exception e)
			{
				return 0;
			}
		}
	}
	public boolean Next(int input)
	{
		InputFactory ifac = new InputFactory(this);
		Input inp = ifac.CreateInput(input);
		inp.HandleInput();
		return true;
	}
	public boolean MoveFocus(int rdir,int cdir)
	{
		m_currow += rdir;
		m_curcol += cdir;
		if(m_currow > 8 || m_currow <= 0 || m_curcol > 8 || m_curcol <= 0)
		{
			m_currow -= rdir;
			m_curcol -= cdir;
		}
		return true;
	}
	private ChessMan[] m_chessman;
	private int m_currow,m_curcol;
	private int m_level;
	private int m_curnum;
}
class ChessMan
{
	int x,y;
	ChessMan(){x = 0;y = 0;}
	ChessMan(int x,int y){
		this.x = x;
		this.y = y;
	}
	public void setX(int x){this.x = x;}
	public void setY(int y){this.y = y;}
	public int getX(){return x;}
	public int getY(){return y;}
	public void setXY(int x,int y){this.x = x;this.y = y;}
}

class BlockChessMan extends ChessMan
{
	BlockChessMan(int x,int y){}
}

class MainChessMan extends ChessMan
{
	
}

class BlankChessMan extends ChessMan
{
	
}


class InputFactory
{
	public InputFactory(ChessBoard cb)
	{
		m_cb = cb;
	}
	public Input CreateInput(int n)
	{
		switch(n)
		{
			case 'a':
				return new LeftInput(m_cb);
			case 'w':
				return new UpInput(m_cb);
			case 'd':
				return new RightInput(m_cb);
			case 's':
				return new DownInput(m_cb);
			default:
				return null;
		}
	}
	private ChessBoard m_cb;
}
abstract class Input
{
	abstract public void HandleInput();
}
class LeftInput extends Input
{
	private ChessBoard m_cb;
	public LeftInput(ChessBoard cb){ m_cb = cb;};
	public void HandleInput()
	{
		m_cb.MoveFocus(0,-1);
	}
}
class RightInput extends Input
{
	private ChessBoard m_cb;
	public RightInput(ChessBoard cb){ m_cb = cb;}
	public void HandleInput()
	{
		m_cb.MoveFocus(0,1);
	}
}
class UpInput extends Input
{
	private ChessBoard m_cb;
	public UpInput(ChessBoard cb){ m_cb = cb;};
	public void HandleInput()
	{
		m_cb.MoveFocus(-1,0);
	}
}
class DownInput extends Input
{
	private ChessBoard m_cb;
	public DownInput(ChessBoard cb){ m_cb = cb;};
	public void HandleInput()
	{
		m_cb.MoveFocus(1,0);
	}
}