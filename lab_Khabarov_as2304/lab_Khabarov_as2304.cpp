#include <iostream>

#include <fstream> // для файлов
#include <string> //для getline (команда полезнее всяких cin)


using namespace std;
//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------

struct Pipe // Данные о трубе. Нужно для записи данных в файл.
{
    string pipe_name = "Nothing"; // Сделаем "шаблон", где везде будут 0, а в тексте NOTHING. Если это NOTHING останется - напишет, что файл не найден. "взломать" файл практически невозможно.
    double pipe_length = 0.0;
    int pipe_diameter = 0;
    bool pipe_repair = false; //  режим работы (0 - ГОТОВ; 1- В РЕМОНТЕ)
};
struct Station //Данные о КС. Делаем также
{
    string station_name = "Nothing";
    int station_workshops = 0;
    int station_working_workshops = 0;
    double station_efficiency = 0.0; // ??? (надо у препода спросить, что за эффективность и какая она должна быть. Насколько я понял, это double)
};
//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------
void check_integer(int& int_data) { // ПРОВЕРКИ (https://stackoverflow.com/questions/12721911/c-how-to-verify-if-the-data-input-is-of-the-correct-datatype)
    cin >> int_data;
    while (cin.fail() || cin.peek() != '\n' || int_data < 0)// число должно быть ЧИСЛО. НЕ ОШИБКА И НЕ ДЛИННОЕ
    {
        cin.clear(); // сотрём то, что написали...
        cin.ignore(10, '\n'); // аналогично ("проигнорим длинные цифры")
        cout << "Пожалуйста, введите натуральное небольшое число :/ :" << endl;
        cin >> int_data;
    }

}
//-------------------------------------------------------------------------------------------------------------------------

void check_double(double& double_data) { // ПРОВЕРКИ
    cin >> double_data;
    while (cin.fail() || cin.peek() != '\n' || double_data < 0)// число должно быть ЧИСЛОМ, большим 0
    {
        cin.clear();
        cin.ignore(10, '\n');
        cout << "Пожалуйста, введите небольшое число, большее 0 (double) :/ :" << endl;
        cin >> double_data;
    }
}

//-------------------------------------------------------------------------------------------------------------------------
void check_bool(bool& bool_data) { // ПРОВЕРКИ
    cin >> bool_data;
    while (cin.fail() || cin.peek() != '\n')// 0 или 1
    {
        cin.clear();
        cin.ignore(10, '\n');
        cout << "Пожалуйста, введите 0 или 1 :/ :" << endl;
        cin >> bool_data;
    }
}
//--------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------
void check_mode_main(int& int_data) { // ПРОВЕРКИ
    cin >> int_data;
    while (cin.fail() || cin.peek() != '\n' || int_data <= 0 || int_data >= 9)// число должно быть ЧИСЛОМ от 1 до 9
    {
        cin.clear();
        cin.ignore(10, '\n');
        cout << "Пожалуйста, введите натуральное число от 1 до 8 :/ :" << endl;
        cin >> int_data;
    }

}
//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------
Pipe Adding_a_pipe() //1. Добавить трубу
{
    Pipe new_pipe; // Берём шаблон сверху и начинаем творить чудеса...
    cout << "Назовите свою трубу (на инглише, по-русски программа понимать не хочет...): " << endl;
    cin.ignore(); //"БЕЗ ЭТОЙ ШТУКИ программа тупо и нагло ПРОПУСКАЕТ шаг. Внаглую! GETLINE и IGNORE должны работать вместе и сообща! (https://stackoverflow.com/questions/21686762/why-do-we-need-to-use-cin-ignore-before-getlinecin-string)"
    getline(cin, new_pipe.pipe_name); // а-ля 'пиши что хочешь'
    cout << "Укажите длину трубы: " << endl;
    check_double(new_pipe.pipe_length);
    cout << "Укажите диаметр трубы: " << endl;
    check_integer(new_pipe.pipe_diameter);
    cout << "Укажите режим трубы:" << endl;
    cout << "0. Готов;" << endl;
    cout << "1. В ремонте." << endl;
    check_bool(new_pipe.pipe_repair);
    return new_pipe;
}//-------------------------------------------------------------------------------------------------------------------------

 Station Adding_a_compressor_station() { //2. Добавить КС  ( аналогично )
     Station new_station;
     
     cout << "Назовите свою КС (На английском, я молю...): " << endl;
     cin.ignore();
     getline(cin, new_station.station_name);
     cout << "Укажите количество цехов: " << endl;
     check_integer(new_station.station_workshops);
     cout << "Укажите количество РАБОЧИХ цехов: " << endl;
     check_integer(new_station.station_working_workshops);
     while (new_station.station_working_workshops > new_station.station_workshops) { // рабочие цеха < всего цехов
         cout << "Количество рабочих цехов не может быть больше количества всех цехов. Поменяйте значение :/ :" << endl;
         cout << "Укажите количество РАБОЧИХ цехов: " << endl;
         check_integer(new_station.station_working_workshops);
     }
     cout << "Укажите эффективность КС: " << endl;
     check_double(new_station.station_efficiency);
     return new_station;
}
//-------------------------------------------------------------------------------------------------------------------------

void pipe_info(Pipe& new_pipe) { // Просмотр всех объектов

    if (new_pipe.pipe_name == "Nothing") { // Ни 1 человек в здравом уме не назовёт трубу Nothing
        cout << "Отсутствуют..." << endl;
    }
    else {
        cout << "Имя: " << new_pipe.pipe_name << endl;
        cout << "Длина: " << new_pipe.pipe_length << " метров."<< endl;
        cout << "Диаметр: " << new_pipe.pipe_diameter << " миллиметров." << endl;
        if (new_pipe.pipe_repair == 0) {
            cout << " Статус: Готов." << endl;
        }
        else {
            cout << "Статус: В ремонте." << endl;
        }
        
    }
}

