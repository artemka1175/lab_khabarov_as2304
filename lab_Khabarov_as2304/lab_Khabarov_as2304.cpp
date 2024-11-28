// боль
#pragma once // связь между CPP и HEADER
#include "Data.h"
#include "Pipe.h"
#include "Station.h"


using namespace std;
using namespace chrono;

//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------

template <typename T>
void printMap(const unordered_map<int, T>& map) //УЗНАЁМ КЛЮЧ
{
    for (auto& [id, val] : map)
    {
        cout << val;
    }
}

template<typename T>
void saveMap(std::ofstream& fout, const std::unordered_map<int, T>& map) //СОХРАНЯЕМ КЛЮЧ
{
    fout << map.size() << endl;
    for (auto& [id, val] : map)
    {
        fout << val;
    }
}

template<typename T>
void loadMap(std::ifstream& fin, std::unordered_map<int, T>& map) //ЗАГРУЖАЕМ КЛЮЧ
{
    map.clear();
    T::resetMaxId();
    int sizemap;
    fin >> sizemap;
    for (int i = 1; i <= sizemap; i++)
    {
        T val; fin >> val;
        map.emplace(val.getID(), val);
    }
}
void saveFile(const unordered_map<int, Pipe>& pipemap, const unordered_map<int, Station>& csmap) // Добавляем возможность сохранить в файл СО СВОИМ ИМЕНЕМ! (https://www.cyberforum.ru/cpp-builder/thread17279.html?ysclid=m40h4biim8719113151)
{
    cout << "Напишите имя файла (при желании, напишите на конце .txt): ";
    string filename = inputString();
    ofstream fout;
    fout.open(filename, ios::out);
    if (fout)
    {
        saveMap(fout, pipemap);
        saveMap(fout, csmap);
        fout.close();
        cout << "Сохранилось " << pipemap.size() << "труб." << endl;
        cout << "сохранилось " << csmap.size() << "КС." << endl;
    }
    else cout << "ОШИБКА." << endl;
}

void loadFile(unordered_map<int, Pipe>& pipemap, unordered_map<int, Station>& csmap) // загрузка файла
{
    cout << "Напишите имя файла (пожалуйста, правильно): ";
    string filename = inputString();
    ifstream fin;
    fin.open(filename, ios::in);
    if (fin)
    { 
        loadMap(fin, pipemap);
        loadMap(fin, csmap);
        fin.close();
        cout << "Загрузилось " << pipemap.size() << " труб." << endl;
        cout << "Загрузилось " << csmap.size() << " КС." << endl;
    }
    else
        cout << "ОШИБКА." << endl;
}

