#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;


struct Car
{
    int number;
    string brand;
    string color;
    string steering_position;
    string type;
    string transmission;
};


const int MAX_PARKING_SPOTS = 25;

//--------------------------------------------------------------------------------------------------------------
void CheckInput(int& a, char str[100])
{
    string input;
    while (true)
    {
        cout << str;
        getline(cin, input);

        istringstream stream(input);
        if (stream >> a)
        {
            if (stream.eof())
                break;
            else
                cout << "Ошибка: найдены лишние символы после ввода числа.\n\n";
        }
        else
        {
            cout << "Ошибка ввода! Пожалуйста, введите одно целое числовое значение.\n\n";
        }
    }
}
//--------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------
vector<Car> loadCars()
{
    vector<Car> cars(MAX_PARKING_SPOTS);
    ifstream file("Parking.txt");

    if (file.is_open())
    {
        Car car;

        while (file >> car.number >> car.brand >> car.color >> car.steering_position >> car.type >> car.transmission)
        {
            cars[car.number - 1] = car;
        }
    }

    return cars;
}
//--------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------
void displayCars(const vector<Car>& cars)
{
    cout << "\n---------------------------------------------\nСписок машин на парковке:\n";

    for (int i = 0; i < MAX_PARKING_SPOTS; ++i)
    {
        if (i < cars.size() and cars[i].number != 0)
        {
            const Car& car = cars[i];

            cout << "Место " << i + 1 << ": Марка: " << car.brand << "\n"
            << "   Цвет: " << car.color << "\n"
            << "   Расположение руля: " << car.steering_position << "\n"
            << "   Тип: " << car.type << "\n"
            << "   Тип КПП: " << car.transmission << "\n\n";
        }
        else
        {
            cout << "Место " << i + 1 << ": Свободно\n";
        }
    }
    cout << "\n---------------------------------------------\n\n";
}
//--------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------
void addCar(vector<Car>& cars)
{
    int number;

    cout << "\n---------------------------------------------\n";
    char str[100];
    sprintf(str, "Введите номер машины(1 - %i) : ", MAX_PARKING_SPOTS);
    CheckInput(number, str);

    if (number < 1 or number > MAX_PARKING_SPOTS)
    {
        cout << "Неверный номер машины. Попробуйте снова.";
    }

    else if (cars[number - 1].number != 0)
    {
        cout << "Это место уже занято. Попробуйте другое.";
    }

    else
    {
        Car car;
        car.number = number;
        cout << "Введите марку: ";
        cin >> car.brand;
        cout << "Введите цвет: ";
        cin >> car.color;
        cout << "Расположение руля (левый/правый): ";
        cin >> car.steering_position;
        cout << "Тип (легковой/грузовой): ";
        cin >> car.type;
        cout << "Тип КПП (механическая/автоматическая): ";
        cin >> car.transmission;

        cars[number - 1] = car;
    }
    cout << "\n---------------------------------------------\n\n";
}
//--------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------
void editCar(vector<Car>& cars)
{
    displayCars(cars);

    int number;
    cout << "\n---------------------------------------------\n";
    char str[100] = "Введите номер машины для редактирования: ";
    CheckInput(number, str);

    if (number < 1 or number > MAX_PARKING_SPOTS or cars[number - 1].number == 0)
    {
        cout << "Неверный номер машины.";
    }

    else
    {
        Car& car = cars[number - 1];
        cout << "Редактирование машины:\n";
        cout << "Введите марку (" << car.brand << "): ";
        cin >> car.brand;
        cout << "Введите цвет (" << car.color << "): ";
        cin >> car.color;
        cout << "Расположение руля (левый/правый) (" << car.steering_position << "): ";
        cin >> car.steering_position;
        cout << "Тип (легковой/грузовой) (" << car.type << "): ";
        cin >> car.type;
        cout << "Тип КПП (механическая/автоматическая) (" << car.transmission << "): ";
        cin >> car.transmission;

        cout << "Машина успешно обновлена.";
    }
    cout << "\n---------------------------------------------\n\n";
}
//--------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------
void deleteCar(vector<Car>& cars)
{
    displayCars(cars);

    int number;
    cout << "\n---------------------------------------------\n";
    char str[100] = "Введите номер машины для удаления: ";
    CheckInput(number, str);

    if (number < 1 or number > MAX_PARKING_SPOTS or cars[number - 1].number == 0)
    {
        cout << "Неверный номер машины.";
    }

    else
    {
        const Car& car = cars[number - 1];
        cout << "\nВы уверены, что хотите удалить эту машину?\n";
        cout << "Марка: " << car.brand << "\n"
        << "Цвет: " << car.color << "\n"
        << "Расположение руля: " << car.steering_position << "\n"
        << "Тип: " << car.type << "\n"
        << "Тип КПП: " << car.transmission << "\n\n";


        char confirm;
        bool a = false;
        cout << "Введите 'y' для подтверждения удаления: ";
        cin >> confirm;
        if (confirm == 'y' or confirm == 'Y')
        {
            a = true;
        }
        if (a == true)
        {
            cars[number - 1].number = 0;
            cout << "Машина успешно удалена.\n";
        }
        else
        {
            cout << "Удаление отменено.";
        }
    }
    cout << "\n---------------------------------------------\n\n";
}
//--------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------
void moveCar(vector<Car>& cars)
{
    displayCars(cars);

    int oldNumber, newNumber;
    cout << "\n---------------------------------------------\n";
    char str[100] = "Введите номер машины для перемещения: ";
    CheckInput(oldNumber, str);

    if (oldNumber < 1 or oldNumber > MAX_PARKING_SPOTS or cars[oldNumber - 1].number == 0)
    {
        cout << "Неверный номер машины.";
    }

    else
    {
        cout << "Введите номер нового места (1-" << MAX_PARKING_SPOTS << "): ";
        cin >> newNumber;

        if (newNumber < 1 or newNumber > MAX_PARKING_SPOTS)
        {
            cout << "Неверный номер места.";
        }

        else if (cars[newNumber - 1].number != 0)
        {
            cout << "Это место уже занято. Попробуйте другое.";
        }

        else
        {
            cars[newNumber - 1] = cars[oldNumber - 1];
            cars[oldNumber - 1].number = 0;
            cars[newNumber - 1].number = newNumber;
            cout << "Машина успешно перемещена.";
        }
    }
    cout << "\n---------------------------------------------\n\n";
}
//--------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------
string toLower(const string& str)
{
    string lower_str = str;
    transform(lower_str.begin(), lower_str.end(), lower_str.begin(), ::tolower);
    return lower_str;
}
//--------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------
void searchCars(const vector<Car>& cars)
{
    cout << "\n---------------------------------------------\n";
    if (all_of(cars.begin(), cars.end(), [](const Car& car) { return car.number == 0; }))
    {
        cout << "На парковке нет машин для поиска.";
    }

    else
    {
        int category;
        string search_value;
        cout << "------------------------------\n"
        << "Выберите категорию для поиска : \n"
        << "1. Номер\n"
        << "2. Марка\n"
        << "3. Цвет\n"
        << "4. Расположение руля\n"
        << "5. Тип машины\n"
        << "6. Тип КПП"
        << "\n------------------------------\n\n";

        char str[100] = "Введите номер категории : ";
        CheckInput(category, str);

        if (category != 1 and category != 2 and category != 3 and category != 4 and category != 5 and category != 6)
        {
            cout << "Неверная категория поиска.";
        }

        else
        {
            cout << "Введите значение для поиска: ";
            cin >> search_value;
            string search_value_lower = toLower(search_value);

            cout << "Результаты поиска:\n";
            bool found = false;

            for (const Car& car : cars)
            {
                bool match = false;
                switch (category)
                {
                    case 1:
                        match = (to_string(car.number) == search_value);
                        break;

                    case 2:
                        match = (toLower(car.brand) == search_value_lower);
                        break;

                    case 3:
                        match = (toLower(car.color) == search_value_lower);
                        break;

                    case 4:
                        match = (toLower(car.steering_position) == search_value_lower);
                        break;

                    case 5:
                        match = (toLower(car.type) == search_value_lower);
                        break;

                    case 6:
                        match = (toLower(car.transmission) == search_value_lower);
                        break;
                }

                if (match)
                {
                    found = true;
                    cout << "Марка: " << car.brand << "\n"
                    << "Цвет: " << car.color << "\n"
                    << "Расположение руля: " << car.steering_position << "\n"
                    << "Тип: " << car.type << "\n"
                    << "Тип КПП: " << car.transmission << "\n\n";
                }
            }

            if (!found)
            {
                cout << "Машины по данному запросу не найдены.";
            }
        }
    }
    cout << "\n---------------------------------------------\n\n";
}
//--------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------
void saveCars(const vector<Car>& cars)
{
    ofstream file("Parking.txt");
    for (const Car& car : cars)
    {
        if (car.number != 0)
        {
            file << car.number << " " << car.brand << " " << car.color << " " << car.steering_position << " " << car.type << " " << car.transmission << "\n";
        }
    }
}
//--------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------
bool Confirm(char str2[100])
{
    char confirm;
    cout << str2;
    cin >> confirm;
    return (confirm == 'y' or confirm == 'Y');
}
//--------------------------------------------------------------------------------------------------------------

