/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVm.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 16:07:18 by nbelouni          #+#    #+#             */
/*   Updated: 2017/08/31 14:08:19 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		ABSTRACT_VM_HPP
# define	ABSTRACT_VM_HPP

# define NONE	-1

#include <dirent.h>
#include <exception>
#include <fstream>
#include <functional>
#include <iostream>
#include <regex>
#include <string>
#include <sstream>
#include <vector>
#include <list>

typedef struct	s_op
{
	int			_inst;
	int			_type;
	std::string	_value;
}				t_op;

enum	eLexem
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
	EXIT1,
	EXIT2
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
const char	*const lexCompare[12] = {
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
	"exit",
	";;"};

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
#include "VM.hpp"

#endif
