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
    Viu = 1,
    Batut = 3
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
// asta va fi clasa de baza pentru arme si armuri;
class Item {
protected:
    static int contorId;
    const int id;
    int pret;
    string nume;
    int nivel;
    string categorie;
public:
    Item(int pret, string nume, int nivel, string categorie) : id(++contorId), pret(pret), nume(nume), nivel(nivel), categorie(categorie){}
    Item(const Item& a) : id(a.id), pret(a.pret), nume(a.nume), nivel(a.nivel), categorie(a.categorie) {}
    virtual ~Item() = 0;

    virtual Item* clona() const = 0;
    int getPret() const {return pret;}
    int getNivel() const {return nivel;}
    string getNume() const {return nume;}
    string getCategorie() const {return categorie;}
    int getId() const {return id;}

    friend ostream& operator <<(ostream&, const Item&);
    virtual void detalii(ostream&) const;

};

int Item::contorId = 0;

Item::~Item() {}

ostream& operator <<(ostream& out, const Item& a) {
    a.detalii(out);
    return out;
}

void Item::detalii(ostream &out) const {
    out << "Id: " << id << endl;
    out << "Nume: " << nume << endl;
    out << "Pret: " << pret << endl;
    out << "Nivel necesar: " << nivel << endl;
    out << "Categorie necesara: " << categorie << endl;
}

// clasa cu care clasa Caracter are o relatie de compunere
class Arme : public Item{
protected:
    int putere;
public:
    Arme(int pret = 30, string nume = "Sabie", int nivel = 1, string categorie = "Razboinic", int putere = 30) : Item(pret, nume, nivel, categorie), putere(putere){}
    Arme(const Arme& a) : Item(a), putere(a.putere) {}
    ~Arme(){};

    Item* clona() const
    {
        return new Arme(*this);
    }
    int getPutere() const {return putere;}

    Arme& operator=(const Arme &a); // operator = de copiere
    friend ostream& operator <<(ostream&, const Arme&);
    friend istream& operator >>(istream&, Arme&);
    void detalii(ostream&) const;

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
    }
    return *this;
}

ostream& operator <<(ostream& out, const Arme& a) {
    a.detalii(out);
    return out;
}

istream& operator >>(istream& in, Arme& a) {
    cout << "Introdu numele armei: ";
    in >> a.nume;
    return in;
}

void Arme::detalii(ostream &out) const {
    Item::detalii(out);
    out << "+" << putere << " putere" << endl;
}

class Armura : public Item
{
private:
    int viata;
public:
    Armura(int pret = 30, string nume = "Platosa", int nivel = 1, string categorie = "Razboinic", int viata = 30) : Item(pret, nume, nivel, categorie), viata(viata) {}
    Armura(const Armura& a) : Item(a), viata(a.viata) {}
    ~Armura() {}

    int getViata() const {return viata;}

    Item* clona() const
    {
        return new Armura(*this);
    }
    Armura& operator=(const Armura &a); // operator = de copiere
    friend ostream& operator <<(ostream&, const Armura&);
    friend istream& operator >>(istream&, Armura&);
    void detalii(ostream&) const;

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
        this->viata = a.viata;
        this->categorie = a.categorie;
    }
    return *this;
}

ostream& operator <<(ostream& out, const Armura& a) {
    a.detalii(out);
    return out;
}

istream& operator >>(istream& in, Armura& a) {
    cout << "Introdu numele armurii: ";
    in >> a.nume;
    return in;
}

