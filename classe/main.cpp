// Agit comme le magasin

#include"classe/client/client.cpp"
#include"classe/commande/commande.cpp"

int tempId=0; //Gestion de l'attribution des identifiants

std::map<int, ClientFidele> listeClientFideles; // Gestion des clients fideles (clé : id, valeur : Constructeur ClientFidele)

std::map<int, Commande> listeCommandes; // Gestion des commandes (clé : id, valeur : Constructeur Commande)

std::map<long int, Produit> listeProduits; // Gestion des produits (clé : id, valeur : Constructeur Produit)

//Les ventes sont renseignées dans un fichier annexe, via la méthode 'EcrireDansFichier'

