#include "main.h"

void line_handler(char **line, ssize_t read);
ssize_t get_new_len(char *line);
void logical_ops(char *line, ssize_t *new_len);

/**
 * line_handler - Partitions a line read from standard input as needed.
 * @line: A pointer to a line read from standard input.
 * @read: The length of line.
 *
 * Description: Spaces are inserted to separate ";", "||", and "&&".
 *              Replaces "#" with '\0'.
 */
void line_handler(char **line, ssize_t read)
{
	char *o_line, *n_line;
	char prev, curr, nxt;
	size_t i, j;
	ssize_t new_len;

	new_len = get_new_len(*line);
	if (new_len == read - 1)
		return;
	n_line = malloc(new_len + 1);
	if (!n_line)
		return;
	j = 0;
	o_line = *line;
	for (i = 0; o_line[i]; i++)
	{
		curr = o_line[i];
		nxt = o_line[i + 1];
		if (i != 0)
		{
			prev = o_line[i - 1];
			if (curr == ';')
			{
				if (nxt == ';' && prev != ' ' && prev != ';')
				{
					n_line[j++] = ' ';
					n_line[j++] = ';';
					continue;
				}
				else if (prev == ';' && nxt != ' ')
				{
					n_line[j++] = ';';
					n_line[j++] = ' ';
					continue;
				}
				if (prev != ' ')
					n_line[j++] = ' ';
				n_line[j++] = ';';
				if (nxt != ' ')
					n_line[j++] = ' ';
				continue;
			}
			else if (curr == '&')
			{
				if (nxt == '&' && prev != ' ')
					n_line[j++] = ' ';
				else if (prev == '&' && nxt != ' ')
				{
					n_line[j++] = '&';
					n_line[j++] = ' ';
					continue;
				}
			}
			else if (curr == '|')
			{
				if (nxt == '|' && prev != ' ')
					n_line[j++]  = ' ';
				else if (prev == '|' && nxt != ' ')
				{
					n_line[j++] = '|';
					n_line[j++] = ' ';
					continue;
				}
			}
		}
		else if (curr == ';')
		{
			if (i != 0 && o_line[i - 1] != ' ')
				n_line[j++] = ' ';
			n_line[j++] = ';';
			if (nxt != ' ' && nxt != ';')
				n_line[j++] = ' ';
			continue;
		}
		n_line[j++] = o_line[i];
	}
	n_line[j] = '\0';

	free(*line);
	*line = n_line;
}

/**
 * get_new_len - Gets the new length of a line partitioned
 *               by ";", "||", "&&&", or "#".
 * @line: The line to check.
 *
 * Return: The new length of the line.
 *
 * Description: Cuts short lines containing '#' comments with '\0'.
 */

ssize_t get_new_len(char *line)
{
	size_t i;
	ssize_t n_len = 0;
	char curr, nxt;

	for (i = 0; line[i]; i++)
	{
		curr = line[i];
		nxt = line[i + 1];
		if (curr == '#')
		{
			if (i == 0 || line[i - 1] == ' ')
			{
				line[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (curr == ';')
			{
				if (nxt == ';' && line[i - 1] != ' ' && line[i - 1] != ';')
				{
					n_len += 2;
					continue;
				}
				else if (line[i - 1] == ';' && nxt != ' ')
				{
					n_len += 2;
					continue;
				}
				if (line[i - 1] != ' ')
					n_len++;
				if (nxt != ' ')
					n_len++;
			}
			else
				logical_ops(&line[i], &n_len);
		}
		else if (curr == ';')
		{
			if (i != 0 && line[i - 1] != ' ')
				n_len++;
			if (nxt != ' ' && nxt != ';')
				n_len++;
		}
		n_len++;
	}
	return (n_len);
}
/**
 * logical_ops - Checks a line for logical operators "||" or "&&".
 * @line: A pointer to the character to check in the line.
 * @new_len: Pointer to new_len in get_new_len function.
 */
void logical_ops(char *line, ssize_t *new_len)
{
	char prev, curr, nxt;

	prev = *(line - 1);
	curr = *line;
	nxt = *(line + 1);

	if (curr == '&')
	{
		if (nxt == '&' && prev != ' ')
			(*new_len)++;
		else if (prev == '&' && nxt != ' ')
			(*new_len)++;
	}
	else if (curr == '|')
	{
		if (nxt == '|' && prev != ' ')
			(*new_len)++;
		else if (prev == '|' && nxt != ' ')
			(*new_len)++;
	}
}
