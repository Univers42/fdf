/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:12:12 by dlesieur          #+#    #+#             */
/*   Updated: 2025/08/08 19:31:30 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stddef.h"
#include <stdlib.h>
#include "ft_stdlib.h"
#include "ft_memory.h"

// Calcular dinámicamente SIZE_MAX sin macros ni bucles for
static size_t	size_max(void)
{
	size_t	size_max;
	size_t	bit_count;
	size_t	i;

	size_max = 0;
	bit_count = sizeof(size_t) * 8;
	i = 0;
	while (i < bit_count)
	{
		size_max |= (size_t)1 << i;
		i++;
	}
	return (size_max);
}

/**
 * Allocates memory for an array of `nmemb` elements, each of `size` bytes,
 * and initializes all bytes in the allocated memory to zero.
 * 
 * @param nmemb Number of elements to allocate.
 * @param size Size of each element in bytes.
 * @return A pointer to the allocated memory, or NULL if the allocation fails.
 */
void	*ft_calloc(t_size nmemb, t_size size)
{
	t_size	total;
	void	*buf;

	if (nmemb && size > size_max() / nmemb)
		return (NULL);
	total = nmemb * size;
	buf = malloc(total);
	if (!buf)
		return (NULL);
	ft_bzero(buf, total);
	return (buf);
}
/**
 * Snenario : Dynamic Memory allocation for a Classroom seating Arrangement
 * The classroom has a variable seating arrangement.
 * Variable rows, and each row has a different number of seats.
 * We need to dynamically allocate memory to store the seating
 * arrangemment and ensure that all seats are initialized to a default 
 * value,, say, (0) indicating that a set is unoccupied.
 */

//int main(void)
//{
//    int rows, seatsPerRow;
//    int **seating;
//    char input[4]; // Buffer to hold input for "yes" or "no"
//    int row, seat;
//    
//   	ft_printf("Enter the number of rows in the classroom: ");
//    scanf("%d", &rows);
//   	ft_printf("Enter the number of seats per row: ");
//    scanf("%d", &seatsPerRow);
//
//    // Allocate memory for seating arrangement
//    seating = (int **)calloc(rows, sizeof(int *));
//    if (seating == NULL) {
//        return 1;  // Memory allocation failure
//    }
//    
//    for (int i = 0; i < rows; i++) {
//        seating[i] = (int *)calloc(seatsPerRow, sizeof(int));
//        if (seating[i] == NULL) {
//            return 2;  // Memory allocation failure for a row
//        }
//    }
//
//   	ft_printf("The doors are opened, people come." 
//		"You have to place people, "
//			"holding their coordinates in your database...\n");
//
//    while (1) {
//       	ft_printf("Has a new person entered the room (yes/no)? ");
//        scanf("%s", input);
//
//        if (ft_strncmp(input, "yes", 3) == 0) {
//           	ft_printf("Where are they placed in your coordinates "
//			"(e.g., [1 2] for row 1, seat 2): ");
//            scanf("%d %d", &row, &seat);
//
//            // Check if the row and seat are valid
//            if (row >= 1 && row <= rows && seat >= 1 && seat <= seatsPerRow) {
//                // Mark the seat as occupied (1 for occupied)
//                seating[row - 1][seat - 1] = 1;
//               	ft_printf("Seat [%d, %d] is now occupied.\n", row, seat);
//            } else {
//               	ft_printf("Invalid seat coordinates. Please try again.\n");
//            }
//			continue;
//        }
//		    break;
//    }
//
//    // Print the classroom seating arrangement
//   	ft_printf("\nClassroom Seating Arrangement:\n");
//    for (int i = 0; i < rows; i++) {
//        for (int j = 0; j < seatsPerRow; j++) {
//           	ft_printf("%d ", seating[i][j]);
//        }
//       	ft_printf("\n");
//    }
//
//    // Free allocated memory
//    for (int i = 0; i < rows; i++) {
//        free(seating[i]);
//    }
//    free(seating);
//
//    return 0;
//}
//