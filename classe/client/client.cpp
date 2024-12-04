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
#include <cassert>
#include <vector>
#include <string>

// Définitions des classes Client et ClientFidele

Client::Client(int id, int age) : m_id(id), m_age(age)
{
    assert(id >= 0 && age >= 0 && "ID et âge doivent être des entiers positifs.");
}

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

void Client::acheter()
{
    // Logique d'achat (nécessite les classes Produit et Vente)
}

void Client::souscrireFidelite(int &tempIdClient, ClientFidele &newClientFidele, Client *oldClient)
{
    int id = ++tempIdClient;

    // Saisie des informations du client
    std::string nom;
    std::cout << "Entrez Nom Prénom : ";
    std::cin >> nom;

    int age;
    std::cout << "Entrez âge : ";
    std::cin >> age;

    std::string adresse;
    std::cout << "Entrez adresse : ";
    std::cin >> adresse;

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
    newClientFidele = ClientFidele(id, age, true, nom, adresse, numTelephone, adresseMail, liste, 0, sexe);
    std::cout << "Client souscrit au programme fidélité !" << std::endl;

    // Suppression de l'ancien client si nécessaire
    if (oldClient != nullptr)
    {
        delete oldClient;
    }
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

const std::vector<std::string> &ClientFidele::getListeAchats() const
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
