/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:14:08 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
//#include "TDD/test.h"
//char *strrev(char *str)
//{
//    size_t str_len;
//    char *left;
//    char *right;
//
//    str_len = ft_strlen(str);
//    left = str;
//    left = str + str_len - 1;
//    while(left < right)
//    {
//        char temp = *left;
//        *right = *left;
//        left++;
//        right++;
//    }
//}
//
//char *strrchr(const char *s, int c)
//{
//
//    //need to reverse the string in this one
//    char *rev = strrev(s);
//    if(!c)
//        return (char *)s;
//    while(*rev)
//    {
//        if(*rev == c)
//            return rev;
//        rev++;
//    }
//    return NULL;
//
//}
/**
 * @param c The character to search for in the string `s`.
 * @return A pointer to the last occurrence of `c` in the string `s`, 
 *         or NULL if `c` is not found.
 * 
 * @note The function performs a backward search, starting 
 * from the end of the string and moving toward the beginning.
 *       If the character `c` is found, the function returns 
 * a pointer to its last occurrence. If `c` is not found, 
 *       it returns NULL. The search is case-sensitive.
 */
char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	if (c == '\0')
		return ((char *)s + i);
	while (i--)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
	}
	return (NULL);
}

//static char *get_file_extension(const char *file_path)
//{
//    char *last_dot = ft_strrchr(file_path, '.');
//
//    if (!last_dot || *(last_dot + 1) == '\0')
//        return NULL;
//
//    // Return the file extension (including the dot)
//    return last_dot;
//}

//int main(void)
//{
//    char *file_path1 = "/home/user/.documents/report.txt";
//    char *file_path2 = "/home/user/.photos/vacation.jpg";
//    char *file_path3 = "/home/user/notes/readme";
//
//    char *ext;
//
//    ext = get_file_extension(file_path1);
//   	ft_printf("File Path: %s\n", file_path1);
//   	ft_printf("File Extension: %s\n", ext ? ext : "(no extension)\n");
//
//    ext = get_file_extension(file_path2);
//   	ft_printf("\nFile Path: %s\n", file_path2);
//   	ft_printf("File Extension: %s\n", ext ? ext : "(no extension)\n");
//
//    ext = get_file_extension(file_path3);
//   	ft_printf("\nFile Path: %s\n", file_path3);
//   	ft_printf("File Extension: %s\n", ext ? ext : "(no extension)\n");
//
//    return 0;
//}