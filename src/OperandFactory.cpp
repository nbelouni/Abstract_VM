/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 13:55:45 by nbelouni          #+#    #+#             */
/*   Updated: 2018/03/09 16:36:27 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AbstractVm.hpp"

OperandFactory::OperandFactory()
{

	_functions.push_back(&OperandFactory::createInt8);
	_functions.push_back(&OperandFactory::createInt16);
	_functions.push_back(&OperandFactory::createInt32);
	_functions.push_back(&OperandFactory::createFloat);
	_functions.push_back(&OperandFactory::createDouble);
}

OperandFactory::OperandFactory(OperandFactory const &rhs)
{
	*this = rhs;
}
OperandFactory::~OperandFactory()
{
	_functions.erase(_functions.begin(), _functions.end());
}

OperandFactory const	&OperandFactory::operator=(OperandFactory const &rhs)
{
	std::vector<OperandFactory::t_createFunctionType> rhs_functions;

	rhs_functions = rhs.getFunctions();
	for	(size_t i = 0; i < _functions.size(); i++)
	{
		_functions[i] = rhs_functions[i];
	}
	return *this;
}

std::vector<OperandFactory::t_createFunctionType>	OperandFactory::getFunctions(void) const
{
	return _functions;
}

IOperand const	*OperandFactory::createOperand(eOperandType type,std::string const &value) const
{
	return (this->*_functions[type])(value);
}

IOperand const	*OperandFactory::createInt8(std::string const &value) const
{
	if (std::stold(value) > static_cast<long double>(std::numeric_limits<char>::max()))
		throw std::range_error("Value larger than maximum value : int8.");
	else if (std::stold(value) < static_cast<long double>(std::numeric_limits<char>::min()))
		throw std::range_error("Value smaller than minimum value : int8.");
	return new Operand<char>(value, INT8);
}

IOperand const	*OperandFactory::createInt16(std::string const &value) const
{
	if (std::stold(value) > static_cast<long double>(std::numeric_limits<short int>::max()))
		throw std::range_error("Value larger than maximum value : int16.");
	else if (std::stold(value) < static_cast<long double>(std::numeric_limits<short int>::min()))
		throw std::range_error("Value smaller than minimum value : int16.");
	return new Operand<short int>(value, INT16);
}

IOperand const	*OperandFactory::createInt32(std::string const &value) const
{
	if (std::stold(value) > static_cast<long double>(std::numeric_limits<int>::max()))
		throw std::range_error("Value larger than maximum value : int32.");
	else if (std::stold(value) < static_cast<long double>(std::numeric_limits<int>::min()))
		throw std::range_error("Value smaller than minimum value value : int32.");
	return new Operand<int>(value, INT32);
}

IOperand const	*OperandFactory::createFloat(std::string const &value) const
{
	if (std::stold(value) > static_cast<long double>(std::numeric_limits<float>::max()))
		throw std::range_error("Value larger than maximum value : float.");
	else if (std::stold(value) < -1 * static_cast<long double>(std::numeric_limits<float>::max()))
		throw std::range_error("Value smaller than minimum value value : float.");
	return new Operand<float>(value, FLOAT);
}

IOperand const	*OperandFactory::createDouble(std::string const &value) const
{
	if (std::stold(value) > static_cast<long double>(std::numeric_limits<double>::max()))
		throw std::range_error("Value larger than maximum value : double.");
	else if (std::stold(value) < -1 * (static_cast<long double>(std::numeric_limits<double>::max()) - 1))
		throw std::range_error("Value smaller than minimum value value : double.");
	return new Operand<double>(value, DOUBLE);
}

