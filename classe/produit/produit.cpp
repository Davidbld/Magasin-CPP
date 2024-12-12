/*
Les produits sont divisés en plusieurs catégorie :
- Alcool soumis à une limite d'âge (18 ans)
- Alimentaire : Produits avec une TVA réduite de 5.5%
- Non Alimentaire : Produit avec une TVA de 20%
*/

#include "produit.hpp"
#include <cassert>

// Constructeur
Produit::Produit()
    :m_prixHT(0), m_typeCategorie(Produit::m_categorie::nonAlimentaire), m_nomProduit(""), m_stock(0){}

Produit::Produit(double prixHT, m_categorie categorie, long int codeProduit, std::string nomProduit, int stock)
    : m_prixHT(prixHT), m_typeCategorie(categorie),m_nomProduit(nomProduit), m_stock(stock) {
    // Vérification des assertions pour valider les entrées
    assert(prixHT >= 0 && "Le prix HT ne peut pas être négatif.");
    assert(
        categorie == m_categorie::Alcool || 
        categorie == m_categorie::Alimentaire || 
        categorie == m_categorie::nonAlimentaire &&
        "La catégorie doit être 'Alcool', 'Alimentaire' ou 'Non Alimentaire'."
    );
    assert(codeProduit > 0 && "Le code produit doit être un entier positif.");
    assert(!nomProduit.empty() && "Le nom du produit ne peut pas être vide.");
    assert(stock>=0 && "Le stock du produit ne peut pas être négatif");
}


// Setters
void Produit::setPrixHT(double prixHT) {
    m_prixHT = prixHT;
}

void Produit::setNomProduit(std::string nomProduit){
    m_nomProduit = nomProduit;
}

void Produit::setCategorie(m_categorie categorie) {
    m_typeCategorie = categorie;
}

void Produit::setCodeProduit(long int codeProduit) {
    m_codeProduit = codeProduit;
}

void Produit::setStock(int stock) {
    m_stock = stock;
}

// Getters
double Produit::getPrixHT() const {
    return m_prixHT;
}

std::string Produit::getNomProduit() const{
    return m_nomProduit;
}

Produit::m_categorie Produit::getCategorie() const {
    return m_typeCategorie;
}

long int Produit::getCodeProduit() const {
    return m_codeProduit;
}

long int Produit::getStock() const {
    return m_stock;
}

//Méthodes

std::string Produit::getCategorieAsString() const {
    if (m_typeCategorie == m_categorie::Alcool) {
        return "Alcool";
    } else if (m_typeCategorie == m_categorie::Alimentaire) {
        return "Alimentaire";
    } else if (m_typeCategorie == m_categorie::nonAlimentaire) {
        return "Non Alimentaire";
    } else {
        return "Inconnu";
    }
}