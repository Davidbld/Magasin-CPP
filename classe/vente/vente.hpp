/*
La vente avec réduction se fait avec la méthode virtuelle
*/
#ifndef VENTE_HPP
#define VENTE_HPP

#include <string>
#include "classe/produit/produit.hpp"

class Vente {
private:
    Produit m_produit;           // Produit associé à la vente
    int m_prixTTC = 0;           // Prix total TTC
    int m_quantite = 0;          // Quantité vendue
    std::string m_dateVente;     // Date de la vente (format jj/mm/aaaa)

public:
    // Constructeur
    Vente(const Produit& produit, int prix, int quantite, const std::string& dateVente);

    // Setters
    void setPrixTTC(int prixTTC);
    void setQuantite(int quantite);
    void setDateVente(const std::string& dateVente);

    // Getters
    int getPrixTTC() const;
    int getQuantite() const;
    const std::string& getDateVente() const;

    // Méthode pour écrire les données dans un fichier ou flux
    void ecrireDansFichier(std::ostream& fichier) const;

    // Destructeur
    ~Vente() = default;
};

#endif