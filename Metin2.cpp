#include <bits/stdc++.h>

using namespace std;

int alegeCaracter();

class Caracter {
private:
    int nivel;
    int bani;
    string categorie;
public:
    Caracter(string categorie = "N/A",  int nivel = 1, int bani = 100);
    Caracter(const Caracter&);
    ~Caracter(){};

    void setCategorie(string categorie);
    void detaliiCaracter(ostream&);

    friend ostream& operator <<(ostream&, Caracter&);
};

Caracter::Caracter(string categorie, int nivel, int bani) {
    this -> categorie = categorie;
    this -> nivel = nivel;
    this -> bani = bani;
    cout << "Caracterul a fost creat!" <<endl;
}

void Caracter::setCategorie(string categorie) {
    this -> categorie = categorie;
}

ostream& operator <<(ostream& out, Caracter& c){
    c.detaliiCaracter(out);
    return out;
}

void Caracter::detaliiCaracter(ostream& out) {
    out << "Categorie: " << categorie << endl;
    out << "Nivel: " << nivel << endl;
    out << "Bani: " << bani << endl;
}

void uiMeniuStart() {
    cout<<"+++++++++++++++++++++++++++++++"<<endl;
    cout <<"+++++ Creeaza caracterul +++++" << endl;
    cout<<"+++++++++++++++++++++++++++++++"<<endl;
}

void uiMeniu() {
    cout<<"+++++++++++++++++++++++++++++++"<<endl;
    cout<<" Introdu 1 pentru a vedea detaliile caracterului "<<endl;
    cout<<" Introdu 2 pentru a nimic "<<endl;
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
    if (ac == 1) {
        cout << "Ai ales Razboinic! \n";
        erou.setCategorie("Razboinic");
    }
    else {
        cout << "Ai ales Ninja! \n";
        erou.setCategorie("Ninja");
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
                cout << "N/A" << endl;
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
