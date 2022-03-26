#pragma once
#include <iostream>
using namespace std;
#include "Glumac.h"


class Uloga {
private:
    Glumac* _glumac;
    char* _opis;
    char* _tipUloge; //Glavna, sporedna, epizodna, statista, gostujuca zvijezda, cameo ...
public:
    //Z4.0
    Uloga() {
        _glumac = nullptr;
        _opis = nullptr;
        _tipUloge = nullptr;
    }
    //Z4.1
    Uloga(Glumac& glumac, const char* opis, const char* tip)
    {
        _glumac = new Glumac(glumac);
        _opis = AlocirajIKopiraj(opis);
        _tipUloge = AlocirajIKopiraj(tip);
    }
    //Z4.2 - copy konstruktor
    Uloga(const Uloga& obj)
        :_glumac(obj._glumac)
    {
        _opis = AlocirajIKopiraj(obj._opis);
        _tipUloge = AlocirajIKopiraj(obj._tipUloge);

    }
    //Z4.3 - move konstruktor
    Uloga(Uloga&& obj)
        : _glumac(move(obj._glumac))
    {
        _opis = obj._opis;
        obj._opis = nullptr;
        _tipUloge = obj._tipUloge;
        obj._tipUloge = nullptr;
    }

    //Z4.4
    Glumac GetGlumac() const { return *_glumac; }
    char* GetOpis() const { return _opis; }
    char* GetTipUloge() const { return _tipUloge; }
    //Z4.5
    void SetGlumac(Glumac glumac) {
        if (_glumac == nullptr)
            _glumac = new Glumac;
        _glumac->SetIme(glumac.GetIme());
        _glumac->SetPrezime(glumac.GetPrezime());        
        _glumac->SetDatumRodjenja(glumac.GetDatumRodjenja());
        _glumac->SetZemljaPorijekla(glumac.GetZemljaPorijekla());
        _glumac->SetSpol(glumac.GetSpol());
    }
    void SetOpis(const char* opis) {
        delete[] _opis;
        _opis = AlocirajIKopiraj(opis);
    }
    void SetTipUloge(const char* tipUloge) {
        delete[] _tipUloge;
        _tipUloge = AlocirajIKopiraj(tipUloge);
    }
    //Z4.6
    void Ispis() {
        cout << "Glumac: ";
        _glumac->Ispis();
        cout << "Opis: " << _opis << endl;
        cout << "Tip uloge: " << _tipUloge << endl;
    }
    //Z4.7
    ~Uloga() {
        delete[] _opis; _opis = nullptr;
        delete[] _tipUloge; _tipUloge = nullptr;
        _glumac = nullptr;
    }
};