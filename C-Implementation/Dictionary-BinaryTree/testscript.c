#include "SIdict.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Written by Christopher Hittner
 * I pledge my honor that I have abided by the Stevens Honor System.
 */

/*
This script contains three tests. They can each be run with argument values 1, 2 and 3.
Each section is weighted and assigned as followed

Submission - 9 pts if compilation successsful, otherwise 4
Basic Functionality - 9 pts
Addition, Lookup and Update - 18 pts
Item Removal - 14 pts

*/

int doAdd(SIdict d, char key[], int val, int aOu) {
    int score = 0;

    if (addOrUpdate(d, key, val) == aOu)
        score += 1;
    else
        printf("Invalid return value when %s key '%s' with value %i (-1 pts)\n", aOu ? "updating" : "adding", key, val);

    return score;

}

/*
If val is 0, then testing non-presence
1 if correctly determines non-presence
2 if correctly determines presence
*/
int doLookup(SIdict d, char key[], int val) {
    int score = 0;

    //Points for having the key in the list
    if (hasKey(d, key)) {
        if (!val) {
            printf("Program found key '%s' that is not in the list (-1 pts)\n", key);
            return 0;
        }

        score += 1;
        
        //Checks getter
        int v = lookup(d, key);
        if (v == val)
            score += 1;
        else {
            printf("Error when looking up key '%s' associated with value %i in list; got %i instead (-1 pts)\n", key, val, v);
        }

    } else if (!val)
        return 1;
    else
        printf("Key '%s' could not be found in list (-2 pts)\n", key);

    return score;

}

int doRemove(SIdict d, char key[], int val) {
    int v = remKey(d, key);
    int score = 0;

    if (val == v)
        score += 1; 
    else {
        printf("Incorrect result code returned when removing key '%s': got %i when %i was expected (-1 pts)\n", key, v, val);
    }

    if (hasKey(d, key)) {
        printf("Key '%s' was not properly removed from the list (-1 pts)\n", key);
    }
    else
        score += 1;
    
    return score;
}

/* Test 1 - Determine whether or not list can be made properly. (9 pts) */
int test1(char *argv[]) {
    
    int score = 0;

    // Makes a dictionary (4 pts)
    SIdict dict = makeSIdict();
    score += 4;
    
    //Check that it can recognize an empty list (1 pts)
    score += doLookup(dict, "a", 0);

    /* [] -> ["a" : 1, "b" : 2, "c" : 3] */

    //Add "a" : 1 (1+2=3 pts)
    score += doAdd(dict, "a", 1, 0);
    score += doLookup(dict, "a", 1);

    //Should not find something that's not there (1 pts)
    score += doLookup(dict, "b", 0);
    
    return score;
            
}

/* Test 2 - Test adding and appending (18 pts) */
int test2(char *argv[]) {
    
    int score = 0;
    
    SIdict dict = makeSIdict();
    
    //Add a, b, and c with values 1, 2, 3 (3x1=3 pts)
    score += doAdd(dict, "a", 1, 0);
    score += doAdd(dict, "b", 2, 0);
    score += doAdd(dict, "c", 3, 0);

    //Can I print them now? (3x2=6 pts)
    score += doLookup(dict, "a", 1);
    score += doLookup(dict, "b", 2);
    score += doLookup(dict, "c", 3);

    //Updates "b" to 4 (1+2=3 pts)
    score += doAdd(dict, "b", 4, 1);
    score += doLookup(dict, "b", 4);

    //Updates "b" to 4 pts (1+2=3)
    score += doAdd(dict, "a", 5, 1);
    score += doLookup(dict, "a", 5);
    
    //Check that non-existence is true, then the presence of a thing (1+2=3 pts)
    score += doLookup(dict, "d", 0);
    score += doLookup(dict, "c", 3);

    return score;

}

/* Test 3 - Removal of items (13 pts) */
int test3(char *argv[]) {
    
    int score = 0;

    SIdict dict = makeSIdict();

    addOrUpdate(dict, "a", 1);
    addOrUpdate(dict, "b", 2);
    addOrUpdate(dict, "c", 3);
    addOrUpdate(dict, "d", 4);

    //Remove 'b' (2 pts)
    score += doRemove(dict, "b", 1);

    //Readd 'b' as 2 (1 pts)
    score += doAdd(dict, "b", 2, 0);

    //Remove 'a' and 'b' as edge cases (2x2=4 pts)
    score += doRemove(dict, "a", 1);
    score += doRemove(dict, "b", 1);

    //Try removing something that's gone (2x2=4 pts)
    score += doRemove(dict, "a", 0);
    score += doRemove(dict, "b", 0);
    
    //Test presence of 'c' and non-presence of 'a' (1+2=3 pts)
    score += doLookup(dict, "c", 3);
    score += doLookup(dict, "a", 0);


    return score;

}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Please give the program a number, Justin.\n");
        return 137;
    }
    
    int test = atoi(argv[1]);
    int score;

    switch (test) {
        case 1:
            printf("PART 1\n======\n");
            score = test1(&argv[2]);
            break;
        case 2:
            printf("PART 2\n======\n");
            score = test2(&argv[2]);
            break;
        case 3:
            printf("PART 3\n======\n");
            score = test3(&argv[2]);
            break;
        default:
            printf("No Justin, %s is not a test.\n", argv[1]);
            score = 139;
    }

    printf("Score for part %i is %i\n\n", test, score);
    
    return score;

}

