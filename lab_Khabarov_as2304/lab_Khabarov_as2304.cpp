﻿#include <iostream>
using namespace std;
#include <chrono>
using namespace std::chrono; // Для добавления секунд.
#include <thread>
using namespace std::this_thread; // sleep_for, sleep_until.

void Adding_a_pipe() { // 1. Добавить трубу 
    cout << "Hello!" << endl;
    cout << "I am a sample function";
}
void Adding_a_compressor_station() { //2. Добавить КС 
    cout << "Hello!" << endl;
    cout << "I am a sample function"; 
}
void viewing_all_objects() { // 3. Просмотр всех объектов 
    cout << "Hello!" << endl;
    cout << "I am a sample function";
}
void editing_a_pipe() { //4. Редактировать трубу 
    cout << "Hello!" << endl;
    cout << "I am a sample function";
}
void editing_the_compressor_station() { //5. Редактировать КС 
    cout << "Hello!" << endl;
    cout << "I am a sample function";
}
void saving_data() { //6. Сохранить 
    cout << "Hello!" << endl;
    cout << "I am a sample function";
}
void uploading_data() { //7. Загрузить 
    cout << "Hello!" << endl;
    cout << "I am a sample function";
}
void exiting_the_program() { //0. Выход
    cout << "the end";
    exit(0);

}

//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------
int main()
{
    int x;
    setlocale(LC_ALL, "Russian"); // Без него консоль не поймёт русский язык и вместо обычного текста выведет набор несвязанных символов
    cout << "Здравствуйте. Добро пожаловать в меню по созданию и редактированию  трубы и КС или НПС!" <<endl;
    sleep_for(seconds(3)); // Задержка на 3 секунды. Исключительно для оформления.

    cout << "Пожалуйста, выберите режим и напишите соответствующую цифру:" << endl;
    cout << "1. Добавить трубу;  " << endl;
    cout << "2. Добавить КС;" << endl;
    cout << "3. Просмотр всех объектов; " << endl;
    cout << "4. Редактировать трубу; " << endl;
    cout << "5. Редактировать КС; " << endl;
    cout << "6. Сохранить; " << endl;
    cout << "7. Загрузить; " << endl;
    cout << "0. Выход." << endl;

    cin >> x;

    switch (x) {
    case 1:
        Adding_a_pipe();
        break;
    case 2:
        Adding_a_compressor_station();
        break;
    case 3:
        viewing_all_objects();
        break;
    case 4:
        editing_a_pipe();
        break;
    case 5:
        editing_the_compressor_station();
        break;
    case 6:
        saving_data();
        break;
    case 7:
        uploading_data();
        break;
    case 0:
        exiting_the_program();
        break;
    default:
        cout << "К сожалению, произошла ошибка, перезапустите программу...";
        sleep_for(seconds(1));
        exit(0);

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