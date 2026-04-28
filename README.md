# C++ Modules 05-08: Advanced Technical Study Guide

This document is a comprehensive pedagogical resource designed to explain the architectural decisions, memory models, and real-world applications of the concepts covered in the C++ modules (05-08).

---

## Module 05: Exception Handling & Defensive Programming

Exception handling is the art of managing "exceptional" states—events that disrupt the normal flow of a program. In professional software, this prevents crashes and ensures data integrity.

### The Mechanics of Exceptions

#### Stack Unwinding Process

```
EXCEPTION THROW
    ↓
STACK UNWINDING STARTS
main() → processData() → validateGrade() → ❌ THROW
    ↑              ↑                ↑
  catch         Destructors        called
  block           called            automatically
    ↓              ↓                ↓
OBJECTS DESTROYED IN REVERSE ORDER
1. validateGrade() locals
2. processData() locals  
3. main() objects survive (handle exception)
```

#### Exception Safety Levels

| Level | Description | Real Impact |
|-------|-------------|-------------|
| **No Safety** | Resource leaks, invalid state | Memory leaks, crashes |
| **Basic** | No leaks, possible invalid state | Partial failures |
| **Strong** | All or nothing operation | Database transactions |
| **No-Throw** | Never throws | Critical system operations |

#### Why This Matters

When an exception occurs, C++ automatically **unwinds the stack**, destroying objects and cleaning up resources. This prevents memory leaks and system crashes. Without proper exception handling, a single error could corrupt your entire application state.

**Real-World Impact**: Banking systems use exceptions to prevent partial transactions - either the entire transfer succeeds or fails completely, preventing money from disappearing.

#### ex00: Bureaucrat Foundation & Grade Management

##### Exception Hierarchy

```
std::exception
    ↓
GradeTooHighException   GradeTooLowException
    ↓                         ↓
         Bureaucrat (grades 1-150)
```

##### Key Concept: Class Invariants

```cpp
class Bureaucrat {
    const std::string _name;
    int _grade;  // Must stay between 1-150
    
    void validateGrade(int grade) const {
        if (grade < 1) throw GradeTooLowException();
        if (grade > 150) throw GradeTooHighException();
    }
    
public:
    Bureaucrat(const std::string& name, int grade) : _name(name) {
        validateGrade(grade);  // Throws if invalid - object never created
        _grade = grade;
    }
};
```

##### Why This Matters

**Class invariants** are rules that must always be true for an object. When a grade goes outside [1, 150], the object becomes invalid. By throwing exceptions in constructors, we prevent invalid objects from ever existing.

**Real-World Impact**: Banking systems use the same principle - account balances can never be negative. If a withdrawal would cause an overdraft, an exception prevents the operation, protecting financial integrity. This prevents subtle bugs that could corrupt system state.

#### ex01: Form Validation & Execution Chain

##### Form Lifecycle State Machine

```
[CREATED] → beSigned() → [SIGNED] → execute() → [EXECUTED]
     ↓              ↓            ↓            ↓
Grade Check     Grade Check   Form Action   Success/Failure
Bureaucrat ≥     Bureaucrat ≥  Performed     Exception if
Sign Grade       Exec Grade                 requirements
                 Exception if                 not met
                 insufficient
```

##### Key Concept: Precondition Validation

```cpp
class Form {
protected:
    bool _isSigned;
    int _gradeToSign, _gradeToExecute;
    
    void validateGrade(const Bureaucrat& b, int required) const {
        if (b.getGrade() > required) throw GradeTooLowException();
    }
    
public:
    virtual void beSigned(const Bureaucrat& b) = 0;
    virtual void execute(const Bureaucrat& e) const = 0;
};
```

##### Why This Matters

**Precondition validation** ensures operations only execute when all requirements are met. The `execute()` method assumes the form is already signed and the executor has sufficient grade. This separation of validation and action makes code more predictable and safer.

**Real-World Impact**: Medical prescription systems use this pattern - a prescription must be signed by a qualified doctor AND verified by a pharmacist before dispensing. If either validation fails, an exception prevents dangerous medication errors, protecting patient safety.

#### ex02: Form Hierarchy & Specialized Implementation

##### Inheritance Hierarchy

