#include "generator.cpp"
#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;


int main(){
    uint32_t seed = time(NULL); // Ziarno generatora
    MersenneTwister mt(seed);
    fstream plik;
    time_t begin, end,duration;
    long int how_many=10;
    plik.open("sek.txt",ios::out | ios::app);

    for (int x=1;x<12;x++){
        time(&begin);

        for (long int i = 0; i < how_many*x; i++)
        {
            uint32_t number = mt.extractNumber();
            cout<<number<<endl;
        }
        time(&end);
        duration=end-begin;

        plik<<how_many*x<<" "<<duration<<endl;
        
    }
    plik.close();
}
