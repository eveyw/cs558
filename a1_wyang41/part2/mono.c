#include <stdlib.h>
#include <stdio.h>
#include <string.h>
char *genmap(int seed)
{
	int i, pos;
	static char m[26];
	memset(m, 0, 26);
	srand(seed);
	for (i = 0; i != 26; ++i){
		pos = rand() % 26;
		while (m[pos] != 0) { pos = (pos + 1) % 26; }
		m[pos] = i + 'a';
	}
	return m;
}
char *genreversemap(char *m)
{
	static char rm[26];
	int i, j;
	for (i = 0; i != 26; ++i){
		for (j = 0; j != 26; ++j){
			if (m[j] == i + 'a'){
				rm[i] = j + 'a';
				break;
			}
		}
	}
	return rm;
}
void printmap(char *m)
{
	int i;
	for (i = 0; i != 26; ++i){
		printf("%c-%c%c", i + 'a', m[i], i == 25 ? '\n' : ',');
	}
}

	
void mono(FILE*, FILE*, int, int);	
void func(char *inf, char *outf, char *seed, char *isen)
{
	FILE *i, *o;
	i = fopen(inf, "r");
	if (i == NULL){
		fprintf(stderr, "cannot open file %s\n", inf);
		exit(1);
	}
	o = fopen(outf, "w");
	if (o == NULL){
		fprintf(stderr, "cannot open file %s\n", outf);
		exit(1);
	}
	mono(i, o, atoi(seed), atoi(isen));
}
void mono(FILE *stri, FILE *stro, int seed, int isen)
{
	char *m = genmap(seed);
	int ch;
	printmap(m);
	if (!isen){
		m = genreversemap(m);
	}
	while ((ch = getc(stri)) != EOF){
		putc(m[ch - 'a'], stro);
	}
	putchar('\n');
	fclose(stri);
	fclose(stro);
}
int main(int c, char **a)
{
	if (c != 5){
		printf("usage: %s <inputfile> <outputfile> <seed> 1/0", a[0]);
	} else {
		func(a[1], a[2], a[3], a[4]);
	}
	return 0;
}
