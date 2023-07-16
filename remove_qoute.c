/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_qoute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:33:56 by mi                #+#    #+#             */
/*   Updated: 2023/07/16 17:31:32 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parse.h"

//!
void copy_data_to_node(t_del_quote **head, char **strs)
{
	int i;
	t_del_quote *new;
	t_del_quote *current;

	i = 0;
	current = *head;
	while (strs[i])
	{
		new = new_del_quote_node(strs[i], i, -1);
		if (i == 0){
			*head = new;
			current = new;
		}
		else
		{
			current->next = new;
			current = new;
		}
		i++;
	}
}

//!
int check_one_word_push_to_endpoint(char *str, char c)
{
	str++;
	while (*str && *str != c)
		str++;
	if (*str == c)
		str++;
	else
		return (-1);
	if (*str == '\0')
		return 1;
	return (0);
}

//!
int check_one_word(char *str)
{
	if (*str == '\'')
		return (check_one_word_push_to_endpoint(str, '\''));
	else if (*str == '\"')
		return (check_one_word_push_to_endpoint(str, '\"'));
	else
	{
		while (*str)
		{
			if (*str == '\'' || *str == '\"')
				return (0);
			str++;
		}
		return (1);
	}
}

//!
int len_one_word(char *str)
{
	int len;

	len = 0;
	if (str[len] == '\'')
	{
		len++;
		while (str[len] && str[len] != '\'')
			len++;
		if (str[len] == '\'')
			len++;
	}
	else if (str[len] == '\"')
	{
		len++;
		while (str[len] && str[len] != '\"')
			len++;
		if (str[len] == '\"')
			len++;
	}
	else
	{
		while (str[len] && (str[len] != '\'' && str[len] != '\"'))
			len++;
	}
	return (len);

}

//! 완료
t_del_quote *new_del_quote_node(char *str, int index, int subordinate)
{
	t_del_quote *new;

	new = (t_del_quote *)malloc(sizeof(t_del_quote));
	new->str = strdup(str);
	new->index = index;
	new->subordinate = subordinate;
	new->next = NULL;
	return (new);
}

/*
//!
t_del_quote *new_splited_word(char *str, int parent_index, int subordinate)
{
	char *word;
	char *remainder;
	int word_len;
	t_del_quote *new;

	word_len = len_one_word(str);
	word = ft_substr(str, 0, word_len);
	new = new_del_quote_node(word, parent_index, subordinate);
	if (strlen(str) - word_len > 0)
		remainder = ft_substr(str, word_len, strlen(str) - word_len);
	else
		remainder = NULL;
	free(str);
	str = NULL;
	if (remainder)
		new->next = new_splited_word(remainder, parent_index + 1, subordinate);
	else
		new->next = NULL;
	return (new);
}
*/
t_del_quote *new_splited_word(char *str, int parent_index, int subordinate)
{
	char *word;
	char *remainder;
	int word_len;
	t_del_quote *new;
	t_del_quote *current;

	word_len = len_one_word(str);
	word = ft_substr(str, 0, word_len);
	new = new_del_quote_node(word, parent_index, subordinate);
	current = new;

	while (str != NULL && strlen(str) - word_len > 0)
	{
		remainder = ft_substr(str, word_len, strlen(str) - word_len);
		free(str);
		str = NULL;

		word_len = len_one_word(remainder);
		word = ft_substr(remainder, 0, word_len);
		current->next = new_del_quote_node(word, parent_index + 1, subordinate);
		current = current->next;
	}
	return (new);
}

