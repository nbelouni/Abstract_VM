/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 15:18:20 by nbelouni          #+#    #+#             */
/*   Updated: 2017/08/24 19:39:41 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		OPERAND_HPP
# define	OPERAND_HPP

template <typename T> class Operand : public IOperand
{
	private:
		std::string		_value;
		eOperandType	_type;

		Operand() : _value(0), _type(INT8) {}

	public:
		Operand(std::string const &n, eOperandType const type) : _value(n), _type(type) {}

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

		virtual IOperand const	*operator+(IOperand const &rhs) const // Sum
		{
			/*
			 *	OVERFLOW
			 *	UNDERFLOW
			 */
			long double n = std::stold(_value) + std::stold(rhs.toString());
			n += 1;	
			/*
			 * Create new Operand
			 *
			 */
			return this;
		}

/*		Operand<T> const	*operator-(Operand const &) const; // Difference
		Operand<T> const	*operator*(Operand const &) const; // Product
		Operand<T> const	*operator/(Operand const &) const; // Quotient
		Operand<T> const	*operator%(Operand const &) const; // Modulo

*/
		std::string const	&toString(void) const // String representation of the instance
		{
			return _value;
		}

		Operand<T>		&operator=(Operand<T> const &rhs)
		{
			/*
			 *	SAME TYPE
			 */
			_value.clear();
			_value.insert(0, rhs.toString());
			return *this;
		}
};

#endif
