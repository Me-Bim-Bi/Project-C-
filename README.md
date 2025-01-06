Here is my project in C++ about manage cost, revenue and income of a fashion store.
Here is some basic rules:
- 1 product has only 1 id. The user can only add a product if all information match, only quantity purchase is different, or the product’s id has not exist att all.
- 1 employee has only 1 id. The user can only add a employee if the employee’s id has not exist att all in the system.
- The user can find, edit or remove a product or en employee with the id number. 
- The user can only edit id number if the new id number does not exist in the system. 
- Every time when the user want to edit a product’s information or remove a product, the product’s information will be shown first. The user can chose if they want to change/remove it.

I use CLion with CMake to code and run this program, so the setup may differ if you use another IDE. For instance, if you are using Microsoft Visual Studio, you will need to modify the code in the Product.cpp file by commenting out or deleting the Product* declaration. Additionally, ensure the language standard is set to C++17 or higher for the program to compile and run correctly.
