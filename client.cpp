#include "header.h"
// Function Prototypes.
void display_Board (string);		// displays tic-tac-toe gameboard.
void draw(int, int, int);
bool check_Valid_Move(int,int);	// Check board for valid move.
int switchPlayer(int);
int isWinner();
void render_visual();

using namespace std;

string Board[3][3];			// create a board of dimension 3 by 3 for the game

////////////////////////////////////////////////////////////////////////////////
//	Client Driver
////////////////////////////////////////////////////////////////////////////////
int main ( int argc, char*argv[]){

	int  count=0;
	int client_socket;                        // original socket in client
	int len, port_number;
	struct sockaddr_in serv_adr;              // server address
	struct hostent *host;
	string PlayerName;
	int result = 1;
	int move[2];
	int recieved_bytes, sent_bytes;
	char buffer[512];
	char *ptr = &buffer[0];
	char winner[10];
	char result_buffer;
	char mov;
	char buff_choice[3], pc_choice[3];
	int move_x,move_y, chance = 1;


	if (argc != 3){		// parse the command line arguments., should be of form " ./a.out 127.0.0.1 5000 "

		cout<<"correct usage is :"<<argv[0]<<"  server "<<"  port_number  "<<endl;
		return 1;
	}



	host = gethostbyname(argv[1]);				// returns a structure of type hostent for a given name
	if (host ==(struct hostent*) NULL) {

		perror(" Error: host name can not be obtained");
		return 2;
	}

	// Create a reliable, stream socket using TCP
	//


	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sock == -1)
	{
		perror("Error: Socket creation failed!");
		return 1;
	}

	memset(&serv_adr, 0, sizeof( serv_adr));	// Initialize all the values of structure which are not explicitly set, to zero

	serv_adr.sin_family = AF_INET;				// IPv4 address family

	memcpy(&serv_adr.sin_addr, host->h_addr, host->h_length);
	port_number = atoi(argv[2]);
	serv_adr.sin_port = htons(port_number);  // host to network short

	// Create a Socket for the client object

	if ((client_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0) {

		perror("Error: Creating client socket");
		return 3;
	}

	// Make a connection object to the client socket obtained from previous step

	if (connect( client_socket,(struct sockaddr *)&serv_adr,sizeof(serv_adr)) < 0) {
		perror("Error: Connection can not be established");
		return 4;
	}

	cout << "Enter Player name:"<<endl;
	cin >> PlayerName;

	// Start game here, begin by displaying intial values, and update the fields with 'x' or '0' as appropraite
	display_Board(PlayerName);

	do
	{



				cout <<"+++ "<<PlayerName << "'s turn+++" << endl;

				cout << "Enter x and y cordinate of your move. Example: 1 [space] 0 for location '10':" << endl;
				cin >>move_x>>move_y;

				bool flag=check_Valid_Move(move_x,move_y);

				 while(flag != true){				//Recursively, prompt user for a valid move
					   cout <<"Kindly try again!"<< endl;
					   cin >> move_x>>move_y;

					   flag=check_Valid_Move(move_x,move_y);
					  	}



						draw(chance,move_x,move_y);


						sprintf(&buff_choice[0], "%d",move_x );
						sprintf(&buff_choice[1], "%d", move_y);
 						sent_bytes = send(client_socket, &buff_choice, sizeof(buff_choice), 0);

						if(sent_bytes == -1)
 						{
 							perror("Error: Client sending the inputs failed");
 							return 5;
 						}


		int value = switchPlayer(chance);
		chance = value;


	recieved_bytes = recv(client_socket, &pc_choice, sizeof(pc_choice), 0);


					if(recieved_bytes == -1)
					{
						perror("Error in Computer's data");
						return 6;
					}
          	int xmove = pc_choice[0]-'0';
			int ymove =pc_choice[1]-'0';
			    	draw(chance,xmove,ymove);

				render_visual();


			//}
		value = switchPlayer(chance);// USER OR PC
		chance= value;

		result = isWinner();
		count=count+result;

		if(count==5 && result==1)
		{
			cout<<"Result: Draw";
			break;
		}

		// game moves in loop until it is 1.
		signal(SIGPIPE, SIG_IGN);

	}while(result == 1);



	return 0;
	}


