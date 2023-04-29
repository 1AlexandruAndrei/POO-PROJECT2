#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>
#include <windows.h>
#include <chrono>
#include <thread>
#include <conio.h>
using namespace std;

class Locatie
{
    string sezon;
    string adresa;
    int capacitate;

public:
    Locatie(string, string, int);
    Locatie(const Locatie&);

    Locatie& operator=(const Locatie&);
    friend istream& operator>>(istream&, Locatie& obj);
    friend ostream& operator<<(ostream&, const Locatie& obj);

    int getCapacitate()const
    {
        return this->capacitate;
    }

    ~Locatie();
};

Locatie::Locatie(string sezon="", string adresa="", int capacitate=0)
{
    this->sezon=sezon;
    this->adresa=adresa;
    this->capacitate=capacitate;
}

Locatie::Locatie(const Locatie& obj)
{
    this->sezon=obj.sezon;
    this->adresa=obj.adresa;
    this->capacitate=obj.capacitate;
}

Locatie& Locatie::operator =(const Locatie& obj)
{
    if(this!=&obj)
    {
        this->sezon=obj.sezon;
        this->adresa=obj.adresa;
        this->capacitate=obj.capacitate;
    }
    return *this;

}

istream& operator >>(istream& in, Locatie& obj)
{
    cout<<"Introdu sezonul cand este deschisa locatia: ";
    in>>obj.sezon;

    cout<<"Introdu adresa locatiei: ";
    in>>obj.adresa;

    cout<<"Introdu capacitatea locatiei: ";
    in>>obj.capacitate;

    return in;
}

ostream& operator <<(ostream& out, const Locatie& obj)
{
    out<<"Locatia este deschisa: "<<obj.sezon<<endl;
    out<<"Adresa locatiei este: "<<obj.adresa<<endl;
    out<<"Numarul de persoane care incap in locatie este: "<<obj.capacitate<<endl;

    return out;
}

Locatie::~Locatie()
{
    this->sezon="anonim";
    this->adresa="anonim";
    this->capacitate=0;
}

///-------------------------------------------------------------------

class Bauturi
{
    string nume;
    int pret;
public:
    Bauturi(string, int);
    Bauturi(const Bauturi&);

    Bauturi& operator=(const Bauturi&);
    friend istream& operator>>(istream&, Bauturi&);
    friend ostream& operator<<(ostream&, const Bauturi&);

    ~Bauturi();

};

Bauturi::Bauturi(string nume="", int pret=0)
{
    this->nume=nume;
    this->pret=pret;
}

Bauturi::Bauturi(const Bauturi& obj)
{
    this->nume=obj.nume;
    this->pret=obj.pret;
}

Bauturi& Bauturi::operator=(const Bauturi& obj)
{
    if(this != &obj)
    {
        this->nume=obj.nume;
        this->pret=obj.pret;
    }
    return *this;
}

istream& operator>>(istream& in, Bauturi& obj)
{
    cout<<"Introdu numele bauturii: ";
    in>>obj.nume;

    cout<<"Introdu pretul bauturii: ";
    in>>obj.pret;

    return in;
}

ostream& operator<<(ostream& out, const Bauturi& obj)
{
    out<<"Numele bauturii este: "<<obj.nume<<endl;
    out<<"Pretul bauturii este: "<<obj.pret<<endl;

    return out;
}

Bauturi::~Bauturi()
{
    this->nume="anonim";
    this->pret=0;
}

///-------------------------------------------------------------------

class IOinterface
{
public:
    virtual istream& citire(istream&)=0;
    virtual ostream& afisare(ostream&) const=0;
};

///-------------------------------------------------------------------

class Club: public IOinterface
{
protected:
    string nume;
    vector<Locatie> listaLoc;
    int anDeschidere;

public:
    Club();
    Club(string nume, const vector<Locatie>& listaLoc, int anDeschidere);
    Club(const Club&);

    Club& operator=(const Club&);
    friend istream& operator>>(istream&, Club&);
    friend ostream& operator<<(ostream&, const Club&);

    istream& citire(istream& in)
    {
        cout<<"Introdu numele clubului:";
        in>>this->nume;
        if(!this->listaLoc.empty())
        {
            this->listaLoc.clear();
        }
        cout<<"1.ADD CLUB\n";
        cout<<"2.STOP\n";
        int k;
        while(cin>>k && k!=2)
        {
            this->listaLoc.push_back(*(new Locatie()));
            in>>this->listaLoc.back();
            cout<<"1.ADD CLUB\n";
            cout<<"2.STOP\n";
        }
        cout<<"Introdu anul deschiderii clubului: ";
        in>>this->anDeschidere;
        return in;
    }

