#include <iostream>
#include <fstream> // для файлов
#include <string> //для getline (команда полезнее всяких cin)
#include "Data.h"
#include "Pipe.h"
#include "Station.h"
#include <unordered_map>
#include <chrono>
#include <format>
#include "GTS.h"

using namespace std;
using namespace chrono;

//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------

/*void saving_data_pipe(Pipe& pipe_data) { //6. Сохранить 
    ofstream fileout("information");  // OF - В ФАЙЛ (ЗАПИСЬ) (Sololearn)
    if (pipe_data.pipe_name == "Nothing") {
        cout << "Вы пока не создали трубу..." << endl;

    }
    else {
        cout << "Сохранение данных (труба)..." << endl;
        if (fileout) {
            fileout << "Инфомация о трубе:" << endl;
            fileout << pipe_data.pipe_name << endl;
            fileout << pipe_data.pipe_length << endl;
            fileout << pipe_data.pipe_diameter << endl;
            fileout << pipe_data.pipe_repair << endl;
            cout << "Готово!" << endl;
        }
    }
    fileout.close();
}
void saving_data_station(Station& station_data) { //6. Сохранить 
    ofstream fileout("information", ios::app);  // OF - В ФАЙЛ (ЗАПИСЬ) (Sololearn)
    if (station_data.station_name == "Nothing") {
        cout << "Вы пока не создали КС..." << endl;
    }
    else {
        cout << "Сохранение данных (КС)..." << endl;
        if (fileout) {
            fileout << "Инфомация о КС:" << endl;;
            fileout << station_data.station_name << endl;
            fileout << station_data.station_workshops << endl;
            fileout << station_data.station_working_workshops << endl;
            fileout << station_data.station_efficiency << endl;
            cout << "Готово!" << endl;
        }
    }
    fileout.close();
}
*/
//-------------------------------------------------------------------------------------------------------------------------
/*
void uploading_data_pipe(Pipe& pipe_data, ifstream& filein) {
    getline(filein, pipe_data.pipe_name);
    filein >> pipe_data.pipe_length;
    filein >> pipe_data.pipe_diameter;
    filein >> pipe_data.pipe_repair;
}


void uploading_data_station(Station& station_data, ifstream& filein) {
    getline(filein, station_data.station_name);
    filein >> station_data.station_workshops;
    filein >> station_data.station_working_workshops;
    filein >> station_data.station_efficiency;
}

void uploading_data(Pipe& pipe_data,Station& station_data) { //7. Загрузить ///!!!!!!!!!!!!!!!!!!!!!!!
    ifstream file("information");
    if (file) 
    {
        string name; // Нужно для проверки
        pipe_data = Pipe();
        station_data = Station();
        while (getline(file, name))
        {
            if (name == "Инфомация о трубе:")
            {
                uploading_data_pipe(pipe_data, file);
            }
            if (name == "Инфомация о КС:") {
                uploading_data_station(station_data, file);
            }
        }
        cout << "Данные загружены" << endl;
        file.close();

    }
}
*/
//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------

