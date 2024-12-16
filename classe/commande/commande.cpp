/* Gère les commandes fournisseur :
- Délais de livraison estimée
- Nom du produit
- Code du produit
- Quantité du produit
*/

#include "commande.hpp"
#include <regex>
#include <vector>

// Constructeur
Commande::Commande() : m_idCommande(0), m_delaiLivraison(0), m_quantiteProduit(0), m_statut(m_statutCommande::EnCours), m_date("")
{
}

Commande::Commande(int idCommande) : m_idCommande(idCommande) {}

Commande::Commande(int idCommande, int delaiLivraison, Produit &produit, int quantiteProduit, m_statutCommande statut, std::string date)
    : m_produit(produit),
      m_delaiLivraison(delaiLivraison),
      m_quantiteProduit(quantiteProduit),
      m_idCommande(idCommande),
      m_statut(statut),
      m_date(date)
{
    // Verification des entrées
    if (m_delaiLivraison < 0)
    {
        throw std::invalid_argument("Le délai de livraison doit être supérieur ou égal à 0 (jours)");
    }
    if (m_quantiteProduit <= 0)
    {
        throw std::invalid_argument("La quantité doit être supérieure à 0.");
    }
    std::regex dateRegex(R"(^\d{2}/\d{2}/\d{4}$)");
    if (!std::regex_match(m_date, dateRegex))
    {
        throw std::invalid_argument("La date doit être au format jj/mm/aaaa.");
    }
    if (
        statut != m_statutCommande::EnCours &&
        statut != m_statutCommande::Validee &&
        statut != m_statutCommande::Annulee)
    {
        throw std::invalid_argument("Le statut doit être EnCours, Validee, ou Annulee");
    }
}

// Getters et Setters

void Commande::setProduit(Produit produit)
{
    m_produit = produit;
}

Produit& Commande::getProduit()
{
    return m_produit;
}

void Commande::setDelaiLivraison(int delaiLivraison)
{
    m_delaiLivraison = delaiLivraison;
}

int Commande::getDelaiLivraison() const
{
    return m_delaiLivraison;
}

void Commande::setQuantiteProduit(int quantiteProduit)
{
    m_quantiteProduit = quantiteProduit;
}

int Commande::getQuantiteProduit() const
{
    return m_quantiteProduit;
}

void Commande::setIdCommande(int IdCommande)
{
    m_idCommande = IdCommande;
}

int Commande::getIdCommande() const
{
    return m_idCommande;
}

void Commande::setStatutCommande(m_statutCommande statut)
{
    m_statut = statut;
}

Commande::m_statutCommande Commande::getStatut() const
{
    return m_statut;
}

void Commande::setDateCommande(const std::string &date)
{
    std::regex dateRegex(R"(^\d{2}/\d{2}/\d{4}$)");
    if (!std::regex_match(date, dateRegex))
    {
        throw std::invalid_argument("La date doit être au format jj/mm/aaaa.");
    }
    m_date = date;
}

const std::string &Commande::getDateCommande() const
{
    return m_date;
}

// Méthodes

std::string Commande::getStatutAsString() const
{
    if (m_statut == m_statutCommande::EnCours)
    {
        return "EnCours";
    }
    else if (m_statut == m_statutCommande::Validee)
    {
        return "Validee";
    }
    else if (m_statut == m_statutCommande::Annulee)
    {
        return "Annulee";
    }
    else
    {
        return "Inconnu";
    }
}

void Commande::afficherCommande() const
{
    std::cout << "ID Commande : " << m_idCommande << "\n";
    std::cout << "Délai de livraison : " << m_delaiLivraison << " jours\n";
    std::cout << "Produit commandé : " << m_produit.getNomProduit() << "\n";
    std::cout << "Quantité : " << m_quantiteProduit << "\n";
    std::cout << "Statut : " << getStatutAsString() << "\n";
    std::cout << "Date : " << m_date << "\n";
}

