#include "header.h"

/* shuffle cards in deck */
void shuffle(int deck[][13])
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */

	/* for each of the 52 cards, choose slot of deck randomly */
	for (card = 0; card <= 51; card++)
	{
		/* choose new random location until unoccupied slot found */
		do
		{
			row = rand() % 4;
			column = rand() % 13;
		} while (deck[row][column] != 0);

		/* place card number in chosen slot of deck */
		deck[row][column] = card;
	}
}

/* deal cards in deck */
struct Hand deal(int deck[][13], int* index, int count, struct Hand hand)
{
	for (int i = 0; i < count; i++)
	{
		hand.cards[5 - count + i] = draw(deck, index);
	}
	return hand;
}

//draw the next card in the deck
struct Card draw(int deck[][13], int* index) {
	struct Card card = { 0, 0 };

	//traverse column, then row
	card.faceIndex = (deck[*index / 13][*index % 13]) % 13;
	card.suitIndex = (deck[*index / 13][*index % 13]) / 13;
	//increment index pointer so same card is not dealt twice
	(*index)++;

	return card;
}

//basic menu for selection options
int gameplay_menu(void)
{
	int option = 0, play_game = 0;

	printf("Welcome to Poker!\n\n");

	printf("Choose an option by entering the corresponding number:\n1. Print game rules\n2. Start a game of Poker\n3. Exit\n");

	scanf("%d", &option);
	if (option == 1) {
		system("cls");
		printf("Welcome to Poker!\n");

		print_game_rules();
		play_game = 1;
	}
	else if (option == 2)
	{
		return 0;
	}
	else if (option == 3) {
		play_game = -1;
	}
	else {
		system("cls");
		printf("Enter a valid response.\n");
	}
	return play_game;

}

//print rules
void print_game_rules(void) 
{
	printf("Play begins with each player being dealt five cards, one at a time, all face down.\n");
	printf("The remaining deck is placed aside. Players pick up the cards and review them.\n");
	printf("If more than one player remains after the first round, the draw phase begins.\n");
	printf("Each player specifies how many of their cards they wish to replace and discards any cards they choose.\n");
	printf("Each player is dealt in turn from the deck so that each player again has five cards.\n");
	printf("Each player's goal is to try have higher priority one of following the ten categories:\n");
	printf("\t (Listed from Best to Worst)\n");
	printf("\t Royal flush - 5 cards of the same suit which are Ace, King, Queen, Jack, Ten\n");
	printf("\t Straight flush - Any five consecutive numbers which are all from the same suit\n");
	printf("\t Four of a kind - Four cards with the same number\n");
	printf("\t Full house - three of a kind and a pair\n");
	printf("\t Flush - Five cards which are all from the same suit\n");
	printf("\t Straight - Any five consecutive numbers\n");
	printf("\t Three of a kind - Three cards with the same number\n");
	printf("\t Two pair - Two pairs\n");
	printf("\t Pair - Two cards with the same number\n");
	printf("\t No pair - None of the above\n");
	printf("If both players end up on the same priority tier, then the highest card will win according to the following order:\n");
	printf("(Highest) A K Q J 10 9 8 7 6 5 4 3 2 (Lowest)\n");
	printf("The combination which is highest on this list will be used as the player's play\n");
	printf("If more than one player remains the player with the best hand wins the pot.\n");
}

int flush(struct Hand hand)
{
	int store[4] = { 0 };

	for (int i = 0; i < 5; i++)
	{
		store[hand.cards[i].suitIndex]++;
	}

	for (int i = 0; i < 4; i++)
	{
		if (store[i] == 5)
		{
			return 1;
		}
	}

	return 0;
}

int three_of_a_kind(struct Hand hand)
{
	int store[13] = { 0 }, x = 0;

	for (int i = 0; i < 5; i++)
	{
		store[hand.cards[i].faceIndex]++;
	}

	for (int i = 0; i < 13; i++)
	{
		if (store[i] > 2) {
			x = 1;
			break;
		}
	}

	return x;
}

int four_of_a_kind(struct Hand hand)
{
	int store[13] = { 0 }, x = 0;

	for (int i = 0; i < 5; i++)
	{
		store[hand.cards[i].faceIndex]++;
	}

	for (int i = 0; i < 13; i++)
	{
		if (store[i] > 3) {
			x = 1;
			break;
		}
	}

	return x;
}