void Armura::detalii(ostream &out) const {
    Item::detalii(out);
    out << "+" << viata << " viata" << endl;
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
    vector<Item*> inventar; // relatie de compunere
    vector<Arme> armaEchipata;
    vector<Armura> armuraEchipata;
    string nume;
    Pet *pet; // relatie de agregare
public:
    // constructor de initializare
    Caracter(string categorie = "N/A", int viata = 100, int putere = 20, int nivel = 1, int bani = 100, int stare = 1, vector<Item*> inventar = {}, vector<Arme> armaEchipata = {}, vector<Armura> armuraEchipata = {}, string nume = "N/A", Pet *pet = nullptr);
    Caracter(const Caracter&); // constructor de copiere
    ~Caracter(){}; // destructor

    // getteri setteri si alte functii
    void setCategorie(string categorie, int viata, int putere);
    void setPet(Pet *pet);
    void detaliiCaracter(ostream&);
    void setNume(istream&);
    void afiseazaInventar(); // functie membra
    bool cumparaArma(const Arme &a); // functie membra
    bool cumparaArmura(const Armura& a);
    void echipeazaArma(int idx); // funtie membra
    void scoateArma();
    void echipeazaArmura(int idx);
    void scoateArmura();
    string getCategorie() const {return categorie;}
    int getBani() const {return bani;}
    int getInventar() const {return inventar.size();}
    int getViata() const {return viata;}
    int getStare() const {return stare;}
    int getPutere() const {return putere;}
    int getNivel() const {return nivel;}
    void setStare(int stare) {this -> stare = stare;}
    void levelUp() {nivel++;}
    void scadeBani(int pret) {bani -= pret;}
    void cresteViata(int hp) {viata += hp;}
    void crestePuterea(int pow) {putere += pow;}
    void scadeViata(int hp) {viata -= hp;}
    void scadePuterea(int pow) {putere -= pow;}
    int DMG() const {return putere - nivel;}
    Item* alegeArma();
    Item* alegeArmura();
    Pet *getPet() {return pet;}
    void adaugaArma(Arme& a);
    void adaugaArmura(Armura& a);
    void setNivel(int nivel) {this -> nivel = nivel;}
    void setBani(int bani) {this -> bani = bani;}
    void setViata(int viata) {this -> viata = viata;}
    void setPutere(int putere) {this -> putere = putere;}
    void viataMaxima() {viata = armuraEchipata[0].getViata() + 90 + 10 * nivel + pet->getViata();};

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

Caracter::Caracter(string categorie, int viata, int putere, int nivel, int bani, int stare, vector<Item*> inventar, vector<Arme> armaEchipata, vector<Armura> armuraEchipata, string nume, Pet *pet) {
    this -> categorie = categorie;
    this -> viata = viata;
    this -> putere = putere;
    this -> nivel = nivel;
    this -> bani = bani;
    this -> stare = stare;
    this -> inventar = inventar;
    this -> armaEchipata = armaEchipata;
    this -> armuraEchipata = armuraEchipata;
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
    cout << "------------------------------\n";
    if (inventar.size() == 0) {
        cout << "Inventarul este gol!\n";
    }
    else {
        for (int i = 0; i < inventar.size(); i++) {
            inventar[i]->detalii(cout);
            cout << "------------------------------\n";
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
    out << "Arma echipata: " << endl;
    out << "-----------" << endl;
    armaEchipata[0].detalii(out);
    out << "-----------" << endl;
    out << "Armura echipata: " << endl;
    out << "-----------" << endl;
    armuraEchipata[0].detalii(out);
    out << "-----------" << endl;
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
    if (this -> categorie != a.getCategorie()) {
        cout << a.getNume() << " nu este de categoria ta! \n";
        return false;
    }
    this -> bani -= a.getPret();
    inventar.push_back(a.clona());
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
    if (this -> categorie != a.getCategorie()) {
        cout << a.getNume() << " nu este de categoria ta! \n";
        return false;
    }
    this -> bani -= a.getPret();
    inventar.push_back(a.clona());
    cout << "Ai cumaparat " << a.getNume() << " !\n";
    return true;
}

void Caracter::scoateArma() {
    putere -= armaEchipata[0].getPutere();
    Arme arma = armaEchipata.back();
    Arme* copiearma = new Arme(arma);
    inventar.push_back(copiearma);
    armaEchipata.pop_back();
}

void Caracter::echipeazaArma(int idx) {
    if (inventar.size() == 0) {
        cout << "Nu ai ce sa echipezi!\n";
    }
    else {
        if (armaEchipata.size() == 0) {
            int ok = 0,id;
            for (int i = 0; i < inventar.size(); i++) {
                if (inventar[i]->getId() == idx)
                {
                    id = i;
                    if (typeid(*inventar[i]) == typeid(Arme))
                        ok = 1;
                }
            }
            if (ok == 0) {
                cout << "Nu exista arma cu acest id!\n";
            }
            else
            {
                Item *ptItem = inventar[id];
                Arme *a = dynamic_cast<Arme*>(ptItem);
                if (a != nullptr)
                {
                    armaEchipata.push_back(*a);
                    this -> putere += a->getPutere();
                    cout << "Ai echipat " << a->getNume() << " si ti-a crescut puterea cu " << a->getPutere() << " !\n";
                    for (int i = 0; i < inventar.size(); i++) {
                        if (inventar[i]->getId() == a->getId()) {
                            inventar.erase(inventar.begin() + i);
                            break;
                        }
                    }
                }
            }
        }
        else {
            scoateArma();
            echipeazaArma(idx);
        }
    }
}

void Caracter::scoateArmura() {
    viata -= armuraEchipata[0].getViata();
    Armura armura = armuraEchipata.back();
    Armura* copiearmura = new Armura(armura);
    inventar.push_back(copiearmura);
    armuraEchipata.pop_back();
}

void Caracter::echipeazaArmura(int idx) {
    if (inventar.size() == 0) {
        cout << "Nu ai ce sa echipezi!\n";
    }
    else {
        if (armuraEchipata.size() == 0)
        {
            int ok = 0,id;
            for (int i = 0; i < inventar.size(); i++) {
                if (inventar[i]->getId() == idx)
                {
                    id = i;
                    if (typeid(*inventar[i]) == typeid(Armura))
                        ok = 1;
                }
            }
            if (ok == 0) {
                cout << "Nu exista armura cu acest id!\n";
            }
            else
            {
                Item *ptItem = inventar[id];
                Armura *a = dynamic_cast<Armura*>(ptItem);
                if (a != nullptr)
                {
                    armuraEchipata.push_back(*a);
                    this -> viata += a->getViata();
                    cout << "Ai echipat " << a->getNume() << " si ti-a crescut viata cu " << a->getViata() << " !\n";
                    for (int i = 0; i < inventar.size(); i++) {
                        if (inventar[i]->getId() == a->getId()) {
                            inventar.erase(inventar.begin() + i);
                            break;
                        }
                    }
                }
            }
        }
        else {
            scoateArmura();
            echipeazaArmura(idx);
        }
    }

}

Item* Caracter::alegeArma() {
    while (true)
    {
        cout << "Ce arma echipezi?\n";
        int id;
        for (int i = 0 ; i < inventar.size(); i++) {
            cout << i+1 << ". " << inventar[i] << endl;
        }
        cout << "Ce arma echipezi?\n";
        cout << "Alege: ";
        cin >> id;
        if (typeid(inventar[id-1]) == typeid(Arme))
            return inventar[id-1];
        else
            cout << "Ceea ce ai ales nu este arma!\n";
    }
}

Item* Caracter::alegeArmura() {
    while (true)
    {
        cout << "Ce arumra echipezi?\n";
        int id;
        for (int i = 0; i < inventar.size(); i++) {
            cout << i+1 << ". " << inventar[i] << endl;
        }
        cout << "Ce arumra echipezi?\n";
        cout << "Alege: ";
        cin >> id;
        if (typeid(inventar[id-1]) == typeid(Armura))
            return inventar[id-1];
        else
            cout << "Ceea ce ai ales nu este armura!\n";
    }
}

void Caracter::adaugaArma(Arme& a)
{
    Arme* a1 = new Arme(a);
    inventar.push_back(a1);
    cout << "Arma " << a.getNume() << " a fost adaugata in inventar\n";
}

void Caracter::adaugaArmura(Armura& a)
{
    Armura* a1 = new Armura(a);
    inventar.push_back(a1);
    cout <<"Armura " << a.getNume() << " a fost adaugata in inventar\n";
}

class Potiune {
protected:
    string marime;
public:
    virtual ~Potiune() {}
    virtual void citire(istream &in);
    virtual void afisare(ostream &out);
    friend istream& operator>>(istream&, Potiune&);
    friend ostream& operator<<(ostream&, Potiune&);

    int getPret() const {
        if (marime == "s" || marime == "S") return 10;
        else if (marime == "m" || marime == "M") return 30;
        else if (marime == "l" || marime == "L") return 50;
        return 0;
    }
    virtual void aplicaEfect(Caracter& c) {}
};

void Potiune::citire(istream &in){
    cout << "Introduceti marimea [S-(+10 status | -10 bani) | M-(+30 status | -30 bani) | L-(+50 status | -50 bani) ] : " << endl;
    in >> marime;
}
void Potiune::afisare(ostream &out){
    out << "Marimea: " << marime << endl;
}
istream& operator>>(istream& in,Potiune& ob){
    ob.citire(in);
    return in;
}

ostream& operator<<(ostream& out, Potiune& ob){
    ob.afisare(out);
    return out;
}

class PotiuneViata : public Potiune {
private:
    int viata;
    string nume;
public:
    PotiuneViata(string nume = "Potiune Viata") : nume(nume) {}
    void citire(istream &in) {
        Potiune::citire(in);
    }
    void setViata() {
        if (marime == "s" || marime == "S") viata = 10;
        if (marime == "m" || marime == "M") viata = 30;
        if (marime == "l" || marime == "L") viata = 30;
    }
    void afisare(ostream& out) {
        cout << nume << endl;
        Potiune::afisare(out);
        cout << "Pret: ";
        if (marime == "s" || marime == "S") cout << 10 << endl;
        if (marime == "m" || marime == "M") cout << 30 << endl;
        if (marime == "l" || marime == "L") cout << 50 << endl;
    }
    int getViata() const {return viata;}

    void aplicaEfect(Caracter& c) {
        setViata();
        c.cresteViata(viata);
        cout << "Ai baut " << nume << "! Hp: " << c.getViata() << endl;
    }
};

class PotiunePutere : public Potiune {
private:
    int putere;
    string nume;
public:
    PotiunePutere(string nume = "Potiune Putere") : nume(nume) {}
    void citire(istream &in) {
        Potiune::citire(in);
    }
    void setPutere() {
        if (marime == "s" || marime == "S") putere = 10;
        if (marime == "m" || marime == "M") putere = 30;
        if (marime == "l" || marime == "L") putere = 30;
    }
    void afisare(ostream& out) {
        cout << nume << endl;
        Potiune::afisare(out);
        cout << "Pret: ";
        if (marime == "s" || marime == "S") cout << 10 << endl;
        if (marime == "m" || marime == "M") cout << 30 << endl;
        if (marime == "l" || marime == "L") cout << 50 << endl;
    }
    int getPutere() const {return putere;}

    void aplicaEfect(Caracter& c) {
        setPutere();
        c.crestePuterea(putere);
        cout << "Ai baut " << nume << "! Putere: " << c.getPutere() << endl;
    }
};


template<typename T>
class InventarPotiuni {
private:
    vector<T> inventar;
public:
    InventarPotiuni();
    void cumpara(Caracter& c, int nr) {
        T potiune;
        int cost = 0;
        vector<T> optiuni;
        for (int i = 0; i < nr; i++)
        {
            cin >> potiune;
            cost += potiune.getPret();
            optiuni.push_back(potiune);
        }
        if (c.getBani() >= cost) {
            c.scadeBani(cost);
            for (int i = 0; i < optiuni.size(); i++)
                inventar.push_back(optiuni[i]);
            cout <<"Potiunile cumparate cu succes!\n";
        }
        else {
            cout <<"Nu ai bani!\n";
        }
    }
    void folosestePotiune(Caracter& c) {
        if (inventar.size() == 0) {
            cout << "Nu ai potiuni!\n";
        }
        else
        {
            cout << "--- Inventar Potiuni ---\n";
            for (int i = 0; i < inventar.size(); i++) {
                cout << i+1 <<" "<< inventar[i] << endl;
            }
            int a;
            cout << "Alege ce potiune folosesti: (1-" << inventar.size() << ") \n";
            cout << "Potiunea: ";
            cin >> a;
            if (a > 0 && a <= inventar.size()) {
                inventar[a-1].aplicaEfect(c);
                inventar.erase(inventar.begin() + (a-1));
            }
            else {
                cout << "Optiune invalida!\n";
            }
        }
    }
};

template <typename T>
InventarPotiuni<T>::InventarPotiuni() {}

class Magazin { // Reminder: sa fac o functie de unde pot cumpara licori de viata pentru a creste viata cand ies din arena
private:
    static Magazin *instance;
    vector<Arme> inventar;
    Magazin() {
        inventar = {Arme(30,"Sabie",1,"Razboinic",30),Arme(40,"Sulita",1,"Razboinic",50),Arme(30,"Cutit",1,"Ninja",40),Arme(40,"Arc",1,"Ninja",60)};
    }
public:
    static Magazin *getInstance() {
        if (!instance)
            instance = new Magazin;
        return instance;
    }

    Magazin(const Magazin&) = delete;
    void operator=(const Magazin&) = delete;

    Arme getArma(int idx);
    void afiseazaInventar();
    int getInvetarSize() const {return inventar.size();}
};

Magazin *Magazin::instance = 0;

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
    return Arme(0,"N/A",0,"N/A",0);
}

class MagazinArmuri{
private:
    static MagazinArmuri *instance;
    vector<Armura> inventar;
    MagazinArmuri() {
        inventar = {Armura(30,"Platosa",1,"Razboinic",70),Armura(30,"Costum",1,"Ninja",40)};
    }
public:
    static MagazinArmuri *getInstance() {
        if (!instance)
            instance = new MagazinArmuri;
        return instance;
    }

    MagazinArmuri(const MagazinArmuri&) = delete;
    void operator=(const MagazinArmuri&) = delete;
    Armura getArmura(int idx);
    void afiseazaInventar();
    int getInvetarSize() const {return inventar.size();}
};

MagazinArmuri *MagazinArmuri::instance = 0;

Armura MagazinArmuri::getArmura(int idx)
{
    if (idx >=0 && idx <=inventar.size()) {
        return inventar[idx];
    }
    cout << "Eroare!!!!\n";
    return Armura(0,"N/A",0,"N/A",0);
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
    Monstru(string nume = "Monstru",int viata = 150,int nivel = 1,int putere = 20,int bani = 20):nume(nume),viata(viata),nivel(nivel),putere(putere),bani(bani){}
    Monstru(const Monstru&);
    virtual ~Monstru(){};
    int getViata() const {return viata;}
    int getNivel() const {return nivel;}
    int getBani() const {return bani;}
    int getPutere() const {return putere;}

    virtual void set(string nume,int viata,int nivel);
    virtual int DMG() const {return putere + nivel;}
    virtual void abilitateSpeciala(Caracter& c) {}
    virtual void setLoot(Caracter& c) {}
    void operator -= (int hp) {
        this -> viata -= hp;
        cout << "Monstrul a pierut " << hp << " hp! \n";
        cout << "Viata monstrului: " << viata << " !\n";
    }
    virtual string getLoot() const {return "nimic";}
    virtual Arme dropeazaArma() {}
    virtual Armura dropeazaArmura() {}
};

void Monstru::set(string nume, int viata, int nivel) {
    this -> nume = nume;
    this -> viata = viata;
    this -> nivel = nivel;
}

class MonstruFoc : virtual public Monstru
{
private:
    vector<Arme> loot;
public:
    MonstruFoc(string nume = "Monstru foc", int viata = 100, int nivel = 5, int putere = 20, int bani = 40, vector<Arme> loot = {}):Monstru(nume,viata,nivel,putere,bani),loot(loot){}
    ~MonstruFoc(){};
    void setLoot(Caracter& c);
    int DMG() const {return putere + nivel * 2;}
    void abilitateSpeciala(Caracter& c) {
        putere += 30;
        c.scadePuterea(30);
        cout << nume <<"ti-a furat 30 putere!\n";
    }
    string getLoot() const {return loot[0].getNume();}
    Arme dropeazaArma() {return loot[0];}
};

void MonstruFoc::setLoot(Caracter& c) {
    if (c.getCategorie() == "Razboinic")    loot.push_back(Arme(30,"Sabie",1,"Razboinic",30));
    else if (c.getCategorie() == "Ninja")   loot.push_back(Arme(30,"Cutit",1,"Ninja",40));
}

class MonstruGheata : virtual public Monstru
{
private:
    vector<Armura> loot;
public:
    MonstruGheata(string nume = "Monstru gheata", int viata = 150, int nivel = 10, int putere = 50, int bani = 80, vector<Armura> loot = {}):Monstru(nume,viata,nivel,putere,bani),loot(loot){}
    ~MonstruGheata(){};
    void setLoot(Caracter& c);
    int DMG() const {return putere + nivel * 4;}
    void abilitateSpeciala(Caracter& c) {
        viata += 30;
        c.scadeViata(30);
        cout << nume <<" ti-a furat 30HP!\n";
    }
    string getLoot() const {return loot[0].getNume();}
    Armura dropeazaArmura() {return loot[0];}
};

void MonstruGheata::setLoot(Caracter& c) {
    if (c.getCategorie() == "Razboinic")    loot.push_back(Armura(30,"Platosa",1,"Razboinic",70));
    else if (c.getCategorie() == "Ninja")   loot.push_back(Armura(30,"Costum Ninja",1,"Ninja",40));
}

class Boss : public MonstruFoc, public MonstruGheata
{
public:
    Boss(string nume = "Boss", int viata = 300, int nivel = 20, int putere = 100, int bani = 200, vector<Arme> lootArme = {}, vector<Armura> lootArmuri = {})
    : Monstru(nume,viata,nivel,putere,bani), MonstruFoc(nume,viata,nivel,putere,bani,lootArme), MonstruGheata(nume,viata,nivel,putere,bani,lootArmuri) {}

    int DMG() const {return putere + nivel * 6;}

    void abilitateSpeciala(Caracter& c) {
        c.scadeViata(20);
        c.scadePuterea(20);
        viata += 20;
        putere += 20;
        cout << nume << " si-a activat abilitatea speciala si ti-a furat 20HP si 20 putere!\n";
    }

    void setLoot(Caracter& c) {
        MonstruFoc::setLoot(c);
        MonstruGheata::setLoot(c);
    }

    string getLoot() const {
        return MonstruFoc::getLoot();
    }
};

void uiMeniuStart() {
    cout<<"+++++++++++++++++++++++++++++++"<<endl;
    cout <<"+++++ Creeaza caracterul +++++" << endl;
    cout<<"+++++++++++++++++++++++++++++++"<<endl;
}

void uiMeniu() {
    cout<<"+++++++++++++++++++++++++++++++"<<endl;
    cout<<" Introdu 1 pentru a vedea detaliile caracterului sau inventarul "<<endl;
    cout<<" Introdu 2 pentru a merge la magazin "<<endl;
    cout<<" Introdu 3 pentru a echipa arma/armura cumparata"<<endl;
    cout<<" Introdu 4 pentru a iti alege un pet"<<endl;
    cout<<" Introdu 5 pentru a bea potiuni" << endl;
    cout<<" Introdu 6 pentru a intra in arena "<<endl;
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
    Magazin *magazinArme = Magazin::getInstance();
    MagazinArmuri *magazinArmuri = MagazinArmuri::getInstance();
    InventarPotiuni<PotiuneViata> invViata;
    InventarPotiuni<PotiunePutere> invPutere;
    Pet p;
    Monstru monstru("Goblin");
    MonstruFoc monstruF("Dragon");
    MonstruGheata monstruG("Golem");
    Boss boss("Seful Dungenului");
    stack<Monstru*> Dungeon;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(1,10);
    // alegerea caracterului
    if (ac == 1) {
        cout << "Ai ales Razboinic! \n";
        erou.setCategorie("Razboinic", 100, 70);
        erou.setNivel(50);
        erou.setBani(100000);
        erou.setViata(1000000);
        erou.setPutere(100000);
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
                    // aici cumparam de la magazin si verifica daca am bani de arma sau arma este categoria mea
                    int alegere;
                    cout << "Magazin arme [Tasta 1] | Magazin armuri [Tasta 2] | Potiuni [Tasta 3]\n";
                    cout << "Alegere: ";
                    cin >> alegere;
                    if (alegere == 1)
                    {
                        int nr, bani;
                        int cos = 0;
                        vector <Arme>optiuni = {};
                        magazinArme->afiseazaInventar();
                        cout << "Banii tai: ";
                        bani = erou.getBani();
                        cout << bani << endl;
                        cout << "Cate arme vrei sa cumperi? [0 daca nu vrei nimic]\n";
                        cout << "Nr: ";
                        cin >> nr;
                        if (nr == 0) {
                            cout << "La revedere!\n";
                        }
                        else {
                            for (int i = 0; i < nr; i++) {
                                Arme armaTemp;
                                cin >> armaTemp; // citirea a n obiecte
                                for (int j = 0; j < magazinArme->getInvetarSize(); j++) {
                                    Arme a = magazinArme->getArma(j);
                                    if (a.getNume() == armaTemp.getNume()) {
                                        optiuni.push_back(a);
                                        if (a.getCategorie() == armaTemp.getCategorie())
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
                                        if (cumpara)
                                            cout << optiuni[i].getNume() << " a fost adaugata in inventar!\n";
                                    }
                                }
                                else throw BugetInsuficientException();
                            }
                            catch (exception& e)
                            {
                                cout << e.what();
                            }
                        }
                    }
                    else if (alegere == 2)
                    {
                        int nr, bani;
                        int cos = 0;
                        vector <Armura>optiuni = {};
                        magazinArmuri->afiseazaInventar();
                        cout << "Banii tai: ";
                        bani = erou.getBani();
                        cout << bani << endl;
                        cout << "Cate armuri vrei sa cumperi? [0 daca nu vrei nimic]\n";
                        cout << "Nr: ";
                        cin >> nr;
                        if (nr == 0) {
                            cout << "La revedere!\n";
                        }
                        else
                        {
                            for (int i = 0; i < nr; i++) {
                                Armura armuraTemp;
                                cin >> armuraTemp; // citirea a n obiecte
                                for (int j = 0; j < magazinArmuri->getInvetarSize(); j++) {
                                    Armura a = magazinArmuri->getArmura(j);
                                    if (a.getNume() == armuraTemp.getNume()) {
                                        optiuni.push_back(a);
                                        if (a.getCategorie() == armuraTemp.getCategorie())
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
                                        if (cumpara)
                                            cout << "Armura a fost adaugata in inventar!\n";
                                    }
                                }
                                else throw BugetInsuficientException();
                            }
                            catch (exception& e)
                            {
                                cout << e.what();
                            }
                        }
                    }
                    else if (alegere == 3) {
                        cout << "Potiuni de viata [Tasta 1] | Potiuni de putere [Tasta 2]\n";
                        cout << "Alegere: ";
                        int alg;
                        cin >> alg;
                        if (alg == 1) {
                            cout << "Cate potiuni dorersti?\n";
                            int nr;
                            cin >> nr;
                            invViata.cumpara(erou,nr);
                        }
                        else if (alg == 2) {
                            cout << "Cate potiuni dorersti?\n";
                            int nr;
                            cin >> nr;
                            invPutere.cumpara(erou,nr);
                        }
                        else {
                            cout << "Invalid!\n";
                        }
                    }
                    break;
                }
            case 3: {
                    int echip;
                    cout << "Acesta este inventarul!\n";
                    erou.afiseazaInventar();
                    cout << "Ce vrei sa echipezi?\n";
                    cout << "Arma [Tasta 1] | Armura [Tasta 2] \n";
                    cout << "Optiune: ";
                    cin >> echip;
                    if (echip == 1) {
                        // echipare arma ( se sterge din inventar si se echiepeaza, trb sa mai fac o functie sa si dezechipez sau sa inlocuiesc daca vr)
                        cout << "Scrie id-ul armei!\n";
                        int id;
                        cout << "ID: ";
                        cin >> id;
                        erou.echipeazaArma(id);
                    }
                    else if (echip == 2)
                    {
                        cout << "Scrie id-ul armurii!\n";
                        int id;
                        cout << "ID: ";
                        cin >> id;
                        erou.echipeazaArmura(id);
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
                    cout << "Ce potiune vrei sa bei?\n";
                    cout << "Viata [Tasta 1] | Putere [Tasta 2]\n";
                    int optiune;
                    cout << "Optiune: ";
                    cin >> optiune;
                    if (optiune == 1) invViata.folosestePotiune(erou);
                    else if (optiune == 2) invPutere.folosestePotiune(erou);
                    else cout << "Optiune invalida!\n";
                    break;
                }
            case 6:
                {
                    cout << "Bun venit in Dungeon!" << endl;
                    bool cont = true;
                    Dungeon.push(&boss);
                    Dungeon.push(&monstruG);
                    Dungeon.push(&monstruF);
                    Dungeon.push(&monstru);
                    while (cont && (erou.getStare() == Viu || erou.getStare() == Batut))
                    {
                        if (Dungeon.empty()) {
                            cout << "Ai terminat jocul. Felicitari!!!\n";
                            cout << "Inca te poti juca dar deja faci fata peste tot!\n";
                            cont = false;
                            continue;
                        }
                        if (erou.getViata() < 50)
                            erou.setStare(Batut);
                        cout << "Continui?\n";
                        cout << "Da [Tasta 1] | Nu [Tasta 2] \n";
                        int asdf;
                        cout << "Alegerea ta: ";
                        cin >> asdf;
                        if (asdf == 1) {
                            if (erou.getStare() == Batut) {
                                cout << "Nu ai asa multa viata! Iti sugerez sa fugi din arena si sa bagi o potiune!\n";
                            }
                            if (5 - Dungeon.size() != 4)
                                cout << "Ai intrat in camera " << 5 - Dungeon.size() << " !\n";
                            else
                                cout << "Ai ajuns la BOSS\n";
                            Monstru* m = Dungeon.top();
                            try
                            {
                                int niv = erou.getNivel();
                                m->setLoot(erou);
                                if (niv >= m->getNivel()) {
                                    while (true) {
                                        int nrRandom = distr(gen);
                                        cout << "Ataci [Tasta 1] sau Fugi [Tasta 2]?\n";
                                        int a;
                                        cout << "Alegerea ta: ";
                                        cin >> a;
                                        if (a == 1) {
                                            if (m -> getViata() > 0 && erou.getViata() > 0) *m -= erou.DMG();
                                            else break;
                                        }
                                        else if (a == 2) {
                                            asdf = 2;
                                            break;
                                        }
                                        if (nrRandom > 7 && m -> getViata() > 0) m -> abilitateSpeciala(erou);
                                        if (erou.getViata() > 0 && m -> getViata() > 0) erou -= m -> DMG();
                                        else break;
                                    }
                                    if (erou.getViata() > 0 and m -> getViata() <= 0)
                                    {
                                        cout << "Felicitari ai castigat in camera " << 5 - Dungeon.size() << " !\n";
                                        erou += m->getBani();
                                        erou.levelUp();
                                        erou.viataMaxima();
                                        erou.setStare(Viu);
                                        cout << "Ai trecut la nivelul " << erou.getNivel() << " !\n";
                                        if (typeid(*m) == typeid(MonstruFoc))
                                        {
                                            cout << "Monstrul a dropat " << m -> getLoot() << " !\n";
                                            Arme a = m -> dropeazaArma();
                                            erou.adaugaArma(a);
                                        }
                                        if (typeid(*m) == typeid(MonstruGheata))
                                        {
                                            cout << "Monstrul a dropat " << m -> getLoot() << " !\n";
                                            Armura a = m -> dropeazaArmura();
                                            erou.adaugaArmura(a);
                                        }
                                        Dungeon.pop();
                                    }
                                    if (erou.getViata() <= 0) {
                                        erou.setStare(Mort);
                                        cout << "Ai murit!\n";
                                    };
                                }
                                else throw NivelMicException();
                            }
                            catch (exception& e) {
                                cout << e.what();
                                asdf = 3;
                            }
                        }
                        if (asdf == 2)
                        {
                            cout << "Revii cand ai tupeu!\n";
                            cont = false;
                        }
                        if (asdf == 3)
                        {
                            cout << "Trebuie sa refaci camera curenta pana ai nivelul necesar!\n";
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