#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_del_quote
{
	char *str;
	// int flag;
	int index;
	int subordinate;

	struct s_del_quote *next;
} t_del_quote;


char *push_str_to_endpoint(char *str, char endpoint);
char *check_quote_set_flag(char *str, int *flag);
int get_count_respect_quote(char *str, char c);
int len_respect_quote(char *str, char c);
char **alloc_split_dismiss_quote(char **result, char *str, char c, int count);
char **split_respect_quote(char *str, char c);


/*
void merge_quoted_tokens(char **strs, int num_strs);
int double_quoter_process(char **strs, int start, int num_strs);
int single_quoter_process(char **strs, int start, int num_strs);
void extra_strs_set_null(char **strs, int new, int old);
int rearange_strs(char **strs, int start, int num_strs, int merge_count);
char *merge_string(char **strs, int start, int merge_len, int merge_count);
int end_of_quoter_check(char **str, int *merge_str_len, int i, char quoter);
*/

void copy_data_to_node(t_del_quote **head, char **strs);
int check_one_word_push_to_endpoint(char *str, char c);
int check_one_word(char *str);
int len_one_word(char *str);
t_del_quote *new_splited_word(char *str, int parent_index, int subordinate);
t_del_quote *new_del_quote_node(char *str, int index, int subordinate);
void split_quote(t_del_quote **head);
char **remove_quote(char **strs);
void destroy_nodes(t_del_quote **head);

char *ft_substr(char const *s, unsigned int start, size_t len);
char **ft_split(char const *s, char c);
char *ft_strchr(const char *str, int c);
int ft_count_char(char *str, char c);
void *ft_memmove(void *dst, const void *src, size_t len);
char *ft_strjoin(char const *s1, char const *s2);


#endif