/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 15:18:20 by nbelouni          #+#    #+#             */
/*   Updated: 2018/03/09 16:38:30 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		OPERAND_HPP
# define	OPERAND_HPP

#include "AbstractVm.hpp"

#include "OperandFactory.hpp"
#include <iomanip>

template <typename T> class Operand : public IOperand
{
	private:
		std::string		_value;
		eOperandType	_type;
		int				_precision;
		OperandFactory	*_factory;
		std::string		_err_max;
		std::string		_err_min;

		Operand() : _value(0), _type(INT8) {}

	public:
		Operand(std::string const &n, eOperandType type) : _value(n), _type(type) 
		{
			_factory = new OperandFactory();
			if (_type <= INT32)
				_precision = 0;
			else
			{
				size_t i = n.find(".");
				if (i == n.npos)
					_precision = 0;
				else
					_precision = std::strlen(&(n.at(i + 1)));
			}
			_err_max.assign("Value larger than maximum value : ").append(TypeCompare[_type]).c_str();
			_err_min.assign("Value smaller than minimum value : ").append(TypeCompare[_type]).c_str();
		}

		Operand(Operand<T> const &rhs)
		{
			*this = rhs;
		}

		~Operand()
		{
			_value.clear();
			_err_max.clear();
			_err_min.clear();
			delete _factory;
		}

/*
**		EXCEPTIONS
**
*/
		class	DivideByZeroException: public std::exception
		{
			public:
				DivideByZeroException()
				{
				}

				DivideByZeroException(DivideByZeroException const &rhs)
				{
					*this = rhs;
				}
				virtual ~DivideByZeroException() throw()
				{
				}

				virtual const char *what() const throw()
				{
					return ("Division by zero.");
				}
		
			private:
			DivideByZeroException &operator=(DivideByZeroException const &);
		};

		class	ModByZeroException: public std::exception
		{
			public:
				ModByZeroException()
				{
				}

				ModByZeroException(ModByZeroException const &rhs)
				{
					*this = rhs;
				}

				virtual ~ModByZeroException() throw()
				{
				}

				virtual const char *what() const throw()
				{
					return ("Modulo by zero.");
				}
		
			private:
			ModByZeroException &operator=(ModByZeroException const &);
		};

/*
**		IOperand Functions
*/


		int 			getPrecision(void) const // Precision of the type of the instance
		{
			return _precision;
		}


		eOperandType	getType(void) const // Type of the instance
		{
			return _type;
		}

		IOperand const	*operator+(IOperand const &rhs) const // Sum
		{
			if (std::stold(_value) + std::stold(rhs.toString()) > static_cast<long double>(std::numeric_limits<T>::max()))
				throw std::range_error(_err_max.c_str());
			else if (std::stold(_value) + std::stold(rhs.toString()) < static_cast<long double>((std::numeric_limits<T>::max() - 1) * -1))
				throw std::range_error(_err_min.c_str());
			long double n = std::stold(_value) + std::stold(rhs.toString());

			std::stringstream blah;
			blah << std::fixed;
			blah << std::setprecision((_precision > rhs.getPrecision()) ? _precision : rhs.getPrecision());
			blah << n;
			return _factory->createOperand((_type > rhs.getType()) ? _type : rhs.getType(), blah.str());
		}

		IOperand const	*operator-(IOperand const &rhs) const // Difference
		{
			if (std::stold(_value) - std::stold(rhs.toString()) > static_cast<long double>(std::numeric_limits<T>::max()))
				throw std::range_error(_err_max.c_str());
			else if (std::stold(_value) - std::stold(rhs.toString()) < static_cast<long double>((std::numeric_limits<T>::max() - 1) * -1))
				throw std::range_error(_err_min.c_str());
			long double n = std::stold(_value) - std::stold(rhs.toString());
			std::stringstream blah;
			blah << std::fixed;
			blah << std::setprecision((_precision > rhs.getPrecision()) ? _precision : rhs.getPrecision());
			blah << n;

			return _factory->createOperand((_type > rhs.getType()) ? _type : rhs.getType(), blah.str());
		}

		IOperand const	*operator*(IOperand const &rhs) const // Product
		{
			if (std::stold(_value) * std::stold(rhs.toString()) > static_cast<long double>(std::numeric_limits<T>::max()))
				throw std::range_error(_err_max.c_str());
			else if (std::stold(_value) * std::stold(rhs.toString()) < static_cast<long double>((std::numeric_limits<T>::max() - 1) * -1))
				throw std::range_error(_err_min.c_str());
			long double n = std::stold(_value) * std::stold(rhs.toString());
			std::stringstream blah;
			blah << std::fixed;
			blah << std::setprecision((_precision > rhs.getPrecision()) ? _precision : rhs.getPrecision());
			blah << n;

			return _factory->createOperand((_type > rhs.getType()) ? _type : rhs.getType(), blah.str());
		}

		IOperand const	*operator/(IOperand const &rhs) const // Quotient
		{
			std::regex zero_regex("^-?0\\.?0*$");

			if (regex_search(rhs.toString(), zero_regex))
				throw DivideByZeroException();
			else if (std::stold(_value) / std::stold(rhs.toString()) > static_cast<long double>(std::numeric_limits<T>::max()))
				throw std::range_error(_err_max.c_str());
			else if (std::stold(_value) / std::stold(rhs.toString()) < static_cast<long double>((std::numeric_limits<T>::max() - 1) * -1))
				throw std::range_error(_err_min.c_str());
			long double n = std::stold(_value) / std::stold(rhs.toString());
			std::stringstream blah;
			blah << std::fixed;
			blah << std::setprecision((_precision > rhs.getPrecision()) ? _precision : rhs.getPrecision());
			blah << n;

			return _factory->createOperand((_type > rhs.getType()) ? _type : rhs.getType(), blah.str());
		}

		IOperand const	*operator%(IOperand const &rhs) const // Modulo
		{
			std::regex zero_regex("^-?0\\.?0*$");

			if (regex_search(rhs.toString(), zero_regex))
				throw ModByZeroException();
			else if (std::fmod(std::stold(_value), std::stold(rhs.toString())) > static_cast<long double>(std::numeric_limits<T>::max()))
				throw std::range_error(_err_max.c_str());
			else if (std::fmod(std::stold(_value), std::stold(rhs.toString())) < static_cast<long double>((std::numeric_limits<T>::max() - 1) * -1))
				throw std::range_error(_err_min.c_str());
			long double n = std::fmod(std::stold(_value), std::stold(rhs.toString()));
			std::stringstream blah;
			blah << n;

			if (_type >= FLOAT)
				std::cout << "\"The expression x - trunc(x/y)*y may not equal fmod(x,y) when the rounding of x/y to initialize the argument of trunc loses too much precision (example: x = 30.508474576271183309, y = 6.1016949152542370172)\"\n     (http://en.cppreference.com/w/cpp/numeric/math/fmod)"<< std::endl;
			return _factory->createOperand((_type > rhs.getType()) ? _type : rhs.getType(), blah.str());
		}


		std::string const	&toString(void) const // String representation of the instance
		{
			return _value;
		}

/*
**	Others Functions
**
*/

		Operand<T>		&operator=(Operand<T> const &rhs)
		{
			_value.assign(rhs.toString());
			_type = rhs.getType();

			return *this;
		}
};

#endif
