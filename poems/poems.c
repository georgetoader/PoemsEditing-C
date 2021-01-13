#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "util/task_helper.h"

#define MAX 5000
#define WD 200
#define INT 10

/*
 * Print poem.
 * @param s - The given poem.
 */
void print(char *s) {
	printf("%s\n\n", s);
}

/*
 * Check lowercase letter.
 * @param c - The letter to be checked.
 * @return - {@code 1} if it's lowercase
 *           {@code 0} if not
 */
int isLowerCase(char c) {
	if (c >= 'a' && c <= 'z') return 1;
	return 0;
}

/*
 * Change uppercase letter.
 * @param c - The letter to be checked.
 * @return - {@code 1} if it's uppercase
 *           {@code 0} if not
 */
int isUpperCase(char c) {
	if (c >= 'A' && c <= 'Z') return 1;
	return 0;
}

/*
 * Check letter.
 * @param c - The letter to be checked.
 * @return - {@code 1} if it's a letter
 *           {@code 0} if not a letter
 */
int isLetter(char c) {
	if (isUpperCase(c) || isLowerCase(c)) return 1;
	return 0;
}

/*
 * Change lowercase to uppercase and vice versa
 * @param c - The letter to be changed.
 * @return - The changed letter.
 */
char change(char c) {
	if (isLowerCase(c)) c -= 32;
	else if (isUpperCase(c)) c += 32;
	return c;
}

/*
 * Change letters from uppercase to lowercase in poem.
 * @param s - The given poem.
 */
void uppercase(char *s)
{
	int i;
	for (i = 0; i < strlen(s); i++) {
		if (isUpperCase(s[i])) s[i] += 32;
		if (s[i-1] == '\n') {
			if (isLowerCase(s[i])) s[i] -= 32;
		}
	}
	if (isLowerCase(s[0])) s[0] -= 32;
}

/*
 * Eliminate non-letter characters from poem
 * @param s - The given poem.
 */
void trimming(char *s)
{
	int i,j,ok=0;
	for (i=0; i < strlen(s); i++) {
		if (!isLetter(s[i])) {
			while (s[i+1]==' ' || s[i+1]=='.' || s[i+1]==','
					|| s[i+1]==';' || s[i+1]=='!' || s[i+1]=='?' || s[i+1]==':') {
			//remove all non-letter characters
				memmove(s+i+1, s+i+2, strlen(s)-i-1);
				s[i] = ' ';
				if (s[i+1] == '\n') break;
			}
			//remove non-letter character at end of line
			if (!isLetter(s[i]) && s[i+1]=='\n' && s[i] != '\n')
				memmove(s+i, s+i+1, strlen(s)-i);
		}
	}
	//remove last character of poem if non-letter
	if (isLetter(s[strlen(s)-1]) == 0) s[strlen(s)-1] = '\0';
}

/*
 * Change every letter randomly using change()
 * @param s - The given poem.
 * @param val - Value used for comparing.
 */
void silly(char *s, float val)
{
	int i;
	for (i = 0; i < strlen(s); i++) {
		if (isLetter(s[i])) {
			float sample = rand() % 100 / 99.0;
			if (sample < val) s[i] = change(s[i]);
		}
	}
}

/*
 * Search the poem and when a word with diminutive is found
 * that word is replaced with its diminutive. The list of diminutives
 * is given as input.
 * @param s - The given poem.
 */
void friendly(char *s)
{
	int i, j, nr = 0;
	char *friendly_word = NULL;
	char *aux = malloc(MAX);		//auxiliary pointer
	for (i = 0; i < strlen(s); i++) {
		if (isLetter(s[i])) {
			//find location of word in poem
			nr = i;
			while (isLetter(s[i])) i++;
			char *word = malloc(i-nr+1);
			memcpy(word, s + nr, i - nr);
			word[i - nr] = '\0';
			//find the diminutive
			get_friendly_word(word, &friendly_word);
			if (friendly_word !=  NULL) {
				//if it has diminutive then change it
				memcpy(aux, s, nr);
				memcpy(aux + nr, friendly_word, strlen(friendly_word));
				strcpy(aux + nr + strlen(friendly_word), s + i);
				strcpy(s,aux);
			}
			free(word);
		}
	}
	free(friendly_word);
	free(aux);
}

