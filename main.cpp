#include <iostream>
#include <array>
#include <vector>
#include <random>
#include <time.h>
using namespace std;


class card
{
public:
    card()
    {
        suit = "";
        num = "";
    }

    card(string s, string n)
    {
        suit = s;
        num = n;
    }

    string getSuit()
    {
        return suit;
    }

    string getNum()
    {
        return num;
    }

    void print()
    {
        cout << num << " of " << suit << endl;
    }

    int convert() //used to order cards so they can be sorted
    {
        if(num == "Ace")
            return 1;

        if(num == "2")
            return 2;

        if(num == "3")
            return 3;

        if(num == "4")
            return 4;

        if(num == "5")
            return 5;

        if(num == "6")
            return 6;

        if(num == "7")
            return 7;

        if(num == "8")
            return 8;

        if(num == "9")
            return 9;

        if(num == "10")
            return 10;

        if(num == "Jack")
            return 11;

        if(num == "Queen")
            return 12;

        if(num == "King")
            return 13;

        cout << "Convert Error!" << endl;
        return 0;
    }

private:
    string suit;
    string num;
};

void swap (card *a, card *b);

class queue
{
private:
    int queueSize;
    vector<card> *queueItems{nullptr};
public:
    queue()
    {
        queueSize = 0;
        queueItems = new vector<card>;
    }

    void push(card x)
    {
        queueItems->push_back(x);
        queueSize = queueSize + 1;
    }

    card pop()
    {
        card item;
        queueSize = queueSize - 1;
        item = queueItems->front();
        queueItems->erase(queueItems->begin());
        return item;
    }

    int size()
    {
        return queueSize;
    }

    card peek()
    {
        return queueItems->front();
    }

    bool isEmpty()
    {
        return queueItems->empty();
    }

    void print()
    {
        for (int i = 0; i < size(); i++)
        {
            queueItems->at(i).print();
        }
    }
};

class priorityQueue
{
public:
    priorityQueue()
    {
        //priorityQueueItems = new vector<card>;
    }

    void bubbleSort(vector<card>& hand) //sorts cards based on number
    {
        if(!hand.empty())
        {
        int i, j;
        for (i = 0; i < hand.size()-1; i++)

        for (j = 0; j < hand.size()-i-1; j++)
            if (hand[j].convert() > hand[j+1].convert())
                swap(&hand[j], &hand[j+1]);
        }
    }

    void suitSort(priorityQueue& hand) //sorts card based on suit
    {
        int size = hand.size();
        vector<card> hearts;
        vector<card> clubs;
        vector<card> diamonds;
        vector<card> spades;

        for(int i = 0; i < size; i++)
        {
            if(hand.peek().getSuit() == "Hearts")
            {
                hearts.push_back(hand.pop());
            }
            else if(hand.peek().getSuit() == "Clubs")
            {
                clubs.push_back(hand.pop());
            }
            else if(hand.peek().getSuit() == "Diamonds")
            {
                diamonds.push_back(hand.pop());
            }
            else if(hand.peek().getSuit() == "Spades")
            {
                spades.push_back(hand.pop());
            }
            else
            {
                cout << "Suit Sort error!" << endl;
            }
        }

        bubbleSort(hearts);
        bubbleSort(clubs);
        bubbleSort(diamonds);
        bubbleSort(spades);

        for(int i = 0; i < clubs.size(); i++)
        {
            hand.add(clubs[i]);
        }

        for(int i = 0; i < diamonds.size(); i++)
        {
            hand.add(diamonds[i]);
        }

        for(int i = 0; i < hearts.size(); i++)
        {
            hand.add(hearts[i]);
        }

        for(int i = 0; i < spades.size(); i++)
        {
            hand.add(spades[i]);
        }

    }

    void push(card x)
    {
        priorityQueueItems.push_back(x);
        suitSort(*this);
    }

    card pop()
    {
        card item;
        item = priorityQueueItems.front();
        priorityQueueItems.erase(priorityQueueItems.begin());
        return item;
    }

    void add(card x)
    {
        priorityQueueItems.push_back(x);
    }

    card peek()
    {
        return priorityQueueItems.front();
    }

    int size()
    {
        return priorityQueueItems.size();
    }

    void playCard(int index, queue& discard)
    {
        discard.push(priorityQueueItems[index]);
        priorityQueueItems.erase(priorityQueueItems.begin() + index - 1);
    }

    void discardHand(queue& discard)
    {
        for(int i = 0; i < size(); i++)
        {
            discard.push(priorityQueueItems[i]);
        }
        priorityQueueItems.clear();
    }

    void print()
    {
        for (int i = 0; i < size(); i++)
        {
            priorityQueueItems[i].print();
        }
    }

private:
    vector<card> priorityQueueItems;
};

