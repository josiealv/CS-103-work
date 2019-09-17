/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) PA
 * Name: Josie Alvarez
 * USC email: josiealv@usc.edu
 * Comments (you want us to know):
 *
 *
 ******************************************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables, if desired.
 * It is up to you if and how you want to use these
 */
const char suit[4] = {'H','S','D','C'};
const char* type[13] =
{"2","3","4","5","6","7",
    "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[])
{
    for (int s=0; s<NUM_CARDS; s++) //initializes array to respective value
    {
        cards [s] = s;
    }
    
    for (int i = NUM_CARDS-1; i > 0; i--)    //shuffles cards
    {
        int j = rand()%(i+1);
        
        int old_cards = cards [i];
        cards [i] = cards[j];
        cards [j] = old_cards;
    }
}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 */

void printCard(int id)
{
    /******** You complete ****************/
    if ( id >= 0 && id <= 12)
    {
        cout << type[id] << "-"<< suit [0];
    }
    
    //id%13 for actual card value
    else if (id >= 13 && id <= 25 )
    {
        cout <<type [id%13] <<"-"<< suit[1];
    }
    else if (id >= 26 && id <= 38)
    {
        cout  << type [id%13] << "-" << suit[2];
    }
    else
    {
        cout << type [id%13] <<"-" << suit [3];
    }
    
    return;
}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 */
int cardValue(int id)
{
    /******** You complete ****************/
    
    int c_value; //actual value of id
    for (int n = 0; n < 13; n++)
    {
        if (n == id%13)
        {
            c_value = value [n];
        }
    }
    return c_value;
}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
    /******** You complete ****************/
    
    /*goes through every element from a given hand
     2 print every card individually on one line*/
    for (int i = 0; i < numCards; i++)
    {
        int current_card = hand [i];
        printCard(current_card);
        cout << " ";
    }
    cout << endl;
    return;
}

/**
 * Should return the total score of the provided hand.
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
    /******** You complete ****************/
    int total = 0;
    for (int i = 0; i < numCards; i++)
    {
        int C_current = hand [i];
        int C_value = cardValue(C_current);
        total += C_value;
    }
    if (total > 21)
    {
        for (int a = 0; a < numCards; a++)
        {
            int card_curr = hand [a];
            int value = cardValue (card_curr);
            
            if (value == 11 &&
                total > 21) //reduces 1 or more Aces to 1 if needed
            {
                total -= 10;
            }
        }
    }
    return total;
}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
    //---------------------------------------
    // Do not change this code -- Begin
    //---------------------------------------
    if(argc < 2){
        cout << "Error - Please provide the seed value." << endl;
        return 1;
    }
    int seed = atoi(argv[1]);
    srand(seed);
    
    int cards[52];
    int dhand[9];
    int phand[9];
    
    shuffle(cards);
    
    //---------------------------------------
    // Do not change this code -- End
    //---------------------------------------
    
    /******** You complete ****************/
    char run = 'y';
    while ( run == 'y')
    {
        char hit_or_stay;
        int card_counterD = 0;
        int card_counterP = 0;
        int current_card = 0; //counter for card taken from deck
        int P_total = 0;
        int D_total = 0;
        
        
        for (int i = 0; i < 2; i++) //gets 1st 4 cards from deck (2 each)
        {
            phand [card_counterP] = cards [current_card];
            current_card++;
            dhand [card_counterD] = cards [current_card];
            
            current_card++;
            card_counterD++;
            card_counterP++;
        }
        
        //prints first 2 cards of Dealer and Player
        //except 1st card is hidden for Dealer
        
        int Dealer_2ndCard = dhand [1];
        cout << "Dealer: " << "?" << " ";
        printCard (Dealer_2ndCard);
        cout << endl;
        
        
        cout << "Player: ";
        printHand (phand, card_counterP);
        
        P_total = getBestScore (phand, card_counterP);
        D_total = getBestScore (dhand, card_counterD);
        
        
        
        if (P_total < 21 && D_total < 21)
        {
            
            while (P_total < 21)
            {
                cout << "Type 'h' to hit and 's' to stay:" << endl;
                cin >> hit_or_stay;
                
                if (hit_or_stay == 'h')
                {
                    phand [card_counterP] = cards [current_card];
                    current_card++;
                    card_counterP++;
                    P_total = getBestScore (phand, card_counterP);
                    cout << "Player: ";
                    printHand (phand, card_counterP);
                }
                
                else if (hit_or_stay == 's')
                {
                    while (D_total < 17) //dealer plays till score >= 17
                    {
                        dhand [card_counterD] = cards [current_card];
                        current_card++;
                        card_counterD++;
                        D_total = getBestScore (dhand, card_counterD);
                    }
                    if (D_total >= 17)
                    {
                        cout << "Dealer: ";
                        printHand(dhand, card_counterD);
                        break;
                    }
                }
                
            }
            
        }
        if (P_total == 21) //dealer continues to play when player reaches 21
        {
            while (D_total < 17)
            {
                dhand [card_counterD] = cards [current_card];
                current_card++;
                card_counterD++;
                D_total = getBestScore (dhand, card_counterD);
            }
        }
        
        if (P_total > 21 &&
            D_total <= 21) //Player busts
        {
            cout << "Player busts"<<endl;
            cout << "Lose " << P_total << " " << D_total << endl;
            cout << endl;
            cout << "Play again? [y/n]" << endl;
            cin >> run;         //if run != 'y' then program ends
        }
        else if ((D_total > P_total) &&
                 (D_total <= 21 && P_total < 21)) //Player loses but doesn't busts
        {
            cout << "Lose " << P_total << " " << D_total << endl;
            cout << endl;
            cout << "Play again? [y/n]" << endl;
            cin >> run;
        }
        else if (P_total <= 21 &&
                 D_total > 21) //Player wins & Dealer busts
        {
            cout << "Dealer busts" << endl;
            cout << "Win " << P_total << " "<< D_total << endl;
            cout << endl;
            cout << "Play again? [y/n]" << endl;
            cin >> run;
        }
        else if (D_total < P_total &&
                 (P_total <= 21 && D_total < 21)) //Player wins
        {
            cout << "Win " << P_total << " "<< D_total << endl;
            cout << endl;
            cout << "Play again? [y/n]" << endl;
            cin >> run;
        }
        else if (P_total == D_total)
        {
            cout << "Tie " << P_total << " "<< D_total<< endl;
            cout << endl;
            cout << "Play again? [y/n]" << endl;
            cin >> run;
        }
        shuffle (cards);
    }
    
    return 0;
}
