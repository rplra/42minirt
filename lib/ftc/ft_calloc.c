/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:13:09 by rraja-az          #+#    #+#             */
/*   Updated: 2024/06/20 15:33:35 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"
/**
 * @brief		Allocates memory for an array of elements and
 * 				initialize all bytes to zero.
 * 
 * @param count	Length of variable
 * @param size	Size of variable(type/byte)
 * @return		None
*/
void	*ft_calloc(size_t count, size_t size)
{
	void	*memory;

	if (count && size && count > (UINT_MAX / size))
		return (NULL);
	memory = malloc(count * size);
	if (memory == NULL)
		return (NULL);
	ft_bzero(memory, (count * size));
	return (memory);
}

/*
int main(void)
{
	int i;
	int *array;
	size_t n = 5;
	
	// Allocate memory for n element of integers and size 
	array = ft_calloc(n, sizeof(int));

	// If calloc fails
	if (array == NULL)
		return (1);
	
	// Print array of elements
	i = 0;
	while (i < n)
	{
		printf("array[%d] = %d\n", i, array[i]);
		i++;
	}
	
	// Free calloc
	free(array);
	return (0);
}
*/

/*
	LOGIC : 
	1. Declare new pointer memory to point at malloc
	2. CHECK FOR OVERFLOW
		- make sure to check (count and size) to be non zero, WHY?
		- if either is zero, then size is definitely zero
		AND
		- (count > UINT_MAX / size); division is the actual count
		- WHY?
		- to make sure memory does not exceed max representable of size_t
		- if exceeed, overflow occurs, CRASH
	3. Allocate memory and assign to pointer > CHECK IF SUCCESSFUL
	4. Call ft_bzero and set all bytes to zero (memory, count * size)
	5. Return pointer
	
	DEBUG :

	// Integer overflow check
	if (count && size && count > (UINT_MAX / size))
		return (NULL);

	count && size
	- 	check if they're both non-zero
	
	count > (UINT_MAX / size)
	- 	computes the max no of elements (count) that can be safely
		safely allocated given the size of each element without
		causing integer overflow
	- 	if 'count' is greater than calculated max, it means 
		count * size > what can be represented by unsigned int
	-	WHY return NULL?
		- if true, will cause int overflow
*/