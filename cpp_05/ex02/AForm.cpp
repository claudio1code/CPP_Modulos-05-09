/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudio <claudio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 22:09:31 by claudio           #+#    #+#             */
/*   Updated: 2026/04/18 23:06:22 by claudio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm() : _name("Default"), _isSigned(false), _sign(150), _exec(150) {}

AForm::AForm(const std::string& name, const int sign, const int exec) : _name(name), _isSigned(false), _sign(sign), _exec(exec) {
	if (sign < 1 || exec < 1)
		throw(GradeTooHighException());
	if (sign > 150 || exec > 150)
		throw(GradeTooLowException());
}

AForm::~AForm() {}

AForm::AForm(const AForm &other) : _name(other._name), _isSigned(other._isSigned), _sign(other._sign), _exec(other._exec) {}

AForm& AForm::operator=(const AForm& other) {
	if (this != &other)
		_isSigned = other._isSigned;
	return (*this);
}

const std::string& AForm::getName() const {
	return (_name);
}

bool AForm::getSigned() const {
	return (_isSigned);
}

int AForm::getSign() const {
	return (_sign);
}

int AForm::getExec() const {
	return (_exec);
}

void AForm::checkExecution(Bureaucrat const &executor) const {
	if (!this->getSigned())
		throw AForm::FormNotSignedException();
	if (executor.getGrade() > this->getExec())
		throw AForm::GradeTooLowException();
}

void AForm::beSigned(const Bureaucrat& bureaucrat)
{
	if (bureaucrat.getGrade() > this->_sign)
		throw AForm::GradeTooLowException();
	this->_isSigned = true;
}

const char* AForm::GradeTooHighException::what() const throw() {
	return ("Grade is too high");
}

const char* AForm::GradeTooLowException::what() const throw() {
	return ("Grade is too low");
}

const char* AForm::FormNotSignedException::what() const throw() {
	return ("Form not signed");
}


std::ostream& operator<<(std::ostream& os, const AForm& obj) {
	os << "O formulario de " << obj.getName();
	if (obj.getSigned())
		os << " está assinado ";
	else
		os << " não está assinado ";
	os << " e requer nota " << obj.getSign() << " para assinar e nota ";
	os << obj.getExec() << " para executar" << std::endl;
	return (os);
}