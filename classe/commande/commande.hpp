#ifndef COMMANDE_HPP
#define COMMANDE_HPP

#include <string>
#include <iostream>
#include "../produit/produit.cpp"

class Commande{
//Attribus
private :
    int m_idCommande=0;
    Produit m_produit;           // Produit associé à la commande
    int m_delaiLivraison=0;
    int m_quantiteProduit=0;

public : 

//attribut enum
enum m_statutCommande{
        EnCours,
        Validee,
        Annulee,
    };
    m_statutCommande m_statut = m_statutCommande::EnCours; // Catégorie par défaut
    std::string m_date;

//Constructeur
    Commande(int idCommande, int delaiLivraison, Produit& produit, int quantiteProduit, m_statutCommande statut, std::string date);

//Getters and Setters
    void setProduit(Produit produit);
    Produit getProduit() const;

    void setDelaiLivraison(int delaiLivraison);
    int getDelaiLivraison() const;

    void setQuantiteProduit(int quantiteProduit);
    int getQuantiteProduit() const;

    void setIdCommande(int idCommande);
    int getIdCommande() const;

    void setStatutCommande(m_statutCommande statut);
    m_statutCommande getStatut() const;

    void setDateCommande(const std::string& date);
    const std::string& getDateCommande() const;

//Methodes

    std::string getStatutAsString() const;
    void afficherCommande() const;
    void creerCommande(std::map<int, Commande>& listeCommandes, std::map<int, Produit>& listeProduits, int& tempId);
    void validerCommande(std::map<int, Commande>& listeCommandes);
    void annulerCommande(std::map<int, Commande>& listeCommandes);
};

#endif