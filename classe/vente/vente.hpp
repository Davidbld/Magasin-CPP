/*
La vente avec réduction se fait avec la méthode virtuelle
*/
#ifndef VENTE_HPP
#define VENTE_HPP

#include "produit.cpp"

class Vente{
private :
    Produit m_produit;
    int m_quantite;
    std::string m_dateVente;
    int m_prixTTC;

public : 
// Constructeur
    Vente(const Produit& produit, int prixTTC, int m_quantite, const std::string& m_dateVente);

// Getters et Setters

    void setPrixTTC(int prixTTC);
    int getPrixTTC() const;

    void setQuantite(int quantite);
    int getQuantite() const;

    void setDateVente(const std::string& m_dateVente);
    const std::string& getDateVente() const;
//Méthode
    void vente();
};

#endif