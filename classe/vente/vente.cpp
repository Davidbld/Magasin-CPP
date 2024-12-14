#include "vente.hpp"
#include <regex>
#include <stdexcept>
#include <iostream>

// Constructeur
Vente::Vente(const Produit& produit, double prix, int quantite, const std::string& dateVente)
    : m_produit(produit), m_prixTTC(prix), m_quantite(quantite), m_dateVente(dateVente) {
    // Vérification des entrées
    if (m_quantite <= 0) {
        throw std::invalid_argument("La quantité doit être supérieure à 0.");
    }
    
    std::regex dateRegex(R"(^\d{2}/\d{2}/\d{4}$)");
    if (!std::regex_match(m_dateVente, dateRegex)) {
        throw std::invalid_argument("La date doit être au format jj/mm/aaaa.");
    }
}

// Setters et getters
void Vente::setPrixTTC(double prixTTC) {
    if (prixTTC < 0) {
        throw std::invalid_argument("Le prix TTC ne peut pas être négatif.");
    }
    m_prixTTC = prixTTC;
}

void Vente::setQuantite(int quantite) {
    if (quantite <= 0) {
        throw std::invalid_argument("La quantité doit être supérieure à 0.");
    }
    m_quantite = quantite;
}
int Vente::getQuantite() const {
    return m_quantite;
}

void Vente::setDateVente(const std::string& dateVente) {
    std::regex dateRegex(R"(^\d{2}/\d{2}/\d{4}$)");
    if (!std::regex_match(dateVente, dateRegex)) {
        throw std::invalid_argument("La date doit être au format jj/mm/aaaa.");
    }
    m_dateVente = dateVente;
}
const std::string& Vente::getDateVente() const {
    return m_dateVente;
}

// Nouvelle méthode pour écrire les données dans un fichier
void Vente::ecrireDansFichier(std::ostream& fichier, Produit produit) const {
    fichier << "Produit : " << m_produit.getNomProduit() << std::endl;
    fichier << "Prix HT :" << produit.getPrixHT() << std::endl;
    fichier << "Prix TTC : " << m_prixTTC << " €" << std::endl;
    fichier << "Quantité : " << m_quantite << std::endl;
    fichier << "Prix total : " << m_quantite*m_prixTTC << " €" << std::endl;
    fichier << "Date : " << m_dateVente << std::endl;
    fichier << "-------------------------\n";
}
