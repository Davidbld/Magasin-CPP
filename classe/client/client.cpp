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

// Définitions des constructeurs

Client::Client(int id, int age) : 
    m_id(id),
    m_age(age) {
        if (id<0||age<0)
        {
            std::cout<<"Erreur d'initialisation : L'âge ne peut pas être inférieur à 0. De même pour l'id."<<std::endl;
        }
        
    }
    
ClientFidele::ClientFidele(int id, int age, bool fidelite, std::string *nom, std::string adresse, 
                           int numTelephone, std::string adresseMail, std::vector<std::string> listeAchats, 
                           int pointsFidelite, std::string sexe) :
    Client(id, age), // Appel du constructeur parent
    m_fidelite(fidelite),
    m_nom(nom),
    m_adresse(adresse),
    m_numTelephone(numTelephone),
    m_adresseMail(adresseMail),
    m_listeAchats(listeAchats),
    m_pointsFidelite(pointsFidelite),
    m_sexe(sexe){
    if (nom == nullptr || nom->empty())
    {
        throw std::invalid_argument("Le nom ne peut pas être nul ou vide.");
    }
    if (adresse.empty())
    {
        throw std::invalid_argument("L'adresse ne peut pas être vide.");
    }
    if (numTelephone <= 0)
    {
        throw std::invalid_argument("Le numéro de téléphone doit être un entier positif.");
    }
    if (adresseMail.empty() || adresseMail.find('@') == std::string::npos)
    {
        throw std::invalid_argument("L'adresse mail doit être valide et contenir un '@'.");
    }
    if (listeAchats.empty())
    {
        std::cerr << "Avertissement : La liste des achats est vide." << std::endl;
    }
    if (pointsFidelite < 0)
    {
        throw std::invalid_argument("Les points de fidélité ne peuvent pas être négatifs.");
    }
    if (sexe != "Homme" && sexe != "Femme" && sexe != "Non spécifié")
    {
        throw std::invalid_argument("Le sexe doit être 'Homme', 'Femme' ou 'Non spécifié'.");
    }
}

