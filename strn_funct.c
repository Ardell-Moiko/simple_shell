#include "main.h"

int _mystrlen(const char *s);
char *_mystrcpy(char *dest, const char *src);
char *_mystrcat(char *dest, const char *src);
char *_mystrncat(char *dest, const char *src, size_t n);

/**
 * _mystrlen - Returns the length of a string.
 * @s: A pointer to the characters string.
 *
 * Return: The length of the character string.
 */
int _mystrlen(const char *s)
{
	int len = 0;

	if (!s)
		return (len);
	for (len = 0; s[len]; len++)
		;
	return (len);
}

/**
 * _mystrcpy - Copies the string pointed to by src, including the
 *           terminating null byte, to the buffer pointed by des.
 * @dest: Pointer to the destination of copied string.
 * @src: Pointer to the src of the source string.
 *
 * Return: Pointer to dest.
 */
char *_mystrcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * _mystrcat - Concantenates two strings.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 *
 * Return: Pointer to destination string.
 */
char *_mystrcat(char *dest, const char *src)
{
	char *d_tmp;
	const char *s_tmp;

	d_tmp = dest;
	s_tmp =  src;

	while (*d_tmp != '\0')
		d_tmp++;

	while (*s_tmp != '\0')
		*d_tmp++ = *s_tmp++;
	*d_tmp = '\0';
	return (dest);
}

/**
 * _mystrncat - Concantenates two strings where n number
 *            of bytes are copied from source.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 * @n: n bytes to copy from src.
 *
 * Return: Pointer to destination string.
 */
char *_mystrncat(char *dest, const char *src, size_t n)
{
	size_t d_len = _mystrlen(dest);
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[d_len + i] = src[i];
	dest[d_len + i] = '\0';

	return (dest);
}

