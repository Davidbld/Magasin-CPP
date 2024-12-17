# SGMagasin-CPP

Un projet universitaire visant à programmer un système de gestion d'un magasin en C++.\
*Nous avons cherché, dans le laps de temps qui nous était imparti, à concevoir un système aussi réaliste que possible.*

Ce système prend en charge des produits de différentes catégories, des clients de différents niveaux, ainsi qu'un registre des ventes et des commandes de réassort.

## Fonctionnalités

Ce système de gestion fictif repose sur plusieurs classes : 

1. **La classe "*Commande*" :**
   - Permet de répertorier les commandes auprès des fournisseurs avec les informations suivantes :
     - Délai de livraison estimé.
     - Nom des produits.
     - Code des produits.
     - Quantité commandée.

2. **La classe "*Client*" :**
   - *Deux types de clients sont pris en charge :*
     - **Clients classiques** : enregistrés avec leur nom et leur âge pour s'assurer que les produits interdits aux mineurs, tels que l'alcool, ne leur soient pas vendus.
     - **Clients fidèles** : disposent d'un profil enrichi avec les informations suivantes :
       - Adresse postale.
       - Numéro de téléphone.
       - Adresse e-mail.
       - Liste d'achats.
       - Points de fidélité disponibles sur leur carte.

3. **La classe "*Produit*" :**
   - Les produits sont enregistrés selon différentes catégories :
     - **Alcool** : nécessite un âge supérieur ou égal à 18 ans pour l'achat.
     - **Alimentaire** : soumis à une TVA réduite de 5,5 %.
     - **Non-alimentaire** : soumis à une TVA standard de 20 %.
   - La gestion des stocks est intégrée dans cette classe.

4. **La classe "*Vente*" :**
   - Permet d'enregistrer les ventes dans un registre sous forme de tableau contenant :
     - Nom du produit.
     - Prix unitaire.
     - Quantité vendue.
     - Date de la vente.

## Utilisation

Afin de bien compiler ce programme, il est crucial de se trouver dans le dosser ```/SGMagasin-CPP/classe```.

En suite, taper la commande suivante : ```g++ main.cpp client/client.cpp commande/commande.cpp produit/produit.cpp vente/vente.cpp -o main.exe```

Et enfin, pour executer le fichier généré, entrez : ```./main```

## Nomenclature des *commits*

- **Add** : Ajout d'une ou plusieurs fonctionnalités.
- **Update** : Mise à jour majeure ou correctif important.
- **Fix** : Correctif mineur ou mise à jour légère.
- **Docs** : Modification ou mise à jour de la documentation.

## Licence

Ce projet open source a été réalisé dans un cadre éducatif. Il ne doit pas être reproduit, commercialisé ou modifié par des tiers en dehors de ses contributeurs principaux.

## Contributeurs

- **David Baldo** ([*Davidbld*](https://github.com/Davidbld))  
- **Jérémy Desbois** ([*Gookd*](https://github.com/Gookd))
