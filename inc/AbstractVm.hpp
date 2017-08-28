/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVm.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 16:07:18 by nbelouni          #+#    #+#             */
/*   Updated: 2017/08/28 19:15:34 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		ABSTRACT_VM_HPP
# define	ABSTRACT_VM_HPP

# define NONE	-1

#include <exception>
#include <functional>
#include <iostream>
#include <regex>
#include <string>
#include <sstream>
#include <vector>

enum	Lexem
{
	PUSH, // n
	POP,
	DUMP,
	ASSERT, // n
	ADD,
	SUB,
	MUL,
	DIV,
	MOD,
	PRINT,
	EXIT
};

enum	eOperandType
{
	INT8,
	INT16,
	INT32,
	FLOAT,
	DOUBLE,
};

/*
**	ADD Factory functions
*/
const char	*const lexCompare[11] = {
	"push",
	"pop",
	"dump",
	"assert",
	"add",
	"sub",
	"mul",
	"div",
	"mod",
	"print",
	"exit"};

const char	*const TypeCompare[6] = {
	"int8",
	"int16",
	"int32",
	"float",
	"double",
	"none"};

#include "IOperand.hpp"
#include "Operand.hpp"
#include "OperandFactory.hpp"
#include "LexerParser.hpp"

#endif
