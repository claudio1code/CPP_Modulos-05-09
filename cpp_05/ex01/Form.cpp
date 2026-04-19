/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudio <claudio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 22:09:31 by claudio           #+#    #+#             */
/*   Updated: 2026/04/18 23:06:22 by claudio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form() : _name("Default"), _isSigned(false), _sign(150), _exec(150) {}

Form::Form(const std::string& name, const int sign, const int exec) : _name(name), _isSigned(false), _sign(sign), _exec(exec) {
	if (sign < 1 || exec < 1)
		throw(GradeTooHighException());
	if (sign > 150 || exec > 150)
		throw(GradeTooLowException());
}

Form::~Form() {}

Form::Form(const Form &other) : _name(other._name), _isSigned(other._isSigned), _sign(other._sign), _exec(other._exec) {}

Form& Form::operator=(const Form& other) {
	if (this != &other)
		_isSigned = other._isSigned;
	return (*this);
}

const std::string& Form::getName() const {
	return (_name);
}

bool Form::getSigned() const {
	return (_isSigned);
}

int Form::getSign() const {
	return (_sign);
}

int Form::getExec() const {
	return (_exec);
}

void Form::beSigned(const Bureaucrat& bureaucrat)
{
	if (bureaucrat.getGrade() > this->_sign)
		throw Form::GradeTooLowException();
	this->_isSigned = true;
}

const char* Form::GradeTooHighException::what() const throw() {
	return ("Grade is too high");
}

const char* Form::GradeTooLowException::what() const throw() {
	return ("Grade is too low");
}

std::ostream& operator<<(std::ostream& os, const Form& obj) {
	os << "O formulario de " << obj.getName();
	if (obj.getSigned())
		os << " está assinado ";
	else
		os << " não está assinado ";
	os << " e requer nota " << obj.getSign() << " para assinar e nota ";
	os << obj.getExec() << " para executar" << std::endl;
	return (os);
}