#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <random>

using namespace std;

int alegeCaracter(); // functie declarata pt ca imi dadea eroare

// asta o sa fac la caracter daca moare in pun ca e mor si se sterge tot
enum stareCaracter {
    Mort = 0,
    Viu = 1
};

class BugetInsuficientException : public exception {
    virtual const char* what() const noexcept {
        return "Nu ai bani!\n";
    }
};

class NivelMicException : public exception {
    virtual const char* what() const noexcept {
        return "Nu ai nivel necesar!\n";
    }
};

//clasa cu care Clasa caracter are o relatie de agregare
class Pet {
private:
    string nume;
    int putere;
    int viata;
public:
    Pet(string nume = "N/A", int putere = 0, int viata = 0);

    void setCategorie(string nume, int putere, int viata);
    string getNume() const {return nume;}
    int getPutere() const {return putere;}
    int getViata() const {return viata;}
};

Pet::Pet(string nume, int putere, int viata) {
    this -> nume = nume;
    this -> putere = putere;
    this -> viata = viata;
}

void Pet::setCategorie(string nume, int putere, int viata) {
    this -> nume = nume;
    this -> putere = putere;
    this -> viata = viata;
}


// clasa cu care clasa Caracter are o relatie de compunere
class Arme {
protected:
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

    virtual int getPret() const {return pret;}
    virtual int getNivel() const {return nivel;}
    virtual string getNume() const {return nume;}
    string getCategorieArma() const {return categorie;}
    int getPutere() const {return putere;}
    virtual int getId() const {return id;}

    Arme& operator=(const Arme &a); // operator = de copiere
    friend ostream& operator <<(ostream&, const Arme&);
    friend istream& operator >>(istream&, Arme&);
    void detaliiArma(ostream&) const;

    // operator incarcat ca functie non membra
    friend Arme operator<(const Arme &a1, const Arme &a2) {
        if (a1.pret < a2.pret)
        {
            return a1;
        }
        return a2;
    }
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

class Armura : public Arme
{
private:
    int viata;
public:
    Armura(int pret = 30, string nume = "Platosa", int nivel = 1, int putere = 0, string categorie = "Razboinic", int id = 1,int viata = 30);
    Armura(const Armura&);

    int getPret() const {return pret;}
    int getNivel() const {return nivel;}
    string getNume() const {return nume;}
    string getCategorieArmura() const {return categorie;}
    int getViata() const {return viata;}
    int getId() const {return id;}

    Armura& operator=(const Armura &a); // operator = de copiere
    friend ostream& operator <<(ostream&, const Armura&);
    friend istream& operator >>(istream&, Armura&);
    void detaliiArmura(ostream&) const;

