#include "OrderManager.h"
#include "Reports.h"

using namespace std;

void manageEmployees(EmployeeManager& empManager);
void manageInventory(InventoryManager& invManager);
void processOrders(OrderManager& orderManager);
void generateReports(EmployeeManager& empManager);

int main()
{
    EmployeeManager employeeManager;
    InventoryManager inventoryManager;

    vector<shared_ptr<OperatorComenzi>> operators =
    {
        make_shared<OperatorComenzi>(2, "Maria", "Ionescu", "2980804123456", "15-06-2018"),
        make_shared<OperatorComenzi>(3, "Alex", "Pop", "1990501123456", "20-02-2023"),
        make_shared<OperatorComenzi>(4, "Elena", "Marin", "2980103123456", "05-03-2021")
    };
    OrderManager orderManager(operators, inventoryManager);

    employeeManager.addEmployee(make_shared<Manager>(1, "Ion", "Popescu", "1990401123456", "01-01-2015"));
    for (auto& operatorComenzi : operators)
    {
        employeeManager.addEmployee(operatorComenzi);
    }

    employeeManager.addEmployee(make_shared<Asistent>(5, "Elena", "Mocanu", "2960508123456", "01-06-2019"));
    employeeManager.addEmployee(make_shared<Asistent>(6, "Dan", "Niculescu", "1950122123456", "15-11-2021"));

    inventoryManager.addProduct(make_shared<Clothing>("Jacheta Rock Star", 10, 250.0, "C001", "Negru", "RockLeather"));
    inventoryManager.addProduct(make_shared<Clothing>("Tricou Rock", 15, 150.0, "C002", "Alb", "RockWear"));
    inventoryManager.addProduct(make_shared<Clothing>("Geaca Punk", 8, 280.0, "C003", "Rosu", "PunkStyle"));
    inventoryManager.addProduct(make_shared<Clothing>("Tricou Metal", 20, 360.0, "C004", "Gri", "MetalCore"));
    inventoryManager.addProduct(make_shared<Clothing>("Hanorac Rock", 12, 150.0, "C005", "Albastru", "RockWear"));
    inventoryManager.addProduct(make_shared<Clothing>("Pantaloni Piele", 6, 200.0, "C006", "Negru", "RockLeather"));
    inventoryManager.addProduct(make_shared<Clothing>("Vesta Denim", 15, 120.0, "C007", "Albastru", "RockDenim"));
    inventoryManager.addProduct(make_shared<Clothing>("Tricou Band", 25, 245.0, "C008", "Negru", "BandMerch"));

    inventoryManager.addProduct(make_shared<Disc>("Classic Rock Anthems", 5, 300.0, "D001", "Warner Music", "2020-05-20", "Various Artists", "Rock Hits Collection"));
    inventoryManager.addProduct(make_shared<Disc>("Modern Rock", 8, 250.0, "D002", "Sony Music", "2021-03-15", "Various Artists", "Rock Legends"));
     inventoryManager.addProduct(make_shared<Disc>("Best of Metal", 10, 280.0, "D003", "Metal Records", "2022-01-15", "Various Artists", "Metal Collection"));
    inventoryManager.addProduct(make_shared<Disc>("Punk Classics", 7, 260.0, "D004", "Punk Label", "2021-08-20", "Various Artists", "Punk Anthology"));
    inventoryManager.addProduct(make_shared<Disc>("Blues Masters", 6, 290.0, "D005", "Blues Records", "2022-03-10", "Various Artists", "Blues Collection"));
    inventoryManager.addProduct(make_shared<Disc>("Progressive Rock", 4, 310.0, "D006", "Prog Records", "2021-11-25", "Various Artists", "Prog Masters"));

    inventoryManager.addProduct(make_shared<VintageDisc>("The Wall", 2, 480.0, "V003", "Harvest", "1979-11-30", "Pink Floyd", "The Wall", true, 4));
    inventoryManager.addProduct(make_shared<VintageDisc>("Master of Reality", 3, 460.0, "V004", "Vertigo", "1971-07-21", "Black Sabbath", "Master", true, 5));
    inventoryManager.addProduct(make_shared<VintageDisc>("In Rock", 2, 470.0, "V005", "Harvest", "1970-06-03", "Deep Purple", "In Rock", true, 4));
    inventoryManager.addProduct(make_shared<VintageDisc>("Paranoid", 1, 520.0, "V006", "Vertigo", "1970-09-18", "Black Sabbath", "Paranoid", true, 5));

    if (!employeeManager.checkOperationalStatus() || !inventoryManager.checkStockValidity())
    {
        cout << "Magazinul nu poate functiona. Se inchide programul.\n";
        return 1;
    }

    orderManager.startSimulation();

    bool running = true;
    while (running)
    {
        cout << "\n=== Meniu Principal ===\n";
        cout << "1. Gestiune Angajati\n";
        cout << "2. Gestiune Stoc\n";
        cout << "3. Procesare Comenzi\n";
        cout << "4. Generare Rapoarte\n";
        cout << "5. Iesire\n";
        cout << "Selectati o optiune: ";
        int option;
        cin >> option;

        switch (option)
        {
        case 1:
            manageEmployees(employeeManager);
            break;
        case 2:
            manageInventory(inventoryManager);
            break;
        case 3:
            processOrders(orderManager);
            break;
        case 4:
            generateReports(employeeManager);
            break;
        case 5:
            cout << "Iesire din program.\n";
            orderManager.stopSimulation();
            running = false;
            break;
        default:
            cout << "Optiune invalida. Incercati din nou.\n";
            break;
        }
    }

    return 0;
}