void Commande::creerCommande(std::map<int, Commande> &listeCommandes, std::map<long int, Produit> &listeProduits, int &tempId)
{

    int idCommande = ++tempId;

    std::string date;
    std::cout << "Entrez la date au format jj/mm/aaaa :\n";
    std::cin >> date;

    int delaiLivraison;
    std::cout << "Entrez le délai de livraison (nombre de jours) :\n";
    std::cin >> delaiLivraison;

    int quantiteCommandee;
    std::cout << "Entrez la quantite du produit commandé :\n";
    std::cin >> quantiteCommandee;

    long int codeProduit;
    std::cout << "Entrez le code produit du produit :\n";
    std::cin >> codeProduit;

    if (listeProduits.count(codeProduit) > 0)
    {
        Commande newCommande(
            idCommande,
            delaiLivraison,
            listeProduits[codeProduit],
            quantiteCommandee,
            Commande::m_statutCommande::EnCours,
            date);

        listeCommandes[idCommande] = newCommande;
        std::cout << "Commande validée." << std::endl;
    }
    else
    {
        std::cout << "Le produit n'existe pas dans la banque de produit, vous devez créer un nouveau produit" << std::endl;

        int stock = 0;

        double prix;
        std::cout << "Entrez le prixHT du produit :\n";
        std::cin >> prix;

        Produit::m_categorie categorie;
        std::string input;

        std::cout << "Entrez la catégorie du produit (Alcool/Alimentaire/nonAlimentaire): \n";
        std::cin >> input;

        if (input == "Alcool")
        {
            categorie = Produit::m_categorie::Alcool;
        }
        else if (input == "Alimentaire")
        {
            categorie = Produit::m_categorie::Alimentaire;
        }
        else if (input == "nonAlimentaire")
        {
            categorie = Produit::m_categorie::nonAlimentaire;
        }
        else
        {
            std::cout << "Erreur : Catégorie invalide !" << std::endl;
            categorie = Produit::m_categorie::nonAlimentaire; // Valeur par défaut
        }

        std::string nom;
        std::cout << "Entrez le nom du produit : \n";
        std::cin >> nom;

        Produit newProduit(prix, categorie, codeProduit, nom, stock);
        listeProduits[codeProduit] = newProduit;

        Commande newCommande(
            idCommande,
            delaiLivraison,
            newProduit,
            quantiteCommandee,
            Commande::m_statutCommande::EnCours,
            date);

        listeCommandes[idCommande] = newCommande;
        std::cout << "Commande validée." << std::endl;
    }
}

void Commande::validerCommande(std::map<int, Commande> &listeCommandes, std::ostream &fichier)
{

    int idToValid;
    std::cout << "Quelle commande souhaitez-vous valider ? (Renseignez l'id de commande) :\n";
    std::cin >> idToValid;
    bool dansListe = false;
    for (auto it = listeCommandes.begin(); it != listeCommandes.end(); it++)
    {
        if (it->second.getStatutAsString() == "EnCours" && it->first == idToValid)
        {
            dansListe = true;
        }
    }
    if (dansListe)
    {
        Commande &commande = listeCommandes[idToValid];
        commande.setStatutCommande(Commande::m_statutCommande::Validee);
        Produit& produit = commande.getProduit();
        produit.setStock(produit.getStock() + commande.getQuantiteProduit());

        std::string dateLivraison;
        std::cout << "Entrez la date : (dd/mm/aaaa)" << std::endl;
        std::cin >> dateLivraison;
        commande.ecrireCommandeDansFichier(fichier, commande, dateLivraison);

        std::cout << "La commande a été validée." << std::endl;
    }
}

void Commande::annulerCommande(std::map<int, Commande> &listeCommandes)
{

    int idToCancel;
    std::cout << "Quelle commande souhaitez-vous annuler ? (Renseignez l'id de commande)";
    std::cin >> idToCancel;
    bool dansListe = false;
    for (auto it = listeCommandes.begin(); it != listeCommandes.end(); it++)
    {
        if (it->second.getStatutAsString() == "EnCours" && it->first == idToCancel)
        {
            dansListe = true;
        }
    }
    if (dansListe)
    {
        Commande &commande = listeCommandes[idToCancel];
        commande.setStatutCommande(Commande::m_statutCommande::Annulee);

        std::cout << "La commande a été Annulee." << std::endl;
    }
}

void Commande::ecrireCommandeDansFichier(std::ostream &fichier, Commande commande, std::string dateLivraison) const
{
    fichier << "-------------------------\n";
    fichier << "Identifiant commande : " << commande.getIdCommande() << std::endl;
    fichier << "Produits commandés : " << commande.getProduit().getNomProduit() << std::endl;
    fichier << "Quantité commandée : " << commande.getQuantiteProduit() << std::endl;
    fichier << "Date livraison : " << dateLivraison << std::endl;
    fichier << "-------------------------\n";
}