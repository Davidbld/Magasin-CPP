#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <iostream>
#include <vector>

class Client
{
    // Attributs
private:
    std::string *m_nom = nullptr;
    int m_age = 0;
    int id=0;

public:
    // Méthodes
    virtual void acheter();
    // La souscription se fait par la transposition d'un objet vers un autre. [A FAIRE AVEC DES CONSTRUCTEURS]
    void souscrireFidelite();
    // Constructeurs
    Client(int id, int age);
    Client(int id, int age, std::string nom);
    // Destructeurs (optionnel)
    ~Client();
    // Getters et Setters
    void setNom(std::string &nom);
    std::string *getNom() const;

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
    std::string m_adresse = "";
    int m_numTelephone = 0;
    std::string m_adresseMail = "";
    std::vector<std::string> m_listeAchats;
    int m_pointsFidelite = 0;
    enum m_sexe
    {
        Male,
        Femmelle,
        Aucun
    };

public:
    // Méthodes
    virtual void acheter() override;
    // Getters et Setters
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

    void setSexe(m_sexe sexe);
    m_sexe getSexe() const;
};

#endif