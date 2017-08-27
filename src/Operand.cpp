/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 15:29:39 by nbelouni          #+#    #+#             */
/*   Updated: 2017/08/27 19:52:02 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "Operand.hpp"
/*
template <class T>
Operand<T>::Operand(T const &n) : _value(n)
{
}

template <class T>
Operand<T>::Operand(Operand<T> const &rhs)
{
	*this = rhs;
}

template <class T>
Operand<T>::~Operand()
{
}
*/
/*
 *	Get/set
 */
/*
template <class T>
void	Operand<T>::setValue(T value)
{
	_value = value;
}

template <class T>
T		Operand<T>::getValue(void)
{
	return _value;
}
*/
/*
 *	Surcharge Operators
 */
/*
template <class T>
Operand<T>	&Operand<T>::operator=(Operand<T> const &rhs) const
{
	_value = rhs.getValue();
	return *this;
}
*/
//template <class T>
//IOperand const	*Operand<T>::operator+(IOperand const &rhs) const// Sum
//{
//	/*
//	 *	OVERFLOW
//	 *	UNDERFLOW
//	 */
//	_value += static_cast<Operand<T>>(rhs).getValue();
//	return *this;
//}

//template <class T>
//Operand<T> const	*Operand<T>::operator-(Operand<T> const &rhs)  const// Difference
//{
//	/*
//	 *	OVERFLOW
//	 *	UNDERFLOW
//	 */
//	_value -= rhs.getValue();
//	return *this;
//}
//
//template <class T>
//Operand<T> const	*Operand<T>::operator*(Operand<T> const &rhs) const // Product
//{
//	/*
//	 *	OVERFLOW
//	 *	UNDERFLOW
//	 */
//	_value *= rhs.getValue();
//	return *this;
//}
//
//template <class T>
//Operand<T> const	*Operand<T>::operator/(Operand<T> const &rhs) const // Quotient
//{
//	/*
//	 *	OVERFLOW
//	 *	UNDERFLOW
//	 *	DIV BY 0
//	 */
//	_value /= rhs.getValue();
//	return *this;
//}
//
//template <class T>
//Operand<T> const	*Operand<T>::operator%(Operand<T> const &rhs) const // Modulo
//{
//	/*
//	 *	OVERFLOW
//	 *	UNDERFLOW
//	 *	MOD BY 0
//	 */
//	_value %= rhs.getValue();
//	return *this;
//}
//
//template <class T>
//std::string const &Operand<T>::toString(void) const// String representation of the instance
//{
//	std::cout << "Operand:    value :"<< _value << ", type: " << typeId(_value).name() << ", precision: " << this->getPrecision() << std::endl;
//}
//
//template <class T>
//int			Operand<T>::getPrecision( void ) const// Precision of the type of the instance
//{
//	return std::cout.precision();
//}
//
//template <class T>
//T			Operand<T>::getType(void) const // Type of the instance
//{
//	char n = 0;
//	return static_cast<T>(n);
//}
//
