#include<iostream>
#include<string>
#include<memory>

class Armure {
public:
    int protection_;
    std::string name_;
    Armure(std::string name,int protection):name_(name),protection_(protection){}
    std::string getName(){return name_;}
    int getProtection(){return protection_;}
};
class Arme{
public:
    int degat_;
    std::string name_;
    Arme(std::string name,int degat):name_(name),degat_(degat){}
    std::string getName(){return name_;}
    int getDegat(){return degat_;}
    void afficherInfos() {
        std::cout << "Nom : " << name_ << std::endl;
        std::cout << "Degat : " << degat_ << std::endl;
    }
};
class Epee: public Arme{
    public:
    Epee():Arme("Epee",50){}
};
class Hache: public Arme{
    public:
    Hache():Arme("Hache",40){}
};
class Baguette: public Arme{
    public:
    Baguette():Arme("Baguette",50){}
    
};
class Arc: public Arme{
    public:
    Arc():Arme("Arc",60){}
};
class EpeeLegendaire : public Arme {
public:
    EpeeLegendaire() : Arme("Épée légendaire", 100) {}
};

class Marteau : public Arme {
public:
    Marteau() : Arme("Marteau", 60) {}
};

class Lance : public Arme {
public:
    Lance() : Arme("Lance", 70) {}
};

class Katana : public Arme {
public:
    Katana() : Arme("Katana", 80) {}
};
class ArcLegendaire : public Arme {
public:
    ArcLegendaire() : Arme("Arc légendaire", 90) {}
};

class Arbalete : public Arme {
public:
    Arbalete() : Arme("Arbalète", 70) {}
};
