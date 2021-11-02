#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

class Biblioteca { 
    int an_construire;
    char *nume;
    char *bibliotecar;
    char adresa[20];
public:
    Biblioteca();   //constructor fara parametrii
    Biblioteca(char [], char *, char *, int);   //constructor cu parametri   
    Biblioteca(const Biblioteca&);  //constructor de copiere
    ~Biblioteca();  //destructor

    void afisare() const;   //afiseaza atributele clasei
    void modif(char*, char*, char[],int);   //modifica atributele clasei
    char* getBibliotecar();
    char* getNume();
    friend int getAn(const Biblioteca&);    //returneaza vechimea obiectului apelat
    friend void interschimbare(Biblioteca&, Biblioteca&); //interschimba valorile dintre 2 obiecte de tip Biblioteca
   
};

Biblioteca::Biblioteca() {
    //cout << "Constructor fara parametri\n";
    an_construire = 0;
    strcpy(adresa, "");
    nume = NULL;
    bibliotecar = NULL;
}

Biblioteca::Biblioteca(char a[], char *b, char *n, int an) {
    //cout << "Constructor cu parametri\n";
    an_construire = an;
    strcpy(adresa, a);
    nume = new char[strlen(n) + 1];
    bibliotecar = new char[strlen(b) + 1];
    strcpy(nume, n);
    strcpy(bibliotecar, b);
} 

Biblioteca::Biblioteca(const Biblioteca &obj) {
    //cout << "Constructor de copiere\n";
    an_construire = obj.an_construire;
    strcpy(adresa, obj.adresa);
    nume = new char[strlen(obj.nume) + 1];
    bibliotecar = new char[strlen(obj.bibliotecar) + 1];
    strcpy(nume, obj.nume);
    strcpy(bibliotecar, obj.bibliotecar);
}

Biblioteca::~Biblioteca() {
    //cout << "Destructor. " << nume << bibliotecar << endl;
    delete[] nume;
    delete[] bibliotecar;
}

void Biblioteca::afisare() const {  //afiseaza atributele clasei
    cout << "An construire " << an_construire << endl;
    cout << "Adresa: " << adresa << endl;
    cout << "Nume: " << nume << endl;
    cout << "Bibliotecar: " << bibliotecar << endl;
    cout << "Adresa: " << adresa << endl;
}

void Biblioteca::modif(char a[], char *b, char *n, int an) { //modifica atributele clasei
    if (nume != NULL) 
        delete[] nume;
    if (bibliotecar != NULL)
        delete[] bibliotecar;
        an_construire = an;
    an_construire = an;
    strcpy(adresa, a);
    nume = new char[strlen(n) + 1];
    bibliotecar = new char[strlen(b) + 1];
    strcpy(nume, n);
    strcpy(bibliotecar, b);
}

char *Biblioteca::getBibliotecar() {
    return bibliotecar;
}
char *Biblioteca::getNume() {
    return nume;
}

int getAn(const Biblioteca &obj) {
    return obj.an_construire;
}

void interschimbare(Biblioteca &obj1, Biblioteca &obj2) {
    Biblioteca obj3(obj1);  //aici folosesc constructorul de copiere
    if(obj1.nume != NULL)
		delete []obj1.nume;
    if(obj1.bibliotecar != NULL)
		delete []obj1.bibliotecar;
    obj1.nume = new char[strlen(obj2.nume) + 1];
	strcpy(obj1.nume, obj2.nume);
    obj1.bibliotecar = new char[strlen(obj2.bibliotecar) + 1];
	strcpy(obj1.bibliotecar, obj2.bibliotecar);
    strcpy(obj1.adresa, obj2.adresa);
    obj1.an_construire = obj2.an_construire;

    //copy everything from obj3 to obj2
    if(obj2.nume != NULL)
		delete []obj2.nume;
    if(obj2.bibliotecar != NULL)
		delete []obj2.bibliotecar;
    obj2.nume = new char[strlen(obj3.nume) + 1];
	strcpy(obj2.nume, obj3.nume);
    obj2.bibliotecar = new char[strlen(obj3.bibliotecar) + 1];
	strcpy(obj2.bibliotecar, obj3.bibliotecar);
    strcpy(obj2.adresa, obj3.adresa);
    obj2.an_construire = obj3.an_construire;

}

int main() {
    Biblioteca obj1;
    Biblioteca obj2((char *)"Sector3", (char *) "Marcel", (char *) "Mihai Eminescu", 1853);
    Biblioteca obj3((char *)"Constanta", (char *)"Ionut", (char *)"Ion Creanga",  1900);
    Biblioteca obj4(obj2); //constructor de copiere

    cout << "\nObj2 si obj 3 inainte de interschimbare:\n" << endl;
    cout << "Obj2:" << endl;
    obj2.afisare();
    cout <<"\nObj3:" << endl;
	obj3.afisare();

	interschimbare(obj2,obj3);

	cout << "\nObj2 si obj 3 dupa interschimbare:\n" << endl;
    cout << "Obj2:" << endl;
    obj2.afisare();
    cout <<"\nObj3:" << endl;
	obj3.afisare();

	cout << "\nObj4 care contine aceleasi date ca si obj2 (am folosit constructorul de copiere):\n" << endl;
    obj4.afisare();

    cout << "Modific datele din obj1: \n" << endl;
    obj4.modif((char *)"Iasi", (char *) "Rares", (char *) "Gheorghe Asachi", 1860);
    cout << "\nObj1 dupa modificare: \n" << endl;
    obj4.afisare();

    Biblioteca *b;
	
    b = new Biblioteca[4];

    b[0].modif((char *)"Bucuresti", (char *) "Marin", (char *) "BCU Bucuresti", 1893);
	b[1].modif((char *)"Sibiu", (char *) "Codrin", (char *) "Astra", 1860);
	b[2].modif((char *)"Brasov", (char *) "Teodor", (char *) "George Baritiu", 1969);
	b[3].modif((char *)"Bucuresti", (char *) "Andrei", (char *) "UMF Carol Davila", 1870);

    //Sortare in functie de nume
    for(int i = 0; i < 3; i ++)
	{
		for (int j = i + 1; j < 4; j++)
		{
			if(strcmp(b[i].getNume(),b[j].getNume()) > 0)
			{
				Biblioteca aux;
				aux = b[i];
				b[i] = b[j];
				b[j] = aux;
			}
		}
	}
    
    cout << "\n\nAfisare vector sortat:" << endl;
    for(int i = 0; i < 4; i++) {
        cout << endl;
        b[i].afisare();
    }

    //Cea mai veche biblioteca
    Biblioteca aux;
    aux = b[0];
    for(int i = 1; i < 4; i ++) {
		if(getAn(aux) < getAn(b[i])) {
            aux = b[i];
        }
	}
    cout << "\n\nCele mai vechi biblioteci: " << endl;
    for(int i = 1; i < 4; i ++) {
		if(getAn(aux) == getAn(b[i])) {
            b[i].afisare();
            cout << "\n";
        }
	}
    delete[] b;     //am eliberat memoria
    
    return 0;
}