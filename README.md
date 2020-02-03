# What is project C--

C-- is a functionally-orientated language that provides a coding experience similar to python and rust while producing 100% backwards compatible C++ logic.

# What is functionally object-orientated

F.O.O is a programming paradigm that accepts the use cases for objects while providing syntax to express the intended transition from state-full to state-less. The goal of FOO is to provide a mechanism for programs receive a system event, attach context to the event and then process the event with context in a functionally.

# C-- Features

* 100% backwards compatible C++ code, libraries. C-- can directly call C++, and C++ can call C--.
* STL implementation as first class citizens
* Compile time reflections
* Touring complete preprocessor.
* Functional programming syntax
* First class concurrent programming
* No speed reduction from native C++
* Embraces the best parts of python and rust
* Built to help IDEs easily implement syntax highlighting, auto-complete, real-time compiling
* Customizable style for company preferences. Code style is required to compile
* Native multi language support
* Scope based memory management with safe borrow checking
* Compiler managed package system
* Friendly syntax - Switch, match, enums, loop

## 100% backwards compatible with C++

C-- compiles into C++ code which is callable by C++ and compatible with the STL your code already uses. C-- can also include C++ headers and use them without any wrappers.

How? C-- uses code uses "target hooks" to write out a native language to compile into. These target hooks (written in Lua) generate basic C++ code. C-- functions are just C++ functions. C-- classes are just C++ classes. 

## STL as first class citizens

String, array, tuple, hash, regex, threads, message passing are all first class citizens. C-- has built in syntax around the most commonly used language tools. The actual implementation of the STL is customizable by changing the lua which selects the STL implementation. 

The hooks are easily editable; targeting complete STL's like QT or boost is a simple as selecting a different target hook.

## Compile time reflections

C-- provides reflections for classes, methods, members, and functions. The reflections are written at compile-time and accessible during run-time for all C-- objects.

## Touring complete preprocessor

Perhaps the most interesting part of C-- is the preprocessor. The C-- language realizes there are many programming cases where the default syntax isn't the best expression method possible. To get around this issue, C-- provides a runtime inside the compiler itself which writes out repetitive code. A few common programming cases are: ORMs, APIs.

## Functional programming syntax

C-- defaults all variables to be immutable. C-- defaults all functions/methods to be stateless. Stateless functions cannot call stateful functions (without explicitly overriding this behavior). 

## First class concurrent programming

C-- provides single word thread and channel creation. Since the language knows which threads have access to which objects, concurrent variable usage without proper protections are built-in. C-- by default applies mutexs of shared data, or allows the user to clearly defined explicit behavior outside the default safety system.

## Default types with no guessing

* i8 - 8bit signed int
* i16 - 16bit signed int
* i32 - 32bit signed int
* i64 - 64bit signed int
* i128 - 128bit signed int
* u8 - 8bit unsigned int
* u16 - 16bit unsigned int
* u32 - 32bit unsigned int
* u64 - 64bit unsigned int
* iu28 - 128bit unsigned int
* f32 - 32bit floating point
* f64 - 64bit floating point
* str - string object


## STL as a first class citizen

C-- believes primitive and stl types should be considered equals. As such STl actions have their own built in syntax for ease of operation. These STL actions use their own set of Lua based target hooks. If a user wants to use their own STL, change the Lua hooks, and now you are using a different STL.

### Strings

Declaration

    let s = "yummy" //A STL string object
    let s2 = 'tasty' //Also a STL string object, double and single quotes are equals
    let raw = "message":i8 //Creates a character signed 8 bit char array
    let raw_uni = "unicode message":i16 //Creates a character signed 16 bit char array

Friendly string arguments

    let random_var = 32 
    "A var message %1, %2 is %3" % { random_var, 3 * 2, "Great"} //Creates a STL string object, with the 3 inserted variables
    "String with #{random_var} and #{4 + 7}" //Vars can also be contained by #{} inside strings for direct replacement

### Arrays

Arrays have feature parity with tuples, except they're size can be changed.

Declaration

    let ary = [0:u64; 5] //Create an array of u64's filled with 5 entries, all 0's
    let ary2 = [1,2,3,4,5] //Basic array creation
    let ary3 = [x * 2 for x in ary2 if x > 2] //Create an array containing [6, 8, 10]
    
Iteration

    foreach x in ary { print(x) } // This will generate a for ( int i = 0... ){} for full speed iteration  


# Goals of C-- Syntax

1. Take the best of many programming languages to create

Features:
