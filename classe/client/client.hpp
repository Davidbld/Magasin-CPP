#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <iostream>
#include <vector>

class Client
{
    // Attributs
protected:
    int m_age = 0;
    int m_id = 0;

public:
    // Méthodes
    virtual void acheter();
    // La souscription se fait par la transposition d'un objet vers un autre. [A FAIRE AVEC DES CONSTRUCTEURS]
    void souscrireFidelite();
    // Constructeurs
    Client(int id, int age);
    // Destructeurs (optionnel)
    ~Client();
    // Getters et Setters

    void setAge(int age);
    int getAge() const;

    void setId(int id);
    int getId() const;
};

class ClientFidele : public Client
{
    // Atributs
private:
    bool m_fidelite;
    std::string *m_nom = nullptr;
    std::string m_adresse = "";
    int m_numTelephone = 0;
    std::string m_adresseMail = "";
    std::vector<std::string> m_listeAchats;
    int m_pointsFidelite = 0;
    std::string m_sexe = "";

public:
    // Méthodes
    virtual void acheter() override;
    // Constructeurs
    ClientFidele(int id, int age, bool fidelite, std::string *nom, std::string adresse, int numTelephone, std::string adresseMail, std::vector<std::string> listeAchats, int pointsFidelite, std::string sexe );

    // Getters et Setters

    void setNom(std::string &nom);
    std::string *getNom() const;

    void setFidelite(bool fidelite);
    bool getFidelite() const;

    void setAdresse(const std::string &adresse);
    const std::string &getAdresse() const;

    void setNumTelephone(int numTelephone);
    int getNumTelephone() const;

    void setAdresseMail(const std::string &adresseMail);
    const std::string &getAdresseMail() const;

    void setListeAchats(const std::vector<std::string> &listeAchats);
    const std::vector<std::string> &getListeAchats() const;

    void setPointsFidelite(int points);
    int getPointsFidelite() const;

    void setSexe(std::string sexe);
    std::string getSexe() const;
};

#endif