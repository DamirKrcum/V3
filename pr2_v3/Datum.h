#pragma once

#include <iostream>
using namespace std;

class Datum
{
private:
    int* _dan;
    int* _mjesec;
    int* _godina;
public:
    //Z1.1 Dflt. ctor [Postaviti na dflt. vrijednosti]
    Datum() {
        _dan = _mjesec = _godina = nullptr;
    }
    //Z1.2 User-def. ctor
    Datum(int d, int m, int g) {
        _dan = new int(d);
        _mjesec = new int(m);
        _godina = new int(g);
    }
    //Z1.3 Copy ctor
    Datum(const Datum& obj) {
        _dan = new int(*obj._dan);
        _mjesec = new int(*obj._mjesec);
        _godina = new int(*obj._godina);
    }
    //Z1.4 Move ctor
    Datum(Datum&& obj) {
        _dan = obj._dan;
        _mjesec = obj._mjesec;
        _godina = obj._godina;
        obj._dan = obj._mjesec = obj._godina = nullptr;
    }
    //Z1.5
    int GetDan() const { return *_dan; }
    int GetMjesec() const { return *_mjesec; }
    int GetGodina() const { return *_godina; }
    //Z1.6
    void SetDan(int dan) {
        if (_dan == nullptr)
            _dan = new int;
        *_dan = dan;
    }
    void SetMjesec(int mjesec) {
        if (_mjesec == nullptr)
            _mjesec = new int;
        *_mjesec = mjesec;
    }
    void SetGodina(int godina) {
        if (_godina == nullptr)
            _godina = new int;
        *_godina = godina;
    }
    //Z1.7
    void Ispis() {
        cout << *_dan << "." << *_mjesec << "." << *_godina;
    }
    //Z1.8
    ~Datum() {
        delete _dan, delete _mjesec, delete _godina;
        _dan = _mjesec = _godina = nullptr;
        
    }
};