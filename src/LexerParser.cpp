/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LexerParser.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 16:19:15 by nbelouni          #+#    #+#             */
/*   Updated: 2017/08/24 14:54:14 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AbstractVm.hpp"
#include "LexerParser.hpp"
#include <string>
#include <regex>
#include <typeinfo>

LexerParser::LexerParser(void) : _inst(0), _type(0), _value("")
{
	std::cout << "LexerParser constructed." << std::endl;
}

LexerParser::LexerParser(LexerParser const &lp)
{
	*this = lp;
}

LexerParser::~LexerParser(void)
{
	std::cout << "LexerParser destroyed." << std::endl;
}

LexerParser		&LexerParser::operator=(LexerParser const &rhs)
{
	this->_inst = rhs.getInst();
	this->_type = rhs.getType();
	this->_value = rhs.getValue();
	std::cout << "LexerParser content copied." << std::endl;
	return *this;
}

bool		LexerParser::Lexer(std::string line)
{
	std::regex pieces_regex(VALID_LINE);
	std::cmatch pieces_match;

	_inst = NONE;
	_type = NONE;
	_value.clear();

	line = std::regex_replace(line, std::regex("([ ]+)"), " ");
	if (std::regex_search(line.c_str(), pieces_match, std::regex("(;[^;])")))
		line = pieces_match.prefix();
	if (line.length() == 0 || !std::regex_match(line.c_str(), pieces_match, pieces_regex))
		throw InvalidLineException();
	for (int i = 0; i < 11; i++)
	{
		if (std::strstr(line.c_str(), lexCompare[i]))
		{
			_inst = i;
			if (i == PUSH || i == ASSERT)
			{
				for (int j = 0; j < 5; j++)
				{
					if (std::strstr(line.c_str(), TypeCompare[j]))
					{
						_type = j;
						std::size_t begin = line.find("(") + 1;
						std::size_t end = line.find(")");
						_value = line.substr(begin, end - begin);
						break;
					}
				}
			}
			break;
		}
	}
	std::cout << "_inst: " << lexCompare[_inst] << std::endl;
	std::cout << "_type: " << TypeCompare[_type] << std::endl;
	std::cout << "_value: " << _value << std::endl;
	std::cout << "found: " << line << std::endl;
	return true;
}

/*
 *	Get/Set
 */

void		LexerParser::setInst(int inst) 
{
	_inst = inst;
}

int			LexerParser::getInst(void) const
{
	return this->_inst;
}

void		LexerParser::setType(int type) 
{
	this->_type = type;
}

int			LexerParser::getType(void) const
{
	return this->_type;
}

void		LexerParser::setValue(std::string value)
{
	this->_value = value;
}

std::string	LexerParser::getValue(void) const
{
	return this->_value;
}

/*
 *	Nested Classes
 */

LexerParser::InvalidLineException::InvalidLineException()
{
}

LexerParser::InvalidLineException::InvalidLineException(InvalidLineException const &i)
{
	*this = i;
}

LexerParser::InvalidLineException::~InvalidLineException() throw()
{
}

LexerParser::InvalidLineException &LexerParser::InvalidLineException::operator=(InvalidLineException const &d)
{
	(void)d;
	return *this;
}

char const	*LexerParser::InvalidLineException::what() const throw()
{
	return ("Syntax error: ");
}
