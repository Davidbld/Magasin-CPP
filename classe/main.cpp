// Agit comme le magasin

#include"client/client.hpp"
#include"commande/commande.hpp"
#include <iostream>
#include <fstream>

int tempId=206; //Gestion de l'attribution des identifiants

std::map<int, ClientFidele> listeClientFideles; // Gestion des clients fideles (clé : id, valeur : Constructeur ClientFidele)

std::map<int, Commande> listeCommandes; // Gestion des commandes (clé : id, valeur : Constructeur Commande)

std::map<long int, Produit> listeProduits; // Gestion des produits (clé : id, valeur : Constructeur Produit)

//Les ventes sont renseignées dans un fichier annexe, via la méthode 'EcrireDansFichier'


int main(){
    std::ofstream fichierVentes("Ventes.txt", std::ios::app);               //Initialisation fichier ventes
    std::ofstream fichierCommandesValidees("Commandes validées.txt", std::ios::app);   //Initialisation fichier commandes validées

    //Initialisation de quelques produits (possibiltié d'en rajouter avec Commande)

    Produit pomme(2.0, Produit::m_categorie::Alimentaire, 101, "Pomme", 50);
    listeProduits[pomme.getCodeProduit()] = pomme;

    Produit shampoing(10.0, Produit::m_categorie::nonAlimentaire, 102, "Shampoing", 30);
    listeProduits[shampoing.getCodeProduit()] = shampoing;

    Produit pain(3.5, Produit::m_categorie::Alimentaire, 103, "Pain", 100);
    listeProduits[pain.getCodeProduit()] = pain;

    Produit vinRouge(20.0, Produit::m_categorie::Alcool, 104, "Vin Rouge", 25);
    listeProduits[vinRouge.getCodeProduit()] = vinRouge;
    
    Produit biscuit(1.5, Produit::m_categorie::Alimentaire, 105, "Biscuit", 200);
    listeProduits[biscuit.getCodeProduit()] = biscuit;


    //Initialisation de quelques clients fidèles (possibilité d'en ajouter ave souscireFidelite)
    ClientFidele alice(201, 25, true, "Alice Dupont", "123 Rue de Paris", 
                   "0123456789", "alice.dupont@example.com", 
                   {"Pain", "Biscuit"}, 150, ClientFidele::TypeSexe::Femme);
    listeClientFideles[alice.getId()] = alice;

    ClientFidele bob(202, 30, true, "Bob Martin", "45 Avenue Victor Hugo", 
                    "0987654321", "bob.martin@example.com", 
                    {"Vin Rouge", "Shampoing"}, 250, ClientFidele::TypeSexe::Homme);
    listeClientFideles[bob.getId()] = bob;

    ClientFidele charlie(203, 28, true, "Charlie Durand", "78 Boulevard Haussmann", 
                        "0678901234", "charlie.durand@example.com", 
                        {"Pomme", "Pain"}, 350, ClientFidele::TypeSexe::Homme);
    listeClientFideles[charlie.getId()] = charlie;

    ClientFidele diana(204, 35, true, "Diana Moreau", "10 Place Bellecour", 
                    "0456789123", "diana.moreau@example.com", 
                    {"Shampoing", "Vin Rouge"}, 50, ClientFidele::TypeSexe::Femme);
    listeClientFideles[diana.getId()] = diana;

    ClientFidele eve(205, 40, true, "Eve Blanc", "99 Quai de la Seine", 
                    "0112233445", "eve.blanc@example.com", 
                    {"Pomme", "Biscuit"}, 500, ClientFidele::TypeSexe::Femme);
    listeClientFideles[eve.getId()] = eve;


    std::string input = "0";
    while (input!="STOP")
    {
        //1.Afficher les produits disponibles
        if (input=="1")
        {
            for (auto it = listeProduits.begin(); it != listeProduits.end(); ++it) {
                std::cout   << "------------------------------"<< "\n"
                            << "Produit : " << it->second.getNomProduit()
                            << ", Prix HT : " << it->second.getPrixHT()
                            << ", Code Produit : " << it->second.getCodeProduit()
                            << ", Stock : " << it->second.getStock() <<"\n";
            }
            std::cout   << "------------------------------"<< "\n";
        }
        
        //2.Afficher les clients possedant une carte de fidelite
        if (input=="2")
        {
            for (auto it = listeClientFideles.begin(); it != listeClientFideles.end(); ++it) {
                std::cout   << "------------------------------"<< "\n"
                            << "Identifiant Client : " << it->second.getId()
                            << ", Identité : " << it->second.getNom()
                            << ", Age : " << it->second.getAge()
                            << ", Sexe : " << it->second.getSexeAsString()
                            << ", Points de fidélité : " << it->second.getPointsFidelite()
                            << ", Numéro de téléphone : " << it->second.getNumTelephone()
                            << ", Adresse Mail : " << it->second.getAdresseMail()
                            << ", Adresse : " << it->second.getAdresse() <<"\n";
            }
            std::cout   << "------------------------------"<< "\n";
        }
        //3.Effectuer un achat d'un client classique
        if (input == "3")
        {     
            std::cout << "Quel produit le client souhaite acheter ? (Insérer code produit)" << std::endl;
            long int code;
            std::cin >> code;
            
            Produit* produitAchete = nullptr;

            bool produitTrouve = false;

            for (auto it = listeProduits.begin(); it != listeProduits.end(); ++it){
                if (it->second.getCodeProduit() == code)
                {
                    produitAchete = &(it->second);

                    produitTrouve = true;
                    break;
                }
                
            }

            if (!produitTrouve)
            {
                std::cout << "Désolé, aucun produit ne correspond à ce code." << std::endl;

            }
            
            if (produitTrouve)
            {   
                int quantiteeAchetee;
                std::cout << "Quelle quantité le client achète-t'il ? (Un entier est attendu)" << std::endl;
                std::cin >> quantiteeAchetee;

                Client client(0,0);
                client.acheter(tempId, *produitAchete, fichierVentes, quantiteeAchetee, listeClientFideles,0);
            }
            
            
        }
        
        //4.Effectuer un achat d'un client ayant une carte de fidélité

        if (input == "4")
        {
            std::cout << "Quel produit le client souhaite acheter ? (Insérer code produit)" << std::endl;
            long int code;
            std::cin >> code;
            
            Produit* produitAchete = nullptr;

            bool produitTrouve = false;

            for (auto it = listeProduits.begin(); it != listeProduits.end(); ++it){
                if (it->second.getCodeProduit() == code)
                {
                    produitAchete = &(it->second);

                    produitTrouve = true;
                    break;
                }
                
            }

            if (!produitTrouve)
            {
                std::cout << "Aucun produit ne correspond à ce code." << std::endl;

            }
            
            if (produitTrouve)
            {   
                int quantiteeAchetee;
                std::cout << "Quelle quantité le client achète-t'il ? (Un entier est attendu)" << std::endl;
                std::cin >> quantiteeAchetee;

                int idClientFidele;
                std::cout << "Quel est l'identifiant du client fidèle ?" << std::endl;
                std::cin >> idClientFidele;

                ClientFidele* clientFidele = nullptr;

                bool clientTrouve = false;

                for (auto it = listeClientFideles.begin(); it != listeClientFideles.end(); ++it){
                    if (it->second.getId() == idClientFidele)
                    {
                        clientFidele = &(it->second);

                        clientTrouve = true;
                        break;
                    }
                }

                if (!clientTrouve)
                {
                    std::cout << "Aucune carte de fidélité ne correspond à cet identifiant." << std::endl;
                }
                
                if (clientTrouve)
                {
                    clientFidele->acheter(0, *produitAchete, fichierVentes, quantiteeAchetee, listeClientFideles, idClientFidele);
                }

            }

        }

        //5.Effectuer une commande fournisseur
        if (input == "5")
        {
            Commande newCommande(0);

            newCommande.creerCommande(listeCommandes, listeProduits, tempId);
        }
        
        //6.Gérer les commandes en cours
        if (input == "6")
        Commande (0);
        {
            int compteur = 0;
            if (!listeCommandes.empty())
            {
                for (auto it = listeCommandes.begin(); it != listeCommandes.end(); it++)
                {
                    if (it->second.getStatutAsString()=="EnCours")
                    {
                        compteur+=1;
                        it->second.afficherCommande();
                    }

                    if (compteur==0)
                    {
                        std::cout << "Il n'y a aucune commande en cours" << std::endl;
                    }
                    if (compteur > 0)
                    {
                        int inputCommande = 0;
                        std::cout << "Souhaitez-vous :\n 1 : Valider une commande.\n2 : Annuler une commande.\n(Un entier est attendu)" << std::endl;
                        if (inputCommande == 1)
                        {
                            Commande validateCommande(0);
                            validateCommande.validerCommande(listeCommandes, fichierCommandesValidees);
                            

                        }

                        if (inputCommande == 2)
                        {
                            Commande cancelCommande(0);
                            cancelCommande.annulerCommande(listeCommandes);
                        }                                      
                }
            }  
        }
        
        //7.Souscrire un client
        if (input == "7")
        {
            Client client(0,0); //se détruit automatiquement à la sortie du bloc if
            client.souscrireFidelite(tempId, listeClientFideles);
        }
        
        //8. Afficher les achats d'un client fidèle
        
        std::cout << "Que voulez-vous faire ?\n"
          << "1 pour afficher les produits disponibles.\n"
          << "2 pour afficher les clients possédant une carte de fidélité.\n"
          << "3 pour enregistrer un achat.\n"
          << "4 pour enregistrer un achat d'un client fidèle.\n"
          << "5 pour effectuer une commande auprès des fournisseurs.\n"
          << "6 pour gérer les commandes en cours.\n"
          << "7 pour souscrire un nouveau client.\n"
          << "8 pour afficher les achats d'un client possédant un compte fidélité.\n"
          << "STOP pour quitter \n"
          << "Veuillez entrer votre choix : ";
        std::cin >> input;
    }
    

    return 0;
}
}