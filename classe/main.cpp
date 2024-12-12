// Agit comme le magasin

#include"client/client.cpp"
#include"commande/commande.cpp"
#include <fstream>

int tempId=0; //Gestion de l'attribution des identifiants

std::map<int, ClientFidele> listeClientFideles; // Gestion des clients fideles (clé : id, valeur : Constructeur ClientFidele)

std::map<int, Commande> listeCommandes; // Gestion des commandes (clé : id, valeur : Constructeur Commande)

std::map<long int, Produit> listeProduits; // Gestion des produits (clé : id, valeur : Constructeur Produit)

//Les ventes sont renseignées dans un fichier annexe, via la méthode 'EcrireDansFichier'


int main(){
    std::ofstream fichierVentes("Ventes.txt", std::ios::app);
    Client client(0,0);

    Produit eau(2, Produit::m_categorie::nonAlimentaire, 1, "eau", 40);
    client.acheter(tempId, eau, fichierVentes, 2, listeClientFideles, 0);


    return 0;
}