#ifndef AFORM_HPP
#define AFORM_HPP

#include <iostream>

class Bureaucrat;

class AForm {
	private:
		const std::string _name;
		bool _isSigned;
		const int _sign;
		const int _exec;
	public:
		AForm();
		AForm(const std::string& name, const int sign, const int exec);
		AForm(const AForm& other);
		AForm& operator=(const AForm& other);
		virtual ~AForm();

		const std::string& getName() const;
		bool getSigned() const;
		int getSign() const;
		int getExec() const;

		virtual void execute(Bureaucrat const &executor) const = 0;
		void checkExecution(Bureaucrat const &executor) const;
		void beSigned(const Bureaucrat& bureaucrat);

		class GradeTooHighException : public std::exception {
			public:
				virtual const char* what() const throw();
		};

		class GradeTooLowException : public std::exception {
			public:
				virtual const char* what() const throw();
		};

		class FormNotSignedException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
};

std::ostream& operator<<(std::ostream& o, const AForm& i);


#endif