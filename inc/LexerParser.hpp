/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LexerParser.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 16:06:28 by nbelouni          #+#    #+#             */
/*   Updated: 2017/08/31 20:39:55 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		LEXER_PARSER_HPP
# define	LEXER_PARSER_HPP


# define VALID_LINE 	"( *(push +(int(8|16|32)\\(-?[0-9]+\\)|((float|double)\\(-?[0-9]+(\\.[0-9]+)?\\)))|pop|dump|assert +(int(8|16|32)\\(-?[0-9]+\\)|((float|double)\\(-?[0-9]+(\\.[0-9]+)?\\)))|add|sub|mul|div|mod|mod|print|exit|;;+) *)"

class LexerParser
{
	private:
		std::list<struct s_op>		_ops;

	public:
		LexerParser();
		LexerParser(LexerParser const &);
		~LexerParser();

		std::list<t_op> const		&getOps(void) const;

		void						clear(void);
		std::vector<std::string>	Lexer(std::string *line);
		std::list<t_op> const 		&Parser(std::vector<std::string> file);

		LexerParser	&operator=(LexerParser const &lex);
		
		class	InvalidLineException : public std::exception
		{
			private:
				std::string		_message;

			public:
				InvalidLineException(std::string);
				InvalidLineException(InvalidLineException const &);
				virtual ~InvalidLineException() throw();
				virtual const char *what() const throw();
		
			private:
			InvalidLineException &operator=(InvalidLineException const &);
		};
};

#endif
