/*
Les produits sont divisés en plusieurs catégorie :
- Alcool soumis à une limite d'âge (18 ans)
- Alimentaire : Produits avec une TVA réduite de 5.5%
- Non Alimentaire : Produit avec une TVA de 20%
*/

#ifndef PRODUIT_HPP
#define PRODUIT_HPP

#include <string>
#include <iostream>

class Produit{
private :
    
    // Initialisation des variables privates pour le prix Hors Taxe et le prix Toutes Taxes Comprises. Le prix TTC est calculé via le prix HT
    double m_prixHT=0;
    std::string m_nomProduit = "";
    long int m_codeProduit=0;
    int m_stock=0;

public : 

    //atribut enum
    enum m_categorie{
        Alcool,
        Alimentaire,
        nonAlimentaire,
    };
    m_categorie m_typeCategorie = m_categorie::nonAlimentaire; // Catégorie par défaut

    //Constructeur
    Produit() = default; // Ajout d'un constructeur par défaut
    Produit(double prixHT, m_categorie categorie, long int codeProduit, std::string nomProduit, int stock);

    // Getters et Setters

    void setNomProduit(std::string nomProduit);
    std::string getNomProduit () const;

    void setPrixHT(double prixHT);
    double getPrixHT() const;

    void setCategorie(m_categorie categorie);
    m_categorie getCategorie() const;

    void setCodeProduit(long int codeProduit);
    long int getCodeProduit() const;

    void setStock(int stock);
    long int getStock() const;

    // Méthode
    std::string getCategorieAsString() const;
};
#endif