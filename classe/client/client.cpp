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

// Définitions des constructeurs

Client::Client(int id, int age) : m_id(id),
                                  m_age(age)
{
    assert(id >= 0 && age >= 0);
    std::cout << "Erreur d'initialisation : L'âge ne peut pas être inférieur à 0. De même pour l'id." << std::endl;
}

ClientFidele::ClientFidele(int id, int age, bool fidelite, std::string *nom, std::string adresse,
                           std::string numTelephone, std::string adresseMail, std::vector<std::string> listeAchats,
                           int pointsFidelite, TypeSexe sexe) : Client(id, age), // Appel du constructeur parent
                                                                m_fidelite(fidelite),
                                                                m_nom(nom),
                                                                m_adresse(adresse),
                                                                m_numTelephone(numTelephone),
                                                                m_adresseMail(adresseMail),
                                                                m_listeAchats(listeAchats),
                                                                m_pointsFidelite(pointsFidelite),
                                                                m_sexe(sexe)
{
    assert(nom == nullptr || nom->empty());
    std::cout << "Le nom ne peut pas être nul ou vide." << std::endl;

    assert(adresse.empty());
    std::cout<<"L'adresse ne peut pas être vide." << std::endl;

    assert(numTelephone.empty());
    std::cout << "Le numéro de téléphone doit être un entier positif."  << std::endl;

    assert(adresseMail.empty());
    std::cout<< "L'adresse mail doit être valide et contenir un '@'."  << std::endl;

    assert(pointsFidelite < 0);
    std::cout<<"Les points de fidélité ne peuvent pas être négatifs."<< std::endl;

    assert(sexe != TypeSexe::Homme && sexe != TypeSexe::Femme && sexe != TypeSexe::NonSpecifie);
    std::cout<<"Le sexe doit être 'Homme', 'Femme' ou 'Aucun'.";
}

//Définition des méthodes
void Client::souscrireFidelite(int& tempId){
    setFidelite(true);
    int id=tempId+1;
    tempId+=1;
    std::string nom;
    std::cout<<"Entrez Nom Prénom";
    std::cin>>nom;
    int age;
    std::cout<<"Entrez âge";
    std::cin>>age;
    std::string adresse;
    std::cout<<"Entrez adresse";
    std::cin>>adresse;
    std::string numTelephone;
    std::cout<<"Entrez numéro de téléphone";
    std::cin>>numTelephone;
    std::string adresseMail;
    std::cout<<"Entrez adresse mail";
    std::cin>>adresseMail;
    int pointFidelite=0;
}
}