#include <iostream>
using namespace std;
#include <chrono>
using namespace std::chrono; // Для добавления секунд.
#include <thread>
using namespace std::this_thread; // sleep_for, sleep_until.
#include <fstream> // для файлов
#include <string>
//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------

struct Pipe // Данные о трубе. Нужно для записи данных в файл.
{
    string pipe_name = "Nothing";
    double pipe_length = 0.0;
    int pipe_diameter = 0;
    bool pipe_repair = false; //  режим работы (0 - ГОТОВ; 1- В РЕМОНТЕ)
};
struct Station //Данные о КС
{
    string station_name = "Nothing";
    int station_workshops = 0;
    int station_working_workshops = 0;
    double station_efficiency = 0.0; // ??? (надо у препода спросить, что за эффективность и какая она должна быть. Насколько я понял, это double)
};
//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------
int check_integer(int& int_data) { // ПРОВЕРКИ
    cin >> int_data;
    while (cin.fail() || cin.peek() != '\n' || int_data <= 0)// число должно быть ЧИСЛОМ, большим 0
    {
        cin.clear();
        cin.ignore(10, '\n');
        cout << "Пожалуйста, введите натуральное небольшое число :/ :" << endl;
        cin >> int_data;
    }
    return int_data;

}
//-------------------------------------------------------------------------------------------------------------------------

int check_double(double& double_data) { // ПРОВЕРКИ
    cin >> double_data;
    while (cin.fail() || cin.peek() != '\n' || double_data <= 0)// число должно быть ЧИСЛОМ, большим 0
    {
        cin.clear();
        cin.ignore(10, '\n');
        cout << "Пожалуйста, введите небольшое число, большее 0 (double) :/ :" << endl;
        cin >> double_data;
    }
    return double_data;
}

//-------------------------------------------------------------------------------------------------------------------------
int check_bool(bool& bool_data) { // ПРОВЕРКИ
    cin >> bool_data;
    while (cin.fail() || cin.peek() != '\n')// 0 или 1
    {
        cin.clear();
        cin.ignore(10, '\n');
        cout << "Пожалуйста, введите 0 или 1 :/ :" << endl;
        cin >> bool_data;
    }
    return bool_data;
}
//--------------------------------------------------------------------------------------------------------------------------
int check_mode(int& int_data) { // ПРОВЕРКИ
    cin >> int_data;
    while (cin.fail() || cin.peek() != '\n' || int_data <= 0 || int_data >= 4)// число должно быть ЧИСЛОМ, большим 0
    {
        cin.clear();
        cin.ignore(10, '\n');
        cout << "Пожалуйста, введите натуральное число от 1 до 4 :/ :" << endl;
        cin >> int_data;
    }
    return int_data;

}
//-------------------------------------------------------------------------------------------------------------------------
int check_mode_main(int& int_data) { // ПРОВЕРКИ
    cin >> int_data;
    while (cin.fail() || cin.peek() != '\n' || int_data <= 0 || int_data >= 9)// число должно быть ЧИСЛОМ, большим 0
    {
        cin.clear();
        cin.ignore(10, '\n');
        cout << "Пожалуйста, введите натуральное число от 1 до 8 :/ :" << endl;
        cin >> int_data;
    }
    return int_data;

}
//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------
Pipe Adding_a_pipe() //1. Добавить трубу
{
    Pipe new_pipe; // Берём шаблон сверху и начинаем творить чудеса...
    cout << "-------------------------------------------------------------------------------------------------------" << endl;
    cout << "Добавляем трубу" << endl;
    cout << "-------------------------------------------------------------------------------------------------------" << endl;
    sleep_for(seconds(1));
    cout << "Назовите свою трубу (на инглише, по русски программа понимать не хочет...): " << endl;
    cin.ignore(); //"сотрём предыдущие данные и запишем новые."
    getline(cin, new_pipe.pipe_name); // а-ля 'пиши что хочешь'
    cout << "Укажите длину трубы: " << endl;
    check_double(new_pipe.pipe_length);
    cout << "Укажите диаметр трубы: " << endl;
    check_integer(new_pipe.pipe_diameter);
    cout << "Укажите режим трубы:" << endl;
    cout << "0. Готов;" << endl;
    cout << "1. В ремонте" << endl;
    check_bool(new_pipe.pipe_repair);
    return new_pipe;
}//-------------------------------------------------------------------------------------------------------------------------

 Station Adding_a_compressor_station() { //2. Добавить КС 
     Station new_station;
     cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
     cout << "Добавляем КС:" << endl;
     cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
     sleep_for(seconds(1));
     cout << "Назовите свою КС: " << endl;
     cin.ignore();
     getline(cin, new_station.station_name);
     cout << "Укажите количество цехов: " << endl;
     check_integer(new_station.station_workshops);
     cout << "Укажите количество РАБОЧИХ цехов: " << endl;
     check_integer(new_station.station_working_workshops);
     while (new_station.station_working_workshops > new_station.station_workshops) {
         cout << "Количество рабочих цехов не может быть больше количества всех цехов. Поменяйте значение :/ :" << endl;
         cout << "Укажите количество РАБОЧИХ цехов: " << endl;
         check_integer(new_station.station_working_workshops);
     }
     cout << "Укажите эффективность КС: " << endl;
     check_double(new_station.station_efficiency);
     return new_station;
}
//-------------------------------------------------------------------------------------------------------------------------

