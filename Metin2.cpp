#include <iostream>
#include <vector>
#include <string>

using namespace std;

int alegeCaracter();

enum stareCaracter {
    Mort = 0,
    Viu = 1
};

class Arme {
private:
    int pret;
    string nume;
    int nivel;
    int putere;
    string categorie;
    int id;
public:
    Arme(int pret = 30, string nume = "Sabie", int nivel = 1, int putere = 30, string categorie = "Razboinic", int id = 1);
    Arme(const Arme&);
    ~Arme(){};

    int getPret() const {return pret;}
    int getNivel() const {return nivel;}
    string getNume() const {return nume;}
    string getCategorieArma() const {return categorie;}
    int getPutere() const {return putere;}
    int getId() const {return id;}

    Arme& operator=(const Arme &a);
    friend ostream& operator <<(ostream&, const Arme&);
    friend istream& operator >>(istream&, Arme&);
    void detaliiArma(ostream&) const;
};

Arme &Arme::operator=(const Arme &a) {
    if (this != &a) {
        this->pret = a.pret;
        this->nume = a.nume;
        this->nivel = a.nivel;
        this->putere = a.putere;
        this->categorie = a.categorie;
        this->id = a.id;
    }
    return *this;
}

Arme::Arme(int pret, string nume, int nivel, int putere, string categorie, int id) {
    this -> pret = pret;
    this -> nume = nume;
    this -> nivel = nivel;
    this -> putere = putere;
    this -> categorie = categorie;
    this -> id = id;
}

Arme::Arme(const Arme& a) {
    this->pret = a.pret;
    this->nume = a.nume;
    this->nivel = a.nivel;
    this->putere = a.putere;
    this->categorie = a.categorie;
    this->id = a.id;
}

ostream& operator <<(ostream& out, const Arme& a) {
    a.detaliiArma(out);
    return out;
}

istream& operator >>(istream& in, Arme& a) {
    cout << "Introdu numele armei: ";
    in >> a.nume;
    return in;
}

void Arme::detaliiArma(ostream &out) const {
    out << "Id: " << id << endl;
    out << "Nume: " << nume << endl;
    out << "Pret: " << pret << endl;
    out << "Nivel necesar: " << nivel << endl;
    out << "+" << putere << " putere" << endl;
    out << "Categorie necesara: " << categorie << endl;
}

class Caracter {
private:
    int nivel;
    int bani;
    string categorie;
    int viata;
    int putere;
    stareCaracter stare;
    vector<Arme> inventar;
    vector<Arme> armaEchipata;
    string nume;
public:
    Caracter(string categorie = "N/A", int viata = 100, int putere = 20, int nivel = 1, int bani = 100, stareCaracter stare = Viu, vector<Arme> inventar = {}, vector<Arme> armaEchipata = {}, string nume = "N/A");
    Caracter(const Caracter&);
    ~Caracter(){};

    void setCategorie(string categorie, int viata, int putere);
    void detaliiCaracter(ostream&);
    void setNume(istream&);
    void afiseazaInventar();
    bool cumparaArma(const Arme &a);
    void echipeazaArma(const Arme &a);
    int getBani() const {return bani;}
    int getInventar() const {return inventar.size();}
    Arme alegeArma();

    void operator +=(int suma) {
        this -> bani += suma;
        cout << "Ai primit " << suma << " !\n";
        cout << "Bani actuali: " << this -> bani << endl;
    }
    friend ostream& operator <<(ostream&, Caracter&);
    friend istream& operator >>(istream&, Caracter&);
};

Caracter::Caracter(string categorie, int viata, int putere, int nivel, int bani, stareCaracter stare, vector<Arme> inventar, vector<Arme> armaEchipata,string nume) {
    this -> categorie = categorie;
    this -> viata = viata;
    this -> putere = putere;
    this -> nivel = nivel;
    this -> bani = bani;
    this -> stare = stare;
    this -> inventar = inventar;
    this -> armaEchipata = armaEchipata;
    this -> nume = nume;
    cout << "Caracterul a fost creat!" <<endl;
}

