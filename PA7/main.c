#include "header.h"

int main(void)
{
	/* initialize suit array */
	const char* suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

	/* initialize face array */
	const char* face[13] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
		"Nine", "Ten", "Jack", "Queen", "King" };

	
	// Set rand string
	srand((unsigned int)time(NULL));
	int a = 1;
	while (a) {
		a = gameplay_menu();
		if (a == -1) {
			printf("Bye bye!");
			return;
		}
	}
	
	
	while (1)
	{
		system("cls");
		/* initalize deck array */
		int deck[4][13] = { 0 };

		// Declare variables

		int index = 0, playerRank = 0, computerRank = 0, count = 0, redrawn = 0, temp = 0;
		int counting[13] = { 0 };
		int indexes[5] = { 0 };
		struct Hand playerHand = { 0 }, computerHand = { 0 };
		int playerFaceValues[5] = { 0 }, computerFaceValues[5] = { 0 };
		int playerMax = 0, computerMax = 0;
		char input;

		shuffle(deck);
		playerHand = deal(deck, &index, 5, playerHand);
		computerHand = deal(deck, &index, 5, computerHand);

		printHand(playerHand);
		playerHand = redraw(playerHand, deck, &index);
		
		playerRank = getRank(playerHand);
		computerRank = getRank(computerHand);
		printf("Computer's hand:\n");
		printHand(computerHand);

		if (computerRank == 0 || computerRank == 1 || computerRank == 2 || computerRank == 3)
		{

			//fill tallying array at face values
			for (int i = 0; i < 5; i++)
			{
				counting[computerHand.cards[i].faceIndex]++;
			}
			//get highest play computer can make
			for (int i = 0; i < 5; i++)
			{
				if (temp < counting[computerHand.cards[i].faceIndex]) {
					temp = counting[computerHand.cards[i].faceIndex];
					count = computerHand.cards[i].faceIndex;
				}
			}
			//tally at cards to redraw
			for (int i = 0; i < 5; i++)
			{
				if (computerHand.cards[i].faceIndex != count) {
					indexes[i]++;
				}
			}
			//if the card is not included, redraw
			for (int i = 0; i < 5; i++)
			{
				if (indexes[i] == 1 && redrawn < 3)
				{
					computerHand.cards[i] = draw(deck, &index);
					redrawn++;
				}
			}

			printf("Computer redrew %d cards.\n\n\n", redrawn);
		}
		computerRank = getRank(computerHand);

		printf("Player Hand:\n");
		printHand(playerHand);
		printf("\nComputer Hand:\n");
		printHand(computerHand);

		if (playerRank > computerRank)
		{
			printf("congratulations you beat a robot\n");
		}
		else if (playerRank < computerRank)
		{
			printf("you lost\n");
		}
		else {
			for (int i = 0; i < 5; i++)
			{
				playerFaceValues[i] = playerHand.cards[i].faceIndex + 1;
				computerFaceValues[i] = computerHand.cards[i].faceIndex + 1;
			}

			bubbleSort(playerFaceValues, 5);
			bubbleSort(computerFaceValues, 5);

			if (playerRank == 8 || playerRank == 5 || playerRank == 4 || playerRank == 0)
			{
				if (playerFaceValues[4] > computerFaceValues[4])
				{
					printf("congratulations you beat a robot\n");
				}
				else if (playerFaceValues[4] < computerFaceValues[4])
				{
					printf("you lost\n");
				}
				else if (playerFaceValues[4] == computerFaceValues[4]) {
					if (playerFaceValues[0] == 1 && computerFaceValues[0] != 1) {
						printf("congratulations you beat a robot\n");
					}
					else if (playerFaceValues[0] != 1 && computerFaceValues[0] == 1) {
						printf("you lost\n");
					}
					else {
						printf("you tied\n");
					}
				}
				else {
					printf("you tied\n");
				}
			}
			else {
				printf("you tied\n");
			}

		}

		printf("Would you like to play again? (y/n)\n");
		scanf(" %c", &input);
		if (input != 'n') {
			continue;
		}
		else {
			break;
		}
	}

	return 0;
}