```
AForm (Abstract Interface)
    ↓
ShrubberyCreationForm  RobotomyRequestForm  PresidentialPardonForm
(creates files)         (50% success rate)     (always succeeds)
```

##### Key Concept: Polymorphic Behavior

```cpp
class RobotomyRequestForm : public AForm {
public:
    void execute(const Bureaucrat& executor) const {
        if (rand() % 100 < 50)  // 50% success rate
            std::cout << "Robotomy successful ✓" << std::endl;
        else
            throw RobotomyFailureException("Procedure failed!");
    }
};
```

##### Why This Matters

**Polymorphic behavior** allows different form types to have completely different execution logic while sharing the same interface. Each form can have unique grade requirements and execution behaviors, yet they're all processed uniformly.

**Real-World Impact**: Enterprise Resource Planning (ERP) systems use this pattern - purchase orders, expense reports, and time-off requests all follow different approval workflows but are processed through the same document management system.

#### ex03: Factory Pattern & Dynamic Object Creation

##### Factory Architecture

```
CLIENT CODE → FACTORY (Intern) → CONCRETE OBJECTS
    ↓              ↓                    ↓
makeForm()    String mapping     ShrubberyForm
"robotomy"   to object type     RobotomyForm
               Runtime creation   PardonForm
```

##### Key Concept: String-to-Type Mapping

```cpp
class Intern {
public:
    AForm* makeForm(const std::string& type, const std::string& target) {
        if (type == "shrubbery creation") return new ShrubberyCreationForm(target);
        if (type == "robotomy request") return new RobotomyRequestForm(target);
        if (type == "presidential pardon") return new PresidentialPardonForm(target);
        throw FormTypeNotFoundException("Unknown form type");
    }
};
```

##### Why This Matters

The **Factory Pattern** decouples object creation from object usage. Instead of hard-coding which form type to create, the factory maps strings to objects at runtime. This follows the **Open/Closed Principle** - the system is open for extension (new forms) but closed for modification.

**Real-World Impact**: Graphics applications use factory patterns for plugin systems. Users can select "blur", "sharpen", or "color correction" filters, and the factory creates the appropriate filter object without the main application knowing about specific filter implementations.

---

## Module 06: The C++ Type System (Casting)

C++ provides four specialized cast operators to replace the unsafe "C-style" cast `(type)value`. Using the correct cast tells the compiler (and other developers) exactly what your intention is.

### Comparison of C++ Casts

| Operator | Purpose | Check Level | Failure Result |
| :--- | :--- | :--- | :--- |
| `static_cast` | Meaningful conversions (int to double, related classes) | Compile-time | Won't compile if unsafe |
| `dynamic_cast` | Safe Downcasting (Inheritance) | Runtime (RTTI) | `NULL` (pointer) / `bad_cast` (ref) |
| `reinterpret_cast` | Raw bit reinterpretation (pointer to int) | None | Garbage data if misused |
| `const_cast` | Removing `const` or `volatile` qualifiers | Compile-time | Undefined behavior if original was const |

### Deep Dives

#### ex00: ScalarConverter - String Parsing & Type Conversion

##### Parsing Process

```
STRING INPUT → LEXICAL ANALYSIS → TYPE CONVERSION → OUTPUT
"42.5f"        Identify type     Convert to all      Print all
"nan"          Check special     primitive types     valid types
"'A'"          Handle edge cases  with validation  Handle errors
```

##### Key Concept: Type Validation

```cpp
class ScalarConverter {
public:
    static void convert(const std::string& input) {
        double value = parseToDouble(input);
        
        // Convert with validation
        printChar(value);   // Range: 0-127, printable
        printInt(value);    // Range: INT_MIN to INT_MAX  
        printFloat(value);  // Precision check
        printDouble(value); // Direct conversion
    }
};
```

##### Why This Matters

**String parsing** is fundamental for reading external data. Configuration files, user input, and network data all come as strings that must be converted to appropriate types with proper validation.

**Real-World Impact**: Web servers parse configuration files where "8080" becomes a port number, "0.75" becomes a timeout value, and "true" becomes a boolean. Robust parsing prevents configuration errors from crashing the server.

#### ex01: Serializer - Memory Layout & Data Persistence

##### Memory Representation

