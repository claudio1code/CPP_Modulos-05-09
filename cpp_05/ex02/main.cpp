/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudio <claudio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 21:18:41 by claudio           #+#    #+#             */
/*   Updated: 2026/04/18 23:18:12 by claudio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"

int main() {
    std::cout << "\n--- TESTE 1: Exceções no Construtor do AForm ---" << std::endl;
    try {
        AForm f1("Contrato Secreto", 0, 50);
    } catch (std::exception &e) {;
        std::cerr << "Erro esperado capturado: " << e.what() << std::endl;
    }

    try {
        AForm f2("Formulario do Lixo", 151, 50);
    } catch (std::exception &e) {
        std::cerr << "Erro esperado capturado: " << e.what() << std::endl;
    }

    std::cout << "\n--- TESTE 2: Assinatura com Sucesso ---" << std::endl;
    try {
        Bureaucrat chefe("Zaphod", 1);
        AForm formA("Aumento de Salario", 10, 5);
        std::cout << formA << std::endl;
        
        chefe.signAForm(formA);
        
        std::cout << formA << std::endl;
    } catch (std::exception &e) {
        std::cerr << "Erro inesperado: " << e.what() << std::endl;
    }

    std::cout << "\n--- TESTE 3: Assinatura Recusada (Nota muito baixa) ---" << std::endl;
    try {
        Bureaucrat estagiario("Arthur", 150);
        AForm formB("Acesso ao Servidor", 50, 50);
        
        std::cout << formB << std::endl;
        
 
        estagiario.signAForm(formB); 
        
        std::cout << formB << std::endl;
    } catch (std::exception &e) {
        std::cerr << "Erro inesperado na execucao: " << e.what() << std::endl;
    }

    return 0;
}