void pipe_info(Pipe& new_pipe) { //3. Просмотр всех объектов
    cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Информация о вашей трубе:" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    sleep_for(seconds(1));
    if (new_pipe.pipe_name == "Nothing") {
        cout << "Отсутствуют..." << endl;
        sleep_for(seconds(1));
    }
    else {
        cout << "Имя: " << new_pipe.pipe_name << endl;
        cout << "Длина: " << new_pipe.pipe_length << " метров."<< endl;
        cout << "Диаметр: " << new_pipe.pipe_diameter << " миллиметров." << endl;
        if (new_pipe.pipe_repair == 0) {
            cout << " Статус: Готов" << endl;
        }
        else {
            cout << "Статус: В ремонте" << endl;
        }
        sleep_for(seconds(1));
        cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    }
}

void station_info(Station& new_station) {
    cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Информация о вашей КС:" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    sleep_for(seconds(1));
    if (new_station.station_name == "Nothing") {
        cout << "Отсутствуют..." << endl;
        sleep_for(seconds(1));
        cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    }
    else {
        cout << "Имя: " << new_station.station_name << endl;
        cout << "Количество цехов: " << new_station.station_workshops << " штук." << endl;
        cout << "Количество рабочих цехов: " << new_station.station_working_workshops << " штук." << endl;
        cout << "Эффективность: " << new_station.station_efficiency << endl;
        sleep_for(seconds(1));
        cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    }
}
//-------------------------------------------------------------------------------------------------------------------------

void editing_a_pipe(Pipe& new_pipe) { //4. Редактировать трубу 
    int num_pipe = 0, new_diameter = 0;
    double new_lenght = 0.0;
    string new_name_pipe = "Nothing";
    bool new_repair = false;

    /*cout << "Назовите свою трубу (на инглише, по русски программа понимать не хочет...): " << endl;
    cin >> new_pipe.pipe_name;
    cout << "Укажите длину трубы: " << endl;
    cin >> new_pipe.pipe_length;
    cout << "Укажите диаметр трубы: " << endl;
    cin >> new_pipe.pipe_diameter;
    cout << "Укажите режим трубы:" << endl;
    cout << "0. Готов;" << endl;
    cout << "1. В ремонте" << endl;
    cin >> new_pipe.pipe_repair;*/
    if (new_pipe.pipe_name == "Nothing") {
        cout << "Вы пока не создали трубу :/..." << endl;
        sleep_for(seconds(1));
        cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    }
    else
    {
    cout << "Что хотите поменять?" << endl;
    cout << "1. Имя;" << endl;
    cout << "2. Длина" << endl;
    cout << "3. Диаметр " << endl;
    cout << "4. Режим" << endl;
    check_mode(num_pipe);
    switch (num_pipe)
    {
    case 1:
    {
        cout << "Назовите свою трубу (на инглише, по русски программа понимать не хочет...): " << endl;
        cin.ignore();
        getline(cin, new_name_pipe);
        new_pipe.pipe_name = new_name_pipe;
        break;
    }
    case 2:
    {
        cout << "Укажите длину трубы: " << endl;
        check_double(new_lenght);
        new_pipe.pipe_length = new_lenght;
        break;
    }
    case 3:
    {
        cout << "Укажите диаметр трубы: " << endl;
        check_integer(new_diameter);
        new_pipe.pipe_diameter = new_diameter;
        break;
    }
    case 4:
    {
        cout << "Укажите режим трубы:" << endl;
        cout << "0. Готов;" << endl;
        cout << "1. В ремонте" << endl;
        check_bool(new_repair);
        new_pipe.pipe_repair = new_repair;
        break;
    }
    default:
    {
        cout << "Произошла ошибка. Попробуем снова..." << endl;
        editing_a_pipe(new_pipe);
    }
    }
    pipe_info(new_pipe);
}
}
//-------------------------------------------------------------------------------------------------------------------------

