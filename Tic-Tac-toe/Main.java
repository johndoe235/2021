package TicToe;

import java.util.Arrays;
import java.util.Scanner;

public class Main {

	public static void main(String[] args)
	{
		Scanner scanner=new Scanner(System.in);
		int[][] game=new int[3][3];
		boolean playerX=false;
		
		AI tictoeMaster=new AI(game,!playerX,4);
		int move=0;
		System.out.println("WELCOME TO TIC-TAC-TOE!");
		
		while(!tictoeMaster.GameOver())
		{
			
			if(move%2==0 && playerX || move%2!=0 && !playerX)
			{
				printArray(game);
				
				
				int row=-1,col=-1;
				while(!tictoeMaster.validMove(row, col))
				{
				System.out.print("MOVE:X:  Y:");
				 int[] input=Arrays.stream(scanner.nextLine().split("\\s+")).mapToInt(Integer::parseInt).toArray();
				 row=input[0];
				 col=input[1];
				}
				game[row][col]=playerX? 1:-1;
				
			}
			else
			{
				tictoeMaster.makeMove();
			}
			
		System.out.println("##############################");
			move++;
		}
		System.out.println("GAME OVER!");
		printArray(game);
	}
	
	public static void printArray(int[][] arr)
	{
		System.out.println();
		for(int[] X:arr)
		{
			for(int Y:X)
			{
				if(Y==1)
					System.out.print("X");
				else if(Y==-1)
					System.out.print("O");
				else
					System.out.print("-");
			}
			System.out.println();
		}
	}
}
