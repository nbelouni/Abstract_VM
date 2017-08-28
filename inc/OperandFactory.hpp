/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 13:44:51 by nbelouni          #+#    #+#             */
/*   Updated: 2017/08/28 18:09:14 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		OPERAND_FACTORY_H
# define	OPERAND_FACTORY_H

//#include "AbstractVm.hpp"


class	OperandFactory
{
	typedef IOperand const *(OperandFactory::*t_createFunctionType)(std::string const &) const;
	private:
		std::vector<t_createFunctionType>	_functions;

		IOperand const	*createInt8(std::string const &value) const;
		IOperand const	*createInt16(std::string const &value) const;
		IOperand const	*createInt32(std::string const &value) const;
		IOperand const	*createFloat(std::string const &value) const;
		IOperand const	*createDouble(std::string const &value) const;

	public:
		OperandFactory();
		OperandFactory(OperandFactory const &);
		~OperandFactory();

		std::vector<t_createFunctionType>	getFunctions(void) const;

		OperandFactory const	&operator=(OperandFactory const &);

		IOperand const	*createOperand(eOperandType type,std::string const &value) const;
};

#endif