void coutNoObjectFound() { cout << "Мы чёт это... не нашли ничего ._." << endl; }
template<typename T, typename U> 
using Filter = bool(*)(T& val, U param); // https://github.com/papilinatm/cpp_lessons_2020/commit/9f09fa11d114b35dfc1bcf3dd34939ea038c08cc
template<typename T>
bool checkByName(T& val, string name)
{
    size_t pos = val.getName().find(name);
    if (pos != std::string::npos) return true; //поиск по имени (позиция)
    else return false;
}
bool checkByRepairStatus(Pipe& Pipe, bool status)
{
    return Pipe.PrintPipeRepair() == status; //поиск по статусу
}
bool checkByWSInWork(Station& Station, double percent)
{
    return Station.GetPercentOfNonActiveWorkshops() >= percent; //поиск по проценту НЕ изготовленных цехов
}
template<typename T, typename U>
unordered_set<int> findByFilter(unordered_map<int, T>& map, Filter<T, U> f, U param) // Провекра на то, подходит ли тот или иной объект под заданное значение.
{
    unordered_set<int> res;
    int i = 0;
    for (auto& [id, val] : map)
    {
        if (f(val, param))
            res.emplace(id);
    }
    return res;
}
unordered_set<int> selectByChosenFilter(unordered_map<int, Pipe>& map)
{
    unordered_set<int> res;
    cout << "Выберите фильтр:" << endl;
    cout << "1. ПО ИМЕНИ;" << endl;
    cout << "2. ПО СТАТУСУ." << endl;
    switch (getCorrectNumber(1, 2))
    {
    case 1:
    {
        cout << "Напишите имя (или кусок от него): "; string name = inputString();
        res = findByFilter(map, checkByName, name);
        break;
    }
    case 2:
    {
        cout << "Напишите статус (0 = В РЕМОНТЕ; 1 = ГОТОВ): "; bool status = getCorrectNumber<int>(0, 1);
        res = findByFilter(map, checkByRepairStatus, status);
        break;
    }
    default:
        break;
    }
    return res;
}
unordered_set<int> selectByChosenFilter(unordered_map<int, Station>& map)
{
    unordered_set<int> res;
    cout << "Выберите фильтр:" << endl;
    cout << "ПО ИМЕНИ;" << endl;
    cout << "ПО ПРОЦЕНТУ РАБОЧИХ ЦЕХОВ." << endl;
    switch (getCorrectNumber(1, 2))
    {
    case 1:
    {
        cout << "Напишите имя (или кусок от него): "; string name = inputString();
        res = findByFilter(map, checkByName, name);
        break;
    }
    case 2:
    {
        cout << "Напишите процент (в процентах): "; double percent = getCorrectNumber<double>(0.0, 100.0);
        res = findByFilter(map, checkByWSInWork, percent);
        break;
    }
    default:
        break;
    }
    return res;
}
template<typename T>
unordered_set<int> selectByChosenID(unordered_map<int, T>& map, unordered_set<int>& set = {})
{
    unordered_set<int> res;
    cout << "Выберите все Id:" << endl;
    cout << "(Для выхода нажмите 0)" << endl;
    while (true)
    {
        int id = inputNumber<int>();
        if (id == 0)
            break;
        if (set.size() == 0)
        {
            if (map.contains(id)) res.emplace(id);
        }
        else
            if (map.contains(id) and set.contains(id)) res.emplace(id);
    }
    return res;
}
void coutFoundWithId(unordered_set<int>& set)
{
    cout << "Мы нашли подходящие Id: ";
    for (int id : set)
        cout << id << " ";
    cout << endl;
}
void editMap(unordered_map<int, Pipe>& map)
{
    for (auto& [id, p] : map)
        p.editPipe();
    if (!map.empty()) cout << "Готово!" << endl;
    else coutNoObjectFound();
}
void editMap(unordered_map<int, Station>& map)
{
    if (!map.empty()) {
        cout << "Вы хотите изменить количество рабочих цехов в большую или в меньшую сторону?" << endl;
        cout << "1. В большую." << endl;
        cout << "2. В меньшую." << endl;
    }
    else coutNoObjectFound();
    switch (getCorrectNumber(1, 2))
    {
    case 1:
    {
        for (auto& [id, cs] : map)
            if (!cs.run_working_workshops())
                cout << "Ошибка у КС " << id << endl;
        break;
    }
    case 2:
    {
        for (auto& [id, cs] : map)
            if (!cs.stop_working_workshops())
                cout << "Ошибка у КС " << id << endl;
        break;
    }
    default:
        break;
    }
    if (!map.empty()) cout << "Готово!" << endl;
    else coutNoObjectFound();
}

template<typename T>
void editSelected(unordered_map<int, T>& map, unordered_set<int>& set)
{
    cout << "Что вы хотите сделать с ними?" << endl;
    cout << "1. Вывести на экран;" << endl;
    cout << "2. Проредактировать;" << endl;
    cout << "3. Удалить;" << endl;
    cout << "4. Выход." << endl;
    switch (getCorrectNumber<int>(0, 3))
    {
    case 1:
    {
        for (int id : set)
            cout << map[id];
        break;
    }
    case 2:
    {
        editMap(map);
        break;
    }
    case 3:
    {
        for (int id : set)
            map.erase(id);
        break;
    }
    case 0:
    {
        break;
    }
    default:
        break;
    }
}
template<typename T>
void selectObjects(unordered_map<int, T>& map)
{
    unordered_set<int> res;
    if (map.empty())
    {
        coutNoObjectFound();
        return;
    }
    cout << "Как мы будем имкать?" << endl;
    cout << "1. По ID;" << endl;
    cout << "2. По фильтру." << endl;
    if (getCorrectNumber(1, 2) == 1) //ID
        res = selectByChosenID(map, res);
    else // Filter
        res = selectByChosenFilter(map);
    if (res.size() != 0)
    {
        coutFoundWithId(res);
        cout << "Вы хотите изменить ВСЕ или конкретные?" << endl;
        cout << "1. ВСЕ;" << endl;
        cout << "2. конкретные." << endl;
        if (getCorrectNumber(1, 2) == 2) //ID
            res = selectByChosenID(map, res);
        if (res.size() != 0)
            editSelected(map, res);
        else coutNoObjectFound();
    }
    else coutNoObjectFound();
}
void deleteAll(unordered_map<int, Pipe>& pipemap, unordered_map<int, Station>& csmap)
{
    if (pipemap.empty() && csmap.empty())
    {
        coutNoObjectFound();
        return;
    }
    pipemap.clear();
    csmap.clear();
    cout << "Готово!" << endl;
    return;
}
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

