#include <bits/stdc++.h>

using namespace std;

int alegeCaracter();

enum stareCaracter {
    Mort = 0,
    Viu = 1
};

class Caracter {
private:
    int nivel;
    int bani;
    string categorie;
    int viata;
    int putere;
    stareCaracter stare;
public:
    Caracter(string categorie = "N/A", int viata = 100, int putere = 20, int nivel = 1, int bani = 100, stareCaracter stare = Viu);
    Caracter(const Caracter&);
    ~Caracter(){};

    void setCategorie(string categorie, int viata, int putere);
    void detaliiCaracter(ostream&);

    friend ostream& operator <<(ostream&, Caracter&);
};

Caracter::Caracter(string categorie, int viata, int putere, int nivel, int bani, stareCaracter stare) {
    this -> categorie = categorie;
    this -> viata = viata;
    this -> putere = putere;
    this -> nivel = nivel;
    this -> bani = bani;
    this -> stare = stare;
    cout << "Caracterul a fost creat!" <<endl;
}

void Caracter::setCategorie(string categorie, int viata, int putere) {
    this -> categorie = categorie;
    this -> viata = viata;
    this -> putere = putere;
}

ostream& operator <<(ostream& out, Caracter& c){
    c.detaliiCaracter(out);
    return out;
}

void Caracter::detaliiCaracter(ostream& out) {
    out << "Categorie: " << categorie << endl;
    out << "HP: " << viata << endl;
    out << "Putere: " << putere << endl;
    out << "Nivel: " << nivel << endl;
    out << "Bani: " << bani << endl;
}

class Arme {
private:
    int pret;
    string nume;
    int nivel;
    int putere;
    string categorie;
public:
    Arme(int pret = 30, string nume = "Sabie", int nivel = 1, int putere = 30, string categorie = "Razboinic");
    Arme(const Arme&);
    ~Arme(){};

    int getPret() { return pret; }
    int getNivel() { return nivel; }
    string getNume() { return nume; }
    string getCategorieArma() { return categorie; }

    friend ostream& operator <<(ostream&, Arme&);
    void detaliiArma(ostream&);
};

Arme::Arme(int pret, string nume, int nivel, int putere, string categorie) {
    this -> pret = pret;
    this -> nume = nume;
    this -> nivel = nivel;
    this -> putere = putere;
    this -> categorie = categorie;
}

Arme::Arme(const Arme& a) {
    this->pret = a.pret;
    this->nume = a.nume;
    this->nivel = a.nivel;
    this->putere = a.putere;
    this->categorie = a.categorie;
}

ostream& operator <<(ostream& out, Arme& a){
    a.detaliiArma(out);
    return out;
}

void Arme::detaliiArma(ostream &out) {
    out << "Pret: " << pret << endl;
    out << "Nume: " << nume << endl;
    out << "Nivel necesar: " << nivel << endl;
    out << "+" << putere << " putere" << endl;
    out << "Categorie necesara: " << categorie << endl;
}

class Magazin {
private:
    vector<Arme> inventar;
public:
    Magazin(vector<Arme> inventar = {});

    void adaugaArme(Arme &);
    void afiseazaInventar();
};

Magazin::Magazin(vector<Arme> inventar) {
    this -> inventar = inventar;
}

void Magazin::adaugaArme(Arme &a) {
    inventar.push_back(Arme(30,"Sabie",1,15,"Razboinic"));
    inventar.push_back(Arme(40,"Sulita",1,20,"Razboinic"));
    inventar.push_back(Arme(30,"Cutit",1,25,"Ninja"));
    inventar.push_back(Arme(40,"Arc",1,30,"Ninja"));
}

void Magazin::afiseazaInventar() {
    cout << "+++++ Asta este marfa +++++\n";
    for (int i = 0; i < inventar.size(); i++) {
        cout << i+1 << inventar[i] << endl;
    }
    cout << "+++++++++++++++++++++++++++\n";
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
    cout<<" Introdu 3 pentru a te duce la negustorul de armuri "<<endl;
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
    while(stop == false) {
        uiMeniu();
        cout<<"Alege ce sa faci: ";
        cin>>opt;
        switch (opt) {
            case 1:
                erou.detaliiCaracter(cout);
                break;
            case 2:
                magazin.afiseazaInventar();
                break;
            case 3:
                cout << "N/A" << endl;
                break;
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
        system("pause");
        system("cls");
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