void editing_the_compressor_station(Station& new_station) { //5. Редактировать КС 
    int num_station = 0, new_workshop = 0, new_working_workshop = 0;
    string new_name_station = "nothing";
    double new_efficiency = 0.0;
    /*cout << "Назовите свою КС: " << endl;
    cin >> new_station.station_name;
    cout << "Укажите количество цехов: " << endl;
    cin >> new_station.station_workshops;
    cout << "Укажите количество РАБОЧИХ цехов: " << endl;
    cin >> new_station.station_working_workshops;
    cout << "Укажите эффективность КС: " << endl;
    cin >> new_station.station_efficiency;*/
    if (new_station.station_name == "Nothing") {
        cout << "Вы пока не создали КС :/..." << endl;
        sleep_for(seconds(1));
        cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    }
    else {
        cout << "Что хотите поменять?" << endl;
        cout << "1. Имя;" << endl;
        cout << "2. Количество цехов" << endl;
        cout << "3. Количество рабочих цехов " << endl;
        cout << "4. Эффективность" << endl;
        check_mode(num_station);
        switch (num_station)
        {
        case 1:
        {
            cout << "Назовите свою КС: " << endl;
            cin.ignore();
            getline(cin, new_name_station);
            new_station.station_name = new_name_station;
            break;
        }
        case 2:
        {
            cout << "Укажите количество цехов: " << endl;
            check_integer(new_workshop);
            new_station.station_workshops = new_workshop;
            break;
        }
        case 3:
        {
            cout << "Укажите количество рабочих цехов: " << endl;
            check_integer(new_working_workshop);
            new_station.station_working_workshops = new_working_workshop;
            while (new_station.station_working_workshops > new_station.station_workshops) {
                cout << "Количество рабочих цехов не может быть больше количества всех цехов. Поменяйте значение :/ :" << endl;
                cout << "Укажите количество РАБОЧИХ цехов: " << endl;
                check_integer(new_working_workshop);
                new_station.station_working_workshops = new_working_workshop;
            }
            break;
        }
        case 4:
        {
            cout << "Укажите эффективность КС:" << endl;
            check_double(new_efficiency);
            new_station.station_efficiency = new_efficiency;
            break;
        }
        default:
        {
            cout << "Произошла ошибка. Попробуем снова..." << endl;
            editing_the_compressor_station(new_station);
        }
        }
        station_info(new_station);
    }
}
//-------------------------------------------------------------------------------------------------------------------------

void saving_data(Pipe& pipe_data, Station& station_data) { //6. Сохранить 
    cout << "-----------------------------------------------------------" << endl;
    ofstream fileout("information");
    if (pipe_data.pipe_name == "Nothing") {
        cout << "Вы пока не создали трубу..." << endl;
        sleep_for(seconds(1));
    }
    else {
        cout << "Сохранение данных (труба)..." << endl;
        if (fileout) {
            fileout << "Инфомация о трубе:" << endl;
            fileout << pipe_data.pipe_name << endl;
            fileout << pipe_data.pipe_length << endl;
            fileout << pipe_data.pipe_diameter << endl;
            fileout << pipe_data.pipe_repair << endl;
            sleep_for(seconds(1));
            cout << "Готово!" << endl;
        }
    }
    cout << "------------------------------------------------------------" << endl;
    if (station_data.station_name == "Nothing") {
        cout << "Вы пока не создали КС..." << endl;
        sleep_for(seconds(1));
    }
    else {
        cout << "Сохранение данных (КС)..." << endl;
        if (fileout) {
            fileout << "Инфомация о КС:" << endl;;
            fileout << station_data.station_name << endl;
            fileout << station_data.station_workshops << endl;
            fileout << station_data.station_working_workshops << endl;
            fileout << station_data.station_efficiency << endl;
            sleep_for(seconds(1));
            cout << "Готово!" << endl;
        }
    }
    cout << "------------------------------------------------------------" << endl;
    fileout.close();
}
//-------------------------------------------------------------------------------------------------------------------------

