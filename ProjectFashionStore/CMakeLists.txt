cmake_minimum_required(VERSION 3.29)
project(ProjectFashionStore)

set(CMAKE_CXX_STANDARD 20)

add_executable(ProjectFashionStore main.cpp
        ProductHandler.cpp
        Product.cpp
        Cosmetic.cpp
        Clothing.cpp
        Menu.h
        Menu.cpp
        Management.h
        Management.cpp
        Employee.h
        EmployeeHandler.h
        Employee.cpp
        EmployeeHandler.cpp)
