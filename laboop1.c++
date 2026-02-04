#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;

class Product {
private:
    string name;
    string productionDate;
    string manufacturer;
    double weight;

public:
    // Конструктор без параметров
    Product() : name(""), productionDate(""), manufacturer(""), weight(0.0) {}
    
    // Конструктор с параметрами
    Product(string n, string date, string manuf, double w) 
        : name(n), productionDate(date), manufacturer(manuf), weight(w) {}
    
    // Деструктор
    ~Product() {}
    
    // Геттеры
    string getName() const { return name; }
    string getProductionDate() const { return productionDate; }
    string getManufacturer() const { return manufacturer; }
    double getWeight() const { return weight; }
    
    // Сеттеры
    void setName(string n) { name = n; }
    void setProductionDate(string date) { productionDate = date; }
    void setManufacturer(string manuf) { manufacturer = manuf; }
    void setWeight(double w) { weight = w; }
    
    // Ввод данных
    void input() {
        cout << "Введите название: ";
        cin.ignore();
        getline(cin, name);
        cout << "Введите дату производства (ДД.ММ.ГГГГ): ";
        getline(cin, productionDate);
        cout << "Введите производителя: ";
        getline(cin, manufacturer);
        cout << "Введите вес (кг): ";
        cin >> weight;
    }
    
    // Вывод данных
    void display() const {
        cout << left << setw(20) << name 
             << setw(15) << productionDate 
             << setw(20) << manufacturer 
             << setw(10) << weight << " кг" << endl;
    }
    
    // Проверка наличия производителя
    bool hasManufacturer() const {
        return !manufacturer.empty();
    }
};

// Глобальный массив продуктов
vector<Product> products;

// 1. Ввод элементов массива
void inputProducts() {
    int n;
    cout << "\nВведите количество продуктов: ";
    cin >> n;
    
    products.clear();
    for (int i = 0; i < n; i++) {
        cout << "\n--- Продукт " << (i + 1) << " ---\n";
        Product p;
        p.input();
        products.push_back(p);
    }
    cout << "\nПродукты успешно введены!\n";
}

// 2. Вывод элементов массива
void displayProducts() {
    if (products.empty()) {
        cout << "\nМассив пуст!\n";
        return;
    }
    
    cout << "\n=== СПИСОК ПРОДУКТОВ ===\n";
    cout << left << setw(20) << "Название" 
         << setw(15) << "Дата" 
         << setw(20) << "Производитель" 
         << setw(10) << "Вес" << endl;
    cout << string(65, '-') << endl;
    
    for (size_t i = 0; i < products.size(); i++) {
        cout << (i + 1) << ". ";
        products[i].display();
    }
}

// 3. Сортировка по названию
void sortByName() {
    if (products.empty()) {
        cout << "\nМассив пуст!\n";
        return;
    }
    
    sort(products.begin(), products.end(), 
         [](const Product& a, const Product& b) {
             return a.getName() < b.getName();
         });
    
    cout << "\nПродукты отсортированы по названию!\n";
    displayProducts();
}

// 4. Вывод продуктов с известным производителем
void displayWithManufacturer() {
    if (products.empty()) {
        cout << "\nМассив пуст!\n";
        return;
    }
    
    cout << "\n=== ПРОДУКТЫ С ИЗВЕСТНЫМ ПРОИЗВОДИТЕЛЕМ ===\n";
    cout << left << setw(20) << "Название" 
         << setw(15) << "Дата" 
         << setw(20) << "Производитель" 
         << setw(10) << "Вес" << endl;
    cout << string(65, '-') << endl;
    
    bool found = false;
    for (const auto& p : products) {
        if (p.hasManufacturer()) {
            p.display();
            found = true;
        }
    }
    
    if (!found) {
        cout << "Нет продуктов с известным производителем.\n";
    }
}

