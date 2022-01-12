#include <stdio.h>
// El primer argumento es el nombre del archivo
int main( int argc, char * argv []) {
    for ( int i = 0; i < argc ; i ++)
        printf("%s\n", argv[i]);
}