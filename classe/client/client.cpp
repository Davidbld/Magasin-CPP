/*
Définie le type de client :
- Fidèle (carte de fidélité) ou non.
- Nom

Pour un client fidèlé :
- Son adresse
- Son numéro de téléphone
- Son adresse Mail
- Sa liste d'achat
- Son nombre de point de fidélité
*/

#include "client.hpp"
#include <iostream>
#include <cmath>
#include <cassert>
#include <cctype>
#include <vector>
#include <string>
#include "../vente/vente.hpp"

// Définitions des classes Client et ClientFidele

Client::Client(int id, int age) : m_id(id), m_age(age)
{
    assert(id >= 0 && age >= 0 && "ID et âge doivent être des entiers positifs.");
}

ClientFidele::ClientFidele()
    : Client(0,0), // Appelle le constructeur par défaut de la classe parent
      m_fidelite(false), m_nom(""),
      m_adresse(""), m_adresseMail(""), m_listeAchats(), m_pointsFidelite(0), m_sexe(TypeSexe::NonSpecifie) {}

ClientFidele::ClientFidele(int id, int age, bool fidelite, const std::string &nom,
                           const std::string &adresse, const std::string &numTelephone,
                           const std::string &adresseMail, const std::vector<std::string> &listeAchats,
                           int pointsFidelite, TypeSexe sexe)
    : Client(id, age),
      m_fidelite(fidelite),
      m_nom(nom),
      m_adresse(adresse),
      m_numTelephone(numTelephone),
      m_adresseMail(adresseMail),
      m_listeAchats(listeAchats),
      m_pointsFidelite(pointsFidelite),
      m_sexe(sexe)
{
    // Vérifications
    assert(!nom.empty() && "Le nom ne peut pas être vide.");
    assert(!adresse.empty() && "L'adresse ne peut pas être vide.");
    assert(!numTelephone.empty() && "Le numéro de téléphone ne peut pas être vide.");
    assert(!adresseMail.empty() && adresseMail.find('@') != std::string::npos &&
           "L'adresse mail doit contenir '@' pour être valide.");
    assert(pointsFidelite >= 0 && "Les points de fidélité ne peuvent pas être négatifs.");
    assert(sexe == TypeSexe::Homme || sexe == TypeSexe::Femme || sexe == TypeSexe::NonSpecifie && "Sexe invalide : doit être Homme, Femme ou Non spécifié.");
}

// Méthodes

std::string ClientFidele::getSexeAsString() const {
    if (m_sexe == TypeSexe::Homme) {
        return "Homme";
    } else if (m_sexe == TypeSexe::Femme) {
        return "Femme";
    } else if (m_sexe == TypeSexe::NonSpecifie) {
        return "Non Specifie";
    } else {
        return "Inconnu";
    }
}

bool Client::operator<(int ageLimite)const{
    return m_age<ageLimite;
}