```
DATA STRUCTURE → MEMORY LAYOUT → SERIALIZATION → NETWORK TRANSMISSION
struct Data      Bytes in memory    Convert to     Send over network
{char, int,     with padding       raw bytes      as byte stream
 char, double}   & alignment       for storage    to other systems
```

##### Key Concept: Memory as Raw Data

```cpp
struct Data { char c1; int n; char c2; double d; };

class Serializer {
public:
    static void serialize(const Data* data) {
        uintptr_t address = reinterpret_cast<uintptr_t>(data);
        // Treat memory as raw bytes for transmission
    }
};
```

##### Why This Matters

**Memory serialization** converts in-memory objects to byte streams for storage or network transmission. Understanding memory layout (alignment, padding, endianness) is crucial for reliable data persistence.

**Real-World Impact**: Network protocols serialize objects before sending them over the network. The receiver deserializes the bytes back into objects. This enables everything from HTTP requests to database replication across different systems.

#### ex02: Base & Derived - RTTI & Dynamic Casting

##### Virtual Table Structure

```
OBJECT LAYOUT
Base object:     [vtable_ptr][base data]
Derived object:  [vtable_ptr][base data][derived data]
                   ↓                    ↓
              Base vtable         Derived vtable
           [destructor]        [destructor]
           [identify()]         [identify()]
           [process()]          [process()]
                                [derivedMethod()]
```

##### Key Concept: Runtime Type Identification

```cpp
class Base { virtual ~Base() {}; virtual std::string identify() = 0; };

class Derived : public Base {
public:
    void derivedMethod() { /* specific functionality */ }
};

// Safe downcasting
Derived* derived = dynamic_cast<Derived*>(basePtr);
if (derived) derived->derivedMethod();  // Only if actually Derived
```

##### Why This Matters

**RTTI (Run-Time Type Information)** enables safe downcasting and type identification at runtime. The vtable stores type information and function pointers, allowing the program to determine an object's actual type and call the correct methods.

**Real-World Impact**: Plugin systems use RTTI extensively. A video editor knows only about the base `Effect` class but can dynamically cast to `BlurEffect` or `ColorCorrectionEffect` to access specialized functionality, enabling extensible architectures.

---

## Module 07: Templates (Generic Programming)

Templates are "blueprints." They allow you to write code once and let the compiler generate specific versions for every data type you use.

### The Instantiation Process
When you call a template function like `swap<int>()`, the compiler looks at your "blueprint" and creates a physical function in the binary that handles `int`. This is why **templates must be in header files**: the compiler needs the blueprint visible at every point it is used.

#### ex00: Function Templates - Generic Algorithms

##### Template Instantiation

```
TEMPLATE DEFINITION → COMPILER USAGE → CODE GENERATION
template<typename T>   min(5, 3) → T=int     Generated min<int>()
T min(T a, T b) {      min(1.5, 2.7) → T=double    Generated min<double>()
    return (a < b) ? a : b;  min("a", "b") → T=string  Generated min<string>()
}
```

##### Key Concept: Type-Agnostic Functions

```cpp
template<typename T>
T min(T a, T b) {
    return (a < b) ? a : b;  // Works with any comparable type
}

// Usage
int result1 = min(5, 3);           // T = int
double result2 = min(1.5, 2.7);   // T = double
std::string result3 = min("a", "b"); // T = string
```

##### Why This Matters

**Template functions** represent **static polymorphism** - the compiler generates optimized code for each type at compile time. This eliminates virtual function call overhead and enables better optimization through inlining.

**Real-World Impact**: Generic sorting algorithms like `quick_sort<T>` can sort any container of comparable elements - integers, strings, or custom objects - without code duplication. This is the foundation of the STL's algorithm library.

#### ex01: Function Pointers & Higher-Order Functions

##### Function Pointer Architecture

```
ITER FUNCTION → FUNCTION OPTIONS → USAGE EXAMPLES
template<typename T>  printInt()         iter(array, printInt)
void iter(T*, F)      squareInt()        iter(array, squareInt)
    for each i        lambda functions   iter(array, [](x){x*x;})
        function(i)
```

##### Key Concept: Behavior as Parameter

