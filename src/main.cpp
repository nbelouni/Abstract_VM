/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 16:06:34 by nbelouni          #+#    #+#             */
/*   Updated: 2017/08/27 19:53:28 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AbstractVm.hpp"

int main()
{
	std::string n = std::string("4");
	LexerParser lexPars = LexerParser();
	OperandFactory factory = OperandFactory();
	for (std::string line; std::getline(std::cin, line);)
	{
		std::cout << line << std::endl;
		try
		{
			lexPars.Parser(lexPars.Lexer(line));

			IOperand const *test = factory.createOperand(INT8, n);

			n.assign("8");
			IOperand const *test2 = factory.createOperand(INT8, n);
	std::cout << "ok" << std::endl;
			std::cout << "value: " << test->toString() << ", type: " << TypeCompare[test->getType()] << std::endl;
			std::cout << "value: " << test2->toString() << ", type: " << TypeCompare[test2->getType()] << std::endl;
			IOperand const *test3 = *test + *test2;
//			std::cout << (test + test2).toString() << std::endl;
			std::cout << "value: " << test3->toString() << ", type: " << TypeCompare[test3->getType()] << std::endl;
		}
		catch(std::exception &e)
		{
			std::cout << e.what() << line << std::endl;
//			exit(1);
		}
	}
	return 0;
}
