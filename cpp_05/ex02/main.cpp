/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudio <claudio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 21:18:41 by claudio           #+#    #+#             */
/*   Updated: 2026/04/19 01:06:08 by claudio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(time(NULL));
    std::cout << "\n--- TESTE 1: SHRUBBERY CREATION FORM ---" << std::endl;
    try {
        Bureaucrat chefe("Zaphod", 1);
        Bureaucrat estagiario("Arthur", 140);
        ShrubberyCreationForm tree("Jardim");

        std::cout << tree << std::endl;

        estagiario.executeForm(tree);

        estagiario.signForm(tree);

        estagiario.executeForm(tree);

        chefe.executeForm(tree);
    } catch (std::exception &e) {
        std::cerr << "Erro fatal: " << e.what() << std::endl;
    }

    std::cout << "\n--- TESTE 2: ROBOTOMY REQUEST FORM ---" << std::endl;
    try {
        Bureaucrat chefe("Zaphod", 1);
        RobotomyRequestForm robo("Bender");

        chefe.signForm(robo);
        
        chefe.executeForm(robo);
        chefe.executeForm(robo);
        chefe.executeForm(robo);
    } catch (std::exception &e) {
        std::cerr << "Erro fatal: " << e.what() << std::endl;
    }

    std::cout << "\n--- TESTE 3: PRESIDENTIAL PARDON FORM ---" << std::endl;
    try {
        Bureaucrat chefe("Zaphod", 1);
        Bureaucrat medio("Ford", 20); 
        PresidentialPardonForm pardon("Marvin");

        medio.signForm(pardon);
        medio.executeForm(pardon);
        chefe.executeForm(pardon);
    } catch (std::exception &e) {
        std::cerr << "Erro fatal: " << e.what() << std::endl;
    }

    std::cout << "\n=============================================" << std::endl;
    std::cout << "Fim dos testes burocráticos!" << std::endl;
    std::cout << "=============================================\n" << std::endl;

    return 0;
}