void Client::acheter(int tempId, Produit& produit, std::ostream& fichierVentes, int quantiteAchetee, std::map<int, ClientFidele>& listeClientsFideles, int idClientFidele)
{
    // Vérification du stock disponible
    if (quantiteAchetee > produit.getStock()) {
        std::cout << "Stock insuffisant pour le produit : " << produit.getNomProduit() << std::endl;
        return; // Achat annulé
    }

    int age;
    std::cout << "Entrez âge : \n";
    std::cin >> age;

    Client tempClient(tempId+1, age);
    tempId+=1;

    std::string categorie = produit.getCategorieAsString();

    //Vérification de l'âge du client
    if (categorie == "Alcool" && tempClient < 18){ //surcharge d'opérateur
        std::cout << "Vous devez avoir 18 ans pour acheter de l'alcool." << std::endl;
        return; 
    }

    std::string date;
    std::cout << "Entre la date. (dd/mm/aaaa) :\n";
    std::cin >> date;

    double TVA  = 0;

    if (categorie == "Alimentaire"){
        TVA=5.5;
    }

    else{
        TVA = 20;
    }

    //Calcul du prix de vente
    double prixTTC = produit.getPrixHT()*(1+TVA/100);
    prixTTC = std::round(prixTTC * 100)/100; //Arrondi au centimes près

    //Renseignement de la vente dans le fichier
    Vente tempVente(produit, prixTTC, quantiteAchetee, date);
    tempVente.ecrireDansFichier(fichierVentes, produit);

    //Mise à jour du stock correspondant au produit vendu
    produit.setStock(produit.getStock()-quantiteAchetee);

    std::string souscription = "";
    std::cout << "Le client veut-il souscire au programme fidélité ? (Oui/Non)" <<std::endl;
    std::cin >> souscription;

    if(souscription == "Oui"){
        Client::souscrireFidelite(tempId, listeClientsFideles, &tempClient);
        ClientFidele& newClient = listeClientsFideles[tempId+1];
        std::vector<std::string>& listeAchats = newClient.getListeAchats();
        listeAchats.push_back(std::to_string(quantiteAchetee)+","+produit.getNomProduit()+","+date);    //Ajouter l'achat à la liste d'achat du nouveau client fidèle créé
        newClient.setPointsFidelite(static_cast<int>(std::floor(prixTTC)));                              //ajouter les points de fidelité correspondant à l'achat
    }

}

void ClientFidele::acheter(int tempId, Produit& produit, std::ostream& fichierVentes, int quantiteAchetee, std::map<int, ClientFidele>& listeClientsFideles, int idClientFidele)
{
    ClientFidele& client = listeClientsFideles[idClientFidele]; //Passage par référence pour pouvoir directement modifier dans la liste

    // Vérification du stock disponible
    if (quantiteAchetee > produit.getStock()) {
        std::cout << "Stock insuffisant pour le produit : " << produit.getNomProduit() << std::endl;
        return; // Achat annulé
    }

    int age = client.getAge();

    std::string date;
    std::cout << "Entre la date. (dd/mm/aaaa)";
    std::cin >> date;

    std::string categorie = produit.getCategorieAsString();

    //Vérification de l'âge du client
    if (categorie == "Alcool" && age < 18){
        std::cout << "Vous devez avoir 18 ans pour acheter de l'alcool." << std::endl;
        return; 
    }

    //Calcul du prix de vente
    double TVA  = 0;

    if (categorie == "Alimentaire"){
        TVA=5.5;
    }

    else{
        TVA = 20;
    }

    double prixTTC = produit.getPrixHT()*(1+TVA/100);
    prixTTC = std::round(prixTTC * 100)/100; //Arrondi au centimes près

    //Application des points fidélité
    std::string usePtFidelite = "";
    std::cout << "Le client veut-il utiliser ses points de fidelite ? (Oui/Non)" <<std::endl;
    std::cin >> usePtFidelite;

    if(usePtFidelite == "Oui"){
        int ptFidelite = client.getPointsFidelite();
        prixTTC = prixTTC - 0.02*ptFidelite;
        client.setPointsFidelite(0);
    }
    
    //Gain des points de fidelité
    client.setPointsFidelite(static_cast<int>(std::floor(prixTTC)));

    //Renseignement de la vente dans le fichier
    Vente tempVente(produit, prixTTC, quantiteAchetee, date);
    tempVente.ecrireDansFichier(fichierVentes, produit);

    //Mise à jour du stock correspondant au produit vendu
    produit.setStock(produit.getStock()-quantiteAchetee);

}

