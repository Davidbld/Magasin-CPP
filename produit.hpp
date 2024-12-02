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
    //Attributs
    int m_prix=0;
    enum m_categorie{
        Alcool,
        Alimentaire,
        nonAlimentaire,
    };
    m_categorie m_typeCategorie = m_categorie::nonAlimentaire; // Catégorie par défaut
    std::string m_codeProduit=0;
    int m_stock=0;

public : 
    //Constructeur
    Produit(int prix, m_categorie categorie, long int codeProduit);

    // Getters et Setters
    void setPrix(int prix);
    int getPrix() const;

    void setCategorie(m_categorie categorie);
    m_categorie getCategorie() const;

    void setCodeProduit(std::string codeProduit);
    std::string getCodeProduit() const;

    void setStock(int stock);
    long int getStock() const;

    // Méthode
    std::string getCategorieAsString() const;
};
#endif