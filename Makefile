#
# /usr/bin/g++ -fdiagnostics-color=always
# -I /home/andrus/learn/tts/3/test-task3/common
# -o /home/andrus/learn/tts/3/test-task3/main.exe
# -g 
# /home/andrus/learn/tts/3/test-task3/main.cpp /home/andrus/learn/tts/3/test-task3/common/*.cpp
#

build: main.exe

clean:
	-rm -f *.exe *.log

all: main.exe server.exe client.exe 

main.exe:
	g++ -I common -o main.exe   -g main.cpp   common/*.cpp

client.exe:
	g++ -I common -o client.exe -g client.cpp common/client_udp.cpp common/common_udp.cpp common/rnd.cpp common/state_mashine.cpp

server.exe:
	g++ -I common -o server.exe -g server.cpp common/common_udp.cpp common/rnd.cpp common/server_udp.cpp

run: main.exe
	./main.exe