/*
 * Returns the last letter of the word given as input.
 * @param word - The word to be checked.
 * @return - Last letter of word.
 */
char lastLetter(char *word) {
	return word[strlen(word)-1];
}

/*
 * Swap 2 words given as input.
 * @param s - The given poem.
 * @param word1 - The new word.
 * @param vers - Index of old word to be swapped.
 * @return - Last letter of word.
 */
void swap_words(char *s, char *word1, int vers) {
	char *aux = malloc(10000);
	memcpy(aux, s, vers);
	memcpy(aux + vers, word1, strlen(word1));
	int l = vers + strlen(word1);
	int q = vers;
	while (isLetter(s[q])) q++;
	strcpy(aux + l, s + q);
	strcpy(s,aux);
}

/*
 * Change the last words of the lyrics so that they rhyme.
 * @param s - The given poem.
 * @param ryme - The type of ryme.
 */
void rhimy(char *s, int ryme)
{
	int i, j, nr = 0, nr_vers = 0;
	char **list1_syn = malloc(WD);	//first word's synonyms
	char **list2_syn = malloc(WD);	//second word's synonyms
	int *n = malloc(INT);
	int *m = malloc(INT);
	int v[4];	//indices of last words
	int vers[4];

	int total_car = 0;
	char aux[MAX];
	strcpy(aux, s);

	char *token = malloc(WD);	//separate on lyrics
	char word[30][WD];
	token = strtok(aux, "\r\n");
	char p[WD];

	while (token != NULL) {
		if (strlen(token) == 2) token = strtok(NULL, "\r\n");
		if (nr_vers == 4) nr_vers = 1, total_car++;
		else nr_vers++;
		i = strlen(token) - 1;
		while (token[i] != ' ') i--;
		while (isLetter(s[total_car + i + 1])) total_car--;
		total_car++;

		if (nr_vers == 1) v[0] = total_car + i + 1;
		else if (nr_vers == 2) v[1] = total_car + i + 1;
		else if (nr_vers == 3) v[2] = total_car + i + 1;
		else if (nr_vers == 4) v[3] = total_car + i + 1;
		total_car += strlen(token)+1;

		memcpy(p, token + i + 1, strlen(token) - i);	//copy last word

		int nr = 1;
		while (!isLetter(p[strlen(p) - nr])) nr++; //make sure it ends with letter
		p[strlen(p) - nr + 1] = '\0';
		uppercase(p);
		strcpy(word[nr_vers - 1], p);

		char best[WD];
		char word1[WD];
		char word2[WD];
		char word3[WD];
		char word4[WD];
		if (nr_vers == 4) {

			if (ryme == 1) {	//mated rhyme
			strcpy(word1,word[0]);
			strcpy(word2,word[1]);
			strcpy(word3,word[2]);
			strcpy(word4,word[3]);
			vers[0]=v[0];
			vers[1]=v[1];
			vers[2]=v[2];
			vers[3]=v[3];
			} else if (ryme == 2) {	//cross rhyme
			strcpy(word1,word[0]);
			strcpy(word2,word[2]);
			strcpy(word3,word[1]);
			strcpy(word4,word[3]);
			vers[0]=v[0];
			vers[1]=v[2];
			vers[2]=v[1];
			vers[3]=v[3];
			} else if (ryme == 3) {	//embraced rhyme
			strcpy(word1,word[0]);
			strcpy(word2,word[3]);
			strcpy(word3,word[1]);
			strcpy(word4,word[2]);
			vers[0]=v[0];
			vers[1]=v[3];
			vers[2]=v[1];
			vers[3]=v[2];
			}
			if (lastLetter(word1) != lastLetter(word2)) {
				get_synonym(word1,n,&list1_syn); //first word's synonyms
				get_synonym(word2,m,&list2_syn); //second word's synonyms
				if (*n > -1 && *m == -1) {	//first word has synonyms
					char c2=lastLetter(word2);
					strcpy(best,"");
					//find best word
					for (i=0; i<*n; i++) {
						char c1=lastLetter(list1_syn[i]);
						if (c1 == c2) { //same letter
							if (i==0 || strlen(best)==0) strcpy(best,list1_syn[i]);
							else if (strcmp(best,list1_syn[i]) > 0)
								strcpy(best,list1_syn[i]);
					}}
					if (strlen(best) > 2) swap_words(s,best,vers[0]);
					int dif1 = strlen(best);
					int dif2 = strlen(word1);
					int dif = dif1 - dif2;
					//if different lengths
					vers[0] = vers[0] + dif;
					vers[1] = vers[1] + dif;
					vers[2] = vers[2] + dif;
					vers[3] = vers[3] + dif;

				} else if (*m >-1 && *n == -1) {
					char c2=lastLetter(word1);
					strcpy(best,"");
					for (i=0; i<*m; i++){
						char c1=lastLetter(list2_syn[i]);
						if (c1 == c2) {
							if (i==0 || strlen(best)==0) strcpy(best,list2_syn[i]);
							else if (strcmp(best,list2_syn[i]) > 0)
								strcpy(best,list2_syn[i]);
					}}
					if (strlen(best) > 2) swap_words(s,best,vers[1]);
					int dif1 = strlen(best);
					int dif2 = strlen(word2);
					int dif = dif1 - dif2;
					vers[0] = vers[0] + dif;
					vers[1] = vers[1] + dif;
					vers[2] = vers[2] + dif;
					vers[3] = vers[3] + dif;
				}}
			if (lastLetter(word3) != lastLetter(word4)) {
				get_synonym(word3,n,&list1_syn); //third word's synonyms
				get_synonym(word4,m,&list2_syn); //fourth word's synonyms
				if (*n > -1 && *m == -1) {
					char c2=lastLetter(word4);
					strcpy(best,"");
					for (i=0; i<*n; i++) {
						char c1=lastLetter(list1_syn[i]);
						if (c1 == c2) {
							if (i==0 || strlen(best)==0) strcpy(best,list1_syn[i]);
							else if (strcmp(best,list1_syn[i]) > 0)
								strcpy(best,list1_syn[i]);
					}}
					if (strlen(best) > 2) swap_words(s,best,vers[2]);
				} else if (*m >-1 && *n == -1) {
					char c2=lastLetter(word3);
					strcpy(best,"");
					for (i=0; i<*m; i++){
						char c1=lastLetter(list2_syn[i]);
						if (c1 == c2) {
							if (i==0 || strlen(best)==0) strcpy(best,list2_syn[i]);
							else if (strcmp(best,list2_syn[i]) > 0)
								strcpy(best,list2_syn[i]);
					}}
					if (strlen(best) > 2) swap_words(s,best,vers[3]);
				}
			}
		}
		token = strtok(NULL, "\r\n"); //next lyric

	}
	free(token);

}