int main()
{
    redirect_output_wrapper cerr_out(cerr);
    string time = std::format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now());
    ofstream logfile("log_" + time);
    if (logfile)
        cerr_out.redirect(logfile);
    setlocale(LC_ALL, "Russian"); // Без него консоль не поймёт русский язык и вместо обычного текста выведет набор несвязанных символов
    cout << endl;
    cout << "Здравствуйте. Добро пожаловать в меню по созданию и редактированию  трубы и КС или НПС!" <<endl;
    cout << "***" << endl;
    cout << "В НОВОЙ версии 1.2 мы добавили функцию РАБОТЫ С НЕСКОЛЬКИМИ ОБЪЕКТАМИ ВАУ ВАУ ВАУ ВАУУУУ!!!!" << endl;
    cout << "***" << endl;
    Pipe pipe0;
    Station station0; // те самые шаблоны, с которыми мы бдуем чудить
    GTS gts;
    unordered_map<int, Pipe> Pipes = {}; //словарь
    unordered_map<int, Station> Stations = {};
    int number = 0;
    while (true) // меню ВСЕГДА будет.
    {
    cout << endl;
    cout << "Пожалуйста, выберите режим и напишите соответствующую цифру:" << endl;
    cout << "1. Добавить трубу;  " << endl;
    cout << "2. Добавить КС;" << endl;
    cout << "3. Просмотр всех объектов; " << endl;
    cout << "4. Редактировать трубу; " << endl;
    cout << "5. Редактировать КС; " << endl;
    cout << "6. Удалить трубу (!!!НОВИНКА!!!); " << endl;
    cout << "7. Удалить КС (!!!НОВИНКА!!!); " << endl;
    cout << "8. Сохранить; " << endl;
    cout << "9. Загрузить; " << endl;
    cout << "10. Найти (!!!НОВИНКА!!!); " << endl;
    cout << "11. Выход." << endl;
    cout << endl;
    switch (GetCorrectData(1, 11))
    {
    case 1:
    {
        Pipe pipe0;
        cin >> pipe0;
        cout << "------------------------------------------------------" << endl;
        Pipes.insert({ pipe0.GetId(), pipe0 });
        break;
    }
    case 2:
    {
        Station station0;
        cin >> station0;
        cout << "------------------------------------------------------" << endl;
        Stations.insert({ station0.GetId(), station0 });
        break;
    }
    case 3:
    {
        cout << "------------------------------------------------------" << endl;
        if (Pipes.size() == 0)
            cout << "Данные о трубах отсутствуют!" << endl;
        for (const auto& elem : Pipes)
            cout << elem.second;
        if (Stations.size() == 0)
            cout << "Данные о КС отсутствуют!" << endl;
        for (const auto& elem : Stations)
        {
            cout << elem.second;
        }
        break;
    }
    case 4:
    {
        cout << "------------------------------------------------------" << endl;
        if (Pipes.size() == 0) {
            cout << "Данные отсутствуют!" << endl;
        }
        else {
            cout << "Редактируем трубу... " << endl;
            cout << "Напишите ID: ";
            int indPipes = Pipes.size();
            Pipe& pipe0 = SelectElement(Pipes, GetCorrectData(1, indPipes));
            gts.EditPipe(pipe0);
        }
    }
    case 5:
    {
        cout << "------------------------------------------------------" << endl;
        if (Stations.size() == 0) {
            cout << "Данные отсутствуют!" << endl;
        }
        else {
            cout << "Редактируем КС... " << endl;
            cout << "Напишите ID: ";
            int indStations = Stations.size();
            Station& station0 = SelectElement(Stations, GetCorrectData(1, indStations));
            gts.EditStation(station0);
        }
        break;
    }

 /*   case 6:
    {
        saving_data_pipe(pipe0);
        cout << "------------------------------------" << endl;
        saving_data_station(station0);
        break;
    }
    case 7: 
    {
        uploading_data(pipe0, station0);
        break;
    }
*/
    case 6:
    {
        cout << "------------------------------------------------------" << endl;
        if (Pipes.size() == 0) {
            cout << "Данные отсутствуют!" << endl;
        }
        else {
            cout << "Удаление трубы..." << endl;
            cout << "Напишите ID: ";
            int key0;
            cin >> key0;
            removeKeyIfExists(Pipes, key0);
        }
        break;
    }
    case 7:
    {
        cout << "------------------------------------------------------" << endl;
        if (Stations.size() == 0) {
            cout << "Данные отсутствуют!" << endl;
        }
        else {
            cout << "Удаление КС... " << endl;
            cout << "Напишите ID: ";
            int key0;
            cin >> key0;
            removeKeyIfExists(Stations, key0);
        }
        break;
    }
    case 8:
    {
        cout << "------------------------------------------------------" << endl;
        cout << "Сохраняем..." << endl;
        ofstream fout;
        string fileName;
        cout << "Назовите файл(на инглише!!!): ";
        cin.ignore();
        getline(cin, fileName);
        fout.open(fileName);
        if (!fout.is_open())
        {
            cout << "Файл не открылся. Ошибка!" << endl;
        }
        else {
            fout << Pipes.size() << endl;
            for (const auto& elem : Pipes)
                fout << elem.second;
            cout << "Сохранение трубы завершено успешно!" << endl;
            fout << Stations.size() << endl;
            for (const auto& elem : Stations)
                fout << elem.second;
            cout << "Сохранение КС завершено успешно!" << endl;
        }
        fout.close();
        break;
    }
    case 9:
    {
        cout << "------------------------------------------------------" << endl;
        cout << "Загрузка" << endl;
        ifstream fin;
        string fileName;
        cout << "Назовите файл (на инглише!!!): ";
        cin.ignore();
        getline(cin, fileName);
        fin.open(fileName);
        if (!fin.is_open())
        {
            cout << "Файл не открылся. Ошибка!" << endl;
        }
        else {
            int pipesSize;
            fin >> pipesSize;
            if (pipesSize == 0)
                cout << "Нет информации о трубе." << endl;
            else {
                cout << "Загрузка информации о трубе успешно завершена." << endl;
            }
            while (pipesSize-- > 0)
            {
                Pipe pipe0;
                fin >> pipe0;
                Pipes.insert({ pipe0.GetId(), pipe0 });
            }
            int csSize;
            fin >> csSize;
            if (csSize == 0)
                cout << "Нет информации о КС." << endl;
            else {
                cout << "Загрузка информации о КС успешно завершена." << endl;
            }
            while (csSize-- > 0)
            {
                Station station0;
                fin >> station0;
                Stations.insert({ station0.GetId(), station0 });
            }
            fin.close();
        }
        break;
    }
    case 10:
    {
        cout << "------------------------------------------------------" << endl;
        bool flag = true;
        while (flag) {
            cout << "Что вы хотите найти:" << endl;
            cout << "1. Трубу;" << endl;
            cout << "2. КС;" << endl;
            cout << "3. Ничего ._." << endl;
            switch (GetCorrectData(1, 3))
            {
            case 1:
                gts.searchPipe(Pipes);
                break;
            case 2:
                gts.searchStation(Stations);
                break;
            case 3:
                flag = false;
                break;
            default:
                cout << "Напишите правильно. Я вас не андерстэрнд." << endl;
                break;
            }
        }
        break;
    }

    case 11:
    {
        return(0);
        break;

    }
    default:
    {
        cout << "К сожалению, произошла ошибка, попробуем снова..." << endl; // Премию тому, кто сломает код.
    }

    }

    }
    return 0; // Конечная. Поезд дальше не идёт. Просьба выйти из вагона.
}

