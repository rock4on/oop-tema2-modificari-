#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Farmacie_abstracta {
protected:
	string s;
	public:
	Farmacie_abstracta(){
		s.assign("");
	}

	Farmacie_abstracta(string str)
	{
		s.assign(str);
	}

	Farmacie_abstracta(Farmacie_abstracta& f)
	{
		s.assign(f.s);
	}

	virtual ~Farmacie_abstracta() {

		};


	virtual void afisare() = 0;
	virtual void calcul_venit() = 0;
};

class Farmacie_offline :public virtual Farmacie_abstracta{
protected:
	int nr_luni;
	double* cifra_afaceri_luna;

public:

	Farmacie_offline():Farmacie_abstracta() {
		nr_luni = 0;
		cifra_afaceri_luna = new double[nr_luni];
	}

	Farmacie_offline(string s) : Farmacie_abstracta(s)
	{
		nr_luni = 0;
		cifra_afaceri_luna = new double[nr_luni];
	}

	Farmacie_offline(int nr, string s = " ") :Farmacie_abstracta(s)
	{
		nr_luni = nr;
		cifra_afaceri_luna = new double[nr_luni];
	}
	
	Farmacie_offline(Farmacie_offline& fo) :Farmacie_abstracta(fo)
	{
		nr_luni = fo.nr_luni;
		cifra_afaceri_luna = new double[nr_luni];
		for (int i = 0; i < nr_luni; i++)
		{
			cifra_afaceri_luna[i] = fo.cifra_afaceri_luna[i];
		}
	}

	friend istream& operator >>(istream &in,Farmacie_offline &fo)
	{
		cout << "nr luni:" << endl;
		in >> fo.nr_luni;
		delete fo.cifra_afaceri_luna;
		fo.cifra_afaceri_luna = new double[fo.nr_luni];

		for (int i = 0; i < fo.nr_luni; i++)
		{
			cout << "luna " << i << " \n";
			in>>fo.cifra_afaceri_luna[i];
		}

		return in;
	}

	Farmacie_offline& operator =(Farmacie_offline& fo)
	{
		s = fo.s;
		nr_luni = fo.nr_luni;
		cifra_afaceri_luna = new double[nr_luni];
		for (int i = 0; i < nr_luni; i++)
		{
			cifra_afaceri_luna[i] = fo.cifra_afaceri_luna[i];
		}
		return *this;
	}





	~Farmacie_offline()
	{
		delete cifra_afaceri_luna;
	}

	virtual void calcul_venit()
	{
		int nr=0;
		for (int i = 0; i < nr_luni; i++)
		{
			nr += (int)cifra_afaceri_luna[i];
		}
		cout <<"nr:"<< nr<<endl;
	}

	virtual void afisare() {
		calcul_venit();
	}


};

class Farmacie_online :public virtual Farmacie_abstracta {
protected:
	string adresa_web;
	int nr_vizitatori;
public:

	Farmacie_online(int nr = 0, string adr = " ",string s=" ") :Farmacie_abstracta(s)
	{
		adresa_web = adr;
		nr_vizitatori = nr;
	}
	Farmacie_online(Farmacie_online &f) : Farmacie_abstracta(f)
	{
		adresa_web = f.adresa_web;
		nr_vizitatori = f.nr_vizitatori;
	}
	

	Farmacie_online& operator =(Farmacie_online& fo)
	{
		adresa_web = fo.adresa_web;
		nr_vizitatori = fo.nr_vizitatori;
		return *this;
	}

	friend istream& operator >>(istream& in, Farmacie_online& fo)
	{
		cout << "adresa web\n ";
		in >> fo.adresa_web;
		cout << "nr viz\n ";
		in >> fo.nr_vizitatori;
		return in;
	}




	virtual void calcul_venit()
	{

	}
	virtual void afisare()
	{
		cout <<"adr : "<< adresa_web<<endl;
		cout <<"nr viz:"<< nr_vizitatori<<endl;
	}




};


class Farmacie_dubla_specializare :public Farmacie_offline, public Farmacie_online {
protected:
	int nr_angajati;
public:

	Farmacie_dubla_specializare(int nr=0,int luni=0,int nr_viz=0,string adresa=" ",string nume=" ") :Farmacie_offline(luni,nume),Farmacie_online(luni,adresa,nume)
	{
		nr_angajati = nr;
	}
	Farmacie_dubla_specializare(Farmacie_dubla_specializare& f) :Farmacie_offline(f), Farmacie_online(f)
	{
		nr_angajati = f.nr_angajati;
	}
	virtual void calcul_venit()
	{
		int nr = 0;
		for (int i = 0; i < nr_luni; i++)
		{
			nr += cifra_afaceri_luna[i];
		}
		cout << nr << endl;
	}

	Farmacie_dubla_specializare& operator =(Farmacie_dubla_specializare& fo)
	{
		s = fo.s;
		nr_luni = fo.nr_luni;
		cifra_afaceri_luna = new double[nr_luni];
		for (int i = 0; i < nr_luni; i++)
		{
			cifra_afaceri_luna[i] = fo.cifra_afaceri_luna[i];
		}
		adresa_web = fo.adresa_web;
		nr_vizitatori = fo.nr_vizitatori;
		return *this;
	}


	friend istream& operator >>(istream& in, Farmacie_dubla_specializare& fo)
	{
		cout <<" nr_angajati"<<endl;
		cin >> fo.nr_angajati;
		cout << "nr luni:" << endl;
		in >> fo.nr_luni;
		delete fo.cifra_afaceri_luna;
		fo.cifra_afaceri_luna = new double[fo.nr_luni];

		for (int i = 0; i < fo.nr_luni; i++)
		{
			in >> fo.cifra_afaceri_luna[i];
		}

		cout << "adresa_web"<<endl;
		in >> fo.adresa_web;
		cout << "nr viz:";
		in >> fo.nr_vizitatori;

		return in;
	}

	operator int() const { return nr_angajati; }

	virtual void afisare()
	{
		calcul_venit();
		cout << nr_angajati << endl;
		cout << adresa_web<<endl;
		cout << nr_vizitatori<<endl;
	}

};


void CitireSiAfisare(istream& in=cin)
{
	Farmacie_abstracta** vect;
	cout << "ne el:" << endl;
	int nr_elm;
	in >> nr_elm;
	vect = new Farmacie_abstracta * [nr_elm];

	int tip;
	
	for (int i = 0; i < nr_elm; i++)
	{
		cout << "0- dubla   1-farmacie offline 2+||0<-farmacie online  "<<endl;
		cout << "tip\n";
		in >> tip;
		if (tip == 0)
		{
			Farmacie_dubla_specializare* fd = new Farmacie_dubla_specializare();
			in >> *fd;
			vect[i] = fd;
		}
		else if (tip == 1)
		{
			Farmacie_offline* fon = new Farmacie_offline();
			in >> *fon;
			vect[i] = fon;
		}
		else {
			Farmacie_online* fof = new Farmacie_online();
			in >> *fof;
			vect[i] = fof;
		}
	}
	system("cls");
	for (int i = 0; i < nr_elm; i++)
	{
		cout << "el " << i << endl;
		vect[i]->afisare();
		cout << endl << endl;
	}


}




int main()
{
 // ifstream fisier("locatie");
  //pentru citire din fisier CitireSiAfisare(fisier);
	CitireSiAfisare();
}
