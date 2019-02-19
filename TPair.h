/*
 * Template TPair pour créer un objet TPair<Key, value> (couple clé, valeur)
 */

#ifndef TPAIR_H
#define TPAIR_H

#include <string>
#include <typeinfo>
#include <c++/4.8.3/ctime>
#include "MyLib.h"

template<class K, class T>
class TPair  {

public :

    /* Constructeurs */
        TPair() : key(genKey_i()), item(77) {}
        TPair(K _tk, T _ti) : key(_tk), item(_ti) {}
        TPair(const TPair &tp) : key(tp.key), item(tp.item) {}
        TPair(TPair &&_tp) : key(std::move(_tp.key)), item(std::move(_tp.item)) {}
        ~TPair() {}

    /* Getters & Setters */
        K getKey() const {
            return key;
        }
        void setKey(K tk) {
            TPair::key = tk;
        }
        T getItem() const {
            return item;
        }
        void setItem(T ti) {
            TPair::item = ti;
        }

    /* Assignations */
        // Assignation par copie
        TPair<K, T>& operator=(const TPair<K, T> &tp) {
            if(this != &tp) {
                key = tp.key;
                item = tp.item;
            }
            return *this;
        }
        // Assignation par déplacement
        TPair<K, T>& operator=(TPair<K, T> &&tp) {
            if(this != &tp) {
                std::swap(key, tp.key);
                std::swap(item, tp.item);
            }
            return *this;
        }

    /* Méthodes & Fonctions */
        // renvoie la taille de la pair
        size_t calcSize() {
            return sizeof(*this);
        }
        // renvoie le type de l'élément de la pair
        std::string giveType() {
            return "key type : " + (std::string)typeid(key).name() + " et Value Type : "+(std::string)typeid(item).name();
        }
        // Renvoie un boolean si 2 paires sont égales (key&value)
        bool operator==(const TPair &rhs) const {
            return key == rhs.key &&
                   item == rhs.item;
        }
        // Renvoie un boolean si 2 paires sont différentes (key&value)
        bool operator!=(const TPair &rhs) const {
            return !(rhs == *this);
        }
        // Renvoie un boolean si la 1ere pair est inférieure à la 2eme (key&value)
        bool operator<(const TPair &rhs) const {
            if (key < rhs.key)
                return true;
            if (rhs.key < key)
                return false;
            return item < rhs.item;
        }
        // Renvoie un boolean si la 1ere pair est supérieure à la 2eme (key&value)
        bool operator>(const TPair &rhs) const {
            return rhs < *this;
        }
        // Renvoie un boolean si la 1ere pair est inférieure ou égale à la 2eme (key&value)
        bool operator<=(const TPair &rhs) const {
            return !(rhs < *this);
        }
        // Renvoie un boolean si la 1ere pair est supérieure ou égale à la 2eme (key&value)
        bool operator>=(const TPair &rhs) const {
            return !(*this < rhs);
        }
        // swap pour permuter 2 TPair
        friend void swap(const TPair<K, T> &tp1, const TPair<K, T> &tp2) {
            std::swap(tp1.key, tp2.key);
            std::swap(tp1.item, tp2.item);
        }
        friend void swap(TPair<K, T> &tp1, TPair<K, T> &tp2) {
            std::swap(tp1.key, tp2.key);
            std::swap(tp1.item, tp2.item);
        }
        // Stream envoie de l'objet TPair dans le flux pour l'afficher
        friend std::ostream& operator<<(std::ostream &os, const TPair<K,T> &t) {
            os << (std::string)"key: " << t.key << " -> valeur: " << t.item;
            return os;
        }
        // génère un string aléatoire
        static std::string genKey_s() {
            std::string caractere="abcdefghijklmnopqrstuvwyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789#-_@=";
            std::string key="";
            size_t taille = (rand()%10)+3;
            for(size_t i=0;i<taille;i++)
            {
                size_t pos = rand()%64+1;
                key+=caractere[pos];
            }
            return key;
        }
        // génère un string aléatoire
        static int genKey_i() {
        srand(time(NULL));
        std::string caractere="0123456789698484651319765349711357913";
        std::string key="";
        size_t taille = (rand()%5)+3;
        for(size_t i=0;i<taille;i++)
        {
            size_t pos = rand()%10+1;
            key+=caractere[pos];
        }
        return stoi(key);
    }

private :

    K key;  // clé
    T item; // objet/valeur stockée

};


#endif
