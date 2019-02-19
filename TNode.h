/*
 * Template TNode pour créer un objet TNode représentant un noeud de l'arbre (feuille et noeud)
 * 1. Un nœud est soit rouge soit noir
 * 2. La racine est noire
 * 3. Le parent d'un nœud rouge est noir
 * 4. Le chemin de chaque feuille à la racine contient le même nombre de nœuds noirs.
 *
 */

#ifndef T_NODE_H
#define T_NODE_H

#include <assert.h>
#include <iostream>
#include <memory>
#include "TPair.h"

template<class K, class T>
class TNode {

public:
    /* Constructeurs */
        TNode() : pair(TPair<K, T>()), parent(nullptr), gauche(nullptr), droite(nullptr), color(-1){}
        TNode(K, T) : pair(TPair<K, T>()), parent(nullptr), gauche(nullptr), droite(nullptr), color(-1){}
        TNode(TPair<K, T> _pair, std::shared_ptr <TNode<K, T>> _parent, std::shared_ptr <TNode<K, T>> _gauche, std::shared_ptr <TNode<K, T>>  _droite, int _color) : pair(_pair), parent(_parent), gauche(std::move(_gauche)), droite(std::move(_droite)), color(_color){}
        TNode(std::shared_ptr <TNode<K, T>> _parent, std::shared_ptr <TNode<K, T>> _gauche, std::shared_ptr <TNode<K, T>>  _droite, int _color) : pair(TPair<K, T>()), parent(_parent), gauche(std::move(_gauche)), droite(std::move(_droite)), color(_color){}
        TNode(const TNode<K, T> &n) : pair(n.pair), parent(std::move(n.parent)), gauche(std::move(n.gauche)), droite(std::move(n.droite)), color(n.color){}
        TNode(TNode<K, T> &&n) : pair(std::move(n.pair)), parent(std::move(n.parent)), gauche(std::move(n.gauche)), droite(std::move(n.droite)), color(std::move(n.color)){}
        ~TNode() {}

    /* Assignations */
        // Assignation par copie
        TNode<K, T>& operator=(const TNode<K, T> &tp) {
            if(this != &tp) {
                pair    = std::move(tp.pair);
                parent  = std::move(tp.parent);
                gauche  = std::move(tp.gauche);
                droite  = std::move(tp.droite);
                color   = std::move(tp.color);
            }
            return *this;
        }
        // Assignation par déplacement
        TNode<K, T>& operator=(TNode<K, T> &&tp) {
            if(this != &tp) {
                std::swap(pair, tp.pair);
                std::swap(parent, tp.parent);
                std::swap(gauche, tp.gauche);
                std::swap(droite, tp.droite);
                std::swap(color, tp.color);
            }
            return *this;
        }

    /* Getters & Setters */
        const TPair<K, T> getPair() const {
            return pair;
        }
        void setPair(const TPair<K, T> &pair) {
            TNode::pair = pair;
        }
        std::shared_ptr <TNode<K, T>> getGauche() {
            return gauche;
        }
        void setGauche(std::shared_ptr <TNode<K, T>>_gauche) {
            if(_gauche != nullptr) {
                std::swap(gauche, _gauche);
            }
        }
        std::shared_ptr <TNode<K, T>> getDroite()  {
            return droite;
        }
        void setDroite(std::shared_ptr <TNode<K, T>> _droite) {
            if(_droite != nullptr) {
                std::swap(TNode::droite, _droite);
            }
        }
        int getColor() const {
            return color;
        }
        void setColor(int color) {
            if(this!= nullptr) {
                TNode::color = color;
            }
        }
        std::shared_ptr <TNode<K, T>> getParent() const {
            return parent;
        }
        void setParent(std::shared_ptr <TNode<K, T>> _parent) {
            if(_parent != nullptr) {
                std::swap(TNode::parent, _parent);
            }
            else {
                parent = _parent;
            }
        }
        // renvoie le grand-parent
        std::shared_ptr <TNode<K, T>> getGrandParent() const {
            if (parent == NULL)
                return NULL; // pas de parent = pas de grand parent
            return parent->getParent();
        }
        void setGrandParent(std::shared_ptr <TNode<K, T>> _parent) {
            swap(parent->parent, _parent);
        }
        // renvoie l'enfant du même parent
        std::shared_ptr <TNode<K, T>> getEnfantDuMParent() {
            if (parent == NULL) {
                return NULL; // pas de parent = pas d'enfant de même parent
            }
            else {
                if (this == parent->gauche)
                    return parent->droite;
                else
                    return parent->gauche;
            }
        }
        // Renvoie le node oncle
        std::shared_ptr <TNode<K, T>> getOncle() const {
            if (this->getGrandParent() == NULL)
                return NULL; // pas de grand-parent = pas d'oncle
            else
            return parent->getGrandParent();
        }

