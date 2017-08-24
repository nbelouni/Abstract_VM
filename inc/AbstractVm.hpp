/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVm.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 16:07:18 by nbelouni          #+#    #+#             */
/*   Updated: 2017/08/24 14:39:53 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

enum	Type
{
	INT8,
	INT16,
	INT32,
	FLOAT,
	DOUBLE,
	NONE
};

/*
**	ADD Factory functions
*/
char const	*lexCompare[11] = {
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

char const	*TypeCompare[6] = {
	"int8",
	"int16",
	"int32",
	"float",
	"double",
	"none"};
