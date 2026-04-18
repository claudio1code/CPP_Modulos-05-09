#ifndef FORM_HPP
# define FORM_HPP

# include <iostream>

class Buroucrat {
    private:
        const std::string   _name;
        int                 _grade;
        
    public:
        Buroucrat();
        Buroucrat(std::string const &name, int grade);
        ~Buroucrat();
        Buroucrat(Buroucrat const &src);
        Buroucrat &operator=(Buroucrat const &src);

        const std::string   getName() const;
        int                 getGrade() const;

};
#endif