/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LexerParser.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 16:06:28 by nbelouni          #+#    #+#             */
/*   Updated: 2017/08/24 14:52:23 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex>
#include <exception>
#include <iostream>

class LexerParser
{
	private:
		int			_inst;
		int			_type;
		std::string	_value;

	public:
		LexerParser();
		LexerParser(LexerParser const &);
		~LexerParser();

		void		setInst(int inst);
		int			getInst(void) const;

		void		setType(int inst);
		int			getType(void) const;

		void		setValue(std::string inst);
		std::string	getValue(void) const;

		bool		Lexer(std::string line);
		bool		Parser(void);

		LexerParser	&operator=(LexerParser const &lex);
		
		class	InvalidLineException : public std::exception
		{
			public:
				InvalidLineException();
				InvalidLineException(InvalidLineException const &);
				virtual ~InvalidLineException() throw();
				virtual const char *what() const throw();
		
			private:
			InvalidLineException &operator=(InvalidLineException const &);
		};
};

# define VALID_LINE 	"( *(push +(int(8|16|32)\\([0-9]+\\)|((float|double)\\([0-9]+(\\.[0-9]+)?\\)))|pop|dump|assert +(int(8|16|32)\\([0-9]+\\)|((float|double)\\([0-9]+(\\.[0-9]+)?\\)))|add|sub|mul|div|mod|mod|print|exit|;;) *)"
