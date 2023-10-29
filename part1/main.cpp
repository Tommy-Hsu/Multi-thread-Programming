#include <iostream>
using namespace std;

int main( int argc, char* argv[] ) {
    
    int             nThreads;
    long long int   nTosses;

    if ( argc != 3 ) {
        cout << "Usage: ./pi <nThreads> <nTosses>" << endl;
        return 1;
    }
    else {
        nThreads = atoi( argv[1] );
        nTosses = atoll( argv[2] );

        if ( nThreads <= 0 || nTosses <= 0 ) {
            cout << "Usage: ./pi <nThreads> <nTosses>" << endl;
            return 1;
        }

        cout << "nThreads: " << nThreads << endl;
        cout << "nTosses: " << nTosses << endl;
    }

    return 0;
}