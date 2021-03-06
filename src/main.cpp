/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 16:06:34 by nbelouni          #+#    #+#             */
/*   Updated: 2018/03/09 17:08:25 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AbstractVm.hpp"
#include <unistd.h>

int main(int argc, char **argv)
{
	LexerParser lexPars = LexerParser();
	if (argc < 2)
	{
		try
		{
			std::list<t_op> ops = lexPars.Parser(lexPars.Lexer(NULL));
			VM vm = VM(ops);
			vm.Run();
		}
		catch(std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	else
	{
		for (int i = 1; i < argc; i++)
		{
			try
			{
				std::string fileName(argv[i]);
				std::list<t_op> ops = lexPars.Parser(lexPars.Lexer(&fileName));
				VM vm = VM(ops);
				vm.Run();

			}
			catch(std::exception &e)
			{
				std::cout << e.what() << std::endl;
			}
			lexPars.clear();
		}
	}
	return 0;
}