void manageEmployees(EmployeeManager& empManager)
{
    cout << "\n=== Gestiune Angajati ===\n";
    cout << "1. Adauga Angajat\n";
    cout << "2. Sterge Angajat\n";
    cout << "3. Modifica Angajat\n";
    cout << "4. Afiseaza Toti Angajatii\n";
    cout << "5. Inapoi la meniul principal\n";
    cout << "Selectati o optiune: ";
    int option;
    cin >> option;

    switch (option)
    {
    case 1:
    {
        string firstName, lastName, CNP, hireDate;
        int id, employeeType;

        cout << "ID: ";
        cin >> id;
        cout << "Prenume: ";
        cin.ignore();
        getline(cin, firstName);
        cout << "Nume: ";
        getline(cin, lastName);
        cout << "CNP: ";
        cin >> CNP;
        cout << "Data Angajarii (dd-mm-yyyy): ";
        cin >> hireDate;

        if (empManager.getEmployee(id) != nullptr)
        {
            cout << "Un angajat cu acest ID exista deja.\n";
            break;
        }

        if (!Employee::validateCNP(CNP))
        {
            cout << "CNP invalid.\n";
            break;
        }

        if (!Employee::isValidDate(hireDate))
        {
            cout << "Data angajarii nu este valida.\n";
            break;
        }

        cout << "\nSelectati tipul de angajat:\n";
        cout << "1. Manager\n";
        cout << "2. Operator Comenzi\n";
        cout << "3. Asistent\n";
        cout << "Tipul angajatului: ";
        cin >> employeeType;

        shared_ptr<Employee> newEmployee;
        try {
            switch (employeeType) {
                case 1:
                    newEmployee = make_shared<Manager>(id, firstName, lastName, CNP, hireDate);
                    break;
                case 2:
                    newEmployee = make_shared<OperatorComenzi>(id, firstName, lastName, CNP, hireDate);
                    break;
                case 3:
                    newEmployee = make_shared<Asistent>(id, firstName, lastName, CNP, hireDate);
                    break;
                default:
                    cout << "Tip de angajat invalid.\n";
                    break;
            }

            if (newEmployee) {
                empManager.addEmployee(newEmployee);
                cout << "Angajat adaugat cu succes ca " << newEmployee->getRole() << ".\n";
            }
        }
        catch (const invalid_argument& e) {
            cout << "Eroare la adaugarea angajatului: " << e.what() << "\n";
        }
        break;
    }
    case 2:
    {
        int id;
        cout << "ID angajat de sters: ";
        cin >> id;
        empManager.removeEmployee(id);
        break;
    }
    case 3:
    {
        int id;
        string newName;
        cout << "ID angajat de modificat: ";
        cin >> id;
        cout << "Nume nou: ";
        cin >> newName;
        empManager.updateEmployeeInfo(id, newName);
        break;
    }
    case 4:
    {
        for (const auto& emp : empManager.getAllEmployees())
        {
            emp->display();
        }
        break;
    }
    case 5:
        return;
    default:
        cout << "Optiune invalida. Incercati din nou.\n";
        break;
    }
}