int Menu()
{
    unordered_map<int, Pipe> pipemap;
    unordered_map<int, Station> csmap;
    while (true) // меню ВСЕГДА будет.
    {
    cout << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
    cout << "Пожалуйста, выберите режим и напишите соответствующую цифру:" << endl;
    cout << "1. Добавить трубу;  " << endl;
    cout << "2. Добавить КС;" << endl;
    cout << "3. Просмотр всех объектов; " << endl;
    cout << "4. Редактировать  нужную трубу (!!!ОБНОВЛЕНИЕ!!!); " << endl;
    cout << "5. Редактировать нужную КС (!!!ОБНОВЛЕНИЕ!!!); " << endl;
    cout << "6. Сохранить; " << endl;
    cout << "7. Загрузить; " << endl;
    cout << "8. Очистить данные (!!!НОВИНКА!!!); " << endl;
    cout << "9. Выход." << endl;
    cout << endl;
    switch (getCorrectNumber(1, 9))
    {
    case 1:
    {
        cout << "-------------------------------------------------------------------------------" << endl;
        Pipe Pipe = Pipe::addPipe();
        pipemap.emplace(Pipe.getID(), Pipe);
        break;
    }
    case 2:
    {
        cout << "-------------------------------------------------------------------------------" << endl;
        Station Station = Station::addStation();
        csmap.emplace(Station.getID(), Station);
        break;
    }
    case 3:
    {
        cout << "-------------------------------------------------------------------------------" << endl;
        if (pipemap.empty() and csmap.empty()) coutNoObjectFound();
        else
        {
            cout << "ТРУБЫ" << endl; printMap(pipemap);
            cout << "-------------------------------------------------------------------------------" << endl;
            cout << "КС" << endl; printMap(csmap);
        }
        break;
    }
    case 4:
    {
        cout << "-------------------------------------------------------------------------------" << endl;
        selectObjects(pipemap);
        break;
    }
    case 5:
    {
        cout << "-------------------------------------------------------------------------------" << endl;
        selectObjects(csmap);
        break;
    }
    case 6:
    {
        cout << "-------------------------------------------------------------------------------" << endl;
        saveFile(pipemap, csmap);
        break;
    }
    case 7:
    {
        cout << "-------------------------------------------------------------------------------" << endl;
        loadFile(pipemap, csmap);
        break;
    }
    case 8:
    {
        cout << "-------------------------------------------------------------------------------" << endl;
        pipemap.clear();
        csmap.clear();
        cout << "ГОТОВО!" << endl;
        break;
    }

    case 9:
    {
        cout << "Прощайте." << endl;
        return 0;
    }
    default:
    {
        cout << "К сожалению, произошла ошибка. Простите..." << endl; // Премию тому, кто сломает код.
        return 0;
    }

    }
    cout << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian"); // русификатор

    cout << endl;
    cout << "Здравствуйте. Добро пожаловать в меню по созданию и редактированию  трубы и КС или НПС!" << endl;
    cout << "***" << endl;
    cout << "В НОВОЙ версии 1.2 мы добавили функцию РАБОТЫ С НЕСКОЛЬКИМИ ОБЪЕКТАМИ ВАУ ВАУ ВАУ ВАУУУУ!!!!" << endl;
    cout << "***" << endl;

    redirect_output_wrapper cerr_out(cerr);
    string time = std::format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now());
    ofstream logfile("log_" + time + ".txt");
    if (logfile)
        cerr_out.redirect(logfile);

    Menu();

    return 0;
}