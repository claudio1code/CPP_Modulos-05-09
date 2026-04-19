/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudio <claudio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 20:29:01 by claudio           #+#    #+#             */
/*   Updated: 2026/04/18 23:35:12 by claudio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"

Bureaucrat::Bureaucrat() : _name("Default"), _grade(150) {}

Bureaucrat::Bureaucrat(const std::string& name, int grade) : _name(name), _grade(grade) {
	if (grade < 1)
		throw(GradeTooHighException());
	if (grade > 150)
		throw(GradeTooLowException());
}

Bureaucrat::~Bureaucrat() {}

Bureaucrat::Bureaucrat(const Bureaucrat &other) : _name(other._name), _grade(other._grade) {}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other) {
	if (this != &other)
		_grade = other._grade;
	return (*this);
}

const std::string& Bureaucrat::getName() const {
	return (this->_name);
}

int Bureaucrat::getGrade() const {
	return (this->_grade);
}

void Bureaucrat::incrementGrade() {
	if (_grade - 1 < 1)
		throw(GradeTooHighException());
	_grade--;
}

void Bureaucrat::decrementGrade() {
	if (_grade + 1 > 150)
		throw(GradeTooLowException());
	_grade++;
}

void Bureaucrat::executeForm(AForm const &form)
{
	try {
		form.execute(*this);
		std::cout << _name << " executed " << form.getName() << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << _name << " couldn't execute " << form.getName() << " because " << e.what() << std::endl;
	}
}

void Bureaucrat::signForm(AForm& form)
{
	try
	{
		form.beSigned(*this);
		std::cout << this->_name << " signed " << form.getName() << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << this->_name << " couldn't sign " << form.getName() << " because " << e.what() << std::endl;
	}
}


const char	*Bureaucrat::GradeTooHighException::what() const throw() {
    return ("Grade is too High!");
}

const char	*Bureaucrat::GradeTooLowException::what() const throw() {
    return ("Grade is too Low!");
}

std::ostream& operator<<(std::ostream& os, const Bureaucrat& obj) {
    os << obj.getName() << " burocratas com classificação " << obj.getGrade();
    return (os);
}
