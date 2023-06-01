#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

//exceptie 1
class FaptePutine:public exception{
public:
    const char *what() const throw() {
        return "Ai introdus putine fapte bune\nReintroduceti numarul: ";
    }
};

//exceptie 2
class BateriiNeg:public exception{
public:
    const char *what() const throw() {
        return "Numarul de baterii nu poate fi negativ\nReintrodu numarul: ";
    }
};

//functie tamplate pentru returnarea numarului minim de baterii
template <typename minim_baterii>minim_baterii min(minim_baterii a, minim_baterii b){
    return (a < b) ? a : b;
}

template <typename Copil>
//clasa template pentru stocarea unui element de tip copil
class Container {
    private:
        Copil copil;
    public:
        Container(Copil value) : copil(value) {}
        Copil get() {
            return copil;
        }
    };

class Jucarie
{
protected:
    string denumire, tip;
    int dimensiune;

public:
    //metoda clone virtuala
    virtual Jucarie* clone(){
        return new Jucarie(*this);
    }

    Jucarie & operator=(const Jucarie & jucarie)
    {
        this->denumire=jucarie.denumire;
        this->tip=jucarie.tip;
        this->dimensiune=jucarie.dimensiune;
        return *this;
    }

    friend istream& operator>>(istream &is, Jucarie &jucarie)
    {
        cout << "Introduceti denumire: ";
        is >> jucarie.denumire;

        cout << "Introduceti dimensiune: ";
        is >> jucarie.dimensiune;

        cout << "Introduceti tipul: ";
        is >> jucarie.tip;

        return is;
    }

    friend ostream& operator<<(ostream &os, Jucarie &jucarie)
    {
        os << "Denumire: " << jucarie.denumire << "\nDimensiune: " << jucarie.dimensiune << "\nTipul: " << jucarie.denumire;
        return os;
    }

    virtual void citirejuc() {
        cin >> *this ;
    }
    virtual void afisarejuc() {
        cout << *this ;
    }
};

class Clasica:public Jucarie{
private:
    string material, culoare;

public:
    Clasica& operator=(const Clasica & jucarie){
        Jucarie::operator=(jucarie);
        this->material = jucarie.material;
        this->culoare = jucarie.culoare;
        return *this ;
    }

    friend istream& operator>>(istream &is, Clasica &clasica) {
        cout << "Introduceti materialul: ";
        is >> clasica.material;

        cout << "Introduceti culoarea: ";
        is >> clasica.culoare;

        return is;
    }

    friend ostream& operator<<(ostream &os, Clasica &clasica){
        os << "Material: " << clasica.material << "\nCuloare: " << clasica.culoare;
        return os;
    }

    void citirejuc() override{
        Jucarie::citirejuc();
        cin >> *this ;
    }

    void afisarejuc() override{
        Jucarie::afisarejuc();
        cout << *this ;
    }
};

class Educativa:virtual public Jucarie{
protected:
    string abilitate;

public:
    friend istream& operator>>(istream &is, Educativa &educativa)
    {
        cout << "Introduceti abilitatea: ";
        is >> educativa.abilitate;
        return is;
    }
    //afisare cu virtualizare (afiseaza intr o functie virtuala -> afisarejuc())
    friend ostream& operator<<(ostream &os, Educativa &educativa)
    {
        os << "Abilitate: " << educativa.abilitate ;
        return os;
    }

    virtual void citirejuc() override{
        Jucarie::citirejuc();
        cin >> *this ;
    }

    //functie cu afisare virtuala
    virtual void afisarejuc() override{
        Jucarie::afisarejuc();
        cout << *this;
    }
};

class Electronica:virtual public Jucarie{
protected:
    int nr_baterii;
public:
    void setNrBaterii(int nrBaterii) {
        nr_baterii = nrBaterii;
    }

    friend istream& operator>>(istream &is, Electronica &electronica)
    {
        cout << "Introduceti numarul de baterii: ";
        is >> electronica.nr_baterii;
        return is;
    }
    //operator cu virtualizare -> afiseaza intr o functie virtuala (afisarejuc())
    friend ostream& operator<<(ostream &os, Electronica &electronica)
    {
        os << "Numar de baterii: " << electronica.nr_baterii ;
        return os ;
    }
    virtual void citirejuc() override{
        Jucarie::citirejuc();
        cin >> *this ;
    }
    virtual void afisarejuc() override{
        Jucarie::afisarejuc();
        cout << *this ;
    }
};

class Moderna:public Educativa, public Electronica{
private:
    string brand, model;
public:
    friend istream& operator>>(istream &is, Moderna &moderna)
    {
        cout << "Introduceti brandul: ";
        is >> moderna.brand;

        cout << "Introduceti modelul: ";
        is >> moderna.model;

        moderna.nr_baterii = 1;
        moderna.abilitate = "generala";

        return is;
    }
    friend ostream& operator<<(ostream &os, Moderna &moderna)
    {
        os << "Brand: " << moderna.brand << "\nModel: " << moderna.model;
        return os;
    }
    void citirejuc() override{
        Jucarie::citirejuc();
        cin >> *this ;
    }
    void afisarejuc() override{
        Jucarie::afisarejuc();
        cout << *this ;
    }
};