```cpp
template<typename T, typename F>
void iter(T* array, size_t length, F function) {
    for (size_t i = 0; i < length; ++i) {
        function(array[i]);  // Apply any function to each element
    }
}

// Usage
int numbers[] = {1, 2, 3, 4, 5};
iter(numbers, 5, [](int x) { std::cout << x * x << " "; }); // Squares
```

##### Why This Matters

**Higher-order functions** separate traversal logic from operation logic. The `iter` function handles iteration while the passed function defines what to do with each element.

**Real-World Impact**: Data processing pipelines use this pattern extensively. Sensor data flows through filter, transform, and aggregate stages - each stage is a function passed to a generic pipeline executor, enabling flexible data workflows.

#### ex02: Custom Container Class - Memory Management & Deep Copy

##### Array Architecture

```
ARRAY<T> CLASS → MEMORY MANAGEMENT → EXCEPTION SAFETY
template<typename T>  Deep copy semantics    Strong guarantee
T* _elements;       Separate memory for     Operations either
unsigned int _size;  each instance          succeed completely
                    Prevents shallow       or leave unchanged
                    copy bugs
```

##### Key Concept: RAII & Deep Copy

```cpp
template<typename T>
class Array {
private:
    T* _elements;
    unsigned int _size;
    
public:
    Array(unsigned int n) : _elements(new T[n]), _size(n) {}
    
    // Deep copy constructor
    Array(const Array& other) : _elements(new T[other._size]), _size(other._size) {
        for (unsigned int i = 0; i < _size; ++i)
            _elements[i] = other._elements[i];
    }
    
    ~Array() { delete[] _elements; }  // RAII cleanup
};
```

##### Why This Matters

**RAII (Resource Acquisition Is Initialization)** ensures deterministic cleanup. The destructor automatically frees memory, preventing leaks. Deep copy prevents multiple objects from sharing the same memory (shallow copy bug).

**Real-World Impact**: Database connection pools use this pattern. Each connection is a managed resource that must be properly cleaned up. The pool ensures connections are always released, even when exceptions occur, preventing resource exhaustion in production systems.

---

## Module 08: The STL Trinity (Containers, Iterators, Algorithms)

The Standard Template Library (STL) is built on three pillars. Understanding how they interact is the key to modern C++.

1.  **Containers**: Where the data lives (`std::vector`, `std::list`).
2.  **Iterators**: The "bridge" or "universal pointer" that moves through the container.
3.  **Algorithms**: The logic that processes the data (`std::find`, `std::sort`).

### ex00: easyfind - Generic Search with Iterators

##### Iterator Categories

```
ITERATOR HIERARCHY
Input Iterator ← Output Iterator ← Forward Iterator ← Bidirectional ← Random Access
     ↓                ↓                ↓                    ↓              ↓
  std::find        write-only      multi-pass         ++/--          [] + +=
 (read-only)       once            traversal          both ways     random access
```

##### Key Concept: Universal Search

```cpp
template<typename T>
typename T::iterator easyfind(T& container, int value) {
    return std::find(container.begin(), container.end(), value);
}

// Works with any container
std::vector<int> vec;
std::list<int> lst;
auto it1 = easyfind(vec, 42);  // Random access iterator
auto it2 = easyfind(lst, 42);  // Bidirectional iterator
```

##### Why This Matters

**Iterator abstraction** provides a uniform interface for traversing different containers. The same `easyfind` function works with vectors, lists, deques, and sets because they all provide iterators that meet the minimum requirements.

**Real-World Impact**: Database query engines use this pattern. The same search logic works across B-trees, hash tables, and sorted arrays without knowing the internal implementation. This enables flexible data storage while maintaining consistent query interfaces.

### ex01: Span - Algorithmic Complexity & Optimization

##### Algorithm Comparison

```
NAIVE O(N²) → OPTIMIZED O(N LOG N)
For each i     Sort array: [1,2,5,8,9]
  For each j   Find adjacent spans: 1,3,3,1
    |i-j|     Shortest span: 1 (adjacent)
               Longest span: 8 (first-last)
Performance: 1M → 10K operations (100x faster)
```

##### Key Concept: Algorithmic Thinking

