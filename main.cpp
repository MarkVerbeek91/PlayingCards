#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class Card
{
public:
    void set_rank(int r)
    {
        card_rank = r;
    }

    void set_suit(string s)
    {
        card_suit = s;
    }

    void set_suit_nr(int i)
    {
        switch(i)
        {
            case 1:
                card_suit = "Hearts";
                break;
            case 2:
                card_suit = "Diamonds";
                break;
            case 3:
                card_suit = "Clubs";
                break;
            case 4:
                card_suit = "Spades";
                break;
            default:
                cout << "unknown suit is given" << endl;
                break;
        }
    }

    int give_rank()
    {
        return card_rank;
    }

    string give_suit()
    {
        return card_suit;
    }

    void clear_card()
    {
        card_rank = -1;
        card_suit = "empty";
    }

    void copy_card(Card x)
    {
        card_rank = x.give_rank();
        card_suit = x.give_suit();
    }

    void print()
    {
        cout << " Card info: " << card_rank << " " << card_suit << endl;
    }

protected:
    int    card_rank;
    string card_suit;
};

class card_stack
{
public:

    void clear_stack()
    {
        length_stack = 0;
        for ( int i = 0; i<52; i++)
        {
            cards[i].clear_card();
        }
    }

    bool compare()
    {
        if ( cards[length_stack-1].give_suit().compare(cards[length_stack-2].give_suit()))
            return true;
        else
            return false;
    }

    void add_card(Card cr)
    {
        cards[length_stack].copy_card(cr);
        length_stack++;

        if ( length_stack == 51)
        {
            cout << "Stack full" << endl;
        }

    }

    Card give_first_card()
    {

        temp_card.copy_card(cards[0]);

        for (int i = 0; i < length_stack-1; i++)
        {
            cards[i].copy_card(cards[i+1]);
        }

        cards[length_stack-1].clear_card();
        length_stack--;

        return temp_card;
    }

    Card give_card(int x)
    {

        temp_card.copy_card(cards[x]);

        for (int i = x; i < length_stack-1; i++)
        {
            cards[i].copy_card(cards[i+1]);
        }

        cards[length_stack-1].clear_card();
        length_stack--;

        return temp_card;
    }

    void print_stack()
    {
        for ( int i = 0; i<length_stack; i++)
            cout << "Suit: " << cards[i].give_suit() << " with rank: " << cards[i].give_rank() << endl;

        cout << "Stack Length: " << length_stack << endl;
    }

    int length_of_stack()
    {
        return length_stack-1;
    }

protected:
    Card cards[52];
    int length_stack;
    Card temp_card;
};

class Game
{
public:
    void Create_Deck()
    {

        start_stack.clear_stack();
        begin_stack.clear_stack();
        stack_inge.clear_stack();
        stack_mark.clear_stack();

        for ( int i = 0; i<13; i++)
        {
            for ( int j = 1; j <= 4; j++)
            {
                temp_card2.set_rank(i);
                temp_card2.set_suit_nr(j);
                start_stack.add_card(temp_card2);
            }
        }
    }

    void Shuffle()
    {
        int cards_number;

        for ( int i = 0; i < 51; i++)
        {
            cards_number = rand() % start_stack.length_of_stack();
            begin_stack.add_card(start_stack.give_card(cards_number));

       //     begin_stack.print_stack();
        }

        for ( int i = 0; i < 26; i++)
        {
            stack_inge.add_card(begin_stack.give_first_card());
            stack_mark.add_card(begin_stack.give_first_card());
        }
    }

    void Play_game()
    {
        while( stack_inge.length_of_stack() != 51 || stack_mark.length_of_stack() != 51)
        {
            begin_stack.add_card(stack_inge.give_first_card());
            begin_stack.add_card(stack_mark.give_first_card());

            if ( begin_stack.compare() )
            {
                begin_stack.print_stack();
                cout << " We got a winner " << endl;
                break;
            }

        }
    }

    void Show_game()
    {
        cout << "- Start stack: " << endl;
        start_stack.print_stack();
        cout << "- Begin stack: " << endl;
        begin_stack.print_stack();
        cout << "- Inge stack: " << endl;
        stack_inge.print_stack();
        cout << "- Mark stack: " << endl;
        stack_mark.print_stack();
    }

protected:
    Card temp_card2;
    card_stack start_stack;
    card_stack begin_stack;
    card_stack stack_inge;
    card_stack stack_mark;
};

int main()
{
    cout << "Hello world!" << endl;

    Game of_Cards;

  //  test_card.set_rank(10);
  //  test_card.set_suit("spade");

  //  cout << "Card suit: " << test_card.give_suit() << endl;
    of_Cards.Create_Deck();

    of_Cards.Show_game();

    of_Cards.Shuffle();

    of_Cards.Show_game();

  //
    of_Cards.Play_game();

    return 0;
}