int main(void)
{
	int i=0, ok=1;
	char *s = malloc(MAX);
	char input[WD];
	srand(42);

	while (ok) {
        fgets(input,30,stdin);
        if (strstr(input,"load") != NULL) {
            if (strstr(input,"1")) load_file("poems/test1/test1", s);
            if (strstr(input,"2")) load_file("poems/test2/test2", s);
            if (strstr(input,"3")) load_file("poems/test3/test3", s);
            if (strstr(input,"4")) load_file("poems/test4/test4", s);
            if (strstr(input,"5")) load_file("poems/test5/test5", s);
        }
        else if (strstr(input,"uppercase") != NULL) uppercase(s);
        else if (strstr(input,"trimming") != NULL) trimming(s);
        else if (strstr(input,"silly") != NULL) {
            char *p = input;
            p += 14;
            float val = atof(p);
            silly(s,val);
        }
        else if (strstr(input,"friendlier") != NULL) friendly(s);
        else if (strstr(input,"rhyme")) {
            if (strstr(input,"imperecheata") != NULL) rhimy(s,1);
            else if (strstr(input,"incrucisata") != NULL) rhimy(s,2);
            else if (strstr(input,"imbratisata") != NULL) rhimy(s,3);
        }
        else if (strstr(input,"print") != NULL) print(s);
        if (strstr(input,"quit") != NULL) ok=0;
	}


	return 0;
}