//clasa de generare ID
class Generator_ID{
    static int ID;

public:
    int next_val(){
        ID++;
        return ID;
    }
};

class Copil{
protected:
    Generator_ID generatorId;
    int ID, varsta,nr_fb;
    string nume, prenume;
    vector<shared_ptr<Jucarie>> vect_jucarii;

public:
    const string &getNume() const {
        return nume;
    }

    void setNrFb(int nrFb) {
        nr_fb = nrFb;
    }

    void setVectJucarii(const vector<shared_ptr<Jucarie>> &vectJucarii) {
        vect_jucarii = vectJucarii;
    }

    const vector<shared_ptr<Jucarie>> &getVectJucarii() const {
        return vect_jucarii;
    }

    int getNrFb() const {
        return nr_fb;
    }

    Copil() = default;
    Copil(int varsta, int nrFb, const string &nume, const string &prenume,
          const vector<shared_ptr<Jucarie>> &vectJucarii) : varsta(varsta), nr_fb(nrFb), nume(nume), prenume(prenume),
                                                            vect_jucarii(vectJucarii) {}
    friend istream& operator>>(istream &is, Copil &copil)
    {
        copil.ID = copil.generatorId.next_val();

        cout << "Introduceti nume: ";
        is >> copil.nume;

        cout << "Introduceti prenume: ";
        is >> copil.prenume;

        cout << "Introduceti varsta: ";
        is >> copil.varsta;

        cout << "Introduceti numar fapte bune: ";
        is >> copil.nr_fb;
        if(copil.nr_fb < 10)
            throw FaptePutine();


        return is;
    }

    friend ostream& operator<<(ostream &os, Copil &copil){
        os << "Nume: " << copil.nume << "\nPrenume: " << copil.prenume << "\nVarsta: " << copil.varsta << "\nNumar de fapte bune: " << copil.nr_fb;
        return os;
    }

    virtual void citire(){
        cin >> *this;
    }

    virtual void afisare(){
        cout << *this;
    }
};

class Cuminte:public Copil{
private:
    int nr_dulciuri;

public:
    Cuminte() = default;
    friend istream& operator>>(istream &is, Cuminte &cuminte){
        cout << "Introduceti numarul de dulciuri: ";
        is >> cuminte.nr_dulciuri;
        return is;
    }

    friend ostream& operator<<(ostream &os, Cuminte &cuminte){
        cout << "Numar de dulciuri: " << cuminte.nr_dulciuri ;
        return os;
    }

    void citire() override{
        Copil::citire();
        cin >> *this ;
    }

    void afisare() override{
        Copil::afisare();
        cout << *this;
    }
};

class Neastamparat:public Copil{
private:
    int nr_carbuni;

public:
    Neastamparat() = default;

    friend istream& operator>>(istream &is, Neastamparat &neastamparat){
        cout << "Introduceti numarul de carbuni: ";
        is >> neastamparat.nr_carbuni;

        return is;
    }

    friend ostream& operator<<(ostream &os, Neastamparat &neastamparat){
        os << "Numar de carbuni: " << neastamparat.nr_carbuni;

        return os;
    }

    void citire() override {
        Copil::citire();
        cin >> *this;
    }
    void afisare() override{
        Copil::afisare();
        cout << *this;
    }
};
int Generator_ID::ID = 0;

