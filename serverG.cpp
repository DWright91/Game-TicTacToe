#include "header.h"

//server code that processes the tic tac toe game
// Game Server Function Prototypes.
int isWinner();
int* randomGenerator();
int switchPlayer(int);
void mark(int, int,int);

string Board[3][3];
////////////////////////////////////////////////////////////////////////////////
//	ServerG Driver
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv){
 	int sockg;
        int len;
	int Turn = 1;
	char winner[10];
	int net_move;
	char buff_choice[3];
	char pc_choice[3];
        char result_buffer;
        int recieved_bytes, sent_bytes;
	char cresult;
	int count=0;
	int x;
	int y;

 if(argc > 1)
  {
		sockg = atoi(argv[1]);
		int result = 1;


 do
	  {
	  		 recieved_bytes = recv(sockg, &buff_choice, sizeof(buff_choice), 0);
	  		 if (recieved_bytes == -1)
			{
				perror("Error: Buffer cordinates unavailable");
				return 1;
			}
			x = buff_choice[0] - '0';
			y = buff_choice[1] - '0';
			mark(Turn,x,y);
			int value= switchPlayer(Turn);
			Turn = value;
			count++;
	   if(count==5)
			 break;

			int *ptr= randomGenerator();
			int x_move =ptr[0];
			int y_move = ptr[1];

			char cmove[2];
			cmove[0] = x_move +'0';
			cmove[1] = y_move + '0';
			//pc_choice[0] = cmove[0];
			//pc_choice[1] = cmove[1];
			mark(Turn,x_move,y_move);
			sprintf(&pc_choice[0], "%d", x_move);
			sprintf(&pc_choice[1], "%d", y_move);
			sent_bytes = send(sockg, &pc_choice, sizeof(pc_choice), 0);

			value= switchPlayer(Turn);// USER OR PC
		  Turn = value;

		  	result = isWinner();
			signal(SIGPIPE, SIG_IGN);


	  }while (result == 1);
	  close(sockg);
    return 0;
}
}


int switchPlayer(int b)
{
   if ( b == 1)
    	b++;
     else if ( b == 2)
   b--;
    return (b);
}

// Gameboard marking.
void mark(int chance, int x,int y)
{
	if (chance == 1 )
	{

		Board[x][y] = 'X';
	}
	else
		Board[x][y] = 'O';
}

int* randomGenerator()   // Generating random number between 0 and 2.
 {

	bool flag = false;

	int *M = new int[2];

	srand(time(0));
	int x_coor,y_coor;
	while(!flag){
		x_coor = rand() %3;
		y_coor = rand() %3;
		if(Board[x_coor][y_coor] != "X" && Board[x_coor][y_coor] != "O"){
		flag = true;
		 M[0] = x_coor;
		 M[1] = y_coor;
		}

  }
         return M;

}



int isWinner()
{
	int end = 0;
	if (Board[0][0] == "X" && Board[0][1] == "X" && Board[0][2] == "X")
	{
		return end;
	}
	else if (Board[1][0] == "X" && Board[1][1] == "X" && Board[1][2] == "X")
	{
		return end;
	}
	else if (Board[2][0] == "X" && Board[2][1] == "X" && Board[2][2] == "X")
	{
		return end;
	}
	else if (Board[0][0] == "X" && Board[1][1] == "X" && Board[2][2] == "X")
	{
		return end;
	}
	else if (Board[0][2] == "X" && Board[1][1] == "X" && Board[2][0] == "X")
	{
		return end;
	}
	else if (Board[0][0] == "X" && Board[1][0] == "X" && Board[2][0] == "X")
	{
		return end;
	}
	else if (Board[0][1] == "X" && Board[1][1] == "X" && Board[2][1] == "X")
	{
		return end;
	}
	else if (Board[0][2] == "X" && Board[1][2] == "X" && Board[2][2] == "X")
	{
		return end;
	}

	// computer
	else if (Board[0][0] == "O" && Board[0][1] == "O" && Board[0][2] == "O")
	{
		return end;
	}
	else if (Board[1][0] == "O" && Board[1][1] == "O" && Board[1][2] == "O")
	{
		return end;
	}
	else if (Board[2][0] == "O" && Board[2][1] == "O" && Board[2][2] == "O")
	{
		return end;
	}
	else if (Board[0][0] == "O" && Board[1][1] == "O" && Board[2][2] == "O")
	{
		return end;
	}
	else if (Board[0][2] == "O" && Board[1][1] == "O" && Board[2][0] == "O")
	{
		return end;
	}
	else if (Board[0][0] == "O" && Board[1][0] == "O" && Board[2][0] == "O")
	{
		return end;
	}
	else if (Board[0][1] == "O" && Board[1][1] == "O" && Board[2][1] == "O")
	{
		return end;
	}
	else if (Board[0][2] == "O" && Board[1][2] == "O" && Board[2][2] == "O")
	{
		return end;
	}
	else
	{
		end = 1;
		return end;
	}

}
