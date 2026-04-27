#ifndef IDENTIFY_HPP
# define IDENTIFY_HPP

# include "Base.hpp"
# include "A.hpp"
# include "B.hpp"
# include "C.hpp"
# include <iostream>
# include <cstdlib>
# include <ctime>
# include <exception>

void identify(Base* p);
void identify(Base& p);

Base* generate(void);

#endif