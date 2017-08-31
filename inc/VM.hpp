/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VM.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 19:16:55 by nbelouni          #+#    #+#             */
/*   Updated: 2017/08/31 20:05:15 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AbstractVm.hpp"

class	VM
{
	typedef void (VM::*tFunction)(void);

	private:
		std::list<t_op> 				_instructions;
		std::vector<IOperand const *>	_stack;
		OperandFactory 					*_factory;
		std::vector<tFunction>			_functions;

	public:
		VM(std::list<t_op>);
		VM(VM const &rhs);
		~VM();

		VM const	&operator=(VM const &rhs);

		std::vector<IOperand const *>	getStack(void) const;
		std::list<t_op>	getInstructions(void) const;
	
		class	BadInstructionException: public std::exception
		{
			private:
				char const	*_message;
			public:
				BadInstructionException(char const *message);
				BadInstructionException(BadInstructionException const &rhs);
				virtual ~BadInstructionException() throw();
				virtual const char *what() const throw();
		
			private:
			BadInstructionException &operator=(BadInstructionException const &);
		};

		void		push(void);
		void		pop(void);
		void		dump(void);
		void		assert(void);
		void		add(void);
		void		sub(void);
		void		mul(void);
		void		div(void);
		void		mod(void);
		void		print(void);
		void		exit(void);

		void		Run(void);
};
