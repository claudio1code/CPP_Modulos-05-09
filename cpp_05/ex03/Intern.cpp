/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudio <claudio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 00:40:32 by claudio           #+#    #+#             */
/*   Updated: 2026/04/19 00:52:05 by claudio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern() {}

Intern::Intern(const Intern& other) {
	(void)other;
}

Intern& Intern::operator=(const Intern& other) {
	(void)other;
	return (*this);
}

Intern::~Intern() {}

AForm* Intern::createShrubbery(const std::string target) {
	return new ShrubberyCreationForm(target);
}

AForm* Intern::createRobotomy(const std::string target) {
	return new RobotomyRequestForm(target);
}

AForm* Intern::createPardon(const std::string target) {
	return new PresidentialPardonForm(target);
}

AForm* Intern::makeForm(std::string name, std::string target) {
	typedef AForm* (Intern::*FormCreator)(const std::string);

	std::string names[] = {
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"
	};

	FormCreator creators[] = {
		&Intern::createShrubbery,
		&Intern::createRobotomy,
		&Intern::createPardon
	};

	for (int i = 0; i < 3; i++) {
		if (names[i] == name) {
			std::cout << "Estágiario cria " << name << std::endl;
			return (this->*creators[i])(target);
		}
	}

	std::cout << "Error: Estágiario não pode criar " << name << ", porquê não existe." << std::endl;
	return NULL;
}