```cpp
class Span {
public:
    int shortestSpan() {
        std::vector<int> sorted = _numbers;
        std::sort(sorted.begin(), sorted.end());  // O(N log N)
        
        int minSpan = INT_MAX;
        for (size_t i = 0; i < sorted.size() - 1; ++i) {
            minSpan = std::min(minSpan, sorted[i+1] - sorted[i]);  // O(N)
        }
        return minSpan;
    }
};
```

##### Why This Matters

**Algorithm selection** dramatically impacts performance. The naive O(N²) approach works for small data but becomes unusable for large datasets. The optimized O(N log N) solution uses preprocessing (sorting) to transform a difficult problem into a simple one.

**Real-World Impact**: Financial market analysis systems process millions of price updates to detect arbitrage opportunities. Efficient algorithms are critical - a slow algorithm means missing profitable trades that disappear in milliseconds.

### ex02: MutantStack - Container Extension & Iterator Design

##### MutantStack Architecture

```
STD::STACK → MUTANTSTACK EXTENSION → DUAL FUNCTIONALITY
LIFO only   Inherit + iterators    Stack operations + iteration
push/pop   begin()/end() methods   Sequential access + LIFO access
top()      Expose underlying      Both interfaces available
           container iterators
```

##### Key Concept: Container Extension

```cpp
template<typename T>
class MutantStack : public std::stack<T> {
public:
    // Expose underlying container iterators
    typedef typename std::stack<T>::container_type::iterator iterator;
    
    iterator begin() { return this->c.begin(); }
    iterator end() { return this->c.end(); }
    
    // Inherited: push(), pop(), top()
    // New: iteration capabilities
};
```

##### Why This Matters

**Container extension** allows adding capabilities while maintaining existing functionality. By inheriting from `std::stack` and exposing iterators, we get both LIFO stack operations and sequential iteration.

**Real-World Impact**: Version control systems like Git use this pattern. Commit history is a stack (latest commit on top), but you also need to iterate through history for analysis. This dual interface enables both efficient recent access and full history traversal.

---

```cpp
// Custom exception hierarchy
class MyException : public std::exception {
public:
    virtual const char* what() const throw() { return "My custom error"; }
};

// Exception safety levels
class SafeClass {
    Resource* _resource;
public:
    SafeClass() : _resource(new Resource()) {
        if (!_resource) throw std::bad_alloc();
    }
    
    ~SafeClass() { delete _resource; }  // RAII cleanup
    
    // Copy constructor with strong guarantee
    SafeClass(const SafeClass& other) : _resource(new Resource(*other._resource)) {
        // If allocation fails, original object is unchanged
    }
};
```

### C++ Casts Reference

| Cast | When to Use | Example |
|------|-------------|---------|
| `static_cast<T>` | Known safe conversions | `double d = static_cast<double>(i);` |
| `dynamic_cast<T>` | Polymorphic downcasting | `Derived* d = dynamic_cast<Derived*>(base);` |
| `reinterpret_cast<T>` | Low-level bit manipulation | `uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);` |
| `const_cast<T>` | Remove const (use carefully) | `char* buf = const_cast<char*>(str.c_str());` |

### Templates Quick Start

```cpp
// Function template
template<typename T>
T max(T a, T b) { return (a > b) ? a : b; }

// Class template
template<typename T>
class Container {
    T* _data;
    size_t _size;
public:
    Container(size_t n) : _data(new T[n]), _size(n) {}
    ~Container() { delete[] _data; }
    T& operator[](size_t i) { return _data[i]; }
};

// Template specialization
template<>
const char* max<const char*>(const char* a, const char* b) {
    return (strcmp(a, b) > 0) ? a : b;
}
```

### STL Essentials

```cpp
// Containers
std::vector<int> vec;           // Dynamic array
std::list<int> lst;             // Doubly-linked list  
std::deque<int> dq;             // Double-ended queue
std::stack<int> st;             // LIFO stack
std::map<std::string, int> mp; // Key-value pairs

// Iterators
auto it = vec.begin();          // Iterator to first element
auto rit = vec.rbegin();        // Reverse iterator
auto cit = vec.cbegin();        // Const iterator

// Algorithms
std::find(vec.begin(), vec.end(), value);     // Find element
std::sort(vec.begin(), vec.end());             // Sort container
std::for_each(vec.begin(), vec.end(), func);   // Apply function
std::transform(begin, end, out, func);         // Transform elements
```