void uploading_data(Pipe& pipe_data, Station& station_data) { //7. Загрузить 
    cout << "-----------------------------------------------------------" << endl;
    ifstream filein("information");
    if (filein) {
        string zero_mean; // Нужно для проверки
        int flag_pipe = 0;
        int flag_station = 0;
        while (getline(filein, zero_mean)) {
            if (zero_mean == "Инфомация о трубе:") {
                cout << "Данные о трубе загружены!" << endl;
                cout << "Информация о трубе:" << endl;
                getline(filein, pipe_data.pipe_name);
                cout << "Имя трубы: " << pipe_data.pipe_name << endl;
                filein >> pipe_data.pipe_length;
                cout << "Длина трубы: " << pipe_data.pipe_length << endl;
                filein >> pipe_data.pipe_diameter;
                cout << "Диаметр трубы: " << pipe_data.pipe_diameter << endl;
                filein >> pipe_data.pipe_repair;
                if (pipe_data.pipe_repair == 0) {
                    cout << "Статус трубы: Готов " << endl;
                }
                else {
                    cout << "Статус трубы: В ремонте" << endl;
                }
                cout << "-----------------------------------------------------------" << endl;
                sleep_for(seconds(1));
                flag_pipe = 1;
            }
            if (zero_mean == "Инфомация о КС:") {
                cout << "Данные о трубе загружены!" << endl;
                cout << "Информация о КС" << endl;
                getline(filein, station_data.station_name);
                cout << "Имя КС: " << station_data.station_name << endl;
                filein >> station_data.station_workshops;
                cout << "Количество цехов: " << station_data.station_workshops << endl;
                filein >> station_data.station_working_workshops;
                cout << "Количество РАБОЧИХ цехов: " << station_data.station_working_workshops << endl;
                filein >> station_data.station_efficiency;
                cout << "Эффективность: " << station_data.station_efficiency << endl;
                cout << "-----------------------------------------------------------" << endl;
                sleep_for(seconds(1));
                flag_station = 1;
            }
        }
            if (flag_pipe == 0) {
                cout << "Вы пока что не создали или не сохраняли информацию о трубе..." << endl;
                cout << "-----------------------------------------------------------" << endl;
                sleep_for(seconds(1));
            }
            if (flag_station == 0) {
                cout << "Вы пока что не создали или не сохраняли информацию о КС..." << endl;
                cout << "-----------------------------------------------------------" << endl;
                sleep_for(seconds(1));
            }
        filein.close();
    }
}
//-------------------------------------------------------------------------------------------------------------------------

void exiting_the_program() { //0. Выход
    cout << "Выход из системы (Работу выполнил студент АС-23-04 Хабаров Артём)..." << endl;
    sleep_for(seconds(2));
    exit(0);

}


//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------

int main()
{
    setlocale(LC_ALL, "Russian"); // Без него консоль не поймёт русский язык и вместо обычного текста выведет набор несвязанных символов
    cout << "Здравствуйте. Добро пожаловать в меню по созданию и редактированию  трубы и КС или НПС!" <<endl;
    sleep_for(seconds(3)); // Задержка на 3 секунды. Исключительно для оформления.
    Pipe pipe0;
    Station station0;
    int number = 0;
    while (true)
    {
    cout << "Пожалуйста, выберите режим и напишите соответствующую цифру:" << endl;
    cout << "1. Добавить трубу;  " << endl;
    cout << "2. Добавить КС;" << endl;
    cout << "3. Просмотр всех объектов; " << endl;
    cout << "4. Редактировать трубу; " << endl;
    cout << "5. Редактировать КС; " << endl;
    cout << "6. Сохранить; " << endl;
    cout << "7. Загрузить; " << endl;
    cout << "8. Выход." << endl;
    check_mode_main(number);


    switch (number)
    {
    case 1:
    {
        pipe0 = Adding_a_pipe();
        pipe_info(pipe0);
        break;
    }
    case 2:
    {
        station0 = Adding_a_compressor_station();
        station_info(station0);
        break;
    }
    case 3:
    {
        pipe_info(pipe0);
        station_info(station0);
        break;
    }
    case 4:
    {
        pipe_info(pipe0);
        editing_a_pipe(pipe0);
        break;
    }
    case 5:
    {
        station_info(station0);
        editing_the_compressor_station(station0);
        break;
    }

    case 6: 
    {
        saving_data(pipe0,station0);
        break;
    }
    case 7: 
    {
        uploading_data(pipe0,station0);
        break;
    }

    case 8:
    {
        exiting_the_program();
        break;
    }

    default:
    {
        cout << "К сожалению, произошла ошибка, попробуем снова..." << endl; // Премию тому, кто сломает код.
        break;
    }

    }

    }
    return 0; // Конечная. Поезд дальше не идёт. Просьба выйти из вагона.
}

/*При запуске программы выводится меню, запрашивающее в бесконечном цикле действие от пользователя.Пример меню: 
1. Добавить трубу 
2. Добавить КС 
3. Просмотр всех объектов 
4. Редактировать трубу 
5. Редактировать КС 
6. Сохранить 
7. Загрузить 
0. Выход*/