    ostream& afisare(ostream& out) const
    {
        out<<"Numele clubului:"<<this->nume<<endl;
        out<<"LISTA CU LOCATIILE CLUBULUI\n";
        for(int i=0; i<this->listaLoc.size(); i++)
            out<<this->listaLoc[i]<<endl;

        out<<"Anul deschiderii clubului este: "<<this->anDeschidere<<endl;
        out<<"Capacitatea clubului este: "<<this->capacitate()<<endl;
        return out;
    }
    string getNume()
    {
        return this->nume;
    }

    virtual int capacitate() const=0;

    ~Club()
    {
        nume="";
        listaLoc.clear();
        anDeschidere=0;
    }

    int getAnDeschidere() const
    {
        return this->anDeschidere;
    }

};

Club::Club()
{
    this->nume="anonim";
    this->listaLoc= {};
    this->anDeschidere=0;
}

Club::Club(string nume, const vector<Locatie>& listaLoc, int anDeschidere)
{
    this->nume=nume;
    this->listaLoc=listaLoc;
    this->anDeschidere=anDeschidere;
}

Club::Club(const Club& obj)
{
    this->nume=obj.nume;
    this->listaLoc=obj.listaLoc;
    this->anDeschidere=obj.anDeschidere;
}

Club& Club::operator=(const Club& obj)
{
    if(this != &obj)
    {
        this->nume=obj.nume;
        this->listaLoc=obj.listaLoc;
        this->anDeschidere=obj.anDeschidere;
    }
    return *this;

}

istream& operator>>(istream& in, Club& obj)
{
    return obj.citire(in);
}

ostream& operator <<(ostream& out, const Club& obj)
{
    return obj.afisare(out);
}

///-------------------------------------------------------------------

class Dancer
{
    string nume;
    int varsta;
public:
    Dancer(string, int);
    Dancer(const Dancer&);

    Dancer& operator=(const Dancer&);
    friend istream& operator>>(istream&, Dancer&);
    friend ostream& operator<<(ostream&, const Dancer&);

    ~Dancer();
};

Dancer::Dancer(string nume="", int varsta=0)
{
    this->nume=nume;
    this->varsta=varsta;
}

Dancer::Dancer(const Dancer& obj)
{
    this->nume=obj.nume;
    this->varsta=obj.varsta;
}

Dancer& Dancer::operator =(const Dancer& obj)
{
    if(this!=&obj)
    {
        this->nume=obj.nume;
        this->varsta=obj.varsta;
    }
    return *this;

}

istream& operator >>(istream& in, Dancer& obj)
{
    cout<<"Introdu numele animatoarei: ";
    in>>obj.nume;

    cout<<"Introdu varsta animatoarei: ";
    in>>obj.varsta;

    while(obj.varsta<18)
    {
        cout<<"Ai gresit varsta animatoarei!"<<endl;
        cout<<"Introdu varsta animatoarei: ";
        in>>obj.varsta;
    }

    return in;
}

ostream& operator <<(ostream& out, const Dancer& obj)
{
    out<<"Numele frumoasei animatoare este: "<<obj.nume<<endl;
    out<<"Varsta animatoarei este: "<<obj.varsta<<endl;

    return out;
}

Dancer::~Dancer()
{
    this->nume="anonim";
    this->varsta=0;
}

///-------------------------------------------------------------------

class Nightclub:virtual public Club
{
protected:
    bool vip;
    vector<Dancer> listaDans;
public:
    Nightclub();
    Nightclub(string nume, const vector<Locatie>& listaLoc, int anDeschidere, bool vip, const vector<Dancer>& listaDans);
    Nightclub(const Nightclub&);