### Memory Management Patterns

```cpp
// RAII - Resource Acquisition Is Initialization
class FileHandler {
    FILE* _file;
public:
    FileHandler(const char* filename) : _file(fopen(filename, "r")) {
        if (!_file) throw std::runtime_error("Cannot open file");
    }
    ~FileHandler() { if (_file) fclose(_file); }  // Automatic cleanup
};

// Smart pointers (C++11, but good to know)
std::unique_ptr<int> ptr(new int(42));  // Auto-delete
std::shared_ptr<int> sptr(new int(42)); // Reference counted
```

### Common Patterns

```cpp
// Factory Pattern
class ShapeFactory {
public:
    static Shape* create(const std::string& type) {
        if (type == "circle") return new Circle();
        if (type == "square") return new Square();
        throw std::invalid_argument("Unknown shape type");
    }
};

// Observer Pattern
class Observer {
public:
    virtual void update(const std::string& message) = 0;
};

class Subject {
    std::vector<Observer*> _observers;
public:
    void attach(Observer* obs) { _observers.push_back(obs); }
    void notify(const std::string& msg) {
        for (auto obs : _observers) obs->update(msg);
    }
};
```

---

## Project Structure

```
CPP_Modulos-05-09/
├── cpp_05/          # Exception Handling & Defensive Programming
│   ├── ex00/        # Bureaucrat basics
│   ├── ex01/        # Forms and validation
│   ├── ex02/        # Form hierarchy
│   └── ex03/        # Intern factory pattern
├── cpp_06/          # C++ Type System (Casting)
│   ├── ex00/        # Scalar conversions
│   ├── ex01/        # Serialization
│   └── ex02/        # RTTI and identification
├── cpp_07/          # Templates (Generic Programming)
│   ├── ex00/        # Generic functions
│   ├── ex01/        # Function templates
│   └── ex02/        # Custom containers
├── cpp_08/          # STL Trinity
│   ├── ex00/        # easyfind and iterators
│   ├── ex01/        # Span and algorithmic efficiency
│   └── ex02/        # MutantStack
└── cpp_09/          # Advanced C++ Concepts
    └── [Coming soon]
```

## Compilation & Usage

Each exercise follows the 42 school coding standards and can be compiled using the provided `class_maker.sh` script or manually with:

```bash
c++ -Wall -Wextra -Werror -std=c++98 [source_files] -o [executable_name]
```

### Makefile Pattern

```makefile
NAME = program_name
SRCS = main.cpp Class.cpp AnotherClass.cpp
OBJS = $(SRCS:.cpp=.o)
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
```

## Learning Path

1. **Start with Module 05** - Master exception handling and defensive programming
2. **Proceed to Module 06** - Understand C++ casting and type safety
3. **Continue with Module 07** - Learn templates and generic programming
4. **Master Module 08** - Dive into the STL and its components
5. **Complete with Module 09** - Advanced concepts (when available)

Each module builds upon the previous one, creating a comprehensive understanding of modern C++ programming practices.

---

## Best Practices Summary

### Code Quality
- **Always validate input** - Never trust external data
- **Use RAII** - Let destructors handle cleanup
- **Prefer composition over inheritance** - Reduce coupling
- **Follow the Rule of Three/Five** - Manage resources properly

### Exception Safety
- **Strong guarantee** - Operations either succeed completely or have no effect
- **No leaks** - Resources cleaned up even when exceptions occur
- **Clear error messages** - Make debugging easier
- **Exception hierarchies** - Group related errors

### Template Design
- **Minimal requirements** - Only require what you actually need
- **Concept documentation** - Clearly state template requirements
- **Header-only** - Keep templates in headers for instantiation
- **Specialization sparingly** - Only when truly needed

### STL Usage
- **Choose the right container** - Match container to usage pattern
- **Prefer algorithms over loops** - More readable and optimized
- **Understand iterator categories** - Know what operations are supported
- **Leverage generic programming** - Write reusable code

---

*This comprehensive study guide covers all essential C++ concepts from modules 05-08, providing both theoretical understanding and practical implementation examples. Use it as a reference throughout your learning journey and return to it whenever you need clarification on these fundamental C++ topics.*
