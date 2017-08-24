/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 16:06:34 by nbelouni          #+#    #+#             */
/*   Updated: 2017/08/24 19:37:53 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AbstractVm.hpp"

int main()
{
	LexerParser lexPars = LexerParser();
	for (std::string line; std::getline(std::cin, line);)
	{
		std::cout << line << std::endl;
		try
		{
			lexPars.Parser(lexPars.Lexer(line));
			Operand<int> test = Operand<int>("4", INT32);
			Operand<int> test2 = Operand<int>("9", INT32);
			std::cout << "value: " << test.toString() << ", type: " << TypeCompare[test.getType()] << std::endl;
			std::cout << "value: " << test2.toString() << ", type: " << TypeCompare[test2.getType()] << std::endl;
			test = test2;
			std::cout << "value: " << test.toString() << ", type: " << TypeCompare[test.getType()] << std::endl;
		}
		catch(std::exception &e)
		{
			std::cout << e.what() << line << std::endl;
//			exit(1);
		}
	}
	return 0;
}