    Nightclub& operator=(const Nightclub&);
    friend istream& operator>>(istream& in, Nightclub &obj);
    friend ostream& operator<<(ostream& out, const Nightclub &obj);
    istream& citire(istream& in)
    {
        this->Club::citire(in);
        cout<<"Clubul este destinat persoanelor exclusiviste?\n1=TRUE 0=FALSE\n";
        in>>this->vip;

        if(!this->listaDans.empty())
        {
            this->listaDans.clear();
        }
        cout<<"1.ADD DANCER\n";
        cout<<"2.STOP\n";
        int ok;
        while(cin>>ok && ok!=2)
        {
            this->listaDans.push_back(*(new Dancer()));
            in>>this->listaDans.back();
            cout<<"1.ADD DANCER\n";
            cout<<"2.STOP\n";

        }

        return in;
    }
    ostream& afisare(ostream& out) const
    {
        this->Club::afisare(out);
        if(this->vip==false)
            out<<"Oricine poate intra in club!\n";
        else
            out<<"Clubul este exclusivist, destinat persoanelor VIP!\n";
        for(int i=0; i<this->listaDans.size(); i++)
            out<<this->listaDans[i]<<endl;
        return out;
    }

    virtual int capacitate() const
    {
        int capacitate=0;
        for(int i=0; i<this->listaLoc.size(); i++)
            capacitate+=this->listaLoc[i].getCapacitate();
        return capacitate*0.1;
    }
    void getDancer()
    {
        for(int i=0; i<this->listaDans.size(); i++)
            cout<<this->listaDans[i]<<endl;
    }

    bool getVip() const
    {
        return this->vip;
    }
    virtual ~Nightclub()
    {
        vip=false;
        listaDans.clear();
    }

};

Nightclub::Nightclub(): Club()
{
    this->vip=false;
    this->listaDans= {};
}

Nightclub::Nightclub(string nume, const vector<Locatie>& listaLoc, int anDeschidere, bool vip, const vector<Dancer>& listaDans):

    Club(nume, listaLoc, anDeschidere)
{
    this->vip=vip;
    this->listaDans=listaDans;
}

Nightclub::Nightclub(const Nightclub& obj):Club(obj)
{
    this->vip=obj.vip;
    this->listaDans=obj.listaDans;
}

Nightclub& Nightclub::operator =(const Nightclub& obj)
{
    if(this != &obj)
    {
        Club::operator=(obj);
        this->vip=obj.vip;
        this->listaDans=obj.listaDans;
    }

    return *this;
}

istream& operator>>(istream& in, Nightclub& obj)
{
    return obj.citire(in);
}

ostream& operator <<(ostream& out, const Nightclub& obj)
{
    return obj.afisare(out);
}


///-------------------------------------------------------------------

class Lounge: virtual public Club
{
protected:
    int consumatieMinima;
    vector<Bauturi> listaBaut;

public:
    Lounge();
    Lounge(string nume, const vector<Locatie>& listaLoc, int anDeschidere, int consumatieMinima, const vector<Bauturi>&listaBaut);
    Lounge(const Lounge&);

    Lounge& operator=(const Lounge&);
    friend istream& operator >>(istream& in, Lounge& obj);
    friend ostream& operator <<(ostream& out, const Lounge& obj);

    istream& citire(istream& in)
    {
        this->Club::citire(in);
        cout<<"Introdu consumatia minima pe care trebuie sa o ai in club: ";
        in>>this->consumatieMinima;

        if(!this->listaBaut.empty())
        {
            this->listaBaut.clear();
        }
        cout<<"1.ADD BAUTURA\n";
        cout<<"2.STOP\n";
        int k1;
        while(cin>>k1 && k1!=2)
        {
            this->listaBaut.push_back(*(new Bauturi()));
            in>>this->listaBaut.back();
            cout<<"1.ADD BAUTURA\n";
            cout<<"2.STOP\n";
        }
        return in;
    }

    ostream& afisare(ostream& out)const
    {
        this->Club::afisare(out);
        out<<"Consumatia minima pe care trebuie sa o faci este: "<<this->consumatieMinima<<" lei"<<endl;
        for(int i=0; i<this->listaBaut.size(); i++)
            out<<this->listaBaut[i]<<endl;
        return out;
    }
    virtual int capacitate() const
    {
        int capacitate=0;
        for(int i=0; i<this->listaLoc.size(); i++)
            capacitate+=this->listaLoc[i].getCapacitate();
        return capacitate*1.1;
    }


    int getConsumatieMinima() const
    {
        return this->consumatieMinima;
    }
    virtual ~Lounge()
    {
        consumatieMinima=0;
        listaBaut.clear();
    }
};

Lounge::Lounge():Club()
{
    this->consumatieMinima=0;
    this->listaBaut= {};
}

