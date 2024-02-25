#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "object.hpp"
#include "personnage.hpp"
using namespace std;

//... une quête va prendre en paramètre une description ainsi que ses dialogues sous forme d'une fonction

class Quete {
public:
    string description;
    function<void(shared_ptr<Personnage>)> dialogue; 
    shared_ptr<Personnage> joueur;
    bool estTerminee;

    Quete(string description, function<void(shared_ptr<Personnage>)> dialogue,shared_ptr<Personnage> joueur) :
        description(description),
        dialogue(dialogue),
        joueur(joueur),
        estTerminee(false) {}

    void terminer() {
        estTerminee = true;
    }
    void executer() {
        if (!estTerminee) {
            dialogue(joueur);
            terminer();
        }}
};

//...fonction qui permet la création du joueur avec la saisie du joueur

auto creer_personnage(std::string name, std::string classe){
    std::shared_ptr<Personnage> perso;
    if (classe == "Chevalier"){
        perso = std::make_shared<Chevalier>(name);
    }  
    else if (classe == "Mage"){
        perso = std::make_shared<Mage>(name);
    }
    else if (classe == "Archer"){
        perso = std::make_shared<Archer>(name);
    }
    else if (classe == "Mercenaire"){
        perso = std::make_shared<Mercenaire>(name);
    }
    else 
    {
        throw "Erreur : personnage non reconnu";
    }
    std::cout<<std::endl;
    std::cout<<"Très bon choix. Un " << classe <<" devrait facilement s'en sortir."<< std::endl;
    perso->afficherInfos();
    return perso;
};

//...fonction qui imlémente l'obtention d'une amre aléatoire lors de l'exploration

std::shared_ptr<Arme> obtenirArmeAleatoire() {
    // Générer un nombre aléatoire pour déterminer la rareté
    int rarete = rand() % 100 + 1; 

    // Déterminer l'arme en fonction de la rareté
    if (rarete <= 5) { // 5% de chance
        int choice=rand()% 2+1;
        if(choice==1){
            return std::make_shared<EpeeLegendaire>();}
        else{
        return std::make_shared<ArcLegendaire>();}
    } else if (rarete <= 40) { // 40% de chance
    int choice=rand()% 3+1;
        if(choice==1){
        return std::make_shared<Marteau>();}
        else if(choice==2){
        return std::make_shared<Lance>();}
        else{
        return std::make_shared<Katana>();}
    } else  { // 70% de chance
    int choice=rand()% 5+1;
        if(choice==1){
        return std::make_shared<Arbalete>();}
        else if(choice==2){
        return std::make_shared<Hache>();}
        else if(choice==3){
        return std::make_shared<Baguette>();}
        else if(choice==4){
        return 
            std::make_shared<Epee>();}
        else{
        return 
            std::make_shared<Arc>();}
        }
    }

// ... Création des dialogues pour les différentes quêtes

