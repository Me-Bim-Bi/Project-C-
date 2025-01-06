# This is my C++ project for managing the costs, revenue, and income of a fashion store. 

## Small but important note:
- I use CLion with CMake to code and run this program, so the setup may differ if you use another IDE. For instance, if you are using Microsoft Visual Studio, you will need to modify the code in the Product.cpp file by commenting out or deleting the Product* declaration. Additionally, ensure the language standard is set to C++17 or higher for the program to compile and run correctly.

## Below are the key rules governing the program:

### 1. Product Rules:
- Each product has a unique ID.
- When adding a product:
  - If the product already exists in the system, the user can choose to update the quantity by importing more or leave it unchanged.
  - A new product can only be added if its ID does not already exist in the system.
### 2. Employee Rules:
- Each employee has a unique ID.
- An employee can only be added if their ID does not already exist in the system.

### 3. Find, Edit, or Remove by ID:
- Users can find, edit, or remove a product or employee using their unique ID.
- ID numbers can only be edited if the new ID does not already exist in the system.

### 4. Confirmation Before Changes:
- When editing or removing a product, its information will be displayed first, allowing the user to confirm whether they want to proceed with the changes.

### 5. Data Sorting:
- Data is sorted before being displayed on the screen or saved to a file.


