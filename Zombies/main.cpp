/********************************************************
 * CS 103 Zombie-pocalypse PA
 * Name: Josie Alvarez
 * USC email: josiealv@usc.edu
 * Comments (you want us to know):
 *
 *
 ********************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
using namespace std;

const int MAXPOP = 100000;

int main()
{
    // Array with enough entries for the maximum population size possible.
    bool pop[MAXPOP];
    int N, k, M, seed;
    
    
    cout << "Enter the following: N k M seed" << endl;
    cin >> N >> k >> M >> seed;
    
    if ( k > N)    //ends when zombies > pop
    {
        return 1;
    }
    
    
    int Total_Nights = 0; //counter for total nights
    int Nights_M = 0;     //counter for nights per simulation (M)
    
    
    srand (seed);
    int Max_n = 0;
    int Min_n = INT_MAX;
    int old_k = k;
    
    for (int s = 0; s < M; s++)    //loop for # of M
    {
        for (int i = 0; i < N; i++)   //loop initalizes zombies & pop
        {
            
            if (i < old_k)
            {
                pop [i] = true;
            }
            else
            {
                pop [i] = false;
            }
            
        }
        while (k != N)  //loop runs until k = N
        {
            Total_Nights++;
            Nights_M++;
            int k2 = k;  //represents # of zombies per night
            
            for(int bite = 0; bite < k2; bite++)    //loop for bites per night
            {
                int r = rand (); //reinitializes random # each iteration
                
                if (pop[(r%N)] == false)
                {
                    pop[(r%N)] = true;
                    k++;
                }
            }
        }
        k = old_k;    //reinitializes k for every M
        
        if (Nights_M >= Max_n)
        {
            Max_n = Nights_M;
        }
        
        if(Nights_M <= Min_n)
        {
            Min_n = Nights_M;
        }
        
        Nights_M = 0; //reinitialies nights for every M
        
    }
    
    double Average_n = ((double)Total_Nights)/M;
    
    cout << "Average Nights: " << Average_n << endl;
    cout << "Max Nights: " << Max_n << endl;
    cout << "Min Nights: " << Min_n << endl;
    
    return 0;
}
