#ifndef FORM_HPP
#define FORM_HPP

#include <iostream>
#include "Bureaucrat.hpp"

class Form {
    private:
        std::string const   _name;
        bool                _isSigned;
        const int           _sign;
        const int           _exec;

    public:
        Form();
        Form(const std::string& name, const int sign, const int exec);
        Form(Form const &other);
        ~Form();
        Form &operator=(Form const &other);

        const std::string& getName() const;
		bool getSigned() const;
		int getSign() const;
		int getExec() const;

		void beSigned(const Bureaucrat& bureaucrat);

		class GradeTooHighException : public std::exception {
			public:
				virtual const char* what() const throw();
		};

		class GradeTooLowException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
};

std::ostream& operator<<(std::ostream& o, const Form& i);


#endif