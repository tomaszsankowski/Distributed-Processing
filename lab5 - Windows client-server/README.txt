How to run:

1. Compile .c files in cmd
gcc -o server.exe server.c -lws2_32
gcc -o client.exe client.c -lws2_32

2. Get your ip adress:
type ipconfig in cmd and get IPv4 adress

3. Run executables:
./server
./client IP_ADRESS:5000 (IP_ADRESS = ip adress from ipconfig