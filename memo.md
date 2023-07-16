```
typedef struct s_del_quote
{
	char *str;
	// int flag;
	int index;
	int subordinate;

	struct s_del_quote *next;
} t_del_quote;

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

char **make_quote_split_strs(char *str)
{
	int strs_count;
	char **result;
	int i;
	
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
			result[i] = ft_substr(str, 0, ft_strchr(str, ' ') - str);
			str = ft_strchr(str, ' ');
			str++;
		}
		i++;
	}
	return result;
}

t_del_quote **new_quote_split_list(t_del_quote **head, t_del_quote *current)
{
	char **splited_str;
	t_del_quote *new_list;
	t_del_quote *head_cur;
	t_del_quote **new_head;
	int i = 0;

	splited_str = make_quote_split_strs(current->str);
	head_cur = *head;
	while (i < current->index)
	{
		if (i == 0)
		{
			new_list = copy_node(head_cur);
			new_head = &new_list;
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
		if (i == 0 && current->index == 0)
		{
			new_list = new_del_quote_node(splited_str[i], current->index, current->index);
			new_head = &new_list;
		}
		else
		{
			new_list->next = new_del_quote_node(splited_str[i], current->index + i, current->index);
			new_list = new_list->next;
		}
		i++;
	}
	head_cur = head_cur->next;
	while (head_cur)
	{
		new_list->next = new_del_quote_node(head_cur->str, head_cur->index + i, head_cur->subordinate);
		new_list = new_list->next;
		head_cur = head_cur->next;
	}
	destroy_nodes(head);
	for(int i = 0; splited_str[i]; i++)
		free(splited_str[i]);
	free(splited_str);
	return (new_head);
}

void split_quote(t_del_quote **head)
{
	int flag;
	int gen_count;
	t_del_quote *current;
	t_del_quote *new;
	t_del_quote *next_current;  // New variable

	current = *head;
	gen_count = 0;
	while (current)
	{
		next_current = current->next;  // Save the next node of current node before merge
		flag = check_one_word(current->str);
		if (flag == 0) // 한 단어가 아닌 경우
		{
			head = new_quote_split_list(head, current);
		}
		else if (flag == 1) // 한 단어인 경우
		{
			current->subordinate = current->index;
		}
		current = next_current;  // Update current node to the next node saved before
	}
}
```
지금 이 코드는 
`split_quote`함수 실행전,
각 노드는
```
"abc asd"'123 '42seoul
"ABC"def
leeminjea'hihi'
```
이렇게 되어 있을때,
함수 실행 후는 
```
"abc asd"
'123 '
42seoul
"ABC"
def
leeminjea
'hihi'
```
이렇게 되는 게 목표야,

이를 위해,
`make_quote_split_strs`함수는 인자로 `"abc asd"'123 '42seoul` 라면
```
"abc asd"
'123 '
42seoul
```
로 되어있는, 문자열의 배열을 만들고,
`new_quote_split_list` 함수는
앞의 노드를 복사, 새로 만든 문자열 배열을 노드로 만들고, 뒤의 노드를 복사해서
새로운 head를 만들어주는 함수야.

하지만 `new_quote_split_list` 함수를 어떻게 만들어야할 지 모르겠어

너가 나의 코드를 보고, 어떻게 함수를 올바르게 새로 만들어야할 지 알려줄 수 있을까?