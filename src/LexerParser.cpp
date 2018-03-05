/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LexerParser.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 16:19:15 by nbelouni          #+#    #+#             */
/*   Updated: 2017/12/09 15:20:20 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AbstractVm.hpp"

LexerParser::LexerParser(void)
{
}

LexerParser::LexerParser(LexerParser const &lp)
{
	*this = lp;
}

LexerParser::~LexerParser(void)
{
	_ops.clear();
}

LexerParser		&LexerParser::operator=(LexerParser const &rhs)
{
	_ops = rhs.getOps();
	return *this;
}

void						LexerParser::clear(void)
{
	_ops.clear();
}

std::vector<std::string>	LexerParser::Lexer(std::string *fileName)
{
	std::regex	pieces_regex(VALID_LINE);
	std::cmatch	pieces_match;
	std::string	line;
	std::vector<std::string>	epurFile;

	if (fileName)
	{
		std::ifstream file(*fileName);
		if (file.is_open())
		{
			while (std::getline(file, line))
			{
				line = std::regex_replace(line, std::regex("([ ]+)"), " ");
				if (std::regex_search(line.c_str(), pieces_match, std::regex("(;[^;]?)")))
					line = pieces_match.prefix();
				if (line.length() != 0 && !std::regex_match(line.c_str(), pieces_match, pieces_regex))
					throw InvalidLineException(std::string("Syntax error: ").append(line));
				epurFile.push_back(line);
			}
		}
	}
	else
	{
		while (std::getline(std::cin, line))
		{
			line = std::regex_replace(line, std::regex("([ ]+)"), " ");
			if (std::regex_search(line.c_str(), pieces_match, std::regex("(;[^;])")))
				line = pieces_match.prefix();
			if (line.length() != 0 && !std::regex_match(line.c_str(), pieces_match, pieces_regex))
				throw InvalidLineException(std::string("Syntax error: ").append(line));
			epurFile.push_back(line);
			if (std::strstr(line.c_str(), lexCompare[EXIT2]))
				break;
		}
	}
	return (epurFile);
}

std::list<t_op> const	&LexerParser::Parser(std::vector<std::string> file)
{
	t_op tmp;

	for (std::vector<std::string>::iterator iFile = file.begin(); iFile != file.end(); iFile++)
	{
		tmp._inst = 0;
		tmp._type = -1;
		tmp._value.clear();
		for (int i = 0; i < 12; i++)
		{
			if ((*iFile).length() > 0 && std::strstr((*iFile).c_str(), lexCompare[i]))
			{
				tmp._inst = i;
				if (i == PUSH || i == ASSERT)
				{
					for (int j = 0; j < 5; j++)
					{
						if (std::strstr((*iFile).c_str(), TypeCompare[j]))
						{
							tmp._type = j;
							std::size_t begin = (*iFile).find("(") + 1;
							std::size_t end = (*iFile).find(")");
							tmp._value = (*iFile).substr(begin, end - begin);
							break;
						}
					}
				}
				_ops.push_back(tmp);
				break;
			}
		}
	}
	return getOps();
}

/*
 *	Get/Set
 */

std::list<t_op>	const &LexerParser::getOps(void) const
{
	return _ops;
}

/*
 *	Nested Classes
 */

LexerParser::InvalidLineException::InvalidLineException(std::string s) : _message(s)
{
}

LexerParser::InvalidLineException::InvalidLineException(InvalidLineException const &i)
{
	*this = i;
}

LexerParser::InvalidLineException::~InvalidLineException() throw()
{
	_message.clear();
}

LexerParser::InvalidLineException &LexerParser::InvalidLineException::operator=(InvalidLineException const &d)
{
	(void)d;
	return *this;
}

char const	*LexerParser::InvalidLineException::what() const throw()
{
	return (_message.c_str());
}
