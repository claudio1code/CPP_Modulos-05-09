/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudio <claudio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 21:18:41 by claudio           #+#    #+#             */
/*   Updated: 2026/04/19 00:59:14 by claudio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include "AForm.hpp"
#include <iostream>

int main() {
    std::cout << "\n--- TESTE 1: A Fabrica do Estagiario ---" << std::endl;
    
    Intern estagiarioZe;
    AForm* rrf;
    AForm* scf;
    AForm* ppf;
    AForm* lixo;

    scf = estagiarioZe.makeForm("shrubbery creation", "Jardim");
    rrf = estagiarioZe.makeForm("robotomy request", "Bender");
    ppf = estagiarioZe.makeForm("presidential pardon", "Marvin");
    
    lixo = estagiarioZe.makeForm("aumento de salario", "Ze");

    std::cout << "\n--- TESTE 2: Burocracia em Acao ---" << std::endl;
    try {
        Bureaucrat chefe("Zaphod", 1);

        if (rrf) {
            std::cout << "\n[Tratando do Robotomy Request Form]" << std::endl;
            chefe.signForm(*rrf);
            chefe.executeForm(*rrf);
        }

        if (scf) {
            std::cout << "\n[Tratando do Shrubbery Creation Form]" << std::endl;
            chefe.signForm(*scf);
            chefe.executeForm(*scf);
        }

        if (ppf) {
            std::cout << "\n[Tratando do Presidential Pardon Form]" << std::endl;
            chefe.signForm(*ppf);
            chefe.executeForm(*ppf);
        }

    } catch (std::exception &e) {
        std::cerr << "Erro fatal na burocracia: " << e.what() << std::endl;
    }

    std::cout << "\n--- TESTE 3: Limpeza de Memoria (Anti-Leaks) ---" << std::endl;
    if (scf) delete scf;
    if (rrf) delete rrf;
    if (ppf) delete ppf;
    // O 'lixo' é NULL, por isso não precisamos de fazer delete, mas se fizéssemos, delete NULL é seguro em C++.
    if (lixo) delete lixo; 

    std::cout << "Memoria limpa!" << std::endl;
    std::cout << "=============================================\n" << std::endl;

    return 0;
}