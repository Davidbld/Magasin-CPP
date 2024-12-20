#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <vector>
#include <map>
#include "../produit/produit.hpp"
class ClientFidele; //ici on informe la class client que la class ClientFidele existe bien, pour qu'il puisse l'utiliser

class Client {
protected:
    // Attributs
    int m_age = 0;
    int m_id = 0;

public:
    // Constructeurs
    Client(int id, int age);

    // Méthodes
    virtual void acheter(int tempId, Produit& produit, std::ostream& fichier, int quantiteAchetee, std::map<int, ClientFidele>& listeClientsFideles, int idClientFidele);
    void souscrireFidelite(int &tempIdClient, std::map<int, ClientFidele>& listeClientsFideles);
    bool operator<(int ageLimite) const; //surcharge de l'opérateur

    // Getters et Setters
    void setAge(int age);
    int getAge() const;

    void setId(int id);
    int getId() const;

    // Virtual destructor pour permettre une suppression correcte des objets hérités
    virtual ~Client() = default;
};

class ClientFidele : public Client {
public:
    // Définition de l'enum
    enum class TypeSexe {
        Homme,
        Femme,
        NonSpecifie
    };

private:
    // Attributs spécifiques à ClientFidele
    bool m_fidelite;
    std::string m_nom = "";
    std::string m_adresse = "";
    std::string m_numTelephone = "";
    std::string m_adresseMail = "";
    std::vector<std::string> m_listeAchats;
    int m_pointsFidelite = 0;
    TypeSexe m_sexe;

public:
    // Constructeurs
    ClientFidele(); //Constructeur par défaut
    ClientFidele(int id, int age, bool fidelite, const std::string &nom, const std::string &adresse, 
                 const std::string &numTelephone, const std::string &adresseMail, 
                 const std::vector<std::string> &listeAchats, int pointsFidelite, TypeSexe sexe);

    // Méthodes
    std::string getSexeAsString() const;
    void acheter(int tempId, Produit& produit, std::ostream& fichier, int quantiteAchetee, std::map<int, ClientFidele>& listeClientsFideles, int idClientFidele) override;

    // Getters et Setters
    void setNom(const std::string &nom);
    const std::string &getNom() const;

    void setFidelite(bool fidelite);
    bool getFidelite() const;

    void setAdresse(const std::string &adresse);
    const std::string &getAdresse() const;

    void setNumTelephone(const std::string &numTelephone);
    const std::string &getNumTelephone() const;

    void setAdresseMail(const std::string &adresseMail);
    const std::string &getAdresseMail() const;

    void setListeAchats(const std::vector<std::string> &listeAchats);
    std::vector<std::string> &getListeAchats();

    void setPointsFidelite(int points);
    int getPointsFidelite() const;

    void setSexe(TypeSexe sexe);
    TypeSexe getSexe() const;

    // Destructeur virtuel
    ~ClientFidele() override = default;
};

#endif