class CopiiBD{
    vector<shared_ptr<Copil>> vCopii;
public:
    void citireBD(){
        string tip_copil, tip_jucarie;
        int n;
        cout << "Introduceti numarul de copii: " ;
        cin >> n ;
        for(int i = 0; i < n; i++)
        {
            cout << "Introduceti tipul de copil (cuminte/obraznic): ";
            cin >> tip_copil;
            if(tip_copil == "cuminte"){
                shared_ptr<Copil> copcuminte = make_shared<Cuminte>();
                //try catch
                try{
                    copcuminte->citire();
                }catch (FaptePutine& obj)
                {
                    cout <<obj.what();
                    int x;
                    do{
                        cin >> x;
                    }while(x<10);
                    copcuminte->setNrFb(x);
                }


                vector<shared_ptr<Jucarie>> vJucarii;
                for(int i = 0 ; i < copcuminte->getNrFb(); i++)
                {
                    cout << "Introduceti tipul de jucarie(clasica/educativa/electronica/moderna): ";
                    cin >> tip_jucarie;
                    if(tip_jucarie == "clasica"){
                        shared_ptr<Jucarie> jucclas = make_shared<Clasica>();
                        jucclas->citirejuc();
                        vJucarii.push_back(jucclas);
                    }
                    else if(tip_jucarie == "educativa"){
                        shared_ptr<Jucarie> jucedu = make_shared<Educativa>();
                        try
                        {
                            jucedu->citirejuc();
                        }
                        catch(BateriiNeg& obj)
                        {
                            cout << obj.what();
                            int x;
                            do {
                                cin >> x;
                            }while(x < 0);
                            jucedu->serNrBaterii(x);
                        }

                        vJucarii.push_back(jucedu);
                    }
                    else if(tip_jucarie == "electronica"){
                        shared_ptr<Jucarie> jucel = make_shared<Electronica>();
                        jucel->citirejuc();
                        vJucarii.push_back(jucel);
                    }
                    else if(tip_jucarie == "moderna"){
                        shared_ptr<Jucarie> jucmod = make_shared<Moderna>();
                        jucmod->citirejuc();
                        vJucarii.push_back(jucmod);
                    }

                }
                copcuminte->setVectJucarii(vJucarii);
                vCopii.push_back(copcuminte);
            }
            else
            {
                shared_ptr<Neastamparat> copneast = make_shared<Neastamparat>();
                copneast->citire();
                vector<shared_ptr<Jucarie>> vJucarii;
                for(int i = 0 ; i < copneast->getNrFb(); i++)
                {
                    cout << "Introduceti tipul de jucarie(clasica/educativa/electronica/moderna): ";
                    cin >> tip_jucarie;
                    if(tip_jucarie == "clasica"){
                        shared_ptr<Jucarie> jucclas = make_shared<Clasica>();
                        jucclas->citirejuc();
                        vJucarii.push_back(jucclas);
                    }
                    else if(tip_jucarie == "educativa"){
                        shared_ptr<Jucarie> jucedu = make_shared<Educativa>();
                        jucedu->citirejuc();
                        vJucarii.push_back(jucedu);
                    }
                    else if(tip_jucarie == "electronica"){
                        shared_ptr<Jucarie> jucel = make_shared<Electronica>();
                        jucel->citirejuc();
                        vJucarii.push_back(jucel);
                    }
                    else if(tip_jucarie == "moderna"){
                        shared_ptr<Jucarie> jucmod = make_shared<Moderna>();
                        jucmod->citirejuc();
                        vJucarii.push_back(jucmod);
                    }

                }
                copneast->setVectJucarii(vJucarii);
                vCopii.push_back(copneast);
            }
        }
    }
    void afisareBD(){
        cout << "Introduceti numarul de copii de afisat: ";
        int m;
        cin >> m;
        for(int i = 0 ; i < m; i++ )
        {
            for(auto copil:vCopii){
                //dynamic cast pentru afisarea tipului de date continut in fct de copil
                //pt cuminte -> nr dulciuri
                Cuminte *cuminte = dynamic_cast<Cuminte*>(copil.get());
                if(cuminte)
                {
                    cuminte->afisare();
                    cout << endl;
                }
                else
                {
                    //pt neastamparat -> nr carbuni
                    Neastamparat *neastamparat = dynamic_cast<Neastamparat*>(copil.get());
                    neastamparat->afisare();
                    cout << endl;
                }
            }
        }
    }
};

//design pattern Factory pentru crearea unui tip de copil
class Factory {
public:
    virtual Copil* createCopil() = 0;
};

class FactoryCuminte : public Factory {
public:
    Copil* createCopil() override {
        return new Cuminte();
    }
};

class FactoryNeastamparat : public Factory {
public:
    Copil* createCopil() override {
        return new Neastamparat();
    }
};

class Meniu{
private:
    static Meniu *instanta;
    Meniu()=default;
    ~Meniu()=default;
public:
    Meniu(const Meniu &meniu) = delete;
    Meniu & operator=(const Meniu &meniu) = delete;
    static Meniu* getInstanta(){
       if(instanta == nullptr)
           instanta = new Meniu();
       return instanta;
    }
    void printMenu(){
        CopiiBD copii;
        int caz = 1;
        do
        {
            cout<<"-----------------MENIU-------------------\n";
            cout<<"1. Apasati 1 pentru citirea a n copii\n";
            cout<<"2. Apasati 2 pentru afisarea a m copii\n";
            cout<<"3. Apasati 0 pentru parasirea meniului\n";
            cout<<"Tasta: ";

            cin >> caz;
            if(caz == 1) {
                copii.citireBD();
            }

            else if(caz == 2) {
                copii.afisareBD();
            }

        }while(caz != 0);
        }
        
    };
    //Meniu * meniu = Meniu::getInstanta(); pt main
Meniu * Meniu::instanta = nullptr;
int main() {

    Meniu * meniu = Meniu::getInstanta();
    meniu->printMenu();

    return 0;
}