int main() {
    vector<Car> cars(MAX_PARKING_SPOTS);
    cars = loadCars();
    int choice;
    char str[100] = "Выберите действие: ";
    char str2[100] = "Введите 'y' для подтверждения выхода: ";

    do {
        cout << "\n---------------------------------------------\n"
        << "1. Показать списк машин\n"
        << "2. Добавить машину\n"
        << "3. Редактировать машину\n"
        << "4. Удалить машину\n"
        << "5. Переместить машину\n"
        << "6. Поиск машин\n"
        << "7. Выйти\n"
        << "---------------------------------------------\n\n";
        CheckInput(choice, str);

        switch (choice) {
            case 1:
                displayCars(cars);
                break;

            case 2:
                addCar(cars);
                saveCars(cars);
                break;

            case 3:
                editCar(cars);
                saveCars(cars);
                break;

            case 4:
                deleteCar(cars);
                saveCars(cars);
                break;

            case 5:
                moveCar(cars);
                saveCars(cars);
                break;

            case 6:
                searchCars(cars);
                break;

            case 7:
                if (Confirm(str2))
                {
                    cout << "Выход...\n";
                }
                else
                {
                    choice = 0;
                }
                break;

            default:
                cout << "Неверный выбор, попробуйте снова.\n";
                break;
        }
    } while (choice != 7);

    return 0;
}
