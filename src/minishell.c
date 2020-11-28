/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 14:50:06 by valentin          #+#    #+#             */
/*   Updated: 2020/11/27 19:17:09 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv) // Doit récupérer les variables d'environnement !
{
	// Initialize the shell : récupération des variables d'environnement
	repl();
	// Exit the program
}
