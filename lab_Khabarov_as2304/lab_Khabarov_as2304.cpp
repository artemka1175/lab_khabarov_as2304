#include <iostream>
using namespace std;
#include <chrono>
using namespace std::chrono; // Для добавления секунд.
#include <thread>
using namespace std::this_thread; // sleep_for, sleep_until.
//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------

struct Pipe // Данные о трубе. Нужно для записи данных в файл.
{
    string pipe_name = "Nothing";
    double pipe_length = 0.0;
    int pipe_diameter = 0;
    bool pipe_repair = false; //  режим работы (в ремонте)
};
struct Station //Данные о КС
{
    string station_name = "Nothing";
    int station_workshops = 0;
    int station_working_workshops = 0;
    double station_efficiency = 0.0; //???
};
//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------
Pipe Adding_a_pipe() //1. Добавить трубу
{
    Pipe new_pipe; // Берём шаблон сверху и начинаем творить чудеса...
    setlocale(LC_ALL, "Russian");
    cout << "-------------------------------------------------------------------------------------------------------" << endl;
    cout << "Добавляем трубу" << endl;
    cout << "-------------------------------------------------------------------------------------------------------" << endl;
    sleep_for(seconds(1));
    cout << "Назовите свою трубу (на инглише, по русски программа понимать не хочет...): " << endl;
    cin >> new_pipe.pipe_name;
    cout << "Укажите длину трубы: " << endl;
    cin >> new_pipe.pipe_length;
    cout << "Укажите диаметр трубы: " << endl;
    cin >> new_pipe.pipe_diameter;
    cout << "Укажите режим трубы:" << endl;
    cout << "0. Готов;" << endl;
    cout << "1. В ремонте" << endl;
    cin >> new_pipe.pipe_repair;
    return new_pipe;
}//-------------------------------------------------------------------------------------------------------------------------

 Station Adding_a_compressor_station() { //2. Добавить КС 
     setlocale(LC_ALL, "Russian");
     Station new_station;
     cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
     cout << "Добавляем КС:" << endl;
     cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
     sleep_for(seconds(1));
     cout << "Назовите свою КС: " << endl;
     cin >> new_station.station_name;
     cout << "Укажите количество цехов: " << endl;
     cin >> new_station.station_workshops;
     cout << "Укажите количество РАБОЧИХ цехов: " << endl;
     cin >> new_station.station_working_workshops;
     cout << "Укажите эффективность КС: " << endl;
     cin >> new_station.station_efficiency;
     return new_station;
}
//-------------------------------------------------------------------------------------------------------------------------

void pipe_info(Pipe new_pipe) { //3. Просмотр всех объектов
    cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Информация о вашей трубе:" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    sleep_for(seconds(1));
    if (new_pipe.pipe_name == "Nothing") {
        cout << "Отсутствуют..." << endl;
        sleep_for(seconds(1));
        cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
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

void station_info(Station new_station) {
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

void editing_a_pipe(Pipe new_pipe) { //4. Редактировать трубу 
    int num_pipe = 0, new_lenght,new_diameter;
    string new_name_pipe;
    bool new_repair;
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
    cout << "Что хотите поменять?" << endl;
    cout << "1. Имя;" << endl;
    cout << "2. Длина" << endl;
    cout << "3. Диаметр " << endl;
    cout << "4. Режим" << endl;
    cin >> num_pipe;
    switch (num_pipe)
    {
    case 1:
    {
        cout << "Назовите свою трубу (на инглише, по русски программа понимать не хочет...): " << endl;
        cin >> new_name_pipe;
        new_pipe.pipe_name = new_name_pipe;
        break;
    }
    case 2:
    {
        cout << "Укажите длину трубы: " << endl;
        cin >> new_lenght;
        new_pipe.pipe_length = new_lenght;
        break;
    }
    case 3:
    {
        cout << "Укажите диаметр трубы: " << endl;
        cin >> new_diameter;
        new_pipe.pipe_diameter = new_diameter;
        break;
    }
    case 4:
    {
        cout << "Укажите режим трубы:" << endl;
        cout << "0. Готов;" << endl;
        cout << "1. В ремонте" << endl;
        cin >> new_repair;
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
//-------------------------------------------------------------------------------------------------------------------------

void editing_the_compressor_station(Station new_station) { //5. Редактировать КС 
    int num_station = 0, new_workshop, new_working_workshop;
    string new_name_station;
    double new_efficiency;
    /*cout << "Назовите свою КС: " << endl;
    cin >> new_station.station_name;
    cout << "Укажите количество цехов: " << endl;
    cin >> new_station.station_workshops;
    cout << "Укажите количество РАБОЧИХ цехов: " << endl;
    cin >> new_station.station_working_workshops;
    cout << "Укажите эффективность КС: " << endl;
    cin >> new_station.station_efficiency;*/
    cout << "Что хотите поменять?" << endl;
    cout << "1. Имя;" << endl;
    cout << "2. Количество цехов" << endl;
    cout << "3. Количество рабочих цехов " << endl;
    cout << "4. Эффективность" << endl;
    cin >> num_station;
    switch (num_station)
    {
    case 1:
    {
        cout << "Назовите свою КС: " << endl;
        cin >> new_name_station;
        new_station.station_name = new_name_station;
        break;
    }
    case 2:
    {
        cout << "Укажите количество цехов: " << endl;
        cin >> new_workshop;
        new_station.station_workshops = new_workshop;
        break;
    }
    case 3:
    {
        cout << "Укажите количество рабочих цехов: " << endl;
        cin >> new_working_workshop;
        new_station.station_working_workshops = new_working_workshop;
        break;
    }
    case 4:
    {
        cout << "Укажите эффективность КС:" << endl;
        cin >> new_efficiency;
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
//-------------------------------------------------------------------------------------------------------------------------

void saving_data() { //6. Сохранить 
    cout << "Hello!" << endl;
    cout << "I am a sample function";
}
//-------------------------------------------------------------------------------------------------------------------------

void uploading_data() { //7. Загрузить 
    cout << "Hello!" << endl;
    cout << "I am a sample function";
}
//-------------------------------------------------------------------------------------------------------------------------

void exiting_the_program() { //0. Выход
    cout << "Выход из системы (Работу выполнил студент АС-23-04 Хабаров Артём)..." << endl;
    sleep_for(seconds(1));
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
    cin >> number;


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
        saving_data();
        break;
    }
    case 7: 
    {
        uploading_data();
        break;
    }

    case 8:
    {
        exiting_the_program();
        break;
    }

    default:
    {
        cout << "К сожалению, произошла ошибка, перезапустите программу...";
        sleep_for(seconds(1));
        exit(0);
    }

    }

    }
    return 0;
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