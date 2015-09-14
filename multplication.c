#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
// for generating random numbers
#include <time.h>

#define MAX_ROUNDS 150
#define NUM_ROUNDS 30
#define MIN_MULTIPLE 2
#define MAX_MULTIPLE 12

#define ONE_SECOND 1000

void game_init(minmult, maxmult, total_rounds);

int main(void){
	
	int choice;
	int min, max, total_rounds;

	printf("Welcome to Multplication Drills! \n Press 0 to start, 1 to customize.");
	scanf_s("%d", &choice);

	if (choice == 0)
		game_init(MIN_MULTIPLE, MAX_MULTIPLE, NUM_ROUNDS);
	else
	{
		printf("Enter a minimum multiplier (integer): ");
		scanf_s("%d", &min);
		printf("Enter a maximum multiplier (integer): ");
		scanf_s("%d", &max);
		printf("How many rounds would you like to play? (max 150): ");
		scanf_s("%d", &total_rounds);
		while (total_rounds > MAX_ROUNDS)
		{
			printf("That's too many rounds!\n");
			printf("How many rounds would you like to play? (max 150): ");
			scanf_s("%d", &total_rounds);
		}

		game_init(min, max, total_rounds);
	}

	printf("Goodbye!\n\n");

	system("PAUSE");
	return 0;
}

void game_init(minmult, maxmult, total_rounds){
	
	/* Initialise round counter, array of questions, and loop constants */
	int round;
	int questionSequence[MAX_ROUNDS * 2];
	int mult1, mult2, guess;
	int correct;
	int k;
	char tryagain;

	/* Initialize clock constants */
	clock_t begin, end;
	double time_spent;

	/* Seed the random function using the setup time */
	srand((int)time(NULL));
	
	printf("Start the multiplication drills!\n\n");
	
	do {
		/* Start the clock */
		begin = clock();

		/* Reset correct answers */
		correct = 0;

		/* Generate question table */
		for (k = 0; k < total_rounds * 2; k++)
			questionSequence[k] = rand() % maxmult + minmult;

		for (round = 0; round < total_rounds; round++)
		{
			/* Select the right question numbers (round 0 gets 0 & 1, round 1 gets 2 and 3, etc)*/
			mult1 = questionSequence[2 * round];
			mult2 = questionSequence[2 * round + 1];

			/* Print the question, take the answer */
			printf("%d * %d = ", mult1, mult2);
			scanf_s("%d", &guess);

			/* If the guess is equal to the right thing, then increment correct,
			* otherwise, display the fail message. */
			if (mult1*mult2 == guess){
				correct++;
				printf("Correct! %d right out of %d. %d left.\n\n", correct, round + 1, total_rounds - round - 1);
			}
			else
				printf("Oh no! It was %d. %d right out of %d. %d left.\n\n", mult1*mult2, correct, round + 1, total_rounds - round - 1);
		}

		/* Stop the clock and calculate time spent in seconds */
		end = clock();
		time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

		/* Display results and prompt user to repeat the exercise. */
		printf("You got %d out of %d correct in %.2f seconds! Try again? (y/n): ", correct, total_rounds, time_spent);
		scanf_s(" %c", &tryagain);
		printf("\n");

	} while (tryagain == 'y');

	return;
}