// 5. Добавить элемент перед продуктом с заданным весом
void addBeforeWeight() {
    if (products.empty()) {
        cout << "\nМассив пуст!\n";
        return;
    }
    
    double targetWeight;
    cout << "\nВведите вес продукта, перед которым нужно вставить: ";
    cin >> targetWeight;
    
    for (size_t i = 0; i < products.size(); i++) {
        if (products[i].getWeight() == targetWeight) {
            cout << "\nВведите данные нового продукта:\n";
            Product newProduct;
            newProduct.input();
            products.insert(products.begin() + i, newProduct);
            cout << "\nПродукт успешно добавлен!\n";
            return;
        }
    }
    
    cout << "\nПродукт с весом " << targetWeight << " кг не найден!\n";
}

// 6. Изменить последний элемент
void modifyLastProduct() {
    if (products.empty()) {
        cout << "\nМассив пуст!\n";
        return;
    }
    
    cout << "\nТекущий последний продукт:\n";
    products.back().display();
    
    cout << "\nВведите новые данные:\n";
    products.back().input();
    cout << "\nПоследний продукт успешно изменен!\n";
}

// 7. Записать в файл
void saveToFile() {
    if (products.empty()) {
        cout << "\nМассив пуст!\n";
        return;
    }
    
    ofstream file("products.txt");
    if (!file) {
        cout << "\nОшибка открытия файла для записи!\n";
        return;
    }
    
    file << products.size() << endl;
    for (const auto& p : products) {
        file << p.getName() << endl;
        file << p.getProductionDate() << endl;
        file << p.getManufacturer() << endl;
        file << p.getWeight() << endl;
    }
    
    file.close();
    cout << "\nДанные успешно записаны в файл products.txt!\n";
}

// 8. Вывести содержимое файла
void displayFromFile() {
    ifstream file("products.txt");
    if (!file) {
        cout << "\nФайл products.txt не найден!\n";
        return;
    }
    
    int count;
    file >> count;
    file.ignore();
    
    if (count == 0) {
        cout << "\nФайл пуст!\n";
        file.close();
        return;
    }
    
    cout << "\n=== СОДЕРЖИМОЕ ФАЙЛА products.txt ===\n";
    cout << left << setw(20) << "Название" 
         << setw(15) << "Дата" 
         << setw(20) << "Производитель" 
         << setw(10) << "Вес" << endl;
    cout << string(65, '-') << endl;
    
    for (int i = 0; i < count; i++) {
        string name, date, manufacturer;
        double weight;
        
        getline(file, name);
        getline(file, date);
        getline(file, manufacturer);
        file >> weight;
        file.ignore();
        
        cout << (i + 1) << ". " 
             << left << setw(20) << name 
             << setw(15) << date 
             << setw(20) << manufacturer 
             << setw(10) << weight << " кг" << endl;
    }
    
    file.close();
}

void showMenu() {
    cout << "\n========== МЕНЮ ==========\n";
    cout << "1. Ввести элементы массива\n";
    cout << "2. Вывести элементы массива\n";
    cout << "3. Сортировать по названию\n";
    cout << "4. Вывести продукты с производителем\n";
    cout << "5. Добавить элемент перед заданным весом\n";
    cout << "6. Изменить последний элемент\n";
    cout << "7. Записать в файл\n";
    cout << "8. Вывести содержимое файла\n";
    cout << "0. Выход\n";
    cout << "==========================\n";
    cout << "Выберите пункт: ";
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    int choice;
    
    do {
        showMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                inputProducts();
                break;
            case 2:
                displayProducts();
                break;
            case 3:
                sortByName();
                break;
            case 4:
                displayWithManufacturer();
                break;
            case 5:
                addBeforeWeight();
                break;
            case 6:
                modifyLastProduct();
                break;
            case 7:
                saveToFile();
                break;
            case 8:
                displayFromFile();
                break;
            case 0:
                cout << "\nВыход из программы. До свидания!\n";
                break;
            default:
                cout << "\nНеверный выбор! Попробуйте снова.\n";
        }
        
    } while (choice != 0);
    
    return 0;
}