void Caracter::setCategorie(string categorie, int viata, int putere) {
    this -> categorie = categorie;
    this -> viata = viata;
    this -> putere = putere;
}

void Caracter::setNume(istream &in) {
    cout << "Nume: ";
    in >> nume;
}

ostream& operator <<(ostream& out, Caracter& c){
    c.detaliiCaracter(out);
    return out;
}

istream& operator >>(istream& in, Caracter& c){
    c.setNume(in);
    return in;
}

void Caracter::afiseazaInventar() {
    cout << "Inventar: \n";
    if (inventar.size() == 0) {
        cout << "Inventarul este gol!\n";
    }
    else {
        for (int i = 0; i < inventar.size(); i++) {
            cout << inventar[i] << " ";
        }
    }
}

void Caracter::detaliiCaracter(ostream& out) {
    out << "Nume: " << nume << endl;
    out << "Categorie: " << categorie << endl;
    out << "HP: " << viata << endl;
    out << "Putere: " << putere << endl;
    out << "Nivel: " << nivel << endl;
    out << "Bani: " << bani << endl;
}

bool Caracter::cumparaArma(const Arme &a) {
    if (this -> bani < a.getPret()) {
        cout << "Nu ai bani!\n";
        return false;
    }
    if (this -> nivel < a.getNivel()) {
        cout << "Nu ai nivelul necesar! \n";
        return false;
    }
    if (this -> categorie != a.getCategorieArma()) {
        cout << "Aceasta arma nu este de categoria ta! \n";
        return false;
    }
    this -> bani -= a.getPret();
    inventar.push_back(a);
    cout << "Ai cumaparat " << a.getNume() << " !\n";
    return true;
}

void Caracter::echipeazaArma(const Arme &a) {
    if (inventar.size() == 0) {
        cout << "Nu ai ce sa echipezi!\n";
    }
    else {
        armaEchipata.push_back(a);
        this -> putere += a.getPutere();
        cout << "Ai echipat " << a.getNume() << " si ti-a crescut puterea cu " << a.getPutere() << " !\n";
        for (vector<Arme>::iterator i = inventar.begin(); i != inventar.end(); i++) {
            if (i->getNume() == a.getNume()) {
                inventar.erase(i);
                break;
            }
        }
    }
}

Arme Caracter::alegeArma() {
    cout << "Ce arma echipezi?\n";
    int id;
    for (int i = 0 ; i < inventar.size(); i++) {
        cout << i+1 << ". " << inventar[i] << endl;
    }
    cout << "Ce arma echipezi?\n";
    cout << "Alege: ";
    cin >> id;
    return inventar[id-1];
}

class Magazin {
private:
    vector<Arme> inventar;
public:
    Magazin(vector<Arme> inventar = {});
    Arme getArma(int idx);
    void adaugaArme();
    void afiseazaInventar();
    int getInvetarSize() const {return inventar.size();}
};

Magazin::Magazin(vector<Arme> inventar) {
    this -> inventar = inventar;
}

void Magazin::adaugaArme() {
    inventar.push_back(Arme(30,"Sabie",1,15,"Razboinic",1));
    inventar.push_back(Arme(40,"Sulita",1,20,"Razboinic",2));
    inventar.push_back(Arme(30,"Cutit",1,25,"Ninja",3));
    inventar.push_back(Arme(40,"Arc",1,30,"Ninja",4));
}

void Magazin::afiseazaInventar() {
    cout << "+++++ Asta este marfa +++++\n";
    for (int i = 0; i < inventar.size(); i++) {
        cout << inventar[i] << endl;
    }
    cout << "+++++++++++++++++++++++++++\n";
}

Arme Magazin::getArma(int idx) {
    if (idx >=0 && idx <=(int)inventar.size()) {
        return inventar[idx];
    }
    cout << "Eroare!!!!\n";
    return Arme(0,"N/A",0,0,"N/A");
}

void uiMeniuStart() {
    cout<<"+++++++++++++++++++++++++++++++"<<endl;
    cout <<"+++++ Creeaza caracterul +++++" << endl;
    cout<<"+++++++++++++++++++++++++++++++"<<endl;
}

