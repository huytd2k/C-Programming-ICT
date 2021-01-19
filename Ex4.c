#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
    int f;
    int s;
} pair;

pair make_pair(int _f, int _s)
{
    pair retPair;
    retPair.f = _f;
    retPair.s = _s;
    return retPair;
}

int c[13][4];

void printCard(pair card);
void printFourOfAKind(pair card[]);
char *decodeSuit(int code);
char *decodeRank(int code);

pair distribute_a_card();

void printBreak()
{
    printf("\n");
    for (int i = 0; i < 65; i++)
        putchar('=');
    printf("\n");
}

int main()
{
    //* https://stackoverflow.com/questions/2516096/fastest-way-to-zero-out-a-2d-array-in-c
    memset(c, 0, sizeof(int) * 13 * 4); //* Init cards array with zeros;
    time_t t;

    pair first_player_cards[13];
    pair second_player_cards[13];
    pair third_player_cards[13];
    pair fourth_player_cards[13];
    srand((unsigned)time(&t));

    // printf("%d", rand());
    for (int i = 0; i < 13; i++)
    {
        first_player_cards[i] = distribute_a_card();
        second_player_cards[i] = distribute_a_card();
        third_player_cards[i] = distribute_a_card();
        fourth_player_cards[i] = distribute_a_card();
    }
    printf("Nguoi choi thu 1 co :\n");
    for (int i = 0; i < 13; i++)
    {
        printCard(first_player_cards[i]);
    }
    printFourOfAKind(first_player_cards);
    printBreak();

    printf("\nNguoi choi thu 2 co :\n");
    for (int i = 0; i < 13; i++)
    {
        printCard(second_player_cards[i]);
    }
    printFourOfAKind(second_player_cards);
    printBreak();

    printf("\nNguoi choi thu 3 co :\n");
    for (int i = 0; i < 13; i++)
    {
        printCard(third_player_cards[i]);
    }
    printFourOfAKind(third_player_cards);
    printBreak();

    printf("\nNguoi choi thu 4 co :\n");
    for (int i = 0; i < 13; i++)
    {
        printCard(fourth_player_cards[i]);
    }
    printFourOfAKind(fourth_player_cards);
    printBreak();
    return 0;
}

pair distribute_a_card()
{
    int random_number = rand() % 52;
    int col = random_number / 4;
    int row = random_number % 4;
    while (c[col][row] == 1)
    {
        random_number = (random_number == 51) ? 0 : random_number + 1;
        col = random_number / 4;
        row = random_number % 4;
    }
    c[col][row] = 1;
    return make_pair(col, row);
}

void printCard(pair card)
{
    char *rank = decodeRank(card.f);
    char *suite = decodeSuit(card.s);
    printf("|%s %s", rank, suite);
}

void printFourOfAKind(pair card[])
{
    int count[13];
    memset(count, 0, sizeof(int) * 13);
    for (int i = 0; i < 13; i++)
    {
        count[card[i].f]++;
    }
    for (int i = 0; i < 13; i++)
    {
        // printf("%d \n", count[i]);
        if (count[i] < 4)
            continue;
        printf("\n Co tu quy %s", decodeRank(i));
    }
}

char *decodeSuit(int code)
{
    switch (code)
    {
    case 0:
        return "co";
    case 1:
        return "ro";
    case 2:
        return "bich";
    case 3:
        return "tep";
    default:
        break;
    }
}
char *decodeRank(int code)
{
    switch (code)
    {
    case 0:
        return "A";
    case 1:
        return "2";
    case 2:
        return "3";
    case 3:
        return "4";
    case 4:
        return "5";
    case 5:
        return "6";
    case 6:
        return "7";
    case 7:
        return "8";
    case 8:
        return "9";
    case 9:
        return "10";
    case 10:
        return "J";
    case 11:
        return "Q";
    case 12:
        return "K";
    default:
        break;
    }
}