Lounge::Lounge(string nume, const vector<Locatie>& listaLoc, int anDeschidere, int consumatieMinima, const vector<Bauturi>&listaBaut):Club(nume, listaLoc, anDeschidere)
{
    this->consumatieMinima=consumatieMinima;
    this->listaBaut=listaBaut;
}


Lounge::Lounge(const Lounge& obj):Club(obj)
{
    this->consumatieMinima=obj.consumatieMinima;
    this->listaBaut=obj.listaBaut;
}

Lounge& Lounge::operator=(const Lounge& obj)
{
    if(this!=&obj)
    {
        Club::operator=(obj);
        this->consumatieMinima=obj.consumatieMinima;
        this->listaBaut=obj.listaBaut;
    }

    return *this;
}

istream& operator>>(istream& in, Lounge& obj)
{
    return obj.citire(in);
}

ostream& operator <<(ostream& out, const Lounge& obj)
{
    return obj.afisare(out);
}

///-------------------------------------------------------------------

///diamant
class Megadiscoteca: public Nightclub, public Lounge
{
    bool happyHour;
public:
    friend istream& operator >>(istream& in, Megadiscoteca& obj);
    friend ostream& operator <<(ostream& out, const Megadiscoteca& obj);

    Megadiscoteca()
    {
        this->happyHour=false;
    }

    Megadiscoteca(string nume, const vector <Locatie>& listaLoc, int anDeschidere,
                  bool vip, const vector<Dancer>& listaDans,
                  int consumatieMinima, const vector<Bauturi>&listaBaut):Club(nume, listaLoc, anDeschidere),
        Nightclub(nume, listaLoc, anDeschidere, vip, listaDans), Lounge(nume, listaLoc, anDeschidere, consumatieMinima, listaBaut)
    {
        this->happyHour=happyHour;
    }


    Megadiscoteca(const Megadiscoteca& obj): Club(obj), Nightclub(obj), Lounge(obj)
    {
        this->happyHour=obj.happyHour;

    }

    Megadiscoteca& operator =(const Megadiscoteca& obj)
    {
        if(this!= & obj)
        {
            Nightclub::operator=(obj);
            Lounge::operator=(obj);
            this->happyHour=obj.happyHour;
        }
        return *this;
    }

    istream& citire(istream& in)
    {
        Club::citire(in);
        cout<<"Megadiscoteca este exclusivista?\n0=NU 1=DA\n";
        in>>this->vip;

        if(!this->listaDans.empty())
        {
            this->listaDans.clear();
        }
        cout<<"1.ADD DANCER\n";
        cout<<"2.STOP\n";
        int ok;
        while(cin>>ok && ok!=2)
        {
            this->listaDans.push_back(*(new Dancer()));
            in>>this->listaDans.back();
            cout<<"1.ADD DANCER\n";
            cout<<"2.STOP\n";

        }

        cout<<"Introduceti consumatia minima pe care trebuie sa o aveti in Megadiscoteca:";
        in>>this->consumatieMinima;

        if(!this->listaBaut.empty())
        {
            this->listaBaut.clear();
        }
        cout<<"1.ADD BAUTURA\n";
        cout<<"2.STOP\n";
        int k1;
        while(cin>>k1 && k1!=2)
        {
            this->listaBaut.push_back(*(new Bauturi()));
            in>>this->listaBaut.back();
            cout<<"1.ADD BAUTURA\n";
            cout<<"2.STOP\n";

        }

        cout<<"Are Happy Hour?\n0=NU 1=DA\n";
        in>>this->happyHour;

        return in;

    }

    ostream& afisare(ostream& out) const
    {
        Club::afisare(out);
        if(this->vip==false)
            out<<"Oricine poate intra in Megadiscoteca!\n";
        else
            out<<"Megadiscoteca este detinata persoanelor exclusiviste!\n";

        out<<"Consumatia minima pe care trebuie sa o aveti in Megadiscoteca este:"<<this->consumatieMinima<<endl;
        for(int i=0; i<this->listaBaut.size(); i++)
            out<<this->listaBaut[i]<<endl;
        out<<endl;

        for(int i=0; i<this->listaDans.size(); i++)
            out<<this->listaDans[i]<<endl;
        out<<endl;
        if(this->happyHour==0)
            out<<"NU ";
        out<<"ARE HAPPY HOUR"<<endl;

        return out;

    }
    virtual int capacitate() const
    {
        return Nightclub::capacitate() + 10 * this->happyHour;
    }
    virtual ~Megadiscoteca() {}

};

