cmake_minimum_required(VERSION 3.29)
project(Project)

set(CMAKE_CXX_STANDARD 20)

add_executable(Project main.cpp
        Clothing.cpp
        Cosmetic.cpp
        Employee.cpp
        EmployeeHandler.cpp
        Management.cpp
        Menu.cpp
        Product.cpp
        ProductHandler.cpp)