void Monstre_de_la_mine(shared_ptr<Personnage> joueur)
{
    cout << "Vous êtes " << joueur->name <<", un sorceleur légendaire, sur la piste d'un monstre féroce." << endl;
    cout << "Vous êtes dans une forêt dense, le lieu de résidence supposé du monstre." << endl;
    cout << "Que choisissez-vous de faire ?" << endl;
    cout << "1. Demander de l'aide aux villageois locaux." << endl;
    cout << "2. Continuer à suivre les traces du monstre." << endl;

    auto monstre=make_shared<Monstre>("Dragon", make_shared<Arme>("Arme de Monstre", 40), make_shared<Armure>("Armure de Monstre", 10), 50);
    auto boss=make_shared<Monstre>("Boss", make_shared<Arme>("Arme du Boss", 60), make_shared<Armure>("Armure du Boss", 20), 100);
    // variable de déscision. Il faut les définir avant le switch
    int choix;
    cin >> choix;
    switch(choix){
    case 1:
        cout << "Vous décidez de demander de l'aide aux villageois locaux." << endl;
        cout << "Vous approchez du premier villageois que vous voyez et lui demandez des informations sur le monstre." << endl;
        cout << "Le villageois vous regarde avec méfiance avant de finalement répondre : 'Le monstre que vous cherchez a été vu près de la vieille mine abandonnée.'" << endl;
        cout << "Vous vous dirigez vers la vieille mine abandonnée, le cœur lourd de la menace qui vous attend à l'intérieur." << endl;
        break;
    case 2:
        cout << "Vous décidez de poursuivre votre traque du monstre sans demander l'aide des villageois." << endl;
        cout << "Vous vous sentez plus confiant en votre propre capacité à résoudre ce problème." << endl;
        cout << "Vous continuez à traquer le monstre à travers la forêt dense, en suivant ses traces." << endl;
        cout << "Soudain, vous tombez sur une clairière où le monstre se tient devant vous." << endl;
        cout << "Préparez-vous au combat !" << endl;

        while (joueur->isAlive() && monstre->isAlive()) {
                        joueur->attaquer(monstre);
                        if (monstre->isAlive()) {
                            monstre->attaquer(joueur);
                        }}
        if (!joueur->isAlive()) {
            cout << "Malheureusement, le monstre était trop fort pour vous. Vous devez battre en retraite." << endl;
            cout << "Votre quête continue une autre fois." << endl;
        }
        break;
        }
    cout << "À l'intérieur de la mine, vous entendez des bruits sinistres qui indiquent la présence du monstre." << endl;
    cout << "Que choisissez-vous de faire ?" << endl;
    cout << "1. Avancer prudemment dans la mine." << endl;
    cout << "2. Utiliser une potion de vision nocturne pour éclairer votre chemin." << endl;

    cin >> choix;
    switch(choix){
    case 1:
        cout << "Vous avancez prudemment dans l'obscurité de la mine, votre épée prête à dégainer à tout moment." << endl;
        cout << "Soudain, le monstre surgit de l'ombre, prêt à vous attaquer !" << endl;

        while (joueur->isAlive() && monstre->isAlive()) {
                        joueur->attaquer(monstre);
                        if (monstre->isAlive()) {
                            monstre->attaquer(joueur);
                        }}
        if (!joueur->isAlive()) {
            cout << "Malheureusement, le monstre était trop fort pour vous. Vous devez battre en retraite." << endl;
            cout << "Votre quête continue une autre fois." << endl;
        }
        break;
    case 2:
        cout << "Vous utilisez une potion de vision nocturne pour éclairer votre chemin dans l'obscurité de la mine." << endl;
        cout << "Cependant, cela attire l'attention du monstre qui vous attaque immédiatement !" << endl;

        while (joueur->isAlive() && monstre->isAlive()) {
                        joueur->attaquer(monstre);
                        if (monstre->isAlive()) {
                            monstre->attaquer(joueur);
                        }}
        if (!joueur->isAlive()) {
            cout << "Malheureusement, le monstre était trop fort pour vous. Vous devez battre en retraite." << endl;
            cout << "Votre quête continue une autre fois." << endl;
        }
        break;
    }

    cout << "Finalement, après un combat acharné, vous parvenez à vaincre le monstre et à le terrasser." << endl;
    cout << "Vous avez sauvé les villageois de la menace du monstre." << endl;
    cout << "Votre réputation de sorceleur légendaire continue de croître." << endl;
} 
void le_monstre_des_marais(shared_ptr<Personnage> joueur) {
    cout << "Vous êtes " <<joueur->name<< ", un sorceleur légendaire, engagé pour traquer un monstre redoutable." << endl;
    cout << "Le contrat indique que le monstre sévit dans les marais au nord du village." << endl;
    cout << "Vous arrivez au village, où les habitants vous accueillent avec soulagement." << endl;
    cout << "Ils vous informent que la créature terrorise le village depuis des semaines." << endl;
    cout << "Que choisissez-vous de faire ?" << endl;
    cout << "1. Aller voir le maire pour obtenir plus d'informations." << endl;
    cout << "2. Examiner les alentours du village à la recherche d'indices." << endl;

    auto monstre = make_shared<Monstre>("Banshee", make_shared<Arme>("Griffes acérées", 35), make_shared<Armure>("Peau résistante", 15), 60);

    int choix;
    cin >> choix;

    switch (choix) {
    case 1:
        cout << "Vous décidez d'aller voir le maire pour obtenir plus d'informations." << endl;
        cout << "Le maire vous raconte les détails des attaques du monstre et vous donne des conseils sur la manière de le combattre." << endl;
        cout << "Il vous recommande de chercher des objets bénis dans la vieille église abandonnée." << endl;
        break;
    case 2:
        cout << "Vous choisissez d'examiner les alentours du village à la recherche d'indices." << endl;
        cout << "Vous découvrez des traces étranges dans la boue, semblables à des griffures profondes." << endl;
        cout << "Vous décidez de suivre les traces qui vous mènent à une grotte dissimulée dans les collines." << endl;
        break;
    }

    cout << "Vous vous retrouvez à un carrefour, avec plusieurs options devant vous." << endl;
    cout << "Que choisissez-vous de faire ?" << endl;
    cout << "1. Explorer la vieille église abandonnée à la recherche d'objets bénis." << endl;
    cout << "2. Entrer dans la grotte dissimulée dans les collines." << endl;
    cout << "3. Demander aux villageois s'ils ont des informations supplémentaires." << endl;

    cin >> choix;
    switch (choix) {
    case 1:
        cout << "Vous décidez d'explorer la vieille église abandonnée à la recherche d'objets bénis." << endl;
        cout << "À l'intérieur de l'église, vous trouvez une vieille croix bénie qui pourrait être utile dans votre combat contre le monstre." << endl;
        break;
    case 2:
        cout << "Vous entrez dans la grotte dissimulée dans les collines." << endl;
        cout << "Vous avancez avec prudence, en suivant les traces que vous avez découvertes." << endl;
        cout << "Au fond de la grotte, vous trouvez une grande salle sombre où la créature vous attend." << endl;
        break;
    case 3:
        cout << "Vous décidez de demander aux villageois s'ils ont des informations supplémentaires." << endl;
        cout << "Ils vous parlent d'un chasseur local qui a vu la créature rôder près du lac au clair de lune." << endl;
        cout << "Vous décidez de vous rendre au lac pour enquêter." << endl;
        break;
    }

    cout << "Vous avez maintenant plusieurs options pour affronter la créature." << endl;
    cout << "Que choisissez-vous de faire ?" << endl;
    cout << "1. Utiliser la croix bénie pour repousser la créature." << endl;
    cout << "2. Entrer dans la grotte et affronter directement la créature." << endl;
    cout << "3. Vous rendre au lac pour enquêter sur les observations du chasseur local." << endl;

    cin >> choix;
    switch (choix) {
    case 1:
        cout << "Vous utilisez la croix bénie pour repousser la créature." << endl;
        cout << "La créature recule devant l'objet sacré, vous donnant l'occasion de la combattre plus facilement." << endl;
        break;
    case 2:
        cout << "Vous entrez dans la grotte et affrontez directement la créature." << endl;
        cout << "La créature se jette sur vous avec fureur, mais vous êtes prêt à lui faire face." << endl;
        break;
    case 3:
        cout << "Vous vous rendez au lac pour enquêter sur les observations du chasseur local." << endl;
        cout << "Vous trouvez des traces fraîches près du rivage, confirmant la présence de la créature." << endl;
        cout << "Vous suivez les traces qui vous mènent à un affrontement imminent avec la créature." << endl;
        break;
    }

    cout << "Le moment du combat final est arrivé." << endl;
    cout << "Que choisissez-vous de faire ?" << endl;
    cout << "1. Utiliser toutes vos compétences pour vaincre la créature." << endl;
    cout << "2. Tenter de négocier avec la créature pour qu'elle quitte les lieux pacifiquement." << endl;
    cout << "3. Utiliser un piège élaboré pour capturer la créature sans lui faire de mal." << endl;

    cin >> choix;
    switch (choix) {
    case 1:
        cout << "Vous utilisez toutes vos compétences pour vaincre la créature." << endl;
        while (joueur->isAlive() && monstre->isAlive()) {
            joueur->attaquer(monstre);
            if (monstre->isAlive()) {
                monstre->attaquer(joueur);
            }
        }
        if (!joueur->isAlive()) {
            cout << "Vous avez été vaincu par la créature. Votre quête prend fin ici." << endl;
        }
        break;
    case 2:
        cout << "Vous tentez de négocier avec la créature pour qu'elle quitte les lieux pacifiquement." << endl;
        cout << "La créature accepte votre offre et s'éloigne paisiblement, laissant le village en paix." << endl;
        cout << "Votre capacité à résoudre le conflit sans violence renforce votre réputation de sorceleur." << endl;
    case 3:
        cout << "Vous utilisez un piège élaboré pour capturer la créature sans lui faire de mal." << endl;
        cout << "La créature est prise au piège, vous permettant de la capturer et de la relâcher loin du village." << endl;
        cout << "Les villageois sont reconnaissants de votre compassion envers la créature et vous remercient chaleureusement." << endl;
    }

    cout << "Finalement, la menace du monstre est éliminée, et vous pouvez quitter le village en sachant que vous avez accompli votre devoir de sorceleur." << endl;
}
void contratVampireNovigrad(shared_ptr<Personnage> joueur) {
    cout << "Vous êtes "<<joueur->name<<", un sorceleur réputé, bien connu pour votre expertise dans la traque de créatures surnaturelles." << endl;
    cout << "Un jour, alors que vous vous trouvez à Novigrad, vous entendez parler d'une série de meurtres mystérieux." << endl;
    cout << "Les habitants parlent d'un vampire qui hante les rues sombres de la ville, se nourrissant du sang des innocents." << endl;
    cout << "Vous décidez d'enquêter sur cette affaire et de mettre fin aux agissements du vampire." << endl;
    
    auto vampire = make_shared<Monstre>("Vampire", make_shared<Arme>("Croc acéré", 70), make_shared<Armure>("Peau résistante", 40), 140);

    cout << "Vous vous rendez dans les quartiers les plus sombres de Novigrad, là où la présence du vampire est la plus forte." << endl;
    cout << "Vous pouvez sentir son aura maléfique dans l'air, mais vous savez que vous êtes prêt à affronter ce danger." << endl;
    cout << "Que choisissez-vous de faire ?" << endl;
    cout << "1. Patrouiller les rues pour traquer le vampire." << endl;
    cout << "2. Interroger les habitants pour obtenir des informations sur le vampire." << endl;

    int choix;
    cin >> choix;

    switch (choix) {
    case 1:
        cout << "Vous décidez de patrouiller les rues sombres de Novigrad, espérant rencontrer le vampire." << endl;
        cout << "Alors que vous explorez les ruelles étroites, vous entendez des bruits de pas furtifs derrière vous." << endl;
        cout << "Le vampire émerge des ténèbres pour vous attaquer." << endl;
        break;
    case 2:
        cout << "Vous choisissez d'interroger les habitants pour obtenir des informations sur le vampire." << endl;
        cout << "Certains vous regardent avec méfiance, mais d'autres partagent des récits terrifiants de rencontres avec le vampire." << endl;
        cout << "Vous décidez de poursuivre vos investigations parmi les habitants." << endl;
        cout << "Peut-être trouverez-vous des indices sur son emplacement ou ses habitudes." << endl;
        // Le vampire se dissimule parmi les habitants
        cout << "Vous commencez à interroger les habitants, cherchant des indices sur le vampire." << endl;
        if (rand() % 2 == 0) {
            cout << "Soudain, vous remarquez un individu étrange qui semble vous observer de loin." << endl;
            cout << "Son comportement est suspect et vous soupçonnez qu'il puisse être le vampire déguisé." << endl;
            cout << "Que choisissez-vous de faire ?" << endl;
            cout << "1. Vous approchez discrètement pour enquêter davantage." << endl;
            cout << "2. Vous gardez vos distances et continuez à observer." << endl;
            cin >> choix;
            if (choix == 1) {
                cout << "Vous vous approchez discrètement de l'individu suspect, prêt à agir si nécessaire." << endl;
                cout << "Vous l'abordez et engagez la conversation." << endl;
                cout << "L'individu se montre évasif mais vous parvient à glaner quelques informations utiles." << endl;
                cout << "Cependant, vous n'êtes pas sûr s'il s'agit vraiment du vampire." << endl;
            } else {
                cout << "Vous gardez vos distances, préférant ne pas risquer une confrontation prématurée." << endl;
                cout << "L'individu disparaît dans la foule avant que vous puissiez en apprendre davantage." << endl;
                cout << "Vous continuez à observer les alentours, cherchant d'autres indices." << endl;
            }
        }
        break;
    }

    cout << "Vous trouvez le vampire dans une vieille crypte abandonnée, prêt à vous attaquer." << endl;
    cout << "Préparez-vous au combat !" << endl;

    // Le vampire a une chance de se métamorphoser en chauve-souris avant le combat
    if (rand() % 2 == 0) {
        cout << "Avant que le combat ne commence, le vampire se métamorphose soudainement en une chauve-souris géante." << endl;
        cout << "Il vous attaque de manière inattendue dans sa forme animale." << endl;
        cout << "Que choisissez-vous de faire ?" << endl;
        cout << "1. Restez sur vos gardes et attaquez la chauve-souris." << endl;
        cout << "2. Cherchez un abri et attendez qu'il reprenne sa forme de vampire." << endl;

        cin >> choix;

        if (choix == 1) {
            cout << "Vous restez sur vos gardes et attaquez la chauve-souris avec votre épée." << endl;
        } else {
            cout << "Vous cherchez rapidement un abri pour vous protéger des attaques de la chauve-souris." << endl;
            cout << "Après quelques instants, le vampire reprend sa forme originale pour vous attaquer." << endl;
        }
    }

    while (joueur->isAlive() && vampire->isAlive()) {
        joueur->attaquer(vampire);
        if (vampire->isAlive()) {
            vampire->attaquer(joueur);
        }
    }

    if (!joueur->isAlive()) {
        cout << "Malheureusement, le vampire était trop fort pour vous. Vous devez battre en retraite." << endl;
        cout << "Votre quête continue une autre fois." << endl;
    }

    cout << "Après un combat acharné, vous parvenez à vaincre le vampire et à libérer Novigrad de son influence maléfique." << endl;
    cout << "Les habitants vous remercient pour votre bravoure et votre dévouement à protéger la ville." << endl;
    cout << "Votre réputation de sorceleur légendaire continue de croître." << endl;
}
void contratOpposantPolitiqueNovigrad(shared_ptr<Personnage> joueur) {
    cout << "Après avoir réussi à éliminer la menace du vampire et à restaurer la paix à Novigrad, vous êtes devenu une figure respectée dans la ville." << endl;
    cout << "Le roi de Novigrad est impressionné par votre gestion de la situation et souhaite de nouveau faire appel à vos services." << endl;
    cout << "Cette fois-ci, il vous engage pour une tâche délicate : éliminer un opposant politique qui menace la stabilité du royaume." << endl;
    
    auto opposantPolitique = make_shared<Personnage>("Opposant Politique", make_shared<Arme>("Poison Mortel", 80), make_shared<Armure>("Robe de Magistrat", 50), 170);

    cout << "Vous recevez des informations détaillées sur l'opposant politique, ses habitudes et son lieu de résidence." << endl;
    cout << "Votre mission est de l'approcher discrètement et de mettre fin à ses plans néfastes pour le royaume." << endl;
    cout << "Vous vous apprêtez à traquer votre cible." << endl;

    cout << "Vous trouvez l'opposant politique dans son manoir, bien protégé par ses gardes." << endl;
    cout << "Que choisissez-vous de faire ?" << endl;
    cout << "1. Tenter de vous infiltrer dans le manoir pour approcher votre cible discrètement." << endl;
    cout << "2. Engager directement les gardes et affronter l'opposant politique dans un combat ouvert." << endl;

    int choix;
    cin >> choix;

    switch (choix) {
    case 1:
        cout << "Vous décidez d'utiliser la discrétion pour approcher votre cible." << endl;
        cout << "Vous vous glissez habilement à travers les ombres, évitant les gardes et les pièges." << endl;
        cout << "Finalement, vous trouvez l'opposant politique dans son bureau, seul et sans méfiance." << endl;
        cout << "Que choisissez-vous de faire ?" << endl;
        cout << "1. Tenter de l'empoisonner discrètement." << endl;
        cout << "2. Lui parler et essayer de le convaincre de renoncer à ses plans." << endl;
        cout << "3. Trouver des preuves incriminantes pour le discréditer publiquement." << endl;
        cout << "4. L'attaquer directement." << endl;

        cin >> choix;

        switch (choix) {
        case 1:
            cout << "Vous décidez d'utiliser le poison pour éliminer votre cible discrètement." << endl;
            cout << "Vous mélangez habilement le poison dans son verre pendant qu'il est distrait." << endl;
            cout << "Il boit le contenu empoisonné et s'effondre silencieusement." << endl;
            break;
        case 2:
            cout << "Vous tentez de raisonner votre cible, lui expliquant les conséquences de ses actions pour le royaume." << endl;
            cout << "Malheureusement, il se montre inflexible et refuse de céder à vos arguments." << endl;
            cout << "Vous n'avez d'autre choix que de passer à l'action." << endl;
            break;
        case 3:
            cout << "Vous décidez de chercher des preuves incriminantes dans le bureau de votre cible." << endl;
            cout << "Après une recherche minutieuse, vous trouvez des documents compromettants." << endl;
            cout << "Vous envisagez de les utiliser pour discréditer votre cible publiquement." << endl;
            break;
        case 4:
            cout << "Vous décidez de passer à l'attaque directe, ne laissant aucune chance à votre cible de se défendre." << endl;
            cout << "Les gardes sont pris par surprise alors que vous vous précipitez sur l'opposant politique." << endl;
            cout << "Le combat est bref mais intense, et vous parvenez finalement à le neutraliser." << endl;
            break;
        }
        break;
    case 2:
        cout << "Vous optez pour une approche plus directe en engageant les gardes et en confrontant votre cible ouvertement." << endl;
        cout << "Les gardes vous encerclent rapidement, mais vous êtes prêt à les affronter." << endl;
        cout << "Votre cible émerge du manoir, prêt à vous faire face." << endl;
        cout << "Que choisissez-vous de faire ?" << endl;
        cout << "1. Tenter de le convaincre de se rendre pacifiquement." << endl;
        cout << "2. Engager le combat directement avec lui et ses gardes." << endl;

        cin >> choix;

        switch (choix) {
        case 1:
            cout << "Vous tentez de raisonner votre cible, lui expliquant les conséquences de ses actions pour le royaume." << endl;
            cout << "Après une brève discussion, il semble comprendre et accepte de se rendre pacifiquement." << endl;
            cout << "Vous l'escortez hors du manoir et le remettez aux autorités." << endl;
            break;
        case 2:
            cout << "Vous décidez de ne pas perdre de temps et de passer directement à l'action." << endl;
            cout << "Les gardes se jettent sur vous alors que vous affrontez votre cible dans un combat intense." << endl;
            cout << "Malgré la résistance acharnée de ses gardes, vous parvenez à vaincre votre cible." << endl;
            break;
        }
        break;
    }

    while (joueur->isAlive() && opposantPolitique->isAlive()) {
        joueur->attaquer(opposantPolitique);
        if (opposantPolitique->isAlive()) {
            opposantPolitique->attaquer(joueur);
        }
    }

    if (!joueur->isAlive()) {
        cout << "Malheureusement, l'opposant politique était mieux préparé que prévu. Vous devez battre en retraite." << endl;
        cout << "Votre réputation en tant que sorceleur en prend un coup, mais votre quête continue une autre fois." << endl;
    }

    cout << "Après un combat difficile, vous parvenez à éliminer l'opposant politique et à préserver la stabilité du royaume." << endl;
    cout << "Le roi de Novigrad vous remercie pour votre loyauté et votre dévouement envers la couronne." << endl;
    cout << "Votre réputation continue de croître, et de nouvelles opportunités d'aventure vous attendent." << endl;
}
// ...
// Fonction main 
// ...
int main() {
    string name, classe;
    cout <<"choisissez un nom de personnage : "<< endl;
    cin >> name;
    cout<< "choisissez une classe de personnage (Mage/Mercenaire/Chevalier/Archer): "<<endl;
    cin >> classe;

    // Création du personnage

    auto joueur = creer_personnage(name, classe);

    // équimement des monstres de farms

    int niveauJoueur = joueur->niveau;
    int bonusDegats = niveauJoueur * 5; 
    int bonusArmure = niveauJoueur * 2;
    int bonusVie = niveauJoueur * 2;
    vector<shared_ptr<Monstre>> monstres;

    // initialisation du pointeur pour l'exploration

    shared_ptr<Arme> exploration{nullptr};

    // construction des quêtes

    vector<Quete> quetes;
    quetes.push_back(Quete("Les villageois ont perdus de noubreux habitants dans leur Mines, ils vous ont engagé pour mener l'enquête",Monstre_de_la_mine,joueur));
    quetes.push_back(Quete("un monstre rode dans les marais et terrifie les habitants du coin, traquez et éliminez le monstre",le_monstre_des_marais,joueur));
    quetes.push_back(Quete("un monstre rode à Novigrad, le bruit court qu'un vampir assoifé décime les riverains, le roi vous a donc personellement engagé pour résoudre ce massacre",contratVampireNovigrad,joueur));

    // variable de sortie de jeu

    bool gameOver = false;

    // début du jeu
    while (joueur->isAlive() && !gameOver) {
        cout << "Que voulez-vous faire ?" << endl;
        cout << "0. Voir mes statistiques" << endl;
        //système de farm
        cout << "1. Explorer" << endl;
        cout << "2. Combattre des monstres" << endl;
        cout << "3. Terminer des quêtes" << endl;
        cout << "4. Quitter le jeu" << endl;
        int choix;
        int changerarme;
        cin >> choix;

        switch (choix) {
            case 0:
                joueur->afficherInfos();
                break;
            case 1:
                cout << "Vous explorez les environs." << endl;
                cout << "vous venez de trouver une arme" << endl;
                exploration = obtenirArmeAleatoire();
                exploration->afficherInfos();
                cout << "votre arme actuelle est : " << endl;
                joueur->arme_->afficherInfos();
                cout << "voulez vous changer d'arme ? (1. Oui / 2. Non)" << endl;
                cin >> changerarme;
                if (changerarme == 1) {
                    joueur->setArme(exploration);
                    cout << "vous avez équipé votre nouvelle arme" << endl;
                }
                break;
            case 2:
                niveauJoueur = joueur->niveau;
                bonusDegats = niveauJoueur * 5; 
                bonusArmure = niveauJoueur * 2;
                bonusVie = niveauJoueur * 2;

                monstres.clear();
                // il faudrait mettre en place un système de loot
                monstres.push_back(make_shared<Monstre>("Goule", make_shared<Arme>("Arme de Monstre",20+bonusDegats), make_shared<Armure>("Armure monstre", 10 + bonusArmure), 50 + bonusVie));
                monstres.push_back(make_shared<Monstre>("Spectre", make_shared<Arme>("Arme de Monstre",20+bonusDegats), make_shared<Armure>("Armure monstre", 5 + bonusArmure), 30 + bonusVie));
                monstres.push_back(make_shared<Monstre>("Noyeur", make_shared<Arme>("Arme de Monstre",20+bonusDegats), make_shared<Armure>("Armure monstre", 8 + bonusArmure), 20 + bonusVie));
                monstres.push_back(make_shared<Monstre>("Wivern", make_shared<Arme>("Arme de Monstre",30+bonusDegats), make_shared<Armure>("Armure monstre", 20 + bonusArmure), 70 + bonusVie));
                cout << "Vous entrez en combat !" << endl;
                for (auto& monstre : monstres) {
                    while (joueur->isAlive() && monstre->isAlive()) {
                        joueur->attaquer(monstre);
                        if (monstre->isAlive()) {
                            monstre->attaquer(joueur);
                        }
                int xpGagne = 100 + (niveauJoueur * 10); 
                joueur->getXP(xpGagne);
                joueur->heal(joueur->max_hp);
                    }
                    if (!joueur->isAlive()) {
                        cout << "Vous avez été vaincu par " << monstre->name << ". Game Over !" << endl;
                        gameOver = true;
                        break;
                    }
                joueur->afficherInfos();
                }
                break;
            case 3:
                cout << "Vous consultez vos quêtes en cours :" << endl;
                for (auto& quete : quetes) {
                    if (!quete.estTerminee) {
                        cout << "- " << quete.description << endl;
                    }
                }
                cout << "Quelle quête voulez-vous terminer ?" << endl;
                for (int i = 0; i < quetes.size(); ++i) {
                    if (!quetes[i].estTerminee) {
                        cout << i + 1 << ". " << quetes[i].description << endl;
                    }
                }
                int choixQuete;
                cin >> choixQuete;
                if (choixQuete >= 1 && choixQuete <= quetes.size()) {
                    quetes[choixQuete - 1].executer();
                    if (choixQuete==3){
                        quetes.push_back(Quete("Après avoir réussi à éliminer la menace du vampire et à restaurer la paix à Novigrad, vous êtes devenu une figure respectée dans la ville. Le roi de Novigrad est impressionné par votre gestion de la situation et souhaite de nouveau faire appel à vos services.",contratOpposantPolitiqueNovigrad,joueur));
                    }
                    quetes[choixQuete - 1].terminer();
                    cout << "Quête terminée : " << quetes[choixQuete - 1].description << endl;
                } else {
                    cout << "Choix invalide." << endl;
                }
                break;
            case 4:
                cout << "Vous quittez le jeu." << endl;
                gameOver = true;
                break;
            default:
                cout << "Choix invalide." << endl;
                break;
        }
    }

    return 0;
}

    