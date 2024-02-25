#pragma once 
#include<iostream>
#include<memory>
#include<string>
#include<vector>
#include "object.hpp"
//classe mère entité qui me permet ensuite de distinguer selon personnage et monstre
class Entity {
public:
    std::string name;
    int hp;
    std::shared_ptr<Arme> arme_;
    std::shared_ptr<Armure> armure_;


    Entity(std::string name, std::shared_ptr<Arme> arme, std::shared_ptr<Armure> armure, int hp) : name{name}, arme_{arme}, armure_{armure}, hp{hp} {}

    void attaquer(std::shared_ptr<Entity> cible)
    {
        std::cout << name << " attaque " << cible->name << " avec son " << arme_->getName() << " et lui inflige " << arme_->getDegat() << " dégats" << std::endl;
        cible->hp -= arme_->getDegat();
    }

    bool isAlive() { return hp > 0; }
    void printName() { std::cout << name << std::endl; }
    void printArme() { std::cout << arme_->getName() << std::endl; }

};

class Monstre : public Entity {
public:
    Monstre(std::string name, std::shared_ptr<Arme> arme, std::shared_ptr<Armure> armure, int hp) : Entity(name, arme, armure, hp) {}
};

class Personnage : public Entity {
public:
    int xp{0};
    int niveau{1};
    int agility{1};
    int max_hp{hp};
    Personnage(std::string name, std::shared_ptr<Arme> arme, std::shared_ptr<Armure> armure, int hp) : Entity(name, arme, armure, hp) {}

    void getXP(int gain) { 
            xp += gain; 
            if (xp >= 100 * niveau * (niveau + 1) / 2) { 
                niveau++;
                //les dégats augmentent avec le niveau du joueur
                this->arme_->degat_+=1;
                std::cout << name << " a atteint le niveau " << niveau << " !" << std::endl;
                this->max_hp += 1;
                this->hp = this->max_hp;
            }
        }
    void afficherInfos() {
        std::cout << "Nom : " << name << std::endl;
        std::cout << "Arme : " << arme_->getName() << std::endl;
        std::cout << "Armure : " << armure_->getName() << std::endl;
        std::cout << "Points de vie : " << hp << std::endl;
        std::cout << "Niveau : " << niveau << std::endl;
    }
    void heal(int amount) {
        hp += amount;
        if (hp > max_hp) {
            hp = max_hp;
        }
    }
    void setArme(std::shared_ptr<Arme> arme) { arme_ = arme; 
    arme_->degat_ +=this->niveau;}
    void setArmure(std::shared_ptr<Armure> armure) { armure_ = armure; }
};
class Chevalier : public Personnage {
public:
    Chevalier(std::string name) : Personnage(name, std::make_shared<Epee>(), std::make_shared<Armure>("Armure lourde", 20), 150) {}
};

class Archer : public Personnage {
public:
    Archer(std::string name) : Personnage(name, std::make_shared<Arc>(), std::make_shared<Armure>("Armure légère", 10), 120) {}
};

class Mage : public Personnage {
public:
    Mage(std::string name) : Personnage(name, std::make_shared<Baguette>(), std::make_shared<Armure>("Robe magique", 5), 100) {}
};

class Mercenaire : public Personnage {
public:
    Mercenaire(std::string name) : Personnage(name, std::make_shared<Hache>(), std::make_shared<Armure>("Armure de cuir renforcée", 25), 170) {}
};