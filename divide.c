#include "main.h"

int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **_mystrtok(char *line, char *delim);

/**
 * token_len - Locates the delimiter index marking the end
 *             of the first token contained within a string.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The delimiter index marking the end of
 *         the intitial token pointed to be str.
 */
int token_len(char *str, char *delim)
{
	int i = 0, len = 0;

	while (*(str + i) && *(str + i) != *delim)
	{
		len++;
		i++;
	}

	return (len);
}

/**
 * count_tokens - Counts the number of delimited
 *                words contained within a string.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The number of words contained within str.
 */
int count_tokens(char *str, char *delim)
{
	int i, tkn = 0, len = 0;

	for (i = 0; *(str + i); i++)
		len++;

	for (i = 0; i < len; i++)
	{
		if (*(str + i) != *delim)
		{
			tkn++;
			i += token_len(str + i, delim);
		}
	}

	return (tkn);
}

/**
 * _mystrtok - Tokenizes a string.
 * @line: The string.
 * @delim: The delimiter character to tokenize the string by.
 *
 * Return: A pointer to an array containing the tokenized words.
 */
char **_mystrtok(char *line, char *delim)
{
	char **ptr;
	int i = 0, tkns, t, ltrs, l;

	tkns = count_tokens(line, delim);
	if (tkns == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tkns + 2));
	if (!ptr)
		return (NULL);

	for (t = 0; t < tkns; t++)
	{
		while (line[i] == *delim)
			i++;

		ltrs = token_len(line + i, delim);

		ptr[t] = malloc(sizeof(char) * (ltrs + 1));
		if (!ptr[t])
		{
			for (i -= 1; i >= 0; i--)
				free(ptr[i]);
			free(ptr);
			return (NULL);
		}

		for (l = 0; l < ltrs; l++)
		{
			ptr[t][l] = line[i];
			i++;
		}

		ptr[t][l] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
}

