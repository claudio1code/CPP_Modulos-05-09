/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudio <claudio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 20:29:01 by claudio           #+#    #+#             */
/*   Updated: 2026/04/18 22:51:33 by claudio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : _name("Default"), _grade(1) {}

Bureaucrat::Bureaucrat(std::string const &name, int grade) : _name(name){
    if (grade < 1)
        throw GradeTooHighException();
    if (grade > 150)
        throw GradeTooLowException();
    this->_grade = grade;
}

Bureaucrat::Bureaucrat(Bureaucrat const &other) : _name(other._name), _grade(other._grade) {}

Bureaucrat::~Bureaucrat() {}

Bureaucrat& Bureaucrat::operator=(Bureaucrat const &other) {
    _grade = other._grade;
    return (*this);
}

std::string         Bureaucrat::getName() const {
    return (_name);
}
int                 Bureaucrat::getGrade() const {
    return (_grade);
}

void                Bureaucrat::incrementGrade() {
    if (_grade == 1)
        throw GradeTooHighException();
    _grade--;
}
void                Bureaucrat::decrementGrade() {
    if (_grade == 150)
        throw GradeTooLowException();
    _grade++;
}

const char	*Bureaucrat::GradeTooHighException::what() const throw() {
    return ("Grade is too High!");
}

const char	*Bureaucrat::GradeTooLowException::what() const throw() {
    return ("Grade is too Low!");
}

std::ostream& operator<<(std::ostream& os, const Bureaucrat& obj) {
    os << obj.getName() << " bureaucrat with classificate " << obj.getGrade();
    return (os);
}
