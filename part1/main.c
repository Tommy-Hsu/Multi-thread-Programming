#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long long int SerialCalHits(long long int nTosses);
void* ThreadCalPi(void* arg);
void ParallelCalPi(int nThreads, long long int nTosses);

typedef struct {
    long long int nTossesPerThread;
    long long int nHitsPerThread;
    int threadID;
} ThreadArg;

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

        // parallel pi with pthread
        ParallelCalPi(nThreads, nTosses);

    }

    return 0;
}

long long int SerialCalHits(long long int nTosses) {
    
    unsigned int seed = (unsigned int)time(NULL) + (unsigned long)pthread_self();
    long long int nHits = 0;
    for( long long int i = 0; i < nTosses; i++ ) {
        double x = (double)rand_r(&seed) / (double)RAND_MAX;
        double y = (double)rand_r(&seed) / (double)RAND_MAX;
        if ( x*x + y*y <= 1.f ) {
            nHits++;
        }
    }

    return nHits;
}

void* ThreadCalPi(void* arg) {
    
    ThreadArg* perThreadarg = (ThreadArg*)arg;
    printf( "Thread %d tosses = %lld\n", perThreadarg->threadID, perThreadarg->nTossesPerThread);
    long long int localHits = SerialCalHits(perThreadarg->nTossesPerThread);
    printf( "Thread %d hits = %lld\n", perThreadarg->threadID, localHits);
    perThreadarg->nHitsPerThread = localHits;
    pthread_exit(0);
}

void ParallelCalPi(int nThreads, long long int nTosses) {
    
    double pi = 0.f;
    long long int nHits = 0;
    
    pthread_t* threads = (pthread_t*)malloc( sizeof(pthread_t) * nThreads );
    ThreadArg* localpi = (ThreadArg*)malloc(sizeof(ThreadArg) * nThreads);

    for( size_t i = 0; i < nThreads; i++ ) {
        localpi[i].nTossesPerThread = nTosses / nThreads;
        if( i == nThreads - 1 ) {
            localpi[i].nTossesPerThread += nTosses % nThreads;
        }
        localpi[i].nHitsPerThread = 0;
        localpi[i].threadID = i;
        pthread_create( &threads[i], NULL, ThreadCalPi, &localpi[i] );
    }

    for ( size_t i = 0; i < nThreads; i++ ) {
        pthread_join( threads[i], NULL );
        nHits += localpi[i].nHitsPerThread;
    }

    pi = 4.f * (double) nHits / (double)nTosses;
    printf( "Parallel Calculate pi = %f\n", pi);
}