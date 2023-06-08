/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 22:01:29 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/08 23:11:33 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>

int main()
{
	
	printf("%s\n", getcwd(NULL, 0));
	chdir("~");
	printf("%s\n", getcwd(NULL, 0));
}
