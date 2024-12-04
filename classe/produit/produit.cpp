/*
Les produits sont divisés en plusieurs catégorie :
- Alcool soumis à une limite d'âge (18 ans)
- Alimentaire : Produits avec une TVA réduite de 5.5%
- Non Alimentaire : Produit avec une TVA de 20%
*/

#include "produit.hpp"
#include <cassert>

// Constructeur
Produit::Produit(int prixHT, int prixTTC, m_categorie categorie, long int codeProduit)
    : m_prixHT(prixHT), m_prixTTC(prixTTC), m_typeCategorie(categorie), m_stock(0) {
    // Vérification des assertions pour valider les entrées

    assert(prixHT >= 0);
        std::cout << "Le prix HT ne peut pas être négatif." << std::endl;

    assert(prixTTC >= 0);
        std::cout << "Le prix TTC ne peut pas être inférieur au prix HT." << std::endl;

    assert(categorie == m_categorie::Alcool || categorie == m_categorie::Alimentaire || categorie == m_categorie::nonAlimentaire);
        std::cout << "La catégorie doit être 'Alcool', 'Alimentaire' ou 'Non Alimentaire'." << std::endl;

    assert(codeProduit > 0);
        std::cout << "Le code produit doit être un entier positif." << std::endl;
}
// Setters et Getters
void Produit::setPrixHT(int prixHT) {
    m_prixHT = prixHT;
}

void Produit::setPrixTTC(int prixTTC) {
    m_prixTTC = prixTTC;
}

void Produit::setCategorie(m_categorie categorie) {
    m_typeCategorie = categorie;
}

void Produit::setCodeProduit(std::string codeProduit) {
    m_codeProduit = codeProduit;
}

void Produit::setStock(int stock) {
    m_stock = stock;
}

// Getters
int Produit::getPrixHT() const {
    return m_prixHT;
}

int Produit::getPrixTTC() const {
    return m_prixTTC;
}

Produit::m_categorie Produit::getCategorie() const {
    return m_typeCategorie;
}

std::string Produit::getCodeProduit() const {
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