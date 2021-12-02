#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <ctype.h>


#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

//With 2 strings of different length string a should always be the shortest one

int dl_strcmp(const char *,  const char *);
int hamming_strcmp(const char *, const char *, unsigned int);
int fuzzy_strcmp(const char *, const char *);
void get_string(char**, size_t *);
void strlower(char*);
int agg_sub_fuzzy_strcmp(char*, char*);

int main(int argc, char *argv[]) {
    if (argc == 1){
        printf("No arguments passed\n");
        return 1;
    }
    int str_arg_len = strlen(argv[1]);

    size_t buffer_size = sizeof(char)*20;
    char * buffer = (char *) malloc(buffer_size);

    get_string(&buffer, &buffer_size);
    
    char * buffer_string = strdup(buffer);
    char * token;
    char * tail;

    int cmp;

    strlower(buffer_string);
    strlower(argv[1]);

    for (token = strtok_r(buffer_string, "\n", &tail);
        token != NULL && *token != -1;
        token = strtok_r(NULL, "\n", &tail)) {
        
        cmp = agg_sub_fuzzy_strcmp(argv[1], token);
        printf("%d\n", cmp);
    }
    free(buffer_string);
    free(buffer);

    return 0;
}

int agg_sub_fuzzy_strcmp(char * str_a, char * str_b){
    char * str_a_workable = strdup(str_a);
    char * token;
    char * tail;

    int str_b_len = strlen(str_b);

    int cmp = 0;

    for (token = strtok_r(str_a_workable, " ", &tail);
         token != NULL && *token != -1;
         token = strtok_r(NULL, " ", &tail)) {
        
        if (strlen(token)<str_b_len){
            cmp += fuzzy_strcmp(token, str_b);
        } else {
            cmp += fuzzy_strcmp(str_b, token);
        }
    }

    free(str_a_workable);

    return cmp;
 
}

void strlower(char * str){
    char * c = str;
    while (*c != '\0'){
        *c = tolower(*c);
        c++;
    } 

}

void get_string(char ** buff_ptr, size_t * cap){
    int character = 1;
    int chars_read = 0;
    char* buff = *buff_ptr;
    while (character != EOF) {
        character = getchar();
        chars_read++;
        if (*cap<=(chars_read-1)){
            *cap = sizeof(char)*(chars_read+1);
            buff = realloc(buff, *cap);
        }
        buff[chars_read-1] = (char) character;
    }
    buff[chars_read] = '\0';
    *buff_ptr = buff;
    
}
int dl_strcmp( const char * str_a, const char * str_b ){
    
    int len_a, len_b, i , j, transposition;
    
    len_a = strlen(str_a);
    len_b = strlen(str_b);
    
    int tab[len_b+1][len_a+1];
    tab[0][0]=0;

    for (i = 1; i<=len_b; i++){
        tab[i][0] = tab[i-1][0] +1;
    }
    for (j = 1; j <= len_a; j++){
        tab[0][j] = tab[0][j-1] + 1;
    }
    for (i = 1; i<=len_b; i++){
        for (j = 1; j<=len_a; j++){
            tab[i][j]= min( 
                min(
                    tab[i-1][j] + 1,
                    tab[i][j-1] + 1
                ),
                min(
                    tab[i-2][j-2] + ((str_a[i] == str_b[j-1] && str_a[i-1] == str_b[j] && j >1 && i >1 )? 1: INT_MAX),
                    tab[i-1][j-1] + (str_a[j-1] == str_b[i-1]? 0 : 1)
                )
            );

        }
    }
    return tab[len_b][ len_a];
}

int hamming_strcmp(const char * str_a, const char * str_b, unsigned int len){
    int diff, i;
    diff = 0;

    for (i = 0; i < len; i++){
        if (str_a[i] != str_b[i])
            diff ++;
    }
    return diff;
}

int fuzzy_strcmp(const char * str_a, const char * str_b){
    int diff, len_a, len_b, i, current;
    diff = INT_MAX;
    len_a = strlen(str_a);
    len_b = strlen(str_b);
    
    for (i =0; i<(len_b-len_a); i++){
        current = hamming_strcmp((str_b+i), str_a, len_a);
        diff = min(diff, current);
    }
    return diff;

}
