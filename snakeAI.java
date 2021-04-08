package snake;

public class snakeAI {

	private int [][] dp;
	private int startRow;
	private int startCol;
	private boolean exists;
	private int counter;
	private final static int DEFAULT_COUNTER=1;
	snakeAI(int tablerows,int tablecols, int rowStart,int colStart)
	{
		
		dp=new int[tablerows][tablecols];
		startRow=rowStart;
		startCol=colStart;
		exists=false;
		counter=DEFAULT_COUNTER;
	}
	
	public boolean generate_Hamilton_cycle()
	{
		if(dfs(startRow,startCol,counter))
			exists=true;
		
		return exists;
	}
	private boolean dfs(int row,int col,int hamiltonNumber)
	{
		if(row<0 || col <0 || row>=dp.length || col>=dp[row].length)
			return false;
		
		if(hamiltonNumber== (dp.length* dp[0].length+counter) && row==startRow && col==startCol)
		{
			return true;
		}
		else
		{
			if(dp[row][col]!=0)return false;
			
			dp[row][col]=hamiltonNumber;
			
			
			//EAST
			if(dfs(row,col+1,hamiltonNumber+1))
				return true;
			//NORTH
			if(dfs(row-1,col,hamiltonNumber+1))
				return true;

			if(dfs(row+1,col,hamiltonNumber+1))
				return true;
			//WEST
			if(dfs(row,col-1,hamiltonNumber+1))
				return true;
			
			dp[row][col]=0;
			
		}
		
		
		
		
		return false;
	}
	
	public void printHamiltonCycle()
	{
		if(exists)
		{
		for(int[] arr:dp)
		{
			for(int element:arr)
			{
				System.out.print(element);
				if(element<10)
					System.out.print("   ");
				else
						System.out.print(" ");
			}
			System.out.println();
		}
		}
	}
	
	
	
}
