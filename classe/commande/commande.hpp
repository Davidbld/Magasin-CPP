#ifndef COMMANDE_HPP
#define COMMANDE_HPP

#include <string>
#include <iostream>

class Commande{
//Attribus
private :
    int m_delaiLivraison=0;
    std::string m_nomProduit="";
    int m_codeProduit=0;
    int m_quantiteProduit=0;

public : 
//Constructeur
    Commande(int delaiLivraison, std::string nomProduit, int codeProduit, int quantiteProduit);
//Getters and Setters
    void setDelaiLivraison(int delaiLivraison);
    int getDelaiLivraison() const;

    void setNomProduit(const std::string& nomProduit);
    const std::string& getNomProduit() const;

    void setCodeProduit(int codeProduit);
    int getCodeProduit() const;

    void setQuantiteProduit(int quantiteProduit);
    int getQuantiteProduit() const;
//Methodes
    void creerCommande();
    void validerCommande();
    void annulerCommande();
};

#endif