    // operator incarcat ca functie non membra
    friend Armura operator<(const Armura &a1, const Armura &a2) {
        if (a1.pret < a2.pret)
        {
            return a1;
        }
        return a2;
    }
};

Armura &Armura::operator=(const Armura &a) {
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

Armura::Armura(int pret, string nume, int nivel, int putere, string categorie, int id, int viata) {
    this -> pret = pret;
    this -> nume = nume;
    this -> nivel = nivel;
    this -> putere = putere;
    this -> categorie = categorie;
    this -> id = id;
    this -> viata = viata;
}

Armura::Armura(const Armura& a) {
    this->pret = a.pret;
    this->nume = a.nume;
    this->nivel = a.nivel;
    this->putere = a.putere;
    this->categorie = a.categorie;
    this->id = a.id;
    this->viata = a.viata;
}

ostream& operator <<(ostream& out, const Armura& a) {
    a.detaliiArmura(out);
    return out;
}

istream& operator >>(istream& in, Armura& a) {
    cout << "Introdu numele armurii: ";
    in >> a.nume;
    return in;
}

void Armura::detaliiArmura(ostream &out) const {
    out << "Id: " << id << endl;
    out << "Nume: " << nume << endl;
    out << "Pret: " << pret << endl;
    out << "Nivel necesar: " << nivel << endl;
    out << "+" << viata << " viata" << endl;
    out << "Categorie necesara: " << categorie << endl;
}

// clasa principala
class Caracter {
private:
    int nivel;
    int bani;
    string categorie;
    int viata;
    int putere;
    int stare;
    vector<Arme> inventar; // relatie de compunere
    vector<Arme> armaEchipata;
    vector<Armura> inventar_armuri;
    vector<Armura> armuraEchipata;
    string nume;
    Pet *pet; // relatie de agregare
public:
    // constructor de initializare
    Caracter(string categorie = "N/A", int viata = 100, int putere = 20, int nivel = 1, int bani = 100, int stare = 1, vector<Arme> inventar = {}, vector<Arme> armaEchipata = {}, string nume = "N/A", Pet *pet = nullptr);
    Caracter(const Caracter&); // constructor de copiere
    ~Caracter(){}; // destructor

    // getteri setteri si alte functii
    void setCategorie(string categorie, int viata, int putere);
    void setPet(Pet *pet);
    void detaliiCaracter(ostream&);
    void setNume(istream&);
    void afiseazaInventar(); // functie membra
    void afiseazaInventarArmuri();
    bool cumparaArma(const Arme &a); // functie membra
    bool cumparaArmura(const Armura& a);
    void echipeazaArma(const Arme &a); // funtie membra
    void echipeazaArmura(const Armura& a);
    string getCategorie() const {return categorie;}
    int getBani() const {return bani;}
    int getInventar() const {return inventar.size();}
    int getInventarArmuri() const {return inventar_armuri.size();}
    int getViata() const {return viata;}
    int getStare() const {return stare;}
    int getPutere() const {return putere;}
    int getNivel() const {return nivel;}
    void setStare(int stare) {this -> stare = stare;}
    void setNivel(int nivel) {this -> nivel += nivel;}
    int DMG() const {return putere - nivel;}
    Arme alegeArma();
    Armura alegeArmura();
    Pet *getPet() {return pet;}


    // operator ca functie membra
    void operator +=(int suma) {
        this -> bani += suma;
        cout << "Ai primit " << suma << " bani !\n";
        cout << "Bani actuali: " << this -> bani << endl;
    }

    void operator -= (int hp) {
        this -> viata -= hp;
        cout << "Ai pierdut " << hp << " hp! \n";
        cout << "HP actual: " << this -> viata << endl;
    }

    friend ostream& operator <<(ostream&, Caracter&); // operator pentru afisare
    friend istream& operator >>(istream&, Caracter&); // operator pentru citire
};

Caracter::Caracter(string categorie, int viata, int putere, int nivel, int bani, int stare, vector<Arme> inventar, vector<Arme> armaEchipata, string nume, Pet *pet) {
    this -> categorie = categorie;
    this -> viata = viata;
    this -> putere = putere;
    this -> nivel = nivel;
    this -> bani = bani;
    this -> stare = stare;
    this -> inventar = inventar;
    this -> armaEchipata = armaEchipata;
    this -> nume = nume;
    this -> pet = pet;
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

void Caracter::setPet(Pet *p) {
    this -> viata = this -> viata + p -> getViata();
    this -> putere = this -> putere + p -> getPutere();
    this -> pet = p;
    cout << "Ai ales " << p -> getNume() << endl;
    if (p -> getPutere() > 0) {
        cout << "Puterea a crecut cu " << p -> getPutere() << "." << endl;
        cout << "Putere actuala: " << this -> putere << "." << endl;
    }
    if (p -> getViata() > 0) {
        cout << "Viata a crescut cu " << p -> getViata() << "." << endl;
        cout << "Viata actuala: " << this -> viata << "." << endl;
    }
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
            cout << inventar[i];
        }
    }
}

void Caracter::afiseazaInventarArmuri() {
    cout << "Inventar: \n";
    if (inventar_armuri.size() == 0) {
        cout << "Inventarul este gol!\n";
    }
    else {
        for (int i = 0; i < inventar_armuri.size(); i++) {
            cout << inventar_armuri[i];
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
    if (this -> pet != nullptr) {
        out << "Pet: " << pet -> getNume() << endl;
    }
    else {
        out << "Pet: Nu ai pet" << endl;
    }
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

bool Caracter::cumparaArmura(const Armura& a) {
    if (this -> bani < a.getPret()) {
        cout << "Nu ai bani!\n";
        return false;
    }
    if (this -> nivel < a.getNivel()) {
        cout << "Nu ai nivelul necesar! \n";
        return false;
    }
    if (this -> categorie != a.getCategorieArmura()) {
        cout << "Aceasta arma nu este de categoria ta! \n";
        return false;
    }
    this -> bani -= a.getPret();
    inventar_armuri.push_back(a);
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

void Caracter::echipeazaArmura(const Armura& a) {
    if (inventar_armuri.size() == 0) {
        cout << "Nu ai ce sa echipezi!\n";
    }
    else {
        armuraEchipata.push_back(a);
        this -> viata += a.getViata();
        cout << "Ai echipat " << a.getNume() << "si ti-a crescut viata cu " << a.getViata() << " !\n";
        for (vector<Armura>::iterator i = inventar_armuri.begin(); i != inventar_armuri.end(); i++) {
            if (i -> getNume() == a.getNume()) {
                inventar_armuri.erase(i);
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

Armura Caracter::alegeArmura() {
    cout << "Ce arumra echipezi?\n";
    int id;
    for (int i = 0; i < inventar_armuri.size(); i++) {
        cout << i+1 << ". " << inventar_armuri[i] << endl;
    }
    cout << "Ce arumra echipezi?\n";
    cout << "Alege: ";
    cin >> id;
    return inventar_armuri[id-1];
}

// clasa magazin (mai am de adaugat si armuri da e la fel ca la arme doar ca creste viata ci nu puterea)
class Magazin { // Reminder: sa fac o functie de unde pot cumpara licori de viata pentru a creste viata cand ies din arena
private:
    vector<Arme> inventar;
public:
    Magazin(vector<Arme> inventar = {});
    Arme getArma(int idx);
    void adauga();
    void sterge();
    void afiseazaInventar();
    int getInvetarSize() const {return inventar.size();}
};

Magazin::Magazin(vector<Arme> inventar) {
    this -> inventar = inventar;
}

void Magazin::adauga() {
    inventar.push_back(Arme(30,"Sabie",1,15,"Razboinic",1));
    inventar.push_back(Arme(40,"Sulita",1,20,"Razboinic",2));
    inventar.push_back(Arme(30,"Cutit",1,25,"Ninja",3));
    inventar.push_back(Arme(40,"Arc",1,30,"Ninja",4));
}

void Magazin::sterge() {
    inventar.clear();
}

void Magazin::afiseazaInventar() {
    cout << "+++++ Asta este marfa +++++\n";
    for (int i = 0; i < inventar.size(); i++) {
        cout << inventar[i] << endl;
    }
    cout << "+++++++++++++++++++++++++++\n";
}

Arme Magazin::getArma(int idx) {
    if (idx >=0 && idx <=inventar.size()) {
        return inventar[idx];
    }
    cout << "Eroare!!!!\n";
    return Arme(0,"N/A",0,0,"N/A");
}

class MagazinArmuri{
private:
    vector<Armura> inventar;
public:
    MagazinArmuri(vector<Armura> inventar = {});
    Armura getArmura(int idx);
    void adauga();
    void sterge();
    void afiseazaInventar();
    int getInvetarSize() const {return inventar.size();}
};

MagazinArmuri::MagazinArmuri(vector<Armura> inventar)
{
    this -> inventar = inventar;
}

Armura MagazinArmuri::getArmura(int idx)
{
    if (idx >=0 && idx <=inventar.size()) {
        return inventar[idx];
    }
    cout << "Eroare!!!!\n";
    return Armura(0,"N/A",0,0,"N/A",999999,0);
}

void MagazinArmuri::adauga()
{
    inventar.push_back(Armura(30,"Platosa",1,0,"Razboinic",1,30));
    inventar.push_back(Armura(30,"Costum ninja",1,0,"Ninja",2,50));
}

void MagazinArmuri::sterge()
{
    inventar.clear();
}

void MagazinArmuri::afiseazaInventar() {
    cout << "+++++ Asta este marfa +++++\n";
    for (int i = 0; i < inventar.size(); i++) {
        cout << inventar[i] << endl;
    }
    cout << "+++++++++++++++++++++++++++\n";
}


class Monstru{
protected:
    string nume;
    int viata;
    int nivel;
    int putere;
    int bani;
public:
    Monstru(string nume = "Monstru",int viata = 50,int nivel = 1,int putere = 20,int bani = 20):nume(nume),viata(viata),nivel(nivel),putere(putere),bani(bani){}
    Monstru(const Monstru&);
    virtual ~Monstru(){};
    int getViata() const {return viata;}
    int getNivel() const {return nivel;}
    int getBani() const {return bani;}
    int getPutere() const {return putere;}

    virtual void set(string nume,int viata,int nivel);
    virtual int DMG() const {return putere + nivel;}
    virtual void abilitateSpeciala() {}
    virtual void setLoot(Caracter& c) {}
    void operator -= (int hp) {
        this -> viata -= hp;
        cout << "Monstrul a pierut " << hp << " hp! \n";
        cout << "Viata monstrului: " << viata << " !\n";
    }
};

void Monstru::set(string nume, int viata, int nivel) {
    this -> nume = nume;
    this -> viata = viata;
    this -> nivel = nivel;
}

class MonstruFoc : public Monstru
{
private:
    vector<Arme> loot;
public:
    MonstruFoc(string nume = "Monstru foc", int viata = 100, int nivel = 5, int putere = 20, int bani = 40, vector<Arme> loot = {}):Monstru(nume,viata,nivel,putere,bani),loot(loot){}
    ~MonstruFoc(){};
    void setLoot(Caracter& c);
    int DMG() const {return putere + nivel * 2;}
    void abilitateSpeciala() {putere += 10;}
};

void MonstruFoc::setLoot(Caracter& c) {
    if (c.getCategorie() == "Razboinic")    loot.push_back(Arme(30,"Sabie",1,15,"Razboinic",1));
    else if (c.getCategorie() == "Ninja")   loot.push_back(Arme(30,"Cutit",1,25,"Ninja",3));
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
    cout<<" Introdu 3 pentru a echipa arma/armura cumparata "<<endl;
    cout<<" Introdu 4 pentru a iti alege un pet"<<endl;
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
    Magazin magazinArme;
    MagazinArmuri magazinArmuri;
    Pet p;
    Monstru monstru("Goblin");
    MonstruFoc monstruF("Dragon");
    stack<Monstru*> Dungeon;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(1,10);
    // alegerea caracterului
    if (ac == 1) {
        cout << "Ai ales Razboinic! \n";
        erou.setCategorie("Razboinic", 100, 70);
    }
    else {
        cout << "Ai ales Ninja! \n";
        erou.setCategorie("Ninja", 70, 100);
    }
    // setare nume pentru a folosi operatoul >> de citire
    cout << "Pune un nume caracterului!\n";
    erou.setNume(cin);
    while(stop == false && erou.getStare() == 1) {
        uiMeniu();
        cout<<"Alege ce sa faci: ";
        cin>>opt;
        switch (opt) {
            case 1:
                    // se afiseaza inventarul si detalii
                    int alg,alg1;
                    cout << "Pentru inventar apasa 1 | Pentru detalii apasa 2\n";
                    cout << "Alegere: ";
                    cin >> alg;
                    if (alg == 1) {
                        cout << "Arme [Tasta 1] | Armuri [Tasta 2]\n";
                        cout << "Alege: ";
                        cin >> alg1;
                        if (alg1 == 1)
                        {
                            erou.afiseazaInventar();
                        }
                        else if (alg1 == 2)
                        {
                            erou.afiseazaInventarArmuri();
                        }
                        else
                        {
                            cout << "Alegere invalida!\n";
                        }
                    }
                    else if (alg == 2) {
                        erou.detaliiCaracter(cout);
                    }
                    else {
                        cout << "Invalid\n";
                    }
                    break;
            case 2: {
                    // aici cumparam de la magazin si verifica daca am bani de arma sau arma este categoria mea
                    int alegere;
                    cout << "Magazin arme [Tasta 1] | Magazin armuri [Tasta 2]\n";
                    cout << "Alegere: ";
                    cin >> alegere;
                    if (alegere == 1)
                    {
                        int nr, bani;
                        int cos = 0;
                        vector <Arme>optiuni = {};
                        magazinArme.adauga();
                        magazinArme.afiseazaInventar();
                        cout << "Banii tai: ";
                        bani = erou.getBani();
                        cout << bani << endl;
                        cout << "Cate arme vrei sa cumperi?\n";
                        cout << "Nr: ";
                        cin >> nr;
                        for (int i = 0; i < nr; i++) {
                            Arme armaTemp;
                            cin >> armaTemp; // citirea a n obiecte
                            for (int j = 0; j < magazinArme.getInvetarSize(); j++) {
                                Arme a = magazinArme.getArma(j);
                                if (a.getNume() == armaTemp.getNume()) {
                                    optiuni.push_back(a);
                                    cos += a.getPret(); // salvarea in cos pentru un pret total
                                }
                            }
                        }
                        bool cumpara;
                        cout << "Totalul este " << cos << " bani!\n";
                        try
                        {
                            if (erou.getBani() >= cos) {
                                for (int i = 0; i < optiuni.size(); i++) {
                                    cumpara = erou.cumparaArma(optiuni[i]);
                                }
                                if (cumpara) {
                                    if (optiuni.size() == 1) {
                                        cout << "Arma a fost adaugata in inventar!\n";
                                    }
                                    else {
                                        cout << "Armele au fost adaugate in inventar!\n";
                                    }
                                }
                            }
                            else throw BugetInsuficientException();
                        }
                        catch (exception& e)
                        {
                            cout << e.what();
                        }
                        magazinArme.sterge();
                    }
                    else if (alegere == 2)
                    {
                        int nr, bani;
                        int cos = 0;
                        vector <Armura>optiuni = {};
                        magazinArmuri.adauga();
                        magazinArmuri.afiseazaInventar();
                        cout << "Banii tai: ";
                        bani = erou.getBani();
                        cout << bani << endl;
                        cout << "Cate armuri vrei sa cumperi?\n";
                        cout << "Nr: ";
                        cin >> nr;
                        for (int i = 0; i < nr; i++) {
                            Armura armuraTemp;
                            cin >> armuraTemp; // citirea a n obiecte
                            for (int j = 0; j < magazinArmuri.getInvetarSize(); j++) {
                                Armura a = magazinArmuri.getArmura(j);
                                if (a.getNume() == armuraTemp.getNume()) {
                                    optiuni.push_back(a);
                                    cos += a.getPret(); // salvarea in cos pentru un pret total
                                }
                            }
                        }
                        bool cumpara;
                        cout << "Totalul este " << cos << " bani!\n";
                        try
                        {
                            if (erou.getBani() >= cos) {
                                for (int i = 0; i < optiuni.size(); i++) {
                                    cumpara = erou.cumparaArmura(optiuni[i]);
                                }
                                if (cumpara) {
                                    if (optiuni.size() == 1) {
                                        cout << "Armura a fost adaugata in inventar!\n";
                                    }
                                    else {
                                        cout << "Armurile au fost adaugate in inventar!\n";
                                    }
                                }
                            }
                            else throw BugetInsuficientException();
                        }
                        catch (exception& e)
                        {
                            cout << e.what();
                        }
                        magazinArmuri.sterge();
                    }
                    break;
                }
            case 3: {
                    int echip;
                    cout << "Ce vrei sa echipezi?\n";
                    cout << "Arma [Tasta 1] | Armura [Tasta 2] \n";
                    cout << "Optiune: ";
                    cin >> echip;
                    if (echip == 1) {
                        // echipare arma ( se sterge din inventar si se echiepeaza, trb sa mai fac o functie sa si dezechipez sau sa inlocuiesc daca vr)
                        Arme arma = erou.alegeArma();
                        if (erou.getInventar() == 0) {
                            cout << "Nu ai arme!\n";
                        }
                        else {
                            erou.echipeazaArma(arma);
                        }
                    }
                    else if (echip == 2)
                    {
                        Armura armura = erou.alegeArmura();
                        if (erou.getInventarArmuri() == 0) {
                            cout << "Nu ai armuri!\n";
                        }
                        else {
                            erou.echipeazaArmura(armura);
                        }
                    }
                    else {
                        cout << "Optiune invalida!\n";
                    }
                    break;
                }
            case 4:
                {
                    // aici se face petul. daca deja avem pet nu mai face nimic
                    Pet *a = erou.getPet();
                    if (a == nullptr) {
                        int o;
                        cout << "Ce pet iti doresti?" << endl;
                        cout << "               [Tasta 1] - Phoenix de foc | [Tasta 2] - Phoenix de gheata \n";
                        cout << " Statistici:               + 30 putere    |             + 30 viata  \n";
                        cout << "Optiune: ";
                        cin >> o;
                        if (o == 1) {
                            p.setCategorie("Phoenix de foc", 30,0);
                        }
                        else if (o == 2) {
                            p.setCategorie("Phoenix de gheata", 0, 30);
                        }
                        else {
                            cout << "Optiune invalida! \n";
                        }
                        erou.setPet(&p);
                    }
                    else {
                        cout << "Ai deja pet! Poti alege doar 1!" << endl;
                    }
                    break;
            }
            case 5:
                {
                    cout << "Bun venit in Dungeon!" << endl;
                    bool cont = true;
                    Dungeon.push(&monstruF);
                    Dungeon.push(&monstru);
                    while (cont && erou.getStare() == Viu)
                    {
                        cout << "Continui?\n";
                        cout << "Da [Tasta 1] | Nu [Tasta 2] \n";
                        int asdf;
                        cout << "Alegerea ta: ";
                        cin >> asdf;
                        if (asdf == 1) {
                            if (Dungeon.empty()) {
                                cout << "Ai terminat jocul. Felicitari!!!\n";
                                cont = false;
                                continue;
                            }
                            Monstru* verif = Dungeon.top();
                            try
                            {
                                int niv = erou.getNivel();
                                verif->setLoot(erou);
                                if (niv >= verif->getNivel()) {
                                    if (erou.getPutere() > verif->getPutere() && erou.getViata() > verif->getViata()) {
                                        erou += verif->getBani();
                                        erou.setNivel(1);
                                        cout << "Felicitari! Ai trecut nivelul " << erou.getNivel() << " !\n";
                                        Dungeon.pop();
                                    }
                                    else
                                    {
                                        cout << "Ai murit!\n";
                                        erou.setStare(Mort);
                                    }
                                }
                                else throw NivelMicException();
                            }
                            catch (exception& e) {
                                cout << e.what();
                            }
                        }
                        else if (asdf == 2)
                        {
                            cout << "Revii cand ai tupeu!\n";
                            cont = false;
                        }
                    }
                }
                break;
            case 0:
                //iesirea
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