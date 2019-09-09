rm -f *.exe
rm -f *.o
rm -f *.out
gcc -c -o speller.o speller.c
gcc -c -o dictionary.o dictionary.c
gcc -o speller speller.o dictionary.o