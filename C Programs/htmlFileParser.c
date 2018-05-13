#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_sub_strings(char text_line[], const char sub_string[]);
char **get_sub_strings(char text_line[], const char sub_start[], 
const char sub_end);

int main()
{
	char *buff=NULL, key; int i=0;
	char **links = NULL;
	int link_count = 0;
	const char START[] = "<a";
	const char END = '>';

	char sup[2] = {'\0'}; 
	int sizer = 2;

    buff = (char*)malloc(sizeof(char));
	*buff='\0';

    while(key = getc(stdin))
    {
		if(key == '\n') {
			buff[i] = '\0';
			link_count = count_sub_strings(buff, START);
			if (link_count > 0) {
				links = get_sub_strings(buff, START, END);
				for (int j = 0; j < link_count; ++j) {
					printf("%s\n", links[j]);
					free(links[j]);
				}
				free(links);
			}

			i=0;
			*buff='\0';
			continue;
		}

    	buff = realloc(buff,sizer * sizeof(char));
    	sup[0] = key;
    	strcat(buff,sup);
    	sizer++;
    	i++;
    }

	free(buff);

	return 0;
}

int count_sub_strings(char text_line[], const char sub_string[])
{
	char *cursor = NULL;
	int sub_count = 0;
	int sub_length = strlen(sub_string);

	cursor = strstr(text_line, sub_string);
	while (cursor != NULL) {
		sub_count++;
		cursor = cursor + sub_length;
		cursor = strstr(cursor, sub_string);
	}

	return sub_count;
}

char **get_sub_strings(char text_line[], const char sub_start[], const char sub_end) 
{
	int sub_index = 0;
	char *cursor = NULL; 
	char *end = NULL;
	char **sub_strings = NULL;
	int sub_count = count_sub_strings(text_line, sub_start);

	if (sub_count > 0) {
		sub_strings = malloc(sizeof(char*) * (sub_count) );
		cursor = strstr(text_line, sub_start);
		while (cursor != NULL) {
			end = strchr(cursor, sub_end) + 1;
			int sub_length = (end - cursor);
			sub_strings[sub_index] = (char *) malloc(sub_length + 1);
			for (int i = 0; i < sub_length; ++i) {
				sub_strings[sub_index][i] = cursor[i];
				if (sub_strings[sub_index][i] == sub_end) {
					sub_strings[sub_index][i+1] = '\0';
				}
			} 
			cursor = strstr(end + 1, sub_start);
			sub_index++;
		}
	} 

	return sub_strings;
}
