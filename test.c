/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-nei <aben-nei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 22:01:29 by aben-nei          #+#    #+#             */
/*   Updated: 2023/06/03 22:09:58 by aben-nei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>

int main() {
	uid_t uid = getuid();
	struct passwd *pw = getpwuid(uid);
	
	if (pw != NULL) {
		printf("Username: %s\n", pw->pw_name);
	} else {
		printf("Failed to retrieve username.\n");
	}
	
	return 0;
}