void Client::souscrireFidelite(int &tempIdClient, std::map<int, ClientFidele>& listeClientsFideles, Client *oldClient)
{
    int id = ++tempIdClient;

    // Saisie des informations du client
    std::string nom;
    std::cin.ignore();
    std::cout << "Entrez Nom Prénom : ";
    std::getline(std::cin, nom);

    int age;
    std::cout << "Entrez âge : ";
    std::cin >> age;

    std::string adresse;
    std::cout << "Entrez adresse : ";
    std::cin.ignore();
    std::getline(std::cin, adresse);

    std::string numTelephone;
    std::cout << "Entrez numéro de téléphone : ";
    std::cin >> numTelephone;

    std::string adresseMail;
    std::cout << "Entrez adresse mail : ";
    std::cin >> adresseMail;

    int sexeInput;
    ClientFidele::TypeSexe sexe;
    std::cout << "Veuillez entrer le sexe du client (0 = Homme, 1 = Femme, 2 = Non spécifié) : ";
    std::cin >> sexeInput;

    if (sexeInput == 0)
    {
        sexe = ClientFidele::TypeSexe::Homme;
    }
    else if (sexeInput == 1)
    {
        sexe = ClientFidele::TypeSexe::Femme;
    }
    else
    {
        sexe = ClientFidele::TypeSexe::NonSpecifie;
    }

    std::vector<std::string> liste; // Liste vide pour ajouter les achats ultérieurement

    // Création du client fidèle
    ClientFidele newClientFidele(id, age, true, nom, adresse, numTelephone, adresseMail, liste, 0, sexe);
    listeClientsFideles[newClientFidele.getId()] = newClientFidele; //Ajoute du client dans le dictionnaire clientFideles

    std::cout << "Client souscrit au programme fidélité !" << std::endl;
}

// Getters et setters

void Client::setAge(int age)
{
    assert(age >= 0 && "L'âge doit être positif.");
    m_age = age;
}

int Client::getAge() const
{
    return m_age;
}

void Client::setId(int id)
{
    assert(id >= 0 && "L'ID doit être positif.");
    m_id = id;
}

int Client::getId() const
{
    return m_id;
}

const std::string &ClientFidele::getNom() const
{
    return m_nom;
}

void ClientFidele::setFidelite(bool fidelite)
{
    m_fidelite = fidelite;
}

bool ClientFidele::getFidelite() const
{
    return m_fidelite;
}

void ClientFidele::setAdresse(const std::string &adresse)
{
    assert(!adresse.empty() && "L'adresse ne peut pas être vide.");
    m_adresse = adresse;
}

const std::string &ClientFidele::getAdresse() const
{
    return m_adresse;
}

void ClientFidele::setNumTelephone(const std::string &numTelephone)
{
    assert(!numTelephone.empty() && "Le numéro de téléphone ne peut pas être vide.");
    m_numTelephone = numTelephone;
}

const std::string &ClientFidele::getNumTelephone() const
{
    return m_numTelephone;
}

void ClientFidele::setAdresseMail(const std::string &adresseMail)
{
    assert(!adresseMail.empty() && adresseMail.find('@') != std::string::npos &&
           "L'adresse mail doit contenir '@' pour être valide.");
    m_adresseMail = adresseMail;
}

const std::string &ClientFidele::getAdresseMail() const
{
    return m_adresseMail;
}

// Liste des produits achetés par un client et qui lui sont affectés
void ClientFidele::setListeAchats(const std::vector<std::string> &listeAchats)
{
    m_listeAchats = listeAchats;
}

std::vector<std::string> &ClientFidele::getListeAchats()
{
    return m_listeAchats;
}

// Points de fidélités
void ClientFidele::setPointsFidelite(int points)
{
    assert(points >= 0 && "Les points de fidélité ne peuvent pas être négatifs.");
    m_pointsFidelite = points;
}

int ClientFidele::getPointsFidelite() const
{
    return m_pointsFidelite;
}

// Utilisation d'un enum pour forcer à choisir entre les différentes valeurs possibles et uniquement les valeurs possibles
void ClientFidele::setSexe(TypeSexe sexe)
{
    assert(sexe == TypeSexe::Homme || sexe == TypeSexe::Femme || sexe == TypeSexe::NonSpecifie && "Sexe invalide.");
    m_sexe = sexe;
}

ClientFidele::TypeSexe ClientFidele::getSexe() const
{
    return m_sexe;
}
