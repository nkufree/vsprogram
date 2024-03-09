#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;
int main()
{
    int* a[13172];
    int** b;
    long int c;
    long i, j, k, l, secx;
    /* Load L2 cache */
    for (i = 0; i < 13171; i++) {
        a[i] = (int*)&a[i + 1];
    }
    auto begin = steady_clock::now();
    /* loop 1500 times */
    for (i = 0; i < 250; i++) {
        b = (int**)a[7];
        /* Load from L2 at 64 byte boundary */
        for (k = 0; k < 80000; k += 8) {
            b = (int**)b[8];
        }
    }
    auto end = steady_clock::now();
    auto time = (end - begin).count();
    cout << "time is " << time << endl;
    cout << "L2 Latency is" << (463000000 * time) / (20001 * 250) << endl;
    cout << "L2 BW is " << (20001 * 250 * 64) / (time * 1000000) << " MB/sec" << endl;
    //fprintf(stderr, "b is %ld\n", b);
}
