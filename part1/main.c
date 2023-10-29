#include <stdio.h>
#include <stdlib.h>

int main( int argc, char* argv[] ) {
    
    int             nThreads;
    long long int   nTosses;

    if ( argc != 3 ) {
        printf( "Usage: ./pi <nThreads> <nTosses>\n" );
        return 1;
    }
    else {
        nThreads = atoi( argv[1] );
        nTosses = atoll( argv[2] );

        if ( nThreads <= 0 || nTosses <= 0 ) {
            printf( "nThreads and nTosses must be positive integers.\n");
            return 1;
        }

        printf( "nThreads = %d\n", nThreads );
        printf( "nTosses = %lld\n", nTosses );
    }

    return 0;
}