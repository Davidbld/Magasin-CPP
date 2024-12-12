// Agit comme le magasin

#include"client/client.hpp"
#include"commande/commande.hpp"
#include <iostream>
#include <fstream>

int tempId=0; //Gestion de l'attribution des identifiants

std::map<int, ClientFidele> listeClientFideles; // Gestion des clients fideles (clé : id, valeur : Constructeur ClientFidele)

std::map<int, Commande> listeCommandes; // Gestion des commandes (clé : id, valeur : Constructeur Commande)

std::map<long int, Produit> listeProduits; // Gestion des produits (clé : id, valeur : Constructeur Produit)

//Les ventes sont renseignées dans un fichier annexe, via la méthode 'EcrireDansFichier'


int main(){
    std::ofstream fichierVentes("Ventes.txt", std::ios::app); //Initialisation fichier ventes

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


    std::string input = 0;
    while (input!="STOP")
    {
        //1.Afficher les produits disponibles
        if (input=="1")
        {
            for (auto it = listeProduits.begin(); it != listeProduits.end(); ++it) {
                std::cout  << "Produit : " << it->second.getNomProduit()
                            << ", Prix HT : " << it->second.getPrixHT()
                            << ", Stock : " << it->second.getStock() << "\n";
            }
        }
        
        //2.Effectuer un achat
        //3.Effectuer une commande
        //4.Souscrire un client
        /*5.Afficher les commandes:
            -toutes les commandes
            -commandes en cours
            -commandes anulées
            -commandes validées
            */
        //6.Afficher les clients possedant une carte de fidelite
        std::cout << "Que voulez-vous faire ?\n"
          << "1 pour afficher les produits disponibles.\n"
          << "2 \n"
          << "3 \n"
          << "4 \n"
          << "STOP pour quitter \n"
          << "Veuillez entrer votre choix : ";
        std::cin >> input;
    }
    

    return 0;
}