/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 15:18:20 by nbelouni          #+#    #+#             */
/*   Updated: 2017/08/27 20:23:50 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		OPERAND_HPP
# define	OPERAND_HPP

#include "AbstractVm.hpp"
#include <sstream>

template <typename T> class Operand : public IOperand
{
	private:
		std::string		_value;
		eOperandType	_type;
		OperandFactory	_factory;
		std::string		_err_max;
		std::string		_err_min;

		Operand() : _value(0), _type(INT8) {}

	public:
		Operand(std::string const &n, eOperandType const type) : _value(n), _type(type) 
		{
			_factory = OperandFactory();
			_err_max.assign("Value larger than maximum value : ").append(TypeCompare[_type]).c_str();
			_err_min.assign("Value smaller than minimum value : ").append(TypeCompare[_type]).c_str();
		}

		Operand(Operand<T> const &rhs)
		{
			*this = rhs;
		}

		~Operand() {}

/*
		int 			getPrecision(void) const; // Precision of the type of the instance
*/		eOperandType	getType(void) const // Type of the instance
		{
			return _type;
		}

		IOperand const	*operator+(IOperand const &rhs) const // Sum
		{
			try
			{
				if (std::stold(_value) > static_cast<long double>(std::numeric_limits<T>::max()))
					throw std::range_error(_err_max.c_str());
				else if (std::stold(_value) < static_cast<long double>(std::numeric_limits<T>::min()))
					throw std::range_error(_err_min.c_str());
				long double n = std::stold(_value) + std::stold(rhs.toString());
				std::stringstream blah;
				blah << n;

				return _factory.createOperand((_type > rhs.getType()) ? _type : rhs.getType(), blah.str());
			}
			catch(std::range_error &e)
			{
				std::cout << e.what() << std::endl;
			}
			return NULL;
		}

		IOperand const	*operator-(Operand const &rhs) const // Difference
		{
			/*
			 *	OVERFLOW
			 *	UNDERFLOW
			 */
			try
			{
				if (std::stold(_value) > static_cast<long double>(std::numeric_limits<T>::max()))
					throw std::range_error(_err_max.c_str());
				else if (std::stold(_value) < static_cast<long double>(std::numeric_limits<T>::min()))
					throw std::range_error(_err_min.c_str());
				long double n = std::stold(_value) - std::stold(rhs.toString());
				std::stringstream blah;
				blah << n;

				return _factory.createOperand((_type > rhs.getType()) ? _type : rhs.getType(), blah.str());
			}
			catch(std::range_error &e)
			{
				std::cout << e.what() << std::endl;
			}
			return NULL;
		}

		IOperand const	*operator*(Operand const &rhs) const // Product
		{
			/*
			 *	OVERFLOW
			 *	UNDERFLOW
			 */
			try
			{
				if (std::stold(_value) > static_cast<long double>(std::numeric_limits<T>::max()))
					throw std::range_error(_err_max.c_str());
				else if (std::stold(_value) < static_cast<long double>(std::numeric_limits<T>::min()))
					throw std::range_error(_err_min.c_str());
				long double n = std::stold(_value) * std::stold(rhs.toString());
				std::stringstream blah;
				blah << n;

				return _factory.createOperand((_type > rhs.getType()) ? _type : rhs.getType(), blah.str());
			}
			catch(std::range_error &e)
			{
				std::cout << e.what() << std::endl;
			}
			return NULL;
		}

		IOperand const	*operator/(Operand const &rhs) const // Quotient
		{
			/*
			 *	OVERFLOW
			 *	UNDERFLOW
			 */
			try
			{
				if (std::stold(_value) > static_cast<long double>(std::numeric_limits<T>::max()))
					throw std::range_error(_err_max.c_str());
				else if (std::stold(_value) < static_cast<long double>(std::numeric_limits<T>::min()))
					throw std::range_error(_err_min.c_str());
				long double n = std::stold(_value) / std::stold(rhs.toString());
				std::stringstream blah;
				blah << n;

				return _factory.createOperand((_type > rhs.getType()) ? _type : rhs.getType(), blah.str());
			}
			catch(std::range_error &e)
			{
				std::cout << e.what() << std::endl;
			}
			return NULL;
		}

		IOperand const	*operator%(Operand const &rhs) const // Modulo
		{
			/*
			 *	OVERFLOW
			 *	UNDERFLOW
			 */
			try
			{
				if (std::stold(_value) > static_cast<long double>(std::numeric_limits<T>::max()))
					throw std::range_error(_err_max.c_str());
				else if (std::stold(_value) < static_cast<long double>(std::numeric_limits<T>::min()))
					throw std::range_error(_err_min.c_str());
				long double n = std::stold(_value) % std::stold(rhs.toString());
				std::stringstream blah;
				blah << n;

				return _factory.createOperand((_type > rhs.getType()) ? _type : rhs.getType(), blah.str());
			}
			catch(std::range_error &e)
			{
				std::cout << e.what() << std::endl;
			}
			return NULL;
		}



		std::string const	&toString(void) const // String representation of the instance
		{
			return _value;
		}

		Operand<T>		&operator=(Operand<T> const &rhs)
		{
			/*
			 *	SAME TYPE
			 */
			_value.assign(rhs.toString());
			_type = rhs.getType();

			return *this;
		}
};

#endif
