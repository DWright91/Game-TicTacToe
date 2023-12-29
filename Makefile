all: serverC serverG client

serverC: serverC.cpp header.h
	g++ -o serverC serverC.cpp

serverG: serverG.cpp header.h
	g++ -o serverG serverG.cpp

client: client.cpp header.h
	g++ -o client client.cpp

clean:
	rm -f client
	rm -f serverC
	rm -f serverG
