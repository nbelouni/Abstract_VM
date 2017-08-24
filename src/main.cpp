/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 16:06:34 by nbelouni          #+#    #+#             */
/*   Updated: 2017/08/24 14:34:49 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LexerParser.hpp"

int main()
{
	LexerParser lexPars = LexerParser();
	for (std::string line; std::getline(std::cin, line);)
	{
		std::cout << line << std::endl;
		try
		{
			lexPars.Lexer(line);
		}
		catch(std::exception &e)
		{
			std::cout << e.what() << line << std::endl;
//			exit(1);
		}
	}
	return 0;
}
