/*
Enregistre les ventes du magasin avant de les écrire dans un autre fichier :
- Ecrit sous forme de tableau avec le nom du produit, le prix à l'unité, la quantité et la date
*/

#include "vente.hpp"
#include <regex>

// Constructeur
Vente::Vente(const Produit& produit, int prix, int quantite, const std::string& dateVente)
    : m_produit(produit), m_quantite(quantite), m_dateVente(dateVente) {
    // Vérification des assertions pour valider les entrées

    assert(m_quantite>0);
        std::cout<<"La quantité du produit doit être supérieure à 0"<<std::endl;
    
    std::regex dateRegex(R"(^\d{2}/\d{2}/\d{4}$)");
    assert(std::regex_match(m_dateVente,dateRegex));
        std::cout<<"la date doit être au format jj/mm/aaaa"<<std::endl;
}

// Setters et getters
void Vente::setPrixTTC(int prixTTC) {
    m_prixTTC = prixTTC;
}
int Vente::getPrixTTC() const {
    return m_prixTTC;
}

void Vente::setQuantite(int quantite) {
    m_quantite = quantite;
}
int Vente::getQuantite() const {
    return m_quantite;
}


void Vente::setDateVente(const std::string& dateVente) {
    m_dateVente = dateVente;
}
const std::string& Vente::getDateVente() const {
    return m_dateVente;
}