///-------------------------------------------------------------------

class Nightlife
{
    Club* club;
    bool isOpen;
public:

    friend istream& operator>>(istream& in, Nightlife& obj)
    {
        cout<<"1.NIGHTCLUB\n";
        cout<<"2.LOUNGE\n";
        cout<<"3.MEGADISCOTECA\n";
        int k;
        cin>>k;
        if(k==1)
        {
            obj.club= new Nightclub();
        }
        if(k==2)
        {
            obj.club=new Lounge();
        }
        if(k==3)
        {
            obj.club=new Megadiscoteca();
        }
        in>>*obj.club;
        cout<<"Clubul este deschis in prezent?\n1=DA 0=NU\n";
        in>>obj.isOpen;
        return in;
    }

    friend ostream& operator<<(ostream& out, const Nightlife& obj)
    {
        out<<"CLUB\n"<<*obj.club<<endl;
        if(obj.isOpen==false)
            out<<"Clubul NU este deschis acum!"<<endl;
        else
            out<<"Clubul este deschis!"<<endl;
        return out;
    }

    Club* getClub() const
    {
        return this->club;
    }

    ~Nightlife()
    {
        delete club;
    }

};

class District
{
    list<Nightlife> inventar;
    vector<Club*> cluburi;
public:
    void addInventar();
    void addCluburi(string numeClub);
    void showInventar();
    void showInventar1();
    void showLoungeCons();
    void showCluburi();
    void aflaAn();
    int showAccess(string inp);


    int getFirstLoungeConsumatieMinima();
    int getFirstVIP();
    ~District() {}
};

void District::addInventar()
{
    Nightlife n;
    cin>>n;
    inventar.push_back(n);
}

void District::showInventar()
{
    for(auto it=inventar.begin(); it!=inventar.end(); it++)
        cout<<*it<<endl;
}

void District::addCluburi(string numeClub)
{
    for(auto it=inventar.begin(); it!=inventar.end(); it++)
    {
        if(it->getClub()->getNume()==numeClub)
        {
            cluburi.push_back(it->getClub());

        }
    }
}

void District::showCluburi()
{
    for(int i=0; i<cluburi.size(); i++)
        cout<<*cluburi[i]<<endl;
}


void District::showInventar1()
{
    for(auto it=inventar.begin(); it!=inventar.end(); it++)
    {
        cout<<it->getClub()->getNume()<<endl;
    }
}

int District::showAccess(string inp)
{
    int ok=0;
    for(auto it=inventar.begin(); it!=inventar.end(); it++)
    {
        if (it->getClub()->getNume() ==inp)
            ok++;
    }
    if(ok==0)
        return 0;
    else
        return 1;
}

///anul de deschidere a nunui club
void District::aflaAn()
{
    for(auto it=inventar.begin(); it!=inventar.end(); it++)
    {
        cout<<it->getClub()->getAnDeschidere()<<endl;
    }
}

int District::getFirstLoungeConsumatieMinima()
{
    for (const auto& nightlife:inventar)
    {
        Lounge* lounge = dynamic_cast<Lounge*>(nightlife.getClub());
        if (lounge!=nullptr)
        {
            return lounge->getConsumatieMinima();///iau consumatia minima de la un obiect LOUNGE
        }
    }

    return 0;///daca nu gasesc obiect in inventar
}

int District::getFirstVIP()
{
    for (const auto& nightlife:inventar)
    {
        Nightclub* nightclub=dynamic_cast<Nightclub*>(nightlife.getClub());
        if (nightclub!=nullptr)
        {
            return nightclub->getVip();
        }
    }

    return 0;
}


///-------------------------------------------------------------------

