/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:30:33 by mi                #+#    #+#             */
/*   Updated: 2023/07/16 16:57:07 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int count_strs(char **strs)
{
	int i;

	i = 0;
	while (strs[i] != NULL)
		i++;
	return (i);
}

void f(){
	system("leaks parser");
}

int main()
{
	atexit(f);
	// char *str = "abc $'123' def";
	char *str = "\"abc asd \"\'123 \'42seoul \"ABC\"def leeminjea\'hihi\' ";
 

	// printf("hi\n");

	char **result = split_respect_quote(str, ' ');
	result = remove_quote(result);
	for (int i = 0; result[i] != NULL; i++){
		printf("%s\n", result[i]);
		free(result[i]);
	}
	free(result);

	return 0;
}