/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VM.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 19:26:41 by nbelouni          #+#    #+#             */
/*   Updated: 2017/12/09 17:54:36 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AbstractVm.hpp"

/*
**		CONSTRUCT / DESTRUCT
*/
VM::VM(std::list<t_op> instructions) : _instructions(instructions), _factory(new OperandFactory())
{
	_functions.push_back(&VM::push);
	_functions.push_back(&VM::pop);
	_functions.push_back(&VM::dump);
	_functions.push_back(&VM::assert);
	_functions.push_back(&VM::add);
	_functions.push_back(&VM::sub);
	_functions.push_back(&VM::mul);
	_functions.push_back(&VM::div);
	_functions.push_back(&VM::mod);
	_functions.push_back(&VM::print);
	_functions.push_back(&VM::exit);
	_functions.push_back(&VM::exit);
}

VM::VM(VM const &rhs) : _instructions(rhs.getInstructions())
{
	*this = rhs;
}

VM::~VM()
{
	_instructions.clear();
	while (!_stack.empty())
		pop();
	_functions.clear();
	delete _factory;
}

/*
**	UTIL
*/
VM const	&VM::operator=(VM const &rhs)
{
	_stack = rhs.getStack();
	return *this;
}

std::vector<IOperand const *>	VM::getStack(void) const
{
	return _stack;
}


std::list<t_op>	VM::getInstructions(void) const
{
	return _instructions;
}

/*
**	STACK FUNCTIONS
*/
void		VM::push(void)
{
	IOperand const * newOp = _factory->createOperand(static_cast<eOperandType>(_instructions.front()._type), _instructions.front()._value);
	_stack.push_back(newOp);
}

void		VM::pop(void)
{
	if (_stack.size() == 0)
		throw VM::BadInstructionException("Cannot pop: empty stack.");
	IOperand const *op = *(_stack.end() - 1);
	_stack.pop_back();
	delete op;
}

void		VM::dump(void)
{
	if (!_stack.empty())
	{
		std::vector<IOperand const *>::iterator tmp = _stack.end() - 1;
		while (1)
		{
			std::cout << std::setprecision((*tmp)->getPrecision()) << "type : " << TypeCompare[(*tmp)->getType()] << ", value : " << (*tmp)->toString() << std::endl;
			if (*tmp == *(_stack.begin()))
				break;
			tmp -= 1;
		}
	}
}

void		VM::assert(void)
{
	if (_stack.size() == 0)
		throw VM::BadInstructionException("Cannot assert: empty stack.");

	std::string toCompare(((*(_stack.end() -1))->toString()));
	int i = 0;
	for (i = toCompare.length() -1 ; i >= 0; i--)
	{
		if (toCompare[i] != '0' && toCompare[i] != '.' && toCompare[i] == '-')
			break;
	}
	if (i >= 0 && i < static_cast<int>(toCompare.length()))
		toCompare = toCompare.substr(0, i + 1);
	else
		toCompare = "0";
	if (_instructions.front()._type != (*(_stack.end() -1 ))->getType()
	||	_instructions.front()._value.compare(toCompare))
		throw VM::BadInstructionException("Assert failed");
}

void		VM::add(void)
{
	if (_stack.size() < 2)
		throw VM::BadInstructionException("Cannot add: less than 2 values on stack.");

	IOperand const *newOp;

	newOp = (*(*(_stack.end() - 1)) + *(*(_stack.end() - 2)));
	pop();
	pop();
	_stack.push_back(newOp);
}

void		VM::sub(void)
{
	if (_stack.size() < 2)
		throw VM::BadInstructionException("Cannot sub: less than 2 values on stack.");

	IOperand const *tmp;

	tmp = (*(*(_stack.end() - 1)) - *(*(_stack.end() - 2)));
	pop();
	pop();
	_stack.push_back(tmp);
}

void		VM::mul(void)
{
	if (_stack.size() < 2)
		throw VM::BadInstructionException("Cannot mul: less than 2 values on stack.");

	IOperand const *tmp;

	tmp = (*(*(_stack.end() - 1)) * *(*(_stack.end() - 2)));
	pop();
	pop();
	_stack.push_back(tmp);
}

void		VM::div(void)
{
	if (_stack.size() < 2)
		throw VM::BadInstructionException("Cannot div: less than 2 values on stack.");

	IOperand const *tmp;

	tmp = (*(*(_stack.end() - 2)) / *(*(_stack.end() - 1)));
	pop();
	pop();
	_stack.push_back(tmp);
}

void		VM::mod(void)
{
	if (_stack.size() < 2)
		throw VM::BadInstructionException("Cannot mod: less than 2 values on stack.");

	IOperand const *tmp;

	if (_stack.size() >= 2)
	{
		tmp = (*(*(_stack.end() - 2)) % *(*(_stack.end() - 1)));
		pop();
		pop();
		_stack.push_back(tmp);
	}
}

void		VM::print(void)
{
	if (_stack.size() == 0)
		throw VM::BadInstructionException("Cannot print: empty stack.");
	if ((*(_stack.end() - 1))->getType() != INT8)
		throw VM::BadInstructionException("Cannot print: bad type.");
	char const c[2] = {static_cast<char>(std::stoi((*(_stack.end() - 1))->toString())), 0};
	std::cout << c << std::endl;
}

void		VM::exit(void)
{
}

void		VM::Run(void)
{
	while (_instructions.size() > 0)
	{
		if (!_instructions.empty())
		{
			if (_instructions.front()._inst >= EXIT1)
			{
				if (_instructions.front()._inst == EXIT2)
					throw VM::BadInstructionException("No program ending.");
				return;
			}
			(this->*_functions[_instructions.front()._inst])();
			_instructions.pop_front();
		}
	}
	throw VM::BadInstructionException("No program ending.");
}

VM::BadInstructionException::BadInstructionException(char const *message) : _message(message)
{
}

VM::BadInstructionException::BadInstructionException(BadInstructionException const &rhs)
{
	*this = rhs;
}

VM::BadInstructionException::~BadInstructionException() throw()
{
}

VM::BadInstructionException &VM::BadInstructionException::operator=(BadInstructionException const &rhs)
{
	(void)rhs;
	return *this;
}

const char *VM::BadInstructionException::what() const throw()
{
	return (_message);
}