//!
int get_node_count(t_del_quote *head)
{
	int count;
	t_del_quote *current;

	count = 0;
	current = head;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

//!
t_del_quote *get_tail(t_del_quote *head)
{
	t_del_quote *current;

	current = head;
	while (current->next)
		current = current->next;
	return (current);
}

//! 확인 완료
t_del_quote *get_node_by_index(t_del_quote *head, int index)
{
	t_del_quote *current;

	current = head;
	while (current)
	{
		if (current->index == index)
			return (current);
		current = current->next;
	}
	return (NULL);
}

//! 확인 완료
void free_node(t_del_quote *node)
{
	if (*(node->str) != '\0')
		free(node->str);
	free(node);
}

/*
//!
void head_merge(t_del_quote **head, t_del_quote **new)
{
	t_del_quote *next;
	t_del_quote *new_tail;

	next = (*head)->next;
	free_node(*head);
	*head = *new;
	new_tail = get_tail(*new);
	new_tail->next = next;
}

//!
void mid_merge(t_del_quote **head, t_del_quote **new)
{
	t_del_quote *prev;
	t_del_quote *next;
	t_del_quote *new_tail;
	t_del_quote *origin;

	origin = get_node_by_index(*head, (*new)->index);
	prev = get_node_by_index(*head, (*new)->index - 1);
	next = get_node_by_index(*head, (*new)->index + 1);
	new_tail = get_tail(*new);
	prev->next = *new;
	new_tail->next = next;
	free_node(origin);
}

//!
void tail_merge(t_del_quote **head, t_del_quote **new)
{
	t_del_quote *prev;
	t_del_quote *origin;
	
	origin = get_node_by_index(*head, (*new)->index);
	prev = get_node_by_index(*head, (*new)->index - 1);
	prev->next = *new;
	free_node(origin);
}


//!
t_del_quote **merge_node(t_del_quote **head, t_del_quote **new, int gen_count)
{
	t_del_quote *current;
	t_del_quote *new_current;
	
	current = *head;
	new_current = *new;
	if (new_current->index == 0)
		head_merge(head, new);
	else if (get_node_count(*head) - 1 == (*new)->index) 
		tail_merge(head, new);
	else
		mid_merge(head, new);
	return (head);
}
*/
t_del_quote *head_merge(t_del_quote **head, t_del_quote **new)
{
	t_del_quote *next;
	t_del_quote *new_tail;

	next = (*head)->next;
	free_node(*head);
	*head = *new;
	new_tail = get_tail(*new);
	new_tail->next = next;
	return (*new); // Modified line
}

t_del_quote *mid_merge(t_del_quote **head, t_del_quote **new)
{
	t_del_quote *prev;
	t_del_quote *next;
	t_del_quote *new_tail;
	t_del_quote *origin;

	origin = get_node_by_index(*head, (*new)->index);
	prev = get_node_by_index(*head, (*new)->index - 1);
	next = get_node_by_index(*head, (*new)->index + 1);
	new_tail = get_tail(*new);
	prev->next = *new;
	new_tail->next = next;
	free_node(origin);
	return (*new); // Modified line
}

t_del_quote *tail_merge(t_del_quote **head, t_del_quote **new)
{
	t_del_quote *prev;
	t_del_quote *origin;

	origin = get_node_by_index(*head, (*new)->index);
	prev = get_node_by_index(*head, (*new)->index - 1);
	prev->next = *new;
	free_node(origin);
	return (*new); // Modified line
}

t_del_quote *merge_node(t_del_quote **head, t_del_quote **new, int gen_count)
{
	t_del_quote *new_current;

	new_current = *new;
	if (new_current->index == 0)
		return head_merge(head, new); // Modified line
	else if (get_node_count(*head) - 1 == (*new)->index)
		return tail_merge(head, new); // Modified line
	else
		return mid_merge(head, new); // Modified line
}
//!
void rearrange_index(t_del_quote **head)
{
	t_del_quote *current;
	int index;

	current = *head;
	index = 0;
	while (current)
	{
		current->index = index;
		index++;
		current = current->next;
	}
}

/*
//!
void split_quote(t_del_quote **head)
{
	int flag;
	int gen_count;
	t_del_quote *current;
	t_del_quote *new;

	current = *head;
	gen_count = 0;
	while (current)
	{
		flag = check_one_word(current->str);
		if (flag == 0) // 한 단어가 아닌 경우
		{
			new = new_splited_word(current->str, current->index, current->index);
			gen_count = get_node_count(new);			//! node는 따로 빼기
			head = merge_node(head, &new, gen_count);	//! node는 따로 빼기
			rearrange_index(head);
			current = *head;
			while (current->index != new->index)
				current = current->next;
			while (gen_count--)
				current = current->next;
		}
		else if (flag == 1) // 한 단어인 경우
		{
			current->subordinate = current->index;
			current = current->next;
		}
	}
}
*/

int quote_split_strs_count(char *str)
{
	int count;
	int len;

	count = 0;
	len = 0;
	while(str[len])
	{	
		if (str[len] == '\'')
		{
			len++;
			while (str[len] && str[len] != '\'')
				len++;
			if (str[len] == '\'')
				len++;
		}
		else if (str[len] == '\"')
		{
			len++;
			while (str[len] && str[len] != '\"')
				len++;
			if (str[len] == '\"')
				len++;
		}
		else
		{
			while (str[len] && (str[len] != '\'' && str[len] != '\"'))
				len++;
		}
		count++;
	}
	return (count);
}

char **make_quote_split_strs(char *str)
{
	int strs_count;
	char **result;
	int i;
	int word_len;
	
	strs_count = quote_split_strs_count(str);
	result = (char **)malloc(sizeof(char *) * (strs_count + 1));
	i = 0;
	result[strs_count] = NULL;
	while (i < strs_count)
	{
		if (*str == '\'')
		{
			result[i] = ft_substr(str, 0, ft_strchr(str + 1, '\'') - str + 1);
			str = ft_strchr(str + 1, '\'') + 1;
		}
		else if (*str == '\"')
		{
			result[i] = ft_substr(str, 0, ft_strchr(str + 1, '\"') - str + 1);
			str = ft_strchr(str + 1, '\"') + 1;
		}
		else
		{
			word_len = len_one_word(str);
			result[i] = ft_substr(str, 0, word_len);
			str += word_len;
		}
		i++;
	}
	return result;
}

t_del_quote *copy_node(t_del_quote *node)
{
	t_del_quote *new;

	new = (t_del_quote *)malloc(sizeof(t_del_quote));
	new->str = strdup(node->str);
	new->index = node->index;
	new->subordinate = node->subordinate;
	new->next = NULL;
	return (new);
}

// t_del_quote **new_quote_split_list(t_del_quote **head, t_del_quote *current)
// {
// 	char **splited_str;
// 	t_del_quote *new_list;
// 	t_del_quote *head_cur;
// 	t_del_quote **new_head;
// 	int i = 0;

// 	splited_str = make_quote_split_strs(current->str);
// 	head_cur = *head;
// 	while (i < current->index)
// 	{
// 		if (i == 0)
// 		{
// 			new_list = copy_node(head_cur);
// 			new_head = &new_list;
// 		}
// 		else
// 		{
// 			new_list->next = copy_node(head_cur);
// 			new_list = new_list->next;
// 		}
// 		head_cur = head_cur->next;
// 		i++;
// 	}
// 	i = 0;
// 	while (splited_str[i])
// 	{
// 		if (i == 0 && current->index == 0)
// 		{
// 			new_list = new_del_quote_node(splited_str[i], current->index, current->index);
// 			new_head = &new_list;
// 		}
// 		else
// 		{
// 			new_list->next = new_del_quote_node(splited_str[i], current->index + i, current->index);
// 			new_list = new_list->next;
// 		}
// 		i++;
// 	}
// 	head_cur = head_cur->next;
// 	while (head_cur)
// 	{
// 		new_list->next = new_del_quote_node(head_cur->str, head_cur->index + i, head_cur->subordinate);
// 		new_list = new_list->next;
// 		head_cur = head_cur->next;
// 	}
// 	destroy_nodes(head);
// 	for(int i = 0; splited_str[i]; i++)
// 		free(splited_str[i]);
// 	free(splited_str);
// 	return (new_head);
// }

//? 이전코드
t_del_quote *new_quote_split_list(t_del_quote **head, t_del_quote *current)
{
	char **splited_str;
	t_del_quote *new_list = NULL;
	t_del_quote *new_start = NULL;
	t_del_quote *head_cur;
	int i = 0;

	splited_str = make_quote_split_strs(current->str);
	head_cur = *head;

	while (i < current->index)
	{
		if (i == 0)
		{
			new_list = copy_node(head_cur);
			new_start = new_list;
		}
		else
		{
			new_list->next = copy_node(head_cur);
			new_list = new_list->next;
		}
		head_cur = head_cur->next;
		i++;
	}

	i = 0;
	while (splited_str[i])
	{
		if (new_list == NULL)
		{
			new_list = new_del_quote_node(splited_str[i], current->index, current->index);
			new_start = new_list;
		}
		else
		{
			new_list->next = new_del_quote_node(splited_str[i], current->index + i, current->index);
			new_list = new_list->next;
		}
		i++;
	}

	head_cur = current->next;
	while (head_cur)
	{
		new_list->next = copy_node(head_cur);
		new_list = new_list->next;
		new_list->index = -1;
		head_cur = head_cur->next;
	}

	destroy_nodes(head);

	// free splited_str
	for (i = 0; splited_str[i]; i++)
	{
		free(splited_str[i]);
	}
	free(splited_str);

	return new_start;
}
//? 이전 코드

// This function handles copying the nodes before the current node.
// t_del_quote *copy_before_current(t_del_quote **head, t_del_quote *current, t_del_quote **new_start)
// {
// 	t_del_quote *new_list = NULL;
// 	t_del_quote *head_cur = *head;
// 	int i = 0;

// 	while (i < current->index)
// 	{
// 		if (i == 0)
// 		{
// 			new_list = copy_node(head_cur);
// 			*new_start = new_list;
// 		}
// 		else
// 		{
// 			new_list->next = copy_node(head_cur);
// 			new_list = new_list->next;
// 		}
// 		head_cur = head_cur->next;
// 		i++;
// 	}

// 	return new_list;
// }

// // This function handles creating new nodes from the split strings.
// t_del_quote *create_new_nodes(char **splited_str, t_del_quote *current, t_del_quote *new_list)
// {
// 	int i = 0;

// 	while (splited_str[i])
// 	{
// 		if (new_list == NULL)
// 		{
// 			new_list = new_del_quote_node(splited_str[i], current->index, current->index);
// 		}
// 		else
// 		{
// 			new_list->next = new_del_quote_node(splited_str[i], current->index + i, current->index);
// 			new_list = new_list->next;
// 		}
// 		i++;
// 	}

// 	return new_list;
// }

// // This function handles copying the nodes after the current node.
// t_del_quote *copy_after_current(t_del_quote *current, t_del_quote *new_list)
// {
// 	t_del_quote *head_cur = current->next;

// 	while (head_cur)
// 	{
// 		new_list->next = copy_node(head_cur);
// 		new_list = new_list->next;
// 		new_list->index = -1;
// 		head_cur = head_cur->next;
// 	}

// 	return new_list;
// }

// // This function handles freeing the splited_str array.
// void free_splited_str(char **splited_str)
// {
// 	for (int i = 0; splited_str[i]; i++)
// 	{
// 		free(splited_str[i]);
// 	}
// 	free(splited_str);
// }

// t_del_quote *new_quote_split_list(t_del_quote **head, t_del_quote *current)
// {
// 	char **splited_str;
// 	t_del_quote *new_start = NULL;

// 	splited_str = make_quote_split_strs(current->str);

// 	t_del_quote *new_list = copy_before_current(head, current, &new_start);
// 	new_list = create_new_nodes(splited_str, current, new_list);
// 	new_list = copy_after_current(current, new_list);

// 	destroy_nodes(head);
// 	free_splited_str(splited_str);

// 	return new_start;
// }

void split_quote(t_del_quote **head)
{
	int flag;
	t_del_quote *current;
	t_del_quote *new;

	current = *head;
	while (current)
	{
		flag = check_one_word(current->str);
		if (flag == 0) // 한 단어가 아닌 경우
		{
			new = new_quote_split_list(head, current);
			*head = new;
			current = *head;
			while (current->next && current->next->index != -1)
				current = current->next;
			rearrange_index(head);
		}
		else if (flag == 1) // 한 단어인 경우
		{
			current->subordinate = current->index;
		}
		current = current->next;  // Update current node to the next node saved before
	}
}

//!
void dequote(t_del_quote **head)
{
	t_del_quote *current;
	char *str;
	char *new_str;
	int len;

	current = *head;
	while (current)
	{
		if (current->str[0] == '\'' || current->str[0] == '\"')
		{
			str = current->str;
			len = strlen(str);
			new_str = ft_substr(str, 1, len - 2);
			free(str);
			str = NULL;
			current->str = new_str;
		}
		current = current->next;
	}
}

//!
int get_strs_count(t_del_quote *head)
{
	int count;
	t_del_quote *current;

	count = 0;
	current = head;
	while (current)
	{
		if (current->index == current->subordinate)
			count++;
		current = current->next;
	}
	return (count);
}

//!
char **dequoted_merge(t_del_quote **head)
{
	char **result;
	t_del_quote *current;
	int strs_count;
	char *new_str;

	strs_count = get_strs_count(*head);
	result = (char **)malloc(sizeof(char *) * (strs_count + 1));
	current = *head;
	while (current)
	{
		if (current->index != -1)
		{
			result[current->index] = current->str;
		}
		else
		{
			new_str = ft_strjoin(result[current->subordinate], current->str);
			// free(result[current->subordinate]);
			result[current->subordinate] = new_str;
		}
		current = current->next;
	}
	result[strs_count] = NULL;
	return (result);
}

//!
void modify_index(t_del_quote **head)
{
	t_del_quote *current;
	int index;
	int new_subordinate;

	current = *head;
	index = 0;
	while (current)
	{
		if(current->index == current->subordinate)
		{
			new_subordinate = index;
			current->subordinate = index;
			current->index = index++;
		}
		else
		{
			current->subordinate = new_subordinate;
			current->index = -1;
		}
		current = current->next;
	}
}

//! 확인 완료
void destroy_nodes(t_del_quote **head)
{
	t_del_quote *current;
	t_del_quote *next;

	current = *head;
	while (current)
	{
		next = current->next;
		free_node(current);
		current = next;
	}
}

//!
char **remove_quote(char **strs)
{
	t_del_quote *head;
	char **result;

	copy_data_to_node(&head, strs);
	split_quote(&head);
	dequote(&head);
	modify_index(&head);
	result = dequoted_merge(&head);
	destroy_nodes(&head);
	for (int i = 0; strs[i]; i++)
		free(strs[i]);
	free(strs);
	return (result);
}