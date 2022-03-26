#pragma once
#include "Datum.h"
#include "_PomocneFunkcije.h"


class Epizoda {
private:
	char* _naziv;
	int* _trajanje; //u minutama
	char _kratakSadrzaj[100];
	Datum _datumPremijere;

	int _maxBrojOcjena; // velicina niza
	int _trenutnoOcjena; //brojac
	int* _ocjene;
public:
	//Z3.0
	//Settovati vrijednosti na defaultne
	Epizoda() {
		_naziv = nullptr;
		_trajanje = nullptr;
		strcpy_s(_kratakSadrzaj, 100, " ");
		_maxBrojOcjena = 0;
		_trenutnoOcjena = 0;
		_ocjene = nullptr;
	}
	//Z3.1
	Epizoda(const char* naziv, int trajanje, const char* kratakOpis, Datum datum, int ukupnoOcjena)
		: _datumPremijere(datum)
	{
		_naziv = AlocirajIKopiraj(naziv);
		_trajanje = new int(trajanje);
		strcpy_s(_kratakSadrzaj, 100, kratakOpis);
		_maxBrojOcjena = ukupnoOcjena;
		_trenutnoOcjena = 0;
		_ocjene = new int[_maxBrojOcjena];
	}
	//Z3.2
	Epizoda(const Epizoda& obj)
		: _datumPremijere(obj._datumPremijere)
	{
		_naziv = AlocirajIKopiraj(obj._naziv);
		_trajanje = new int(*obj._trajanje);
		strcpy_s(_kratakSadrzaj, 100, obj._kratakSadrzaj);
		_maxBrojOcjena = obj._maxBrojOcjena;
		_trenutnoOcjena = obj._trenutnoOcjena;
		_ocjene = new int[_maxBrojOcjena];
		for (int i = 0; i < _trenutnoOcjena; i++)
		{
			_ocjene[i] = obj._ocjene[i];
		}
	}

	//Z3.3
	Epizoda(Epizoda&& obj)
		: _datumPremijere(move(obj._datumPremijere))					// move constructor radi u zaglavlju
	{
		_naziv = obj._naziv;
		obj._naziv = nullptr;
		_trajanje = obj._trajanje;
		obj._trajanje = nullptr;
		strcpy_s(_kratakSadrzaj, 100, obj._kratakSadrzaj);
		strcpy_s(obj._kratakSadrzaj, 100, " ");
		_maxBrojOcjena = obj._maxBrojOcjena;
		_trenutnoOcjena = obj._trenutnoOcjena;
		_ocjene = obj._ocjene;
		obj._ocjene = nullptr;

	}

	//Z3.4
	char* GetNaziv() const { return _naziv; }
	int GetTrajanje() const { return *_trajanje; }
	const char* GetKratakSadrzaj() const { return _kratakSadrzaj; }
	Datum GetDatumPremijere() const { return _datumPremijere; }
	int GetTrenutnoOcjena() const { return _trenutnoOcjena; }
	int GetMaxBrojOcjena() const { return _maxBrojOcjena; }

	//Z3.5
	//Vratiti vrijednost na lokaciji specificiranoj ulaznim parametrom 'index'
	//Ukoliko je proslijedjena nevalidna vrijednost, potrebno je vratiti element niza sa najblizim validnim indeksom
	//Npr. Ako je index = -5, vratiti vrijednost _ocjene na indexu 0; Isto vazi i za indekse vece od vrijednosti brojaca '_trenutnoOcjena'.
	int GetOcjena(int index) const {
		index = Min(index, _trenutnoOcjena);
		index = Max(0, index);
		return _ocjene[index];
	}
	//Z3.6
	void SetNaziv(const char* naziv) {
		delete[] _naziv;
		_naziv = AlocirajIKopiraj(naziv);
	}
	void SetTrajanje(int trajanje) {
		if (_trajanje == nullptr)
			_trajanje = new int;
		*_trajanje = trajanje;
	}
	void SetKratakSadrzaj(const char* kratakSadrzaj) {
		strcpy_s(_kratakSadrzaj, 100, kratakSadrzaj);
	}
	void SetDatumPremijere(Datum datum) {
		_datumPremijere.SetDan(datum.GetDan());
		_datumPremijere.SetMjesec(datum.GetMjesec());
		_datumPremijere.SetGodina(datum.GetGodina());
	}

	//Z3.7
	//Prosiriti niza _ocjene na sljedeci nacin:
	//  *Konstruisati novi niz velicine [_maxBrojOcjena + prosiriZa]
	//  *Kopirati vrijednosti iz starog niza u novi niz
	//  *Dealocirati stari niz
	void ProsiriNizOcjena(int prosiriZa) {
		if (_ocjene == nullptr) {
			_ocjene = new int[prosiriZa];
			_maxBrojOcjena += prosiriZa;
		}
		else {
			int* temp = _ocjene;
			_maxBrojOcjena += prosiriZa;
			_ocjene = new int[_maxBrojOcjena];
			for (int i = 0; i < _trenutnoOcjena; i++)
			{
				_ocjene[i] = temp[i];
			}
			delete[] temp;
			temp = nullptr;
		}
		
	}

	//Z3.8
	//Ukoliko je brojac dosao do kraja (jednak velicini niza), uraditi prosirivanje niza za 10 elemenata;
	void DodajOcjenu(int ocjena) {
		if (_trenutnoOcjena == _maxBrojOcjena)
			ProsiriNizOcjena(10);
		_ocjene[_trenutnoOcjena] = ocjena;
		_trenutnoOcjena++;
	}
	//Z3.9
	bool UkloniZadnjuOcjenu() {
		if (_trenutnoOcjena == 0)
			return false;
		_trenutnoOcjena--;
		return true;
	}

	//Z3.10
	float GetProsjecnaOcjena() {
		if (_trenutnoOcjena == 0)
			return 0;

		float zbir = 0;
		for (int k = 0; k < _trenutnoOcjena; k++)
		{
			zbir += _ocjene[k];
		}

		return (float)(zbir / _trenutnoOcjena);
	}
	//Z3.11
	void Ispis() {
		cout << "Naziv: " << _naziv << endl;
		cout << "Trajanje (u minutama): " << *_trajanje << endl;
		cout << "Kratak sadrzaj: " << _kratakSadrzaj << endl;
		cout << "Premijerno prikazivanje: ";
		_datumPremijere.Ispis();
		cout << endl;
		cout << "Prosjecna ocjena: " << GetProsjecnaOcjena() << endl;

	}
	//Z3.12
	~Epizoda() {
		delete[] _naziv; _naziv = nullptr;
		delete _trajanje; _trajanje = nullptr;
		delete[] _ocjene; _ocjene = nullptr;
	}
};
