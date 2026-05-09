Metin2 CLI - Proiect Programare Orientată pe Obiecte
Acesta este un joc de tip RPG (Role-Playing Game) bazat pe text, inspirat din universul Metin2, implementat în C++. Proiectul demonstrează utilizarea conceptelor avansate de Programare Orientată pe Obiecte.

Descrierea Jocului
Jucătorul își poate crea un personaj (Războinic sau Ninja), poate cumpăra echipament de la magazin, poate echipa obiecte din inventar, poate folosi poțiuni și se poate aventura într-un Dungeon plin de monștri și boss-i pentru a crește în nivel.

Concepte POO Implementate
1. Ierarhia de Clase și Moștenire
Item (Clasa de bază abstractă): Definește structura generală pentru obiecte.

Arme și Armura moștenesc clasa Item.

Monstru (Clasa de bază):

MonstruFoc și MonstruGheata moștenesc virtual clasa Monstru.

Boss implementează moștenirea multiplă, preluând caracteristici de la ambii tipuri de monștri.

2. Polimorfism
Funcții Virtuale: Utilizate pentru metode precum detalii(), clona() și abilitateSpeciala().

Dynamic Cast & Typeid: Utilizate pentru a identifica tipul obiectelor la runtime (de exemplu, în inventar sau la drop-ul de loot).

3. Incapsulare și Abstractizare
Folosirea modificatorilor de acces (private, protected, public).

Clase abstracte cu metode virtuale pure (ex: virtual ~Item() = 0).

4. Gestiunea Memoriei și Design Patterns
Singleton Pattern: Implementat în clasele Magazin și MagazinArmuri pentru a asigura o singură instanță a magazinului în tot jocul.

Deep Copy: Implementat prin constructori de copiere și operatori de atribuire pentru gestionarea corectă a pointerilor.

Stivă (Stack): Utilizată pentru a gestiona progresia în Dungeon.

5. Template-uri și STL
Clase Template: InventarPotiuni<T> permite gestionarea diferitelor tipuri de poțiuni folosind aceeași logică.

Containere STL: Utilizarea std::vector pentru inventar și std::stack pentru structura camerelor din Dungeon.

6. Tratarea Excepțiilor
Definirea unor excepții custom: BugetInsuficientException și NivelMicException pentru a valida acțiunile jucătorului.

Funcționalități principale
Creare Caracter: Alegerea clasei și setarea numelui.

Sistem de Magazin: Cumpărarea de arme/armuri cu validare de bani și nivel.

Sistem de Inventar: Echiparea și dezechiparea obiectelor (cu actualizarea statisticilor de HP și DMG).

Sistem de Pet-uri: Agregarea unui animal de companie care oferă bonusuri permanente.

Dungeon System: Lupte pe etape cu monștri ce posedă abilități speciale și sistem de loot randomizat.
