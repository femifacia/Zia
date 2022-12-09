# ZIA

## Summary

A C++ API for web services hebergement usings modules (http, ssl, ftp, php, etc...)

## Workflow

![WorkFlow](documentation/Workflow%20Zia.png)

## Os supported
- Windows
- Linux
- MacOs

## Requirement

### On Windows
* Conan 
* CMake 3.17
* Visual Studio 2019
* Php-Cgi [Installation link](https://www.sitepoint.com/how-to-install-php-on-windows/)

### On Linux
* g++
* Conan 
* CMake 3.17
* Php-Cgi [Installation link](https://www.sitepoint.com/how-to-install-php-on-windows/)

### On MacOs
* g++
* Conan
* CMake 3.17
* Php-Cgi [Installation link](https://www.sitepoint.com/how-to-install-php-on-windows/)

## HOW TO COMPILE 

## On Linux

    mkdir build && cd build && conan install .. && cmake ../ -G 'Unix Makefiles' && cmake –build . && make

## On MacOs

    mkdir build && cd build && conan install .. && cmake ../ -G 'Unix Makefiles' && cmake –build . && make

## On Windows

- First on a Shell type this

        mkdir build && cd build && conan install .. && cmake .. 
    
- Lauch the file Zia.sln
- In the solution explorer, go to zia Project Pages / Configuration Properties / C,C++ / Preprocessor / Preprocessor Definitions
- Add "_ITERATOR_DEBUG_LEVEL=0"
- Then, go to zia Project Pages / Configuration Properties / C,C++ / Code Generation / Runtime Library
- Select Multi-threaded DLL (/MD)
- Do the same in all solution of the solution explorer execpt ALL_BUILD
- Finally, for each solution of the solution explorer, go to Project / Project Properties / C, C++ / Language / C++ Language Standard 
- Select Preview - Features from the Latest C++ Working Draft (/std:c++latest)

## HOW TO EXECUTE

### On Linux and MacOs

After the compilation go to the **build** file

Type this

    ./bin/zia

### Windows

After the compilation step launch a new **Debug session** from the VStudio session