void station_info(Station& new_station) {
    
    if (new_station.station_name == "Nothing") {
        cout << "Отсутствуют..." << endl;
        
    }
    else {
        cout << "Имя: " << new_station.station_name << endl;
        cout << "Количество цехов: " << new_station.station_workshops << " штук." << endl;
        cout << "Количество рабочих цехов: " << new_station.station_working_workshops << " штук." << endl;
        cout << "Эффективность: " << new_station.station_efficiency << endl;
        
    }
}
//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------
void editing_a_pipe(Pipe& new_pipe) { //4. Редактировать трубу  


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
        cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    }
    else
    {
        cout << "Укажите режим трубы:" << endl;
        cout << "0. Готов;" << endl;
        cout << "1. В ремонте" << endl;
        check_bool(new_pipe.pipe_repair);
    pipe_info(new_pipe);
}
}
//-------------------------------------------------------------------------------------------------------------------------

void editing_the_compressor_station(Station& new_station) { //5. Редактировать КС  (АНАЛОГИЧНО)

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
        cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    }
    else {
        cout << "Укажите количество рабочих цехов: " << endl;
        check_integer(new_station.station_working_workshops);
        while (new_station.station_working_workshops > new_station.station_workshops) {
            cout << "Количество рабочих цехов не может быть больше количества всех цехов. Поменяйте значение :/ :" << endl;
            cout << "Укажите количество РАБОЧИХ цехов: " << endl;
            check_integer(new_station.station_working_workshops);
        }
        station_info(new_station);
    }
}
//-------------------------------------------------------------------------------------------------------------------------

/*void saving_data_pipe(Pipe& pipe_data, Station& station_data) { //6. Сохранить //!!!!!!!!!!!!!!
    cout << "-----------------------------------------------------------" << endl;
    ofstream fileout("information"); // OF - В ФАЙЛ (ЗАПИСЬ) (Sololearn)
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
*/
void saving_data_pipe(Pipe& pipe_data) { //6. Сохранить 
    ofstream fileout;
    fileout.open("information"); // OF - В ФАЙЛ (ЗАПИСЬ) (Sololearn)
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
    ofstream fileout;
    fileout.open("information"); ("information"); // OF - В ФАЙЛ (ЗАПИСЬ) (Sololearn)
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
//-------------------------------------------------------------------------------------------------------------------------

void uploading_data_pipe(Pipe& pipe_data) { //7. Загрузить ///!!!!!!!!!!!!!!!!!!!!!!!
    ifstream filein;
    filein.open("information"); // IF - ИЗ ФАЙЛА (ЧТЕНИЕ) (Sololearn)
    if (filein) 
    {
        string name; // Нужно для проверки
        bool flag_pipe = 0;
        while (getline(filein, name))
        {
            if (name == "Инфомация о трубе:") 
            {
                cout << "Данные о трубе загружены!" << endl;
                getline(filein, pipe_data.pipe_name);
                filein >> pipe_data.pipe_length;
                filein >> pipe_data.pipe_diameter;
                filein >> pipe_data.pipe_repair;
                if (pipe_data.pipe_repair == 0) {
                    cout << "Статус трубы: Готов " << endl;
                }
                else {
                    cout << "Статус трубы: В ремонте" << endl;
                }
                flag_pipe = 1;
            }
        }
        if (flag_pipe == 0) 
        {
            cout << "Вы пока что не создали или не сохраняли информацию о трубе..." << endl;

            flag_pipe = {};
        }
        filein.close();
    }
}

void uploading_data_station(Station& station_data) { //7. Загрузить ///!!!!!!!!!!!!!!!!!!!!!!!
    ifstream filein;
    filein.open("information"); // IF - ИЗ ФАЙЛА (ЧТЕНИЕ) (Sololearn)
    if (filein) 
    {
        string name; // Нужно для проверки
        bool flag_station = 0;
        while (getline(filein, name))
        {
   
            if (name == "Инфомация о КС:") 
            {
                cout << "Данные о КС загружены!" << endl;
                getline(filein, station_data.station_name);
                filein >> station_data.station_workshops;
                filein >> station_data.station_working_workshops;
                filein >> station_data.station_efficiency;
                flag_station = 1;
            }
        }
        if (flag_station == 0) 
        {
            cout << "Вы пока что не создали или не сохраняли информацию о КС..." << endl;

            station_data = {};
        }
        filein.close();
    }
}


//-------------------------------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------

int main()
{
    setlocale(LC_ALL, "Russian"); // Без него консоль не поймёт русский язык и вместо обычного текста выведет набор несвязанных символов
    cout << "Здравствуйте. Добро пожаловать в меню по созданию и редактированию  трубы и КС или НПС!" <<endl;
    Pipe pipe0;
    Station station0; // те самые шаблоны, с которыми мы бдуем чудить
    int number = 0;
    while (true) // меню ВСЕГДА будет.
    {
    cout << "-----------------------------------------------------------" << endl;
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
        saving_data_pipe(pipe0);
        saving_data_station(station0);
        break;
    }
    case 7: 
    {
        uploading_data_pipe(pipe0);
        uploading_data_station(station0);
        break;
    }

    case 8:
    {
        return(0);

    }
    default:
    {
        cout << "К сожалению, произошла ошибка, попробуем снова..." << endl; // Премию тому, кто сломает код.
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