int main()
{

    District d;
    //Nightclub n;
    int k=1;
    while(k==1)
    {
        cout<<"1. ADD INVENTAR\n";
        cout<<"2. SHOW INVENTAR\n";
        cout<<"3. ADD CLUBURI\n";
        cout<<"4. SHOW CLUBURI\n";
        cout<<"\033[1;33m5. VREAU SA MA DISTREZ\n\033[0m";
        cout<<"6. STOP\n";
        int cmd;
        cin>>cmd;
        switch(cmd)
        {
        case 1:
        {
            system("cls");
            d.addInventar();
            break;
        }
        case 2:
        {
            system("cls");
            d.showInventar();
            break;
        }
        case 3:
        {
            system("cls");
            cout<<"NUMELE CLUBULUI: ";
            string nume;
            cin>>nume;
            d.addCluburi(nume);
            break;
        }
        case 4:
        {
            system("cls");
            d.showCluburi();
            break;
        }
        case 5:
        {
            system("cls");
            int cm;
            cout<<"0.STOP\n1.INTRA IN NIGHTCLUB\n2.INTRA IN LOUNGE\n3.INTRA IN MEGADISCOTECA\n";
            cin>>cm;

            if(cm==0)
                break;
            else
            {
                cout<<"INTRODU NUMELE CLUBULUI IN CARE VREI SA INTRI:";
                string numeclub;
                cin>>numeclub;



                if(d.showAccess(numeclub)==0)
                {
                    system("cls");
                    cout<<"\033[31mACCESS DENIED\033[0m"<<endl;
                    break;
                }
                else
                {
                    system("cls");
                    cout<<"\033[32mACCESS IS ALLOWED\033[0m" <<endl;

                    int c,minima,consumatie=0,ex;

                    cout<<"BUN VENIT IN ";
                    d.showInventar1();

                    cout<<"\nCLUBUL A FOST DESCHIS IN ";
                    d.aflaAn();
                    cout<<endl;


                    if(cm==2)
                    {
                        minima=d.getFirstLoungeConsumatieMinima();
                        cout<<"AICI, CONSUMATIA MINIMA PE CARE TREBUIE SA O AI ESTE "<<minima<<" \033[4;32mRON\033[0m"<<endl;
                        while(consumatie<minima)
                        {
                            if(consumatie<minima)
                            {
                                cout<<"VREAU SA CONSUM O BAUTURA IN VALOARE DE (RON):";
                                cin>>c;
                                consumatie+=c;
                            }
                        }
                        system("cls");
                        cout<<"POTI SA RAMAI IN CLUB PENTRU PETRECERE\n";
                        Sleep(3000);


                        cout<<endl<<"DISTRACTIE PLACUTA!\n";
                        Sleep(3000);
                        system("cls");

                        int seconds=10,i;
                        for(i=seconds; i>=2; i--)
                        {
                            cout<<"PETRECEREA DIN LOUNGE INCEPE IN "<<i<<" MINUTE"<<endl;

                            Sleep(1000);
                            system("cls");
                        }
                        cout<<"PETRECEREA DIN LOUNGE INCEPE IN 1 MINUT"<<endl;
                        Sleep(1000);
                        system("cls");


                        cout<<"WELCOME"<<endl;

                        int notes[]= {262, 294, 330, 392, 330, 294, 262, 262, 294, 294, 262, 294, 330, 294, 262};
                        int durations[]= {300, 150, 150, 300, 150, 150, 300, 150, 150, 300, 150, 150, 300, 150, 600};

                        for (int i=0; i<15; i++)
                        {
                            Beep(notes[i], durations[i]);
                            Sleep(50);
                        }
                        system("cls");
                        Sleep(1000);
                        cout<<"\033[38;2;255;192;203mGOODBYE!\033[0m\n";
                        Sleep(4000);
                        system("cls");
                    }
                    else if (cm==1)
                    {
                        ex=d.getFirstVIP();
                        if(ex==0)
                        {
                            cout<<"CLUBUL DE NOAPTE ESTE DESCHIS PUBLICULUI LARG!"<<endl;

                        }
                        else
                        {
                            cout<<"ACCESUL IN CLUB ESTE RESTRICTIONAT!\nINTRODU PAROLA PENTRU A INTRA:";
                            string pass="";
                            char ch;
                            while ((ch = getch()) != '\r')
                            {
                                if (ch == '\b')
                                {
                                    if (pass.length() > 0)
                                    {
                                        pass.pop_back();
                                        cout << "\b \b";
                                    }
                                }
                                else
                                {
                                    pass += ch;
                                    cout << "*";
                                }
                            }
                            if(pass=="club123")
                            {
                                system("cls");
                                cout<<"\033[32mCORRECT PASSWORD, COME IN\033[0m" <<endl;

                            }
                            else
                            {
                                system("cls");
                                cout<<"\033[31mWRONG PASSWORD, GET OUT\033[0m"<<endl;
                                break;
                            }
                        }

                        int seconds=10,i;
                        for(i=seconds; i>=2; i--)
                        {
                            cout<<"PETRECEREA DIN NIGHTCLUB INCEPE IN "<<i<<" MINUTE"<<endl;

                            Sleep(1000);
                            system("cls");
                        }
                        cout<<"PETRECEREA DIN NIGHTCLUB INCEPE IN 1 MINUT"<<endl;
                        Sleep(1000);
                        system("cls");

                        int notes[] = {330, 392, 523, 659, 784, 659, 523, 392, 330, 392, 523, 659};
                        int durations[] = {300, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 600};

                        for (int i=0; i<12; i++)
                        {
                            Beep(notes[i], durations[i]);
                            Sleep(50);
                        }


                        Sleep(1000);
                        cout<<"\033[38;2;255;192;203mGOODBYE!\033[0m\n";
                        Sleep(4000);
                        system("cls");

                    }
                    else if (cm==3)
                    {
                        ex=d.getFirstVIP();
                        if(ex==0)
                        {
                            cout<<"CLUBUL DE NOAPTE ESTE DESCHIS PUBLICULUI LARG!"<<endl;

                        }
                        else
                        {
                            cout<<"INAINTE DE A INTRA, INTRODU PAROLA:";

                            string pass="";
                            char ch;
                            while ((ch = getch()) != '\r')
                            {
                                if (ch == '\b')
                                {
                                    if (pass.length() > 0)
                                    {
                                        pass.pop_back();
                                        cout << "\b \b";
                                    }
                                }
                                else
                                {
                                    pass += ch;
                                    cout << "*";
                                }
                            }
                            if(pass=="club123")
                            {
                                system("cls");
                                cout<<"\033[32mCORRECT PASSWORD, COME IN\033[0m" <<endl;

                            }
                            else
                            {
                                system("cls");
                                cout<<"\033[31mWRONG PASSWORD, GET OUT\033[0m"<<endl;
                                break;
                            }
                        }

                        minima=d.getFirstLoungeConsumatieMinima();
                        cout<<"AICI, CONSUMATIA MINIMA PE CARE TREBUIE SA O AI ESTE "<<minima<<" \033[4;32mRON\033[0m"<<endl;
                        while(consumatie<minima)
                        {
                            if(consumatie<minima)
                            {
                                cout<<"VREAU SA CONSUM O BAUTURA IN VALOARE DE (RON):";
                                cin>>c;
                                consumatie+=c;
                            }
                        }
                        system("cls");
                        cout<<"POTI SA RAMAI IN CLUB PENTRU PETRECERE\n";
                        Sleep(3000);

                        cout<<endl<<"DISTRACTIE PLACUTA!\n";
                        Sleep(3000);

                        int seconds=10,i;
                        for(i=seconds; i>=2; i--)
                        {
                            cout<<"PETRECEREA DIN NIGHTCLUB INCEPE IN "<<i<<" MINUTE"<<endl;

                            Sleep(1000);
                            system("cls");
                        }
                        cout<<"PETRECEREA DIN NIGHTCLUB INCEPE IN 1 MINUT"<<endl;
                        Sleep(1000);
                        system("cls");

                        int notes[] = {523, 659, 784, 523, 659, 784, 880, 987, 880, 784, 659, 523, 440, 494, 523, 659, 784, 659, 523, 440};
                        int durations[] = {600, 300, 300, 600, 300, 300, 600, 300, 300, 300, 300, 600, 150, 150, 600, 300, 300, 600, 300, 300};

                        int num_notes = sizeof(notes) /sizeof(notes[0]);

                        int total_duration=0;
                        for (int i=0; i<num_notes; i++)
                        {
                            total_duration+=durations[i];
                        }

                        int delay=(10000-total_duration)/num_notes;

                        for (int i=0; i<num_notes; i++)
                        {
                            Beep(notes[i], durations[i]);
                            Sleep(delay);
                        }
                        cout<<"\033[38;2;255;192;203mGOODBYE!\033[0m\n";
                        Sleep(4000);
                        system("cls");

                    }

                    break;
                }
            }

        }
        case 6:
        {
            k=0;
            break;
        }
        default:
        {
            system("cls");
            cout<<"INVALID\n";
            system("pause");
            break;
        }
        }
    }

    return 0;
}
