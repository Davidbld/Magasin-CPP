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
Commande::Commande(int idCommande, int delaiLivraison, Produit& produit, int quantiteProduit, m_statutCommande statut, std::string date)
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

void Commande::setProduit(Produit produit){
    m_produit = produit;
}

Produit Commande::getProduit() const{
    return m_produit;
}

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

//Méthodes

std::string Commande::getStatutAsString() const {
    if (m_statut == m_statutCommande::EnCours) {
        return "EnCours";
    } else if (m_statut == m_statutCommande::Validee) {
        return "Validee";
    } else if (m_statut == m_statutCommande::Annulee) {
        return "Non Annulee";
    } else {
        return "Inconnu";
    }
}

void Commande::afficherCommande() const {
    std::cout << "ID Commande : " << m_idCommande << "\n";
    std::cout << "Délai de livraison : " << m_delaiLivraison << " jours\n";
    std::cout << "Quantité : " << m_quantiteProduit << "\n";
    std::cout << "Statut : " << getStatutAsString() << "\n";
    std::cout << "Date : " << m_date << "\n";
}

void creerCommande(std::map<int, Commande>& listeCommandes, std::map<long int, Produit>& listeProduits, int& tempId){

    int idCommande = ++tempId;

    std::string date;
    std::cout << "Entrez la date au format jj/mm/aaaa ";
    std::cin >> date;

    int delaiLivraison;
    std::cout << "Entrez le délai de livraison (nombre de jours) ";
    std::cin >> delaiLivraison;

    int quantiteCommandee;
    std::cout << "Entrez la quantite du produit commandé";
    std::cin >> quantiteCommandee;

    long int codeProduit;
    std::cout << "Entrez le code produit du produit ";
    std::cin >> codeProduit;
    
    if (listeProduits.count(codeProduit) > 0 ){
        Commande newCommande(
            idCommande, 
            delaiLivraison, 
            listeProduits[codeProduit], 
            quantiteCommandee, 
            Commande::m_statutCommande::EnCours, 
            date);

        listeCommandes[idCommande] = newCommande;
    }
    else{
        std::cout<<"Le produit n'existe pas dans la banque de produit, vous devez créer un nouveau produit" << std::endl;

        int stock = 0;

        double prix;
        std::cout << "Entrez le prixHT du produit";
        std::cin >> prix;

        Produit::m_categorie categorie;
        std::string input;

        std::cout << "Entrez la catégorie du produit (Alcool/Alimentaire/nonAlimentaire): ";
        std::cin >> input;

        if (input == "Alcool") {
            categorie = Produit::m_categorie::Alcool;
        } else if (input == "Alimentaire") {
            categorie = Produit::m_categorie::Alimentaire;
        } else if (input == "nonAlimentaire") {
            categorie = Produit::m_categorie::nonAlimentaire;
        } else {
            std::cout << "Erreur : Catégorie invalide !" << std::endl;
            categorie = Produit::m_categorie::nonAlimentaire; // Valeur par défaut
        }

        std::string nom;
        std::cout << "Entrez le nom du produit";
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
    }
}

void validerCommande(std::map<int, Commande>& listeCommandes){
    std::vector<int>listeIdToValid;
    std::cout << "Voici la liste des commandes en cours\n";
    for (auto it = listeCommandes.begin(); it != listeCommandes.end(); it++){
        if (it->second.getStatutAsString() == "EnCours"){
            listeIdToValid.push_back(it->first);
            it->second.afficherCommande();
        }
    }

    if (listeIdToValid.empty()) {
        std::cout << "Aucune commande en cours à valider.\n";
        return;
    }

    int idToValid;
    std::cout << "Quelle commande souhaitez-vous valider ? (Renseignez l'id de commande)";
    std::cin >> idToValid;
    bool dansListe = false;
    for (int id : listeIdToValid){
        if(id == idToValid){
            dansListe = true;
            break;
        }
    }
    if(dansListe){
        Commande& commande = listeCommandes[idToValid];
        commande.setStatutCommande(Commande::m_statutCommande::Validee);
        Produit produit = commande.getProduit();
        produit.setStock(produit.getStock()+commande.getQuantiteProduit());
        commande.setProduit(produit);

        std::cout << "La commande a été validée." << std::endl;
    }
}

void annulerCommande(std::map<int, Commande>& listeCommandes){
    std::vector<int>listeToCancel;
    std::cout << "Voici la liste des commandes en cours\n";
    for (auto it = listeCommandes.begin(); it != listeCommandes.end(); it++){
        if (it->second.getStatutAsString() == "EnCours"){
            listeToCancel.push_back(it->first);
            it->second.afficherCommande();
        }
    }

    if (listeToCancel.empty()) {
        std::cout << "Aucune commande en cours à annuler.\n";
        return;
    }

    int idToCancel;
    std::cout << "Quelle commande souhaitez-vous annuler ? (Renseignez l'id de commande)";
    std::cin >> idToCancel;
    bool dansListe = false;
    for (int id : listeToCancel){
        if(id == idToCancel){
            dansListe = true;
            break;
        }
    }
    if(dansListe){
        Commande& commande = listeCommandes[idToCancel];
        commande.setStatutCommande(Commande::m_statutCommande::Annulee);

        std::cout << "La commande a été Annulee." << std::endl;
    }
}