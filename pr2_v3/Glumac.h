#pragma once

#include <iostream>
#include "Datum.h"
#include "_PomocneFunkcije.h"
using namespace std;


class Glumac
{
private:
    char* _ime;
    char* _prezime;
    char* _zemljaPorijekla;
    Datum* _datumRodjenja;
    bool* _spol; //1-Muski, 0-Zenski
public:
    //Z2.0 Dflt. ctor
    Glumac() {
        _ime = _prezime = _zemljaPorijekla = nullptr;
        _datumRodjenja = nullptr;
        _spol = nullptr;
    }
    //Z2.1 User-def. ctor
    Glumac(const char* ime, const char* prez, const char* zemlja, int d, int m, int g, bool spol) {
        _ime = AlocirajIKopiraj(ime);
        _prezime = AlocirajIKopiraj(prez);
        _zemljaPorijekla = AlocirajIKopiraj(zemlja);
        _datumRodjenja = new Datum(d, m, g);
        _spol = new bool(spol);
    }
    //Z2.2 Copy ctor
    Glumac(const Glumac& obj)
        :_datumRodjenja(obj._datumRodjenja)
    {
        _ime = AlocirajIKopiraj(obj._ime);
        _prezime = AlocirajIKopiraj(obj._prezime);
        _zemljaPorijekla = AlocirajIKopiraj(obj._zemljaPorijekla);
        _spol = new bool(obj._spol);
    }
    //Z2.3 Move ctor
    Glumac(Glumac&& obj) {
        _ime = obj._ime;
        obj._ime = nullptr;
        _prezime = obj._prezime;
        obj._prezime = nullptr;
        _zemljaPorijekla = obj._zemljaPorijekla;
        obj._zemljaPorijekla = nullptr;
        _datumRodjenja = obj._datumRodjenja;
        obj._datumRodjenja = nullptr;
        _spol = obj._spol;
        obj._spol = nullptr;
    }
    //Z2.4
    char* GetIme() const { return _ime; }
    char* GetPrezime() const { return _prezime; }
    char* GetZemljaPorijekla() const { return _zemljaPorijekla; }
    Datum GetDatumRodjenja() const { return *_datumRodjenja; }
    bool GetSpol() const { return *_spol; }

    //Z2.5
    void SetIme(const char* ime) {
        delete[] _ime;
        _ime = AlocirajIKopiraj(ime);
    }
    void SetPrezime(const char* prezime) {
        delete[] _prezime;
        _prezime = AlocirajIKopiraj(prezime);
    }
    void SetZemljaPorijekla(const char* zemlja) {
        delete[] _zemljaPorijekla;
        _zemljaPorijekla = AlocirajIKopiraj(zemlja);
    }
    void SetDatumRodjenja(Datum datumRodjenja) {
        if (_datumRodjenja == nullptr)
            _datumRodjenja = new Datum;
        _datumRodjenja->SetDan(datumRodjenja.GetDan());
        _datumRodjenja->SetMjesec(datumRodjenja.GetMjesec());
        _datumRodjenja->SetGodina(datumRodjenja.GetGodina());
    }
    void SetSpol(bool spol) {
        if (_spol == nullptr)
            _spol = new bool;
        *_spol = spol;
    }

    //Z2.6
    void Ispis() {
        cout << "Ime i prezime: " << _ime << " " << _prezime << endl;
        cout << "Zemlja porijekla: " << _zemljaPorijekla << endl;
        cout << "Datum rodjenja: ";
        _datumRodjenja->Ispis();
        cout << endl;
        cout << "Spol: " << ((*_spol == true) ? "Muski" : "Zenski") << endl;
    }
    //Z2.7
    ~Glumac() {
        delete[] _ime, delete[] _prezime, delete[] _zemljaPorijekla;
        _ime = nullptr, _prezime = nullptr, _zemljaPorijekla = nullptr;
       // _datumRodjenja = nullptr;
        delete _spol;
        _spol = nullptr;
    }
};