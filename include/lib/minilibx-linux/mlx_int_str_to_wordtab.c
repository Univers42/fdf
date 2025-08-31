/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_str_to_wordtab.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:26:45 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/31 15:27:20 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

/**
 * @brief Finds the first occurrence of a substring within a string.
 *
 * Searches for the substring 'find' in the string 'str' up to 'len' characters.
 * Returns the position of the first occurrence, or -1 if not found.
 *
 * @param str The string to search in.
 * @param find The substring to search for.
 * @param len The maximum number of characters to search.
 * @return The position of the first occurrence, or -1 if not found.
 */
int	mlx_int_str_str(char *str,char *find,int len)
{
  int	len_f;
  int	pos;
  char	*s;
  char	*f;

  len_f = strlen(find);
  if (len_f>len)
    return (-1);
  pos = 0;
  while (*(str+len_f-1))
    {
      s = str;
      f = find;
      while (*(f++) == *(s++))
        if (!*f)
          return (pos);
      str ++;
      pos ++;
    }
  return (-1);
}

/**
 * @brief Finds the first occurrence of a substring outside quotes.
 *
 * Searches for the substring 'find' in the string 'str' up to 'len' characters,
 * but ignores matches that occur inside double quotes. Returns the position of
 * the first occurrence outside quotes, or -1 if not found.
 *
 * @param str The string to search in.
 * @param find The substring to search for.
 * @param len The maximum number of characters to search.
 * @return The position of the first occurrence outside quotes, or -1 if not found.
 */
int	mlx_int_str_str_cote(char *str,char *find,int len)
{
  int	len_f;
  int	pos;
  char	*s;
  char	*f;
  int	cote;

  len_f = strlen(find);
  if (len_f>len)
    return (-1);
  cote = 0;
  pos = 0;
  while (*(str+len_f-1))
    {
      if (*str=='"')
	cote = 1-cote;
      if (!cote)
	{
	  s = str;
	  f = find;
	  while (*(f++) == *(s++))
	    if (!*f)
	      return (pos);
	}
      str ++;
      pos ++;
    }
  return (-1);
}

/**
 * @brief Splits a string into words separated by spaces or tabs.
 *
 * This function tokenizes the input string into an array of words, using spaces
 * and tabs as delimiters. It modifies the input string by inserting null terminators
 * and returns an array of pointers to the beginning of each word.
 *
 * @param str The string to split. This string will be modified.
 * @return A NULL-terminated array of word pointers, or NULL on allocation failure.
 */
char	**mlx_int_str_to_wordtab(char *str)
{
  char	**tab;
  int	pos;
  int	nb_word;
  int	len;

  len = strlen(str);
  nb_word = 0;
  pos = 0;
  while (pos<len)
  {
    while (*(str+pos)==' ' || *(str+pos)=='\t')
      pos ++;
    if (*(str+pos))
      nb_word ++;
    while (*(str+pos) && *(str+pos)!=' ' && *(str+pos)!='\t')
      pos ++;
  }
  if (!(tab = malloc((1+nb_word)*sizeof(*tab))))
    return ((char **)0);
  nb_word = 0;
  pos = 0;
  while (pos<len)
    {
      while (*(str+pos)==' ' || *(str+pos)=='\t')
	{
	  *(str+pos) = 0;
	  pos ++;
	}
      if (*(str+pos))
	{
	  tab[nb_word] = str+pos;
	  nb_word ++;
	}
      while (*(str+pos) && *(str+pos)!=' ' && *(str+pos)!='\t')
	pos ++;
    }
  tab[nb_word] = 0;
  return (tab);
}