int pair(struct Hand hand)
{
	int store[13] = { 0 }, x = 0;

	for (int i = 0; i < 5; i++)
	{
		store[hand.cards[i].faceIndex]++;
	}

	for (int i = 0; i < 13; i++)
	{
		if (store[i] > 1) {
			x = 1;
			break;
		}
	}

	return x;
}

int twoPair(struct Hand hand) {
	int store[13] = { 0 };
	int count = 0;

	for (int i = 0; i < 5; i++)
	{
		store[hand.cards[i].faceIndex]++;
	}

	for (int i = 0; i < 13; i++)
	{
		if (store[i] == 2) {
			count++;
		}
	}

	return count == 2 ? 1 : 0;
}

int full_house(struct Hand hand)
{
	int store[13] = { 0 }, x = 0, comp1 = 0, comp2 = 0;

	for (int i = 0; i < 5; i++)
	{
		store[hand.cards[i].faceIndex]++;
	}

	for (int i = 0; i < 13; i++)
	{
		if (store[i] == 2)
		{
			comp1 = 1;
		}
		if (store[i] == 3)
		{
			comp2 = 1;
		}
	}

	if (comp1 == 1 && comp2 == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int straight(struct Hand hand)
{
	int temp[13] = { 0 };
	int count = 0;

	for (int i = 0; i < 5; i++)
	{
		temp[hand.cards[i].faceIndex]++;
	}
	for (int i = 0; i < 13; i++)
	{
		if (temp[i] == 1) {
			count++;
		}
		if (temp[i] == 0) {
			count = 0;
		}
		if (count == 5) {
			return 1;
		}
	}
	return 0;
}

void swap(struct Card cards[], int i1, int i2)
{
	struct Card temp = cards[i1];
	cards[i1] = cards[i2];
	cards[i2] = temp;
}

void printHand(struct Hand hand) {
	const char* suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };
	const char* face[13] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };

	for (int i = 0; i < 5; i++)
	{
		printf("%d: %5s of %-8s\n", i + 1, face[hand.cards[i].faceIndex], suit[hand.cards[i].suitIndex]);
	}
}

//redraw
struct Hand redraw(struct Hand hand, int deck[][13], int* index)
{
	int redrawn_num = 0, store[3] = { 0, 0, 0 }, reroll_card = 0;

	do {
		printf("Enter the amount of cards you wish to redraw (1 - 3) or input 0 if you wish to redraw no cards: \n");
		scanf("%d", &redrawn_num);
		printHand(hand);
		//store redrawn indexes into array
		if (redrawn_num == 0)
		{
			return;
		}
		else if (redrawn_num == 1) {
			printf("Enter the index of the card you would like to replace: \n");
			scanf("%d", &store[0]);
		}
		else if (redrawn_num == 2) {
			printf("Enter the indexes of the cards you would like to replace: \n");
			scanf("%d %d", &store[0], &store[1]);
		}
		else if (redrawn_num == 3) {
			printf("Enter the indexes of the cards you would like to replace: \n");
			scanf("%d %d %d", &store[0], &store[1], &store[2]);
		}
	} while (redrawn_num < 0 || redrawn_num > 3);
	
	//loop through array and redraw at indexes
	for (int i = 0; i < redrawn_num; i++)
	{
		hand.cards[store[i] - 1] = draw(deck, index);
	}

	printHand(hand);
	return hand;
}

void bubbleSort(int arr[], int count) {
	int temp, swapped;
	do {
		swapped = 0;
		for (int i = 1; i < count; i++)
		{
			if (arr[i - 1] > arr[i]) {
				swapped++;
				temp = arr[i];
				arr[i] = arr[i - 1];
				arr[i - 1] = temp;
			}
		}
	} while (swapped != 0);
}

//return score
int getRank(struct Hand hand) {
		
	if (straight(hand) && flush(hand)) {
		return 8;
	}
	else if (four_of_a_kind(hand)) {
		return 7;
	}
	else if (full_house(hand))
	{
		return 6;
	}
	else if (flush(hand))
	{
		return 5;
	}
	else if (straight(hand))
	{
		return 4;
	}
	else if (three_of_a_kind(hand))
	{
		return 3;
	}
	else if (twoPair(hand)) {
		return 2;
	}
	else if (pair(hand)) {
		return 1;
	}
}