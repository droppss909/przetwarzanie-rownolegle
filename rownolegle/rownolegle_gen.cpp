#include "generator.cpp"
#include <iostream>
#include <fstream>
#include <time.h>
#include <omp.h>
using namespace std;

int main() {
    uint32_t seed = time(NULL); // Ziarno generatora
    fstream plik;
    time_t begin, end, duration;
    int ind=12;
    long int how_many = 10;
    plik.open("row.txt", ios::out | ios::app);
    int tab[20]={0};
    #pragma omp parallel private(begin, end, duration)
    {
        MersenneTwister mt(seed + omp_get_thread_num()); // Każdy wątek ma swoją własną instancję generatora

        for (int x = 1; x < ind; x++) {
            #pragma omp critical
            {
                time(&begin);
            }

            uint32_t number;

            #pragma omp for
            for (long int i = 0; i < how_many * x; i++) {
                number = mt.extractNumber();
                cout<<number<<endl;

            }

            #pragma omp critical
            {   
                time(&end);
                duration = end - begin;
                if (tab[x-1]==0){
                    plik << how_many * x << " " << duration << endl;
                    tab[x-1]=1;
                }
            }
        }
    }

    plik.close();
    return 0;
}
