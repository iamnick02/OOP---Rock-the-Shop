# ROCK_the_SHOP
## 📖 Description
"ROCK_the_SHOP" is a C++ project created as part of the Object-Oriented Programming course. The system is designed to manage an online store specializing in rock-themed products, such as clothing and musical discs. It showcases the use of advanced object-oriented principles to handle employee management, inventory control, and order processing efficiently.

## 📄 Project Requirements
To better understand the initial objectives of the project, you can view the full requirements document here:  
- **[Project Requirements (PDF)](docs/Proiect_POO_2024_final.pdf)**

## 🏆 Key Features
**Employee Management**:
- Includes roles such as managers, order operators, and assistants.
- Calculates salaries based on experience, bonuses, and performance.

**Inventory Management**:
- Adds, removes, and updates stock for products like clothing, CDs, and vintage records.
- Calculates delivery prices and handles product-specific attributes (color, brand, rarity).

**Order Processing**:
- Automatically assigns orders to available operators.
- Validates and processes orders, ensuring compliance with inventory and business rules.

**Reports**:
- Generates detailed performance reports, including:
  - Most orders processed by an operator.
  - Top 3 employees by salary and order value.

**Modular Design**:
- Uses an extensible architecture based on inheritance and polymorphism.


## 🚀 How to Run
- `git clone https://github.com/your-username/ROCK_the_SHOP.git`

Navigate to the project directory:
- `cd ROCK_the_SHOP`
  
Compile the project:
- `g++ *.cpp -o ROCK_the_SHOP`

Run the application:
- `./ROCK_the_SHOP`

## 📂 Documentation
For a detailed explanation of the project structure, class hierarchy, and implementation details, you can refer to the following:

- **[Project Documentation (PDF)](docs/Documentatie_Petrescu_Nicolae_Adrian_324AA.pdf)**: Includes a comprehensive explanation of the code, classes, and their functionalities.

## 💡 Key Concepts Used
**Object-Oriented Design**:
- Inheritance and polymorphism for extensibility.
- Encapsulation to manage employee and product data securely.
  
**Modern C++ Features**:
- Smart pointers (shared_ptr) for safe memory management.
- STL containers like vector and queue for data handling.
  
**Error Handling**:
- Exception-based error handling for robust application logic.
