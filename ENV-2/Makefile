all: main.o complex.o sort.o  finish clear
 main.o: main.cpp
        g++ -c main.cpp
         
 complex.o: complex.cpp
        g++ -c complex.cpp
               
sort.o: sort.cpp 
        g++ -c sort.cpp
         
  finish:
        g++ main.o complex.o sort.o -o main
       
clear: 
        rm -f *.o
