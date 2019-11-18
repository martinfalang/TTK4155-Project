#include "../Node1/src/highscore.h"

#include <stdio.h>

void print_all_scores(void) {
    char str[HIGHSCORE_STR_MAX_LENGTH];
    for (int p = 1; p <= NUM_HIGHSCORES; ++p) {
        highscore_print_score(str, p);
        printf(str);
        printf("\n");
    }
}

void test_highscore(void) {
    printf("\nInitializing highscore...\n");
    highscore_init();

    printf("\nPrinting scores\n");
    print_all_scores();

    printf("\nPrinting invalid score\n");
    char str[HIGHSCORE_STR_MAX_LENGTH];
    highscore_print_score(str, NUM_HIGHSCORES + 1); 
    
    printf(str);

    printf("\nNominating 13...\n");
    highscore_nominate(13);

    print_all_scores();
}