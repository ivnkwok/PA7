#pragma once
/*
PROJ: PA 5
AUTH: Alan Sun
DATE LAST MODIFIED: OCT 18 2022
INSTR: Andy O'Fallon
COURSE: CPT-S 121
PURPOSE: To play the game Yahtzee with multiple players
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

typedef struct Card {
	int faceIndex;
	int suitIndex;
} card;

typedef struct Hand {
	struct Card cards[5];
} hand;

void shuffle(int deck[][13]);

struct Hand deal(int deck[][13], int* index, int count, struct Hand hand);

struct Card draw(int deck[][13], int* index);

int gameplay_menu(void);

void print_game_rules(void);

int pair(struct Hand hand);

int twoPair(struct Hand hand);

int three_of_a_kind(struct Hand hand);

int four_of_a_kind(struct Hand hand);

int full_house(struct Hand hand);

int straight(struct Hand hand);

int flush(struct Hand hand);

void printHand(struct Hand hand);

void swap(struct Card cards[], int i1, int i2);

void redraw(struct Hand hand, int deck[][13], int* index);

void bubbleSort(int arr[], int count);

int getRank(struct Hand hand);