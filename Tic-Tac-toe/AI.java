package TicToe;

public class AI {

	private int depth;
	boolean isX;
	int[][] gameBoard;
	
	
	
	public AI(int[][] gameBoard,boolean X,int depth)
	{
		this.isX=X;
		this.gameBoard=gameBoard;
		this.depth=depth;
	}
	public boolean GameOver()
	{
		if(hasXwon() || hasOwon() || !freeMoves())
			return true;
		
		return false;
		
		
	}
	public boolean validMove(int x,int y)
	{
		if(x<0 || x>gameBoard.length || y<0 || y>gameBoard[x].length || gameBoard[x][y]!=0)
			return false;
		
		return true;
	}
	
	
	
	
	private  boolean hasXwon()
	{
		//rows
		if(gameBoard[0][0]+gameBoard[0][1]+gameBoard[0][2]==3)
			return true;
		if(gameBoard[1][0]+gameBoard[1][1]+gameBoard[1][2]==3)
			return true;
		if(gameBoard[2][0]+gameBoard[2][1]+gameBoard[2][2]==3)
			return true;
		//columns
		if(gameBoard[0][0]+gameBoard[1][0]+gameBoard[2][0]==3)
			return true;
		if(gameBoard[0][1]+gameBoard[1][1]+gameBoard[2][1]==3)
			return true;
		if(gameBoard[0][2]+gameBoard[1][2]+gameBoard[2][2]==3)
			return true;
		
		//diagonals
		if(gameBoard[0][0]+gameBoard[1][1]+gameBoard[2][2]==3)
			return true;
		if(gameBoard[0][2]+gameBoard[1][1]+gameBoard[2][0]==3)
			return true;
		
		
		return false;
	}
	
	private  boolean hasOwon()
	{
		//rows
		if(gameBoard[0][0]+gameBoard[0][1]+gameBoard[0][2]==-3)
			return true;
		if(gameBoard[1][0]+gameBoard[1][1]+gameBoard[1][2]==-3)
			return true;
		if(gameBoard[2][0]+gameBoard[2][1]+gameBoard[2][2]==-3)
			return true;
		//columns
		if(gameBoard[0][0]+gameBoard[1][0]+gameBoard[2][0]==-3)
			return true;
		if(gameBoard[0][1]+gameBoard[1][1]+gameBoard[2][1]==-3)
			return true;
		if(gameBoard[0][2]+gameBoard[1][2]+gameBoard[2][2]==-3)
			return true;
		
		//diagonals
		if(gameBoard[0][0]+gameBoard[1][1]+gameBoard[2][2]==-3)
			return true;
		if(gameBoard[0][2]+gameBoard[1][1]+gameBoard[2][0]==-3)
			return true;
		
		
		return false;
	}
	
	public void makeMove()
	{
		
		if(isX)
		{
			minMax(depth,isX);
		}
		else
			minMax(depth,isX);
	}
	
	private int minMax(int depth,boolean MaxPlayer)
	{
		if(depth==0 || hasXwon() || hasOwon() || !freeMoves())
		{
			
			
			return getScore(depth);
		}
		else
		{
			
				int bestMoveX=0,bestMoveY=0;
				int bestScore=MaxPlayer? Integer.MIN_VALUE:Integer.MAX_VALUE;
				for(int i=0;i<gameBoard.length;i++)
				{
					for(int j=0;j<gameBoard[i].length;j++)
					{
						if(gameBoard[i][j]==0)
						{
							if(MaxPlayer)
							{
								gameBoard[i][j]=1;
								int score=minMax(depth-1,false);
								if(score>bestScore)
								{
									
									bestScore=score;
									bestMoveX=i;
									bestMoveY=j;
								}
								gameBoard[i][j]=0;
								
							}
							else
							{
								gameBoard[i][j]=-1;
								int score=minMax(depth-1,true);
								if(score<bestScore)
								{
									
									bestScore=score;
									bestMoveX=i;
									bestMoveY=j;
								}
								gameBoard[i][j]=0;
								
							}
							
						}
					}
				}
			
		if(depth==this.depth)
		{
			gameBoard[bestMoveX][bestMoveY]=MaxPlayer? 1:-1;
		}
		return bestScore;
		}	
	}
	private int getScore(int depth)
	{
		if(hasXwon())
			return 3+depth;
		if(hasOwon())
			return -3-depth;
		
		if(!freeMoves())
			return 0;
		
		
		return 0;
	}
	private boolean freeMoves()
	{
		
		
		for(int i=0;i<gameBoard.length;i++)
		{
			for(int j=0;j<gameBoard[i].length;j++)
			{
				if(gameBoard[i][j]==0)
					return true;
			}
				
		}
		
		return  false;
	}
	
	
	
}