    /* Méthodes et fonctions membres */
        // tourne à gauche
        void rotation_gauche() {
            try {
                assert(!is_feuille(droite)); // feuille de l'arbre rouge noir vides, donc ne peut être un noeud interne
                throw std::string("rotation_gauche() erreur, droite est NULL");
            }
            catch(std::string const& chaine) {
                std::cout << chaine << std::endl;
            }
        }
        // tourne à droite
        void rotation_droite() {
            try {
                assert(!is_feuille(gauche)); // feuille de l'arbre rouge noir vides, donc ne peut être un noeud interne
                throw std::string("rotation_droite() erreur, gauche est NULL");
            }
            catch(std::string const& chaine) {
                std::cout << chaine << std::endl;
            }

        }
        // compare si 2 nodes sont égaux
        bool operator==(const TNode &rhs) const {
            return pair == rhs.pair &&
                   parent == rhs.parent &&
                   gauche == rhs.gauche &&
                   droite == rhs.droite &&
                   color == rhs.color;
        }
        // compare si 2 nodes sont différents
        bool operator!=(const TNode &rhs) const {
            return !(rhs == *this);
        }
        // compare si 2 nodes sont inférieures
        bool operator<(const TNode &rhs) const {
            if (pair < rhs.pair)
                return true;
            if (rhs.pair < pair)
                return false;
            if (parent < rhs.parent)
                return true;
            if (rhs.parent < parent)
                return false;
            if (gauche < rhs.gauche)
                return true;
            if (rhs.gauche < gauche)
                return false;
            if (droite < rhs.droite)
                return true;
            if (rhs.droite < droite)
                return false;
            return color < rhs.color;
        }
        // compare si 2 nodes sont supérieures
        bool operator>(const TNode &rhs) const {
            return rhs < *this;
        }
        // compare si 2 nodes sont inférieures ou égaux
        bool operator<=(const TNode &rhs) const {
            return !(rhs < *this);
        }
        // compare si 2 nodes sont supérieures ou égaux
        bool operator>=(const TNode &rhs) const {
            return !(*this < rhs);
        }

    /* Méthodes et fonctions externes/friend */
        // détermine si un noeud est une feuille
        friend bool is_feuille(const std::shared_ptr <TNode<K, T>> &node) {
            std::cout << "is_feuille() called pour le node " << &node << std::endl;
                if(node == NULL) {
                    std::cout << "impossible de tester si le node est une feuille, le node est NULL !" << std::endl;
                    return -1;
                }
                else {
                    if (node->gauche == NULL && node->droite == NULL) {
                        std::cout << "le node est une feuille" << std::endl;
                        return true;
                    } else {
                        std::cout << "le node n'est pas une feuille" << std::endl;
                        return false;
                    }
               }

        }
        // stream, envoie l'objet TNode dans le flux cout pour l'afficher
        friend std::ostream &operator<<(std::ostream &os, const TNode<K, T> &node) {
                // os << "stream overload with reference called\n"
                os << "parent adresse: " << node.parent
                   << " | Val parent: " << ((node.parent == nullptr) ? "0 (objet null) " : "valeur de l'objet parent")
                   << "\ngauche adresse: " << node.gauche
                   << " | Val gauche: " << ((node.gauche == nullptr) ? "0 (objet null) " : "valeur de l'objet parent")
                   << "\ndroite adresse: "  << node.droite
                   << " | Val droite: " << ((node.droite == nullptr) ? "0 (objet null) " : "valeur de l'objet parent")
                   << "\ncolor: " << ((node.color == 0) ? "rouge" : "noir")
                   << "\npair: " << node.pair
                   << std::endl;
        return os;
        }
        // swap pour permuter 2 TNode
        friend void swap(const TNode<K, T> &tn1, const TNode<K, T> &tn2) {
            std::swap(tn1.pair, tn2.pair);
            std::swap(tn1.parent, tn2.parent);
            std::swap(tn1.gauche, tn2.gauche);
            std::swap(tn1.droite, tn2.droite);
            std::swap(tn1.color, tn2.color);
        }
        friend void swap(TNode<K, T> &tn1, TNode<K, T> &tn2) {
        std::swap(tn1.pair, tn2.pair);
        std::swap(tn1.parent, tn2.parent);
        std::swap(tn1.gauche, tn2.gauche);
        std::swap(tn1.droite, tn2.droite);
        std::swap(tn1.color, tn2.color);
    }

private :

    TPair<K, T> pair;                       // Pair key/value du noeaud
    std::shared_ptr <TNode<K, T>> parent;   // pointeur vers le parent
    std::shared_ptr <TNode<K, T>> gauche;   // pointeur vers le fils gauche
    std::shared_ptr <TNode<K, T>> droite;   // pointeur vers le fils droit
    int color;                              // couleur du noeud 0: noire 1:rouge
};


#endif