void createDeck(queue& q) //adds all the cards into a deck
{
    for(int i = 2; i < 11; i++)
    {
        q.push(card("Hearts", std::to_string(i)));
    }
    q.push(card("Hearts", "Jack"));
    q.push(card("Hearts", "Queen"));
    q.push(card("Hearts", "King"));
    q.push(card("Hearts", "Ace"));

    for(int i = 2; i < 11; i++)
    {
        q.push(card("Clubs", std::to_string(i)));
    }
    q.push(card("Clubs", "Jack"));
    q.push(card("Clubs", "Queen"));
    q.push(card("Clubs", "King"));
    q.push(card("Clubs", "Ace"));

    for(int i = 2; i < 11; i++)
    {
        q.push(card("Diamonds", std::to_string(i)));
    }
    q.push(card("Diamonds", "Jack"));
    q.push(card("Diamonds", "Queen"));
    q.push(card("Diamonds", "King"));
    q.push(card("Diamonds", "Ace"));

    for(int i = 2; i < 11; i++)
    {
        q.push(card("Spades", std::to_string(i)));
    }
    q.push(card("Spades", "Jack"));
    q.push(card("Spades", "Queen"));
    q.push(card("Spades", "King"));
    q.push(card("Spades", "Ace"));

}

void swap (card *a, card *b)
{
    card temp = *a;
    *a = *b;
    *b = temp;
}

void shuffle(queue& deck) //shuffles deck of cards
{
    int size = deck.size();
    card list[deck.size()];

    for(int i = 0; i < size; i++)
    {
        list[i] = deck.pop();
    }

    srand (time(NULL));

    for(int i = size - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);

        swap(&list[i], &list[j]);
    }

    for(int i = 0; i < size; i++)
    {
        deck.push(list[i]);
    }

}

void reshuffle(queue& deck, queue& discard);

void drawCard(queue& deck, priorityQueue& hand, queue& discard) //only used in drawCards method
{
    if(!deck.isEmpty())
    {
    hand.push(deck.pop());
    }
    else
    {
        reshuffle(deck, discard);
        cout << "reshuffle" << endl;
        drawCard(deck, hand, discard);
    }
}

void drawCards(queue& deck, priorityQueue& hand, queue& discard, int num) //draws cards based on number the user enters
{
    for(int i = 0; i < num; i++)
    {
        drawCard(deck, hand, discard);
    }
}

void reshuffle(queue& deck, queue& discard) //moves cards from discard pile to deck then shuffles deck
{
    int size = discard.size();
    for(int i = 0; i < size; i++)
    {
        deck.push(discard.pop());
    }
    shuffle(deck);
}

int main()
{

    queue deck;
    priorityQueue hand;
    queue discard;
    createDeck(deck);
    shuffle(deck);

    int userNum;
    bool end = false;

    while(!end)
    {
        cout << "Enter a number from the menu" << endl;
        cout << "1. See more info" << endl;
        cout << "2. Check cards in hand" << endl;
        cout << "3. Use card in hand" << endl;
        cout << "4. Add cards from deck to hand" << endl;
        cout << "5. Shuffle deck" << endl;
        cout << "6. Reshuffle cards in discard pile into deck" << endl;
        cout << "7. End the program" << endl;
        cin >> userNum;

        if(userNum == 1)
        {
            cout << endl;
            cout << "what infomation would you like to see?" << endl;
            cout << "1. See cards in deck" << endl;
            cout << "2. See cards in discard pile" << endl;
            cout << "3. See number of cards in deck, hand and discard pile" << endl;
            cout << "4. Go back" << endl;
            cin >> userNum;

            if(userNum == 1)
            {
                cout << endl;
                cout << "Cards in deck:" << endl;
                deck.print();
            }
            else if(userNum == 2)
            {
                cout << endl;
                cout << "Cards in discard pile:" << endl;
                discard.print();
            }
            else if(userNum == 3)
            {
                cout << "Number of cards in deck: " << deck.size() << endl;
                cout << "Number of cards in hand: " << hand.size() << endl;
                cout << "Number of cards in discard pile: " << discard.size() << endl;
            }
            else if(userNum == 4)
            {
                cout << "Going back" << endl;
            }
            else
            {
                cout << "Error: not an option" << endl;
            }
        }
        else if(userNum == 2)
        {
            cout << "Cards in hand:" << endl;
            hand.print();
        }
        else if(userNum == 3)
        {
            cout << endl;
            cout << "Cards in hand:" << endl;
            hand.print();

            cout << "Enter the card you would like to play based on it's number, the first card is number 1" << endl;
            cin >> userNum;

            if(userNum < hand.size())
            {
                hand.playCard(userNum, discard);
                cout << "Card was played" << endl;
            }
            else
            {
                cout << "Error, not  valid card" << endl;
            }
        }
        else if(userNum == 4)
        {
            cout << "Enter how many cards you would like to draw" << endl;
            cin >> userNum;

            drawCards(deck, hand, discard, userNum);

            cout << "The cards have been drawn" << endl;
        }
        else if(userNum == 5)
        {
            shuffle(deck);
            cout << "The deck has been shuffled" << endl;
        }
        else if(userNum == 6)
        {
            reshuffle(deck, discard);
            cout << "Discard pile has been shuffled into deck" << endl;
        }
        else if(userNum == 7)
        {
            cout << "Goodbye" << endl;
            end = true;
        }
        else
        {
            cout << "Enter a number between 1 and 7" << endl;
        }

        cout << endl;
        cout << endl;

    }

    return 0;
}
