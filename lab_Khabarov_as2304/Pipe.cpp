#include "Pipe.h"
#include "Data.h"

int Pipe::maxId = 0;

int Pipe::GetId()
{
    return Id;
}
int Pipe::GetDiameter() const
{
    return Pipe_diameter;
}
int Pipe::GetLen() const {
    return Pipe_length;
}
string Pipe::Getname() const
{
    return pipe_name;
}

bool Pipe::GetRepairStatus()
{
    return isUnderRepair;
}

int Pipe::GetCSid1() const {
    return CSid1;
}

int Pipe::GetCSid2() const {
    return CSid2;
}

int Pipe::GetCapac() {
    return capac;
}

bool Pipe::Get_free() {
    return free;
}

void Pipe::Set_free(bool status) {
    free = status;
}

void Pipe::SetRepairStatus(bool status)
{
    isUnderRepair = status;
}

void Pipe::SetDiameter(int diam) {
    Pipe_diameter = diam;
}

void Pipe::SetCapac(int c) {
    capac = c;
}

void Pipe::DeleteConnection()
{
    CSid1 = 0;
    CSid2 = 0;
}

bool Pipe::ConnectionNotBusy() const
{
    return CSid1 < 1 || CSid2 < 1;
}


void Pipe::PrintRepairStatus()
{
    if (GetRepairStatus() == true)
    {
        cout << "Статус трубы: 1." << endl;
    }
    else
        cout << "Статус трубы: 0.";
}
void Pipe::EditPipe() {
    cout << "Вы хотите поменять статус трубы?" << endl;
    cout << "1. ДА" << endl;
    cout << "2. НЕТ" << endl;
    switch (GetCorrectData(1, 2))
    {
    case 1:
    {
        cout << "Если трубы в ремонте - пишите 1. Если труба готова/не в ремонте - пишите 0: " << endl;
        bool pipeRepair = GetCorrectData(false, true);
        SetRepairStatus(pipeRepair);
        PrintRepairStatus();
        break;
    }
    case 2:
        return;
    default:
        cout << "._." << endl;
        break;
    }
}



istream& operator >> (istream& in, Pipe& newPipe)
{
    newPipe.Id = ++newPipe.maxId;
    cout << "ID: " << newPipe.Id << endl;
    cout << "Напишите имя: " << endl;
    INPUT_LINE(in, newPipe.pipe_name);
    cout << "Напиши длину трубы (в метрах, до 10 км): " << endl;
    newPipe.Pipe_length = GetCorrectData(0.0, 10000.0);
    cout << "Напиши диаметр трубы (в миллиметрах, до 1400): " << endl;
    newPipe.Pipe_diameter = GetCorrectData(0.0, 1400.0);
    cout << " Напиши статус трубы (Если трубы в ремонте - пишите 1. Если труба готова/не в ремонте - пишите 0): " << endl;
    newPipe.isUnderRepair = GetCorrectData(0, 1);
    return in;
}

ostream& operator << (ostream& out, const Pipe& newPipe)
{
    if (newPipe.pipe_name == "Nothing")
    {
        out << "В файле пусто.";
    }
    else
    {
        out << "ID: " << newPipe.Id << ";" << endl;
        out << "Имя трубы: " << newPipe.pipe_name << ";" << endl;
        out << "Длина: " << newPipe.Pipe_length << ";" << endl;
        out << "Диаметр: " << newPipe.Pipe_diameter << ";" << endl;
        out << "Статус трубы: " << newPipe.isUnderRepair << ";" << endl;
    }
    return out;
}

ifstream& operator >> (ifstream& flin, Pipe& newPipe)
{
    flin >> newPipe.Id;
    newPipe.maxId = newPipe.Id;
    flin.ignore();
    getline(flin, newPipe.pipe_name);
    flin >> newPipe.Pipe_length;
    flin >> newPipe.Pipe_diameter;
    flin >> newPipe.isUnderRepair;
    return flin;
}

ofstream& operator << (ofstream& fout, const Pipe& newPipe)
{
    fout << newPipe.Id << endl;
    fout << newPipe.pipe_name << endl;
    fout << newPipe.Pipe_length << endl;
    fout << newPipe.Pipe_diameter << endl;
    fout << newPipe.isUnderRepair << endl;
    return fout;
}