bool check_Valid_Move (int x_pt, int y_pt )	// As long as the x co-ordinate and y-cordinate are not occupied, this function returns true, else false
{						// We represent the occupied poistion by X's or O's as in conventional tic- tac - toe game

    while( x_pt>=0 && x_pt<3 && y_pt>=0 && y_pt<3)
    {
        if (Board[x_pt][y_pt] != "X" && Board[x_pt][y_pt] != "O" )
        {
		return true;
        }

        else
        {

	cout<<"Error: Invalid Move:"<< endl;

        return false;
        }
    }
}



void display_Board (string playername1)    // Displays the initial board, check for null entries in the board, and set that to appropriate positions corresponding to row num and column num,
					   //
{
	int row_iter;
	int col_iter;

	char f_index[2];
	char s_index[2];
	;

   cout <<"+++ Let's Start it +++ "<<endl;

   cout << playername1 << " is Player \'X\' and Computer is \'O\'."<< endl;

   	for (row_iter=0;row_iter<3;row_iter++)
	{
		for(col_iter=0;col_iter<3;col_iter++)
		{

			if (Board[row_iter][col_iter] ==  "\0")
			{
				sprintf(f_index,"%d",row_iter);
				sprintf(s_index,"%d",col_iter);

				Board[row_iter][col_iter]=strcat(f_index,s_index);

			}
		}
	}



   cout << endl;

   render_visual();   // Call the board render visual function


}


void render_visual()
{


   int print_row=0;
   int print_col=0;

   cout<<"-------------------"<<endl;

   	for (print_row=0; print_row<3; print_row++)
   	{
	   for(print_col=0;print_col<3;print_col++)
	   {
		   cout<< Board[print_row][print_col]<<"  |  ";

	   }

	   cout<<endl<<"-------------------"<<endl;
  	 }

}


void draw(int chance, int m,int n)
{
	if (chance == 1 )
	{

		Board[m][n] = 'X';
	}
	else
		Board[m][n] = 'O';
}



int switchPlayer(int temp)
{
   if ( temp == 1)
		  temp++;

    else if ( temp == 2)
   		temp--;

    return (temp);
}



int isWinner()
{
	int end = 0;

	// Checking winning conditions for Players

	if ( (Board[0][0] == "X" && Board[0][1] == "X" && Board[0][2] == "X") ||

	   (Board[1][0] == "X" && Board[1][1] == "X" && Board[1][2] == "X") ||

	   (Board[2][0] == "X" && Board[2][1] == "X" && Board[2][2] == "X") ||

	   (Board[0][0] == "X" && Board[1][1] == "X" && Board[2][2] == "X") ||

	   (Board[0][2] == "X" && Board[1][1] == "X" && Board[2][0] == "X") ||

	   (Board[0][0] == "X" && Board[1][0] == "X" && Board[2][0] == "X") ||

	   (Board[0][1] == "X" && Board[1][1] == "X" && Board[2][1] == "X") ||

	   (Board[0][2] == "X" && Board[1][2] == "X" && Board[2][2] == "X")  )
	   {

   		cout << endl;

		render_visual();

		cout << " CONGRATULATIONS !  YOU WIN "<< endl;
	}



	//  Checking winning conditions for Computer
	else if ( ( Board[0][0] == "O" && Board[0][1] == "O" && Board[0][2] == "O") ||

	   (Board[1][0] == "O" && Board[1][1] == "O" && Board[1][2] == "O") ||

	   (Board[2][0] == "O" && Board[2][1] == "O" && Board[2][2] == "O") ||

	   (Board[0][0] == "O" && Board[1][1] == "O" && Board[2][2] == "O") ||

	   (Board[0][2] == "O" && Board[1][1] == "O" && Board[2][0] == "O") ||

	   (Board[0][0] == "O" && Board[1][0] == "O" && Board[2][0] == "O") ||

	   (Board[0][1] == "O" && Board[1][1] == "O" && Board[2][1] == "O") ||

	   (Board[0][2] == "O" && Board[1][2] == "O" && Board[2][2] == "O")  )
	{
		 cout << endl;
		 render_visual();

		 cout<< "COMPUTER WINS "<<endl;
	}
	else
	{
		end = 1;
		return end;
	}

}
