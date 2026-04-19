/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudio <claudio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 21:18:41 by claudio           #+#    #+#             */
/*   Updated: 2026/04/18 21:27:35 by claudio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"


int main() {
    std::cout << "\n--- TESTE 1: Instanciação Valida e Operador << ---" << std::endl;
    try {
        Bureaucrat normal("Claudio", 42);
        std::cout << "Sucesso: " << normal << std::endl;
    } catch (std::exception &e) {
        std::cerr << "Erro inesperado: " << e.what() << std::endl;
    }

    std::cout << "\n--- TESTE 2: Nota Alta Demais (Excecao no Construtor) ---" << std::endl;
    try {
        Bureaucrat tooHigh("CEO", 0);
        std::cout << tooHigh << std::endl;
    } catch (std::exception &e) {
        std::cerr << "Erro esperado capturado: " << e.what() << std::endl;
    }

    std::cout << "\n--- TESTE 3: Nota Baixa Demais (Excecao no Construtor) ---" << std::endl;
    try {
        Bureaucrat tooLow("Estagiario", 151);
        std::cout << tooLow << std::endl;
    } catch (std::exception &e) {
        std::cerr << "Erro esperado capturado: " << e.what() << std::endl;
    }

    std::cout << "\n--- TESTE 4: Promocao Ilegal (incrementGrade) ---" << std::endl;
    try {
        Bureaucrat boss("Chefe", 2);
        std::cout << boss << std::endl;
        
        boss.incrementGrade();
        std::cout << "Apos 1 promocao: " << boss << std::endl;
        
        boss.incrementGrade();
        std::cout << "ERRO, o meu throw falhou!" << std::endl;
    } catch (std::exception &e) {
        std::cerr << "Erro de promocao capturado: " << e.what() << std::endl;
    }

    std::cout << "\n--- TESTE 5: Despromocao Ilegal (decrementGrade) ---" << std::endl;
    try {
        Bureaucrat noob("Noob", 149);
        std::cout << noob << std::endl;
        
        noob.decrementGrade(); 
        std::cout << "Apos 1 despromocao: " << noob << std::endl;
        
        noob.decrementGrade();
        std::cout << "ERRO, O meu throw falhou!" << std::endl;
    } catch (std::exception &e) {
        std::cerr << "Erro de despromocao capturado: " << e.what() << std::endl;
    }

    std::cout << "\n=============================================" << std::endl;
    std::cout << "Fim dos testes. O programa chegou ao fim vivo!" << std::endl;
    std::cout << "=============================================\n" << std::endl;

    return 0;
}