void manageInventory(InventoryManager& invManager)
{
    cout << "\n=== Gestiune Stoc ===\n";
    cout << "1. Adauga Produs\n";
    cout << "2. Sterge Produs\n";
    cout << "3. Modifica Stoc\n";
    cout << "4. Afiseaza Produse\n";
    cout << "5. Inapoi la meniul principal\n";
    cout << "Selectati o optiune: ";
    int option;
    cin >> option;
    cin.ignore();

    switch (option)
    {
    case 1:
    {
        int productType;
        cout << "Selectati tipul de produs:\n";
        cout << "1. Articol vestimentar\n";
        cout << "2. Disc\n";
        cout << "3. Disc Vintage\n";
        cout << "Tipul produsului: ";
        cin >> productType;
        cin.ignore();

        string name, uniqueCode, color, brand, recordLabel, releaseDate, band, albumName;
        int stock, rarityCoefficient;
        float basePrice;
        bool isMintCondition;

        cout << "Nume Produs: ";
        getline(cin, name);
        cout << "Stoc: ";
        cin >> stock;
        cout << "Pret Baza: ";
        cin >> basePrice;
        cin.ignore();
        cout << "Cod Unic: ";
        getline(cin, uniqueCode);

        if (invManager.productExists(uniqueCode))
        {
            cout << "Un produs cu acest cod unic exista deja.\n";
            break;
        }

        switch (productType)
        {
        case 1: // Articol vestimentar
            cout << "Culoare: ";
            getline(cin, color);
            cout << "Brand: ";
            getline(cin, brand);
            invManager.addProduct(make_shared<Clothing>(name, stock, basePrice, uniqueCode, color, brand));
            break;
        case 2: // Disc
            cout << "Casa de discuri: ";
            getline(cin, recordLabel);
            cout << "Data lansarii: ";
            getline(cin, releaseDate);
            cout << "Trupa: ";
            getline(cin, band);
            cout << "Numele albumului: ";
            getline(cin, albumName);
            invManager.addProduct(make_shared<Disc>(name, stock, basePrice, uniqueCode, recordLabel, releaseDate, band, albumName));
            break;
        case 3: // Disc Vintage
            cout << "Casa de discuri: ";
            getline(cin, recordLabel);
            cout << "Data lansarii: ";
            getline(cin, releaseDate);
            cout << "Trupa: ";
            getline(cin, band);
            cout << "Numele albumului: ";
            getline(cin, albumName);
            cout << "Conditie mint (1 = da, 0 = nu): ";
            cin >> isMintCondition;
            cout << "Coeficient de raritate (1-5): ";
            cin >> rarityCoefficient;
            invManager.addProduct(make_shared<VintageDisc>(name, stock, basePrice, uniqueCode, recordLabel, releaseDate, band, albumName, isMintCondition, rarityCoefficient));
            break;
        default:
            cout << "Tipul de produs introdus este invalid.\n";
            break;
        }

        cout << "Produs adaugat cu succes.\n";
        break;
    }
    case 2:
    {
        // Sterg produs
        string uniqueCode;
        cout << "Cod unic produs de sters: ";
        getline(cin, uniqueCode);
        invManager.removeProduct(uniqueCode);
        cout << "Produs sters cu succes.\n";
        break;
    }
    case 3:
    {
        // Modific stoc
        string uniqueCode;
        int newStock;
        cout << "Cod unic produs: ";
        getline(cin, uniqueCode);
        cout << "Stoc nou: ";
        cin >> newStock;
        cin.ignore();
        invManager.updateStock(uniqueCode, newStock);
        cout << "Stoc actualizat cu succes.\n";
        break;
    }
    case 4:
    {
        // Afisez produse
        invManager.displayAllProducts();
    }
    case 5:
        // Inapoi la meniul principal
        return;
    default:
        cout << "Optiune invalida. Incercati din nou.\n";
        break;
    }
}

void processOrders(OrderManager& orderManager)
{
    cout << "\nProcesarea comenzilor in asteptare...\n";
    orderManager.loadOrdersFromFile("orders.csv");
    orderManager.processWaitingOrders();
    cout << "\nComenzi procesate. Situatia actuala:\n";
    orderManager.displayOperatorStatus();
}

void generateReports(EmployeeManager& empManager)
{
    cout << "Generarea rapoartelor...\n";
    empManager.reportMostOrdersProcessed("MostOrdersProcessedReport.csv");
    empManager.reportTop3MostValuableOrders("Top3MostValuableOrdersReport.csv");
    empManager.reportTop3HighestSalaries("Top3HighestSalariesReport.csv");
    cout << "Rapoarte generate cu succes.\n";
}