void uiMeniu() {
    cout<<"+++++++++++++++++++++++++++++++"<<endl;
    cout<<" Introdu 1 pentru a vedea detaliile caracterului "<<endl;
    cout<<" Introdu 2 pentru a merge la magazin "<<endl;
    cout<<" Introdu 3 pentru a echipa arma cumparata "<<endl;
    cout<<" Introdu 4 pentru a sparge piatra metin"<<endl;
    cout<<" Introdu 5 pentru a intra in arena "<<endl;
    cout<<" Pentru a iesi din program apasa 0"<<endl;
    cout<<"-----------------------------\n";
}

void meniu () {
    bool stop = false;
    int opt;
    uiMeniuStart();
    int ac;
    ac = alegeCaracter();
    Caracter erou;
    Magazin magazin;
    if (ac == 1) {
        cout << "Ai ales Razboinic! \n";
        erou.setCategorie("Razboinic", 100, 70);
    }
    else {
        cout << "Ai ales Ninja! \n";
        erou.setCategorie("Ninja", 70, 100);
    }
    cout << "Pune un nume caracterului!\n";
    erou.setNume(cin);
    while(stop == false) {
        uiMeniu();
        cout<<"Alege ce sa faci: ";
        cin>>opt;
        switch (opt) {
            case 1:
                int alg;
                cout << "Pentru inventar apasa 1 | Pentru detalii apasa 2\n";
                cout << "Alegere: ";
                cin >> alg;
                if (alg == 1) {
                    erou.afiseazaInventar();
                }
                else if (alg == 2) {
                    erou.detaliiCaracter(cout);
                }
                else {
                    cout << "Invalid\n";
                }
                break;
            case 2: {
                int nr, id, bani;
                int cos = 0;
                vector <Arme>optiuni = {};
                magazin.adaugaArme();
                magazin.afiseazaInventar();
                cout << "Banii tai: ";
                bani = erou.getBani();
                cout << bani << endl;
                cout << "Cate arme vrei sa cumperi?\n";
                cout << "Nr: ";
                cin >> nr;
                for (int i = 0; i < nr; i++) {
                    Arme armaTemp;
                    cin >> armaTemp;
                    for (int j = 0; j < magazin.getInvetarSize(); j++) {
                        Arme a = magazin.getArma(j);
                        if (a.getNume() == armaTemp.getNume()) {
                            optiuni.push_back(a);
                            cos += a.getPret();
                        }
                    }
                }
                cout << "Totalul este " << cos << " bani!\n";
                if (erou.getBani() < cos) {
                    cout << "Nu ai bani suficienti!\n";
                }
                else {
                    for (int i = 0; i <= optiuni.size(); i++) {
                        erou.cumparaArma(optiuni[i]);
                    }
                    cout << "Armele au fost adaugate in inventar!\n";
                }
                break;
            }
            case 3: {
                Arme arma = erou.alegeArma();
                if (erou.getInventar() == 0) {
                    cout << "Nu ai arme!\n";
                }
                else {
                    erou.echipeazaArma(arma);
                }
                break;
            }
            case 4:
                cout << "N/A" << endl;
                break;
            case 5:
                cout << "N/A" << endl;
                break;
            case 0:
                cout << "Ai iesit! Nu s-a salvat nimic." << endl;
                stop = true;
                break;
            default:
                cout << "Optiune nevalida! Incearca din nou.\n";
        }
    }
}

int alegeCaracter() {
    bool valid = false;
    int op;
    while (!valid) {
        cout << "+++++ Alege caracterul +++++ \n";
        cout << "Razboinic (HP - Mare | DMG - Mediu ) [Tasta 1] \n";
        cout << "Ninja (HP - Mediu | DMG - Mare ) [Tasta 2] \n";
        cout << "Alegerea ta: ";
        cin >> op;
        if (op == 1 || op == 2) {
            valid = true;
        }
        else {
            cout << "Optiune invalida! Alege 1 sau 2\n";
        }
    }
    return op;
}
int main() {

    meniu();
    return 0;
}
