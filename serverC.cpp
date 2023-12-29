// serverC.cpp

//server code that accepts client connections using sockets

#include "header.h"
////////////////////////////////////////////////////////////////////////////////
//	ServerC Driver
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {

	pid_t err;
	int socketserver, client_socket, port_number,n,Turn=1,Move;
	socklen_t clientaddr;
	// buffer for storing
	char buffer[512],child[30],user[15];
	struct sockaddr_in serv_addr, cli_addr; //server address, client address

	if(argc < 2) // check the validity of the argument count
	{
		cout <<"Usage: \"./serverC\" [port_number]" <<endl; //port number is 5000;
		exit(1);
	}

		// Creates a socket
		socketserver = socket(AF_INET, SOCK_STREAM, 0);

		if(socketserver<0)
		{
			cout <<"Error: Socket can not be opened" <<endl;
			exit(2);
		}


		// local address structure
		memset(&serv_addr, 0, sizeof(serv_addr));
		port_number = atoi(argv[1]);
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		serv_addr.sin_port = htons(port_number);

		// bind socket to the local address
		if(bind(socketserver, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		{
			cout <<"Error: Bind Error" <<endl;
			exit(3);
		}

		// listen for socket
		if(listen(socketserver,5) < 0)
		{
			cout <<"Error: listen Error" <<endl;
			exit(4);
		}

	// connecting to a client using iteration while loop
	while(1)
		{
			clientaddr = sizeof(cli_addr);

			// Connect to the client.
			client_socket = accept(socketserver, (struct sockaddr *) &cli_addr, &clientaddr);
			if(client_socket < 0)
			{
				cout <<"Error: Creation";
				exit(4);
			}

			cout <<"New Connection succefully established with port " <<inet_ntoa(cli_addr.sin_addr) <<ntohs(cli_addr.sin_port) <<endl;

			err = fork();
			if(err == -1){
				cout <<"parent process : fork failed, errno : " <<errno <<endl;
				exit(5);
			}

			else if(err == 0){
				sprintf(child, "%d", client_socket);
				err = execl("./serverG", "serverG", child, NULL);
				if ( err == -1 )
					{
					cout <<" parent:  execl failed, errno = " <<errno <<endl;
					exit (6);
					}
				cout <<err <<endl;
				close(client_socket);
				return 0;
				}
			else
				close(client_socket);

	}
		return 0;
}
