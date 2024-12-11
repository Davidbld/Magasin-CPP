/* Gère les commandes fournisseur :
- Délais de livraison estimée
- Nom du produit
- Code du produit
- Quantité du produit
*/

#include "commande.hpp"
#include <regex>

// Constructeur
Commande::Commande(int idCommande, int delaiLivraison, Produit produit, int quantiteProduit, m_statutCommande statut, std::string date)
    : m_produit(produit),
      m_delaiLivraison(delaiLivraison),
      m_quantiteProduit(quantiteProduit),
      m_idCommande(idCommande),
      m_statut(statut),
      m_date(date)
       {
    //Verification des entrées
    if(m_delaiLivraison<0){
        throw std::invalid_argument("Le délai de livraison doit être supérieur ou égal à 0 (jours)");
    }
    if (m_quantiteProduit <= 0) {
        throw std::invalid_argument("La quantité doit être supérieure à 0.");
    }
    std::regex dateRegex(R"(^\d{2}/\d{2}/\d{4}$)");
    if (!std::regex_match(m_date, dateRegex)) {
        throw std::invalid_argument("La date doit être au format jj/mm/aaaa.");
    }
    if(
        statut != m_statutCommande::EnCours &&
        statut != m_statutCommande::Validee &&
        statut != m_statutCommande::Annulee )
        {
            throw std::invalid_argument("Le statut doit être EnCours, Validee, ou Annulee");
        }
      }

// Getters et Setters

void Commande::setDelaiLivraison(int delaiLivraison) {
    m_delaiLivraison = delaiLivraison;
}

int Commande::getDelaiLivraison() const {
    return m_delaiLivraison;
}

void Commande::setQuantiteProduit(int quantiteProduit) {
    m_quantiteProduit = quantiteProduit;
}

int Commande::getQuantiteProduit() const {
    return m_quantiteProduit;
}

void Commande::setIdCommande(int IdCommande){
    m_idCommande = IdCommande;
}

int Commande::getIdCommande() const {
    return m_idCommande;
}

void Commande::setStatutCommande(m_statutCommande statut){
    m_statut=statut;
}

Commande::m_statutCommande Commande::getStatut() const {
    return m_statut;
}

void Commande::setDateCommande(const std::string& date) {
    std::regex dateRegex(R"(^\d{2}/\d{2}/\d{4}$)");
    if (!std::regex_match(date, dateRegex)) {
        throw std::invalid_argument("La date doit être au format jj/mm/aaaa.");
    }
    m_date = date;
}

const std::string& Commande::getDateCommande() const {
    return m_date;
}