#pragma once
#include <iostream>
using namespace std;
#include "Uloga.h"
#include "Epozida.h"


class Serija {
private:
    char* _naziv;
    int _trenutnoUloga;
    Uloga* _uloge[50] = { nullptr }; //Svi elementi (pokazivaci) se postavljaju na NULL

    int _maxBrojEpizoda;
    int _trenutnoEpizoda;
    Epizoda* _epizode;
public:
    //Z5.0
    Serija() {
        _naziv = nullptr;
        _trenutnoUloga = 0;
        _maxBrojEpizoda = 0;
        _trenutnoEpizoda = 0;
        _epizode = nullptr;
    }
    //Z5.1
    Serija(const char* naziv, int maxBrojEpizoda) {
        _naziv = AlocirajIKopiraj(naziv);
        _trenutnoUloga = 0;
        _maxBrojEpizoda = maxBrojEpizoda;
        _epizode = new Epizoda[_maxBrojEpizoda];
        _trenutnoEpizoda = 0;

    }
    //Z5.2
    Serija(const Serija& obj) {
        _naziv = AlocirajIKopiraj(obj._naziv);
        _trenutnoUloga = obj._trenutnoUloga;
        //
        for (int i = 0; i < _trenutnoUloga; i++)
        {
            _uloge[i] = new Uloga;
            _uloge[i]->SetGlumac(obj._uloge[i]->GetGlumac());
            _uloge[i]->SetOpis(obj._uloge[i]->GetOpis());
            _uloge[i]->SetTipUloge(obj._uloge[i]->GetTipUloge());
        }
        _maxBrojEpizoda = obj._maxBrojEpizoda;
        _trenutnoEpizoda = obj._trenutnoEpizoda;
        _epizode = new Epizoda[_maxBrojEpizoda];
        for (int i = 0; i < _trenutnoEpizoda; i++)
        {
            _epizode[i].SetNaziv(obj._epizode->GetNaziv());
            _epizode[i].SetTrajanje(obj._epizode->GetTrajanje());
            _epizode[i].SetKratakSadrzaj(obj._epizode->GetKratakSadrzaj());
            _epizode[i].SetDatumPremijere(obj._epizode->GetDatumPremijere());
            
            for (int y = 0; y < obj._epizode[i].GetTrenutnoOcjena(); y++)
            {
                _epizode[i].DodajOcjenu(obj._epizode[i].GetOcjena(y));
            }
           
            
        }
    }

    //Z5.3
    bool DodajUlogu(Uloga& uloga) {
        if (_trenutnoUloga == 50)
            return false;
        _uloge[_trenutnoUloga] = new Uloga(uloga);
        _trenutnoUloga++;
        return true;
    }
    //Z5.4
    bool DodajEpizodu(Epizoda& ep) {
        if (_maxBrojEpizoda == _trenutnoEpizoda)
            return false;
        _epizode[_trenutnoEpizoda].SetNaziv(ep.GetNaziv());
        _epizode[_trenutnoEpizoda].SetTrajanje(ep.GetTrajanje());
        _epizode[_trenutnoEpizoda].SetDatumPremijere(ep.GetDatumPremijere());
        _epizode[_trenutnoEpizoda].SetDatumPremijere(ep.GetDatumPremijere());
        for (int y = 0; y < ep.GetTrenutnoOcjena(); y++)
        {
            _epizode[_trenutnoEpizoda].DodajOcjenu(ep.GetOcjena(y));
            
        }
        _trenutnoEpizoda++;
        return true;
    }
    //Z5.5
    Epizoda* GetNajboljeOcijenjenaEpizoda() {
        Epizoda* temp = _epizode;
        for (int z = 1; z < _trenutnoEpizoda; z++)
        {
            if (_epizode[z].GetProsjecnaOcjena() > temp->GetProsjecnaOcjena())
                temp = &_epizode[z];
        }
        return temp;
    }
    //Z5.6 :: Pored ostalih atributa ispisati i sve uloge i sve epizode
    void Ispis() {
        cout << "Naziv: " << _naziv << endl;
        cout << "Uloge: " << endl;
        for (int i = 0; i < _trenutnoUloga; i++)
        {
            _uloge[i]->Ispis();
        }
        cout << "Epizode: " << endl;
        for (int j = 0; j < _trenutnoEpizoda; j++)
        {
            _epizode[j].Ispis();
        }
    }
    //Z5.7
    ~Serija() {
        delete[] _naziv; _naziv = nullptr;
        for (int i = 0; i < _trenutnoUloga; i++)
        {
            delete _uloge[i]; _uloge[i] = nullptr;
        }
        _epizode = nullptr;     // Da li je potrebno nulirati pokazivac ili ga prepustiti maticnom destruktoru
    }
    
};