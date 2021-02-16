# Automated testing with Boost

Testing C++ code with Boost Unit Test Framework.

## Info

- The zip-file has to be named handin.zip
- The main()-function has to be placed in main.cpp or removed
- Every header file needs the extension .h
- Only works with oving03 (cannonball) at the moment
- Every function has to be declared exactly the same as in the assignment
- The delivered code has to be in a runnable state

## Install Boost

[Boost-1.75.0](http://www.linuxfromscratch.org/blfs/view/svn/general/boost.html)

or

```sh
sudo apt-get install libboost-all-dev
```

## Version

```txt
clang 10.0.0
cmake 3.10.2
Boost 1.75.0
FLTK 1.4.0
```

## Nice to know

To write the output of a command to a file, there are basically 10 commonly used ways.

```txt
          || visible in terminal ||   visible in file   || existing
  Syntax  ||  StdOut  |  StdErr  ||  StdOut  |  StdErr  ||   file   
==========++==========+==========++==========+==========++===========
    >     ||    no    |   yes    ||   yes    |    no    || overwrite
    >>    ||    no    |   yes    ||   yes    |    no    ||  append
          ||          |          ||          |          ||
   2>     ||   yes    |    no    ||    no    |   yes    || overwrite
   2>>    ||   yes    |    no    ||    no    |   yes    ||  append
          ||          |          ||          |          ||
   &>     ||    no    |    no    ||   yes    |   yes    || overwrite
   &>>    ||    no    |    no    ||   yes    |   yes    ||  append
          ||          |          ||          |          ||
 | tee    ||   yes    |   yes    ||   yes    |    no    || overwrite
 | tee -a ||   yes    |   yes    ||   yes    |    no    ||  append
          ||          |          ||          |          ||
 n.e. (*) ||   yes    |   yes    ||    no    |   yes    || overwrite
 n.e. (*) ||   yes    |   yes    ||    no    |   yes    ||  append
          ||          |          ||          |          ||
|& tee    ||   yes    |   yes    ||   yes    |   yes    || overwrite
|& tee -a ||   yes    |   yes    ||   yes    |   yes    ||  append
```
