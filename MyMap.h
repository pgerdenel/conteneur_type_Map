/*
 *  Objet MyMap contenant la racine de l'arbre rouge noire
 *  1. chaque nœud du sous-arbre gauche a une clé inférieure ou égale à celle du nœud considéré
 *  2. chaque nœud du sous-arbre droit possède une clé supérieure ou égale à celle-ci
 *  3. les clés de valeur égales ont été choisi comme interdits
 *  4. les nœuds que l'on ajoute deviennent des feuilles de l'arbre.
 */

#ifndef MYMAP_H
#define MYMAP_H

#include <iostream>
#include <vector>
#include "TPair.h"
#include "TNode.h"


template<class K, class T, class Compare = std::less<K>>
class MyMap {
public :
    /* Class myIterator
     * Définit l'objet itérateur permettant de définir les fonctions de parcours de la map
     *
     */
    template<class K1, class T1>
    class MyIterator {
    public :
        /* Constructeurs */
        MyIterator<K1, T1>() : root() {}
        MyIterator<K1, T1>(std::shared_ptr <TNode<K, T>> v) : root(std::move(v)) {}
        MyIterator<K1, T1>(const MyIterator<K, T> &mi) : root(std::move(mi.root)) {}
        MyIterator<K1, T1>(MyIterator<K, T> &&mi) : root(std::move(mi.root)) {}

        /* Getters & Setters */
        const std::shared_ptr<TNode<K, T>> &getRoot() const {
            return root;
        }
        void setRoot(const std::shared_ptr<TNode<K, T>> &root) {
            MyIterator::root = root;
        }
        const K1 getFirst() const {
            return root.get()->getPair().getKey();
        }
        const T1 getSecond() const {
            return root.get()->getPair().getItem();
        }
        /* Assignations */
        // Assignation par copie
        MyIterator<K1, T1>& operator=(const MyIterator<K, T> &mi) {
            if(this != &mi) {
                root = std::move(mi.root);
            }
            return *this;
        }
        // Assignation par déplacement
        MyIterator<K1, T1>& operator=(MyIterator<K, T> &&mi) {
            if(this != &mi) {
                std::swap(root, mi.root);
            }
            return *this;
        }

        /* Opérateur d'égalité */
        bool operator==(const MyIterator &rhs) const {
            return root == rhs.root;
        }
        bool operator!=(const MyIterator &rhs) const {
            return !(rhs == *this);
        }

        /* Opérateur arithémtique */
        bool operator<(const MyIterator &rhs) const {
            return root < rhs.root;
        }
        bool operator>(const MyIterator &rhs) const {
            return rhs < *this;
        }
        bool operator<=(const MyIterator &rhs) const {
            return !(rhs < *this);
        }
        bool operator>=(const MyIterator &rhs) const {
            return !(*this < rhs);
        }

        /* Méthodes et fonctions membres */
        /* Méthode et fonctions friend */
        // affiche un iterator
        friend std::ostream &operator<<(std::ostream &os, const MyIterator &rooterator) {
            std::cout << *rooterator.getRoot() << std::endl;
        }
        // renvoie le node d'après
        friend std::shared_ptr<TNode<K, T>> operator++(const MyIterator &it) {
            try {
                if(it.getRoot().get()->getGauche() == NULL) {
                    // On renvoie NULL
                    return NULL;
                }
                else {
                    // on vérifie si droit est null
                    if(it.getRoot().get()->getDroite() == NULL) {
                        // On renvoie NULL
                        return NULL;
                    }
                    else {
                        return it.getRoot().get()->getDroite().get()->getGauche();
                    }
                }
            }
            catch(std::string const& chaine) {
                std::cerr << chaine << std::endl;
                return NULL;
            }
        };
        // renvoie le node parent d'avant
        friend std::shared_ptr<TNode<K, T>> operator--(const MyIterator &it) {
            try {
                if( it.getRoot().get()->getParent() == NULL) {
                    throw std::string("le node parent est NULL");
                }
                else {
                    return it.getRoot().get()->getParent();
                }
            }
            catch(std::string const& chaine) {
                std::cerr << chaine << std::endl;
                return NULL;
            }
        };

    private :
        std::shared_ptr <TNode<K, T>> root; // contient un pointeur sur un node

    };

    /* Constructeurs */
        MyMap<K, T, Compare>() : racine(nullptr), size(0), maxSize(0)/*, key_compare(m.key_comp()), value_compare(m.value_comp()), it(new MyIterator<K, T>(nullptr))*/ {}
        MyMap<K, T, Compare>(std::shared_ptr <TNode<K, T>> _racine, size_t _size, size_t _maxSize) : racine(std::move(_racine)), size(_size), maxSize(_maxSize)/*, key_compare(m.key_comp()), value_compare(m.value_comp()), it(new MyIterator<K, T>(racine))*/ {}
        MyMap<K, T, Compare>(const MyMap<K, T, Compare> &m) : racine(std::move(m.racine)), size(std::move(m.size)), maxSize(std::move(m.maxSize)), key_compare(std::move(m.key_compare)), value_compare(std::move(m.value_compare)), it(std::move(m.it))  {}
        MyMap<K, T, Compare>(MyMap<K, T, Compare> &&m) : racine(std::move(m.racine)), size(std::move(m.size)), maxSize(std::move(m.maxSize)), key_compare(std::move(m.key_compare)), value_compare(std::move(m.value_compare)), it(std::move(m.it))  {}
        ~MyMap() {}

    /* Getters & Setters */
        std::shared_ptr <TNode<K, T>>getRacine() const {
            return racine;
        }
        TNode<K, T> getRacine_Obj() const {
            if(racine != nullptr) {
                return *racine;
            }
            else {
                std::cout << "l'objet racine peut pas etre return car le pointeur ne pointe sur aucun objet existant" << std::endl;
            }
        }
        void setRacine(std::shared_ptr <TNode<K, T>> racine) {
            swap(MyMap::racine, racine);
        }
        size_t getSize() const noexcept {
            std::cout << size << std::endl;
            return size;
        }
        void setSize(size_t size) {
            MyMap::size = size;
        }
        size_t getMaxSize() const noexcept{
            std::cout << maxSize << std::endl;
            return maxSize;
        }
        void setMaxSize(size_t maxSize) {
            MyMap::maxSize = maxSize;
        }
        Compare getKey_compare() const {
            std::cout << "key_compare = " << &key_compare << std::endl;
            return key_compare;
        }
        void setKey_compare(Compare key_compare) {
            MyMap::key_compare = key_compare;
        }
        Compare getValue_compare() const {
            std::cout << "value_compare = " << &value_compare << std::endl;
            return value_compare;
        }
        void setValue_compare(Compare value_compare) {
            MyMap::value_compare = value_compare;
        }
        const MyIterator<K, T> &getIt() const {
            return it;
        }
        void setIt(const MyIterator<K, T> &it) {
            MyMap::it = it;
        }

    /* Assignations */
        // Assignation par copie
        MyMap<K, T, Compare>& operator=(const MyMap<K, T, Compare> &mm) {
            if(this != &mm) {
                racine = std::move(mm.racine);
                size = std::move(mm.size);
                maxSize = std::move(mm.maxSize);
            }
            return *this;
        }
        // Assignation par déplacement
        MyMap<K, T, Compare>& operator=(MyMap<K, T, Compare> &&mm) {
            if(this != &mm) {
                std::swap(racine, mm.racine);
                std::swap(size, mm.size);
                std::swap(maxSize, mm.maxSize);
            }
            return *this;
        }

    /* Opérateurs d'égalité et arithmétiques */
        // Compare si 2 map sont égales
        bool operator==(const MyMap &rhs) const {
            return racine == rhs.racine;
        }
        // Compare si 2 map sont différentes
        bool operator!=(const MyMap &rhs) const {
            return !(rhs == *this);
        }
        // Compare si la map est inférieure à la 2eme
        bool operator<(const MyMap &rhs) const {
            return racine < rhs.racine;
        }
        // Compare si la map est supérieure à la 2eme
        bool operator>(const MyMap &rhs) const {
            return rhs < *this;
        }
        // Compare si la map est inférieure ou égale à la 2eme
        bool operator<=(const MyMap &rhs) const {
            return !(rhs < *this);
        }
        // Compare si la map est supérieure ou égale à la 2eme
        bool operator>=(const MyMap &rhs) const {
            return !(*this < rhs);
        }

    /* Méthodes et Fonctions membres */
        /* Fonctions pour l'insertion/suppresion */
        // Permet d'insérere un noeud node dans l'arbre
        void insertion(std::shared_ptr <TNode<K, T>> n) {
            std::cout << "insertion called " << std::endl;
            // 1. insertion du noeud
            insertion_recursif(racine, n);
            // 2. Réparation de l'arbre au cas où les propriétés rouge-noir seraient violées
            // repareArbre(n); // équilibrage !!!!!!!!!!!
        }
        // Permet d'insérer un noeaud dans l'arbre à l'endroit où une feuille est présente selon les règles d'équilibre
        void insertion_recursif (std::shared_ptr <TNode<K, T>> node_racine_ou_pas, std::shared_ptr <TNode<K, T>> n) {
            std::cout << "insertion_recursif() called " << std::endl;
            // descente récursive dans l'arbre jusqu'à atteindre une feuille

            // si la racine est != NULL et que la clé de la pair du node à inséré est < à la clé de la pair de la racine
            if (racine != NULL && n->getPair().getKey() < racine->getPair().getKey()) {
                std::cout << "insertion_recursif() called IF 1" << std::endl;
                std::cout << "insertion_recursif() --> first check passed" << std::endl;
                // Si le node gauche de la racine n'est pas une feuille
                if (!is_feuille(racine->getGauche())) {
                    std::cout << "insertion_recursif() --> first.1 check called" << std::endl;
                    // On rappelle la fonction avec comme racine : le node droit de la racine
                    insertion_recursif(racine->getGauche(), n);
                }
                else { // si le node gauche est une feuille
                    std::cout << "insertion_recursif() --> first.2 check called" << std::endl;
                    // On assigne le node à insérer comme node gauche de la racine
                    racine->setGauche(n);
                }
            }
                // si la racine n'est pas NULL
            else if (racine != NULL) {
                std::cout << "insertion_recursif() called IF 2" << std::endl;
                std::cout << "insertion_recursif() --> second check passed" << std::endl;
                // Si le node droit de la racine n'est pas une feuille
                if (!is_feuille(racine->getDroite())) {
                    std::cout << "insertion_recursif() --> second.1 check called" << std::endl;
                    // On rappelle la fonction avec comme racine : le node droit de la racine
                    insertion_recursif(racine->getDroite(), n);
                }
                else { // si le node droit est une feuille
                    std::cout << "insertion_recursif() --> second.1 check called" << std::endl;
                    // On assigne le node à insérer comme node droit de la racine
                    racine->setDroite(n);
                }
            }

            // on insère le nouveau noeud
            std::cout << "insertion_recursif() : insertion du noeud comme nouveau noeud" << std::endl;
            n->setParent(racine);
            /*n->setGauche(std::shared_ptr<TNode<int, int>>(new TNode<K, T>()));
            n->setDroite(std::shared_ptr<TNode<int, int>>(new TNode<K, T>()));*/
            n->setGauche(nullptr);
            n->setDroite(nullptr);
            n->setColor(1); // rouge
            // insertion du nouveau noeud n
            std::swap(racine, n);
        }
        // Insertion d'un élément de façon équilibré
        // Recupère le parent et la couleur du node parent pour savoir quel insertion effectuer
        void repareArbre(std::shared_ptr <TNode<K, T>>n) {
            std::cout << "repareArbre() called " << std::endl;
                if (n->getParent() == NULL) {
                    std::cout << "repareArbre() first condition called " << std::endl;
                    insertion_cas1(n);
                } else if (n->getParent()->getColor() == 0) {
                    std::cout << "repareArbre() second condition called " << std::endl;
                    insertion_cas2(n);
                } else if (n->getOncle()!= NULL) {
                    std::cout << "repareArbre() third condition called " << std::endl;
                    if(n->getOncle()->getColor() == 1) {
                        insertion_cas3(n);
                    }
                } else /*if (n->getGrandParent() != NULL && n->getGrandParent()->getGauche() != NULL && n->getGrandParent()->getGauche()->getDroite() != NULL)*/{
                    std::cout << "repareArbre() fourth condition called " << std::endl;
                    insertion_cas4(n);
                }
                /*else {
                    std::cout << "toutes les conditions non envisagés" << std::endl;
                }*/
        }
        /* insertion d'un éléments quand N is the root node, i.e., first node of red–black tree
         The current node N is at the root of the tree. In this case, it is repainted black to satisfy property 2 (the root is black).
         Since this adds one black node to every path at once, property 5 (all paths from any given node to its leaf nodes contain
         the same number of black nodes) is not violated.
         */
        void insertion_cas1 (std::shared_ptr <TNode<K, T>> n) {
            if (n->getParent() == NULL)
                n->setColor(0);
        }
        /* insertion d'un éléments quand N's parent (P) is black
         * The current node's parent P is black, so property 4 (both children of every red node are black) is not invalidated.
         * In this case, the tree is still valid. Property 5 (all paths from any given node to its leaf nodes contain the same number of black nodes) is not threatened,
         * because the current node N has two black leaf children, but because N is red, the paths through each of its children have the same number of black nodes as the path through the leaf it replaced,
         * which was black, and so this property remains satisfied.
         */
        void insertion_cas2 (std::shared_ptr <TNode<K, T>> n) {
            return; /* Ne rien faire puisque l'arbre est bien un arbre rouge-noir */
        }
        /* insertion d'un éléments quand P is red (so it can't be the root of the tree) and N's uncle (U) is red
         * If both the parent P and the uncle U are red, then both of them can be repainted black and the grandparent G becomes red to maintain property 5
         * (all paths from any given node to its leaf nodes contain the same number of black nodes).
         * Since any path through the parent or uncle must pass through the grandparent, the number of black nodes on these paths has not changed.
         * However, the grandparent G may now violate Property 2 (The root is black) if it is the root or Property 4 (Both children of every red node are black) if it has a red parent.
         * To fix this, the tree's red-black repair procedure is rerun on G.
         */
        void insertion_cas3 (std::shared_ptr <TNode<K, T>> n) {
            n->getParent()->setColor(0);
            n->getOncle()->setColor(0);
            n->getGrandParent()->setColor(1);
            repareArbre(n->getGrandParent()); // A VERIF
        }
        /* insertion d'un éléments quand P is red and U is black
         * The parent P is red but the uncle U is black.
         * The ultimate goal will be to rotate the current node into the grandparent position, but this will not work if
         * the current node is on the "inside" of the subtree under G (i.e., if N is the left child of the right child of the grandparent or the right child of the left child of the grandparent).
         * In this case, a left rotation on P that switches the roles of the current node N and its parent P can be performed.
         * The rotation causes some paths (those in the sub-tree labelled "1") to pass through the node N where they did not before.
         * It also causes some paths (those in the sub-tree labelled "3") not to pass through the node P where they did before.
         * However, both of these nodes are red, so property 5 (all paths from any given node to its leaf nodes contain the same number of black nodes) is not violated by the rotation.
         * After this step has been completed, property 4 (both children of every red node are black) is still violated, but now we can resolve this by continuing to step 2.
         */
        void insertion_cas4 (std::shared_ptr <TNode<K, T>> n) {
            std::shared_ptr <TNode<K, T>> p = n->getParent();
            std::shared_ptr <TNode<K, T>> g = n->getGrandParent();
            if(n->getGrandParent() != NULL && n->getGrandParent()->getGauche() != NULL && n->getGrandParent()->getGauche()->getDroite() != NULL) {
                std::cout << "insertion_cas4etape1 called" << std::endl;
                if (n == n->getGrandParent()->getGauche()->getDroite()) {
                    n->getParent()->rotation_gauche();
                    n = n->getGauche();
                } else if (n == n->getGrandParent()->getDroite()->getGauche()) {
                    n->getParent()->rotation_droite();
                    n = n->getDroite();
                }
                //insertion_cas4etape2(n);
            }
            else {
                std::cout << "insertion_cas4 ne peut pas être appliqué car le grand-parent ou le fils gauche du grand-parent ou le fils droit du fils gauche du grand parent est null" << std::endl;
                std::cout << "insertion_cas4etape2 called" << std::endl;
                insertion_cas4etape2(n);
            }
        }
        /* équilibre les valeurs de l'arbre 2
         * The current node N is now certain to be on the "outside" of the subtree under G (left of left child or right of right child).
         * In this case, a right rotation on G is performed; the result is a tree where the former parent P is now the parent of both the current node N and the former grandparent G.
         * G is known to be black, since its former child P could not have been red without violating property 4.
         * Once the colors of P and G are switched, the resulting tree satisfies property 4 (both children of every red node are black).
         * Property 5 (all paths from any given node to its leaf nodes contain the same number of black nodes) also remains satisfied,
         * since all paths that went through any of these three nodes went through G before, and now they all go through P
         */
        void insertion_cas4etape2 (std::shared_ptr <TNode<K, T>> n) {
            if (n == n->getParent()->getGauche()) {
                n->getGrandParent()->rotation_droite();
            }
            else {
                if(n->getGrandParent() != NULL) {
                    std::cout << "insertion_cas4etape2 check 1.1 called" << std::endl;
                    n->getGrandParent()->rotation_gauche();
                    n->getParent()->setColor(0);
                    n->getGrandParent()->setColor(1);
                }
                else {
                    std::cout << "insertion_cas4etape2 check 1.2 called\n==> Ce cas n'est pas gere ::(" << std::endl;

                }
            }
        }
        void delete_one_child(std::shared_ptr <TNode<K, T>> n) {
            /*
             * Precondition: n has at most one non-leaf child.
             */
            std::shared_ptr <TNode<K, T>> child = is_feuille(n->getDroite()) ? n->getGauche() : n->getDroite();

            std::swap(n, child); // replace_node(n, child);
            if (n->getColor() == 0) {
                if (child->getColor() == 1)
                    child->setColor(0);
                else
                    delete_case1(child);
            }

        }
        /*
         * N is the new root. In this case, we are done. We removed one black node from every path, and the new root is black, so the properties are preserved.
         */
        void delete_case1(std::shared_ptr <TNode<K, T>> n) {
            if (n->getParent() != NULL)
                delete_case2(n);
        }
        /*
         * S is red. In this case we reverse the colors of P and S, and then rotate left at P, turning S into N's grandparent.
         * Note that P has to be black as it had a red child. The resulting subtree has a path short one black node so we are not done.
         * Now N has a black sibling and a red parent, so we can proceed to step 4, 5, or 6. (Its new sibling is black because it was once the child of the red S.)
         * In later cases, we will relabel N's new sibling as S.
         */
        void delete_case2(std::shared_ptr <TNode<K, T>> n) {
            std::shared_ptr <TNode<K, T>> s = n->getEnfantDuMParent();

            if (s->getColor() == 1) {
                n->getParent()->setColor(1);
                s->setColor(0);
                if (n == n->getParent()->getGauche())
                    n->getParent()->rotation_gauche();
                else
                    n->getParent()->rotation_droite();
            }
            delete_case3(n);
        }
        /*
         *  P, S, and S's children are black. In this case, we simply repaint S red.
         *  The result is that all paths passing through S, which are precisely those paths not passing through N, have one less black node.
         *  Because deleting N's original parent made all paths passing through N have one less black node, this evens things up. However,
         *  all paths through P now have one fewer black node than paths that do not pass through P, so property 5 (all paths from any given node to its leaf nodes contain the same number of black nodes) is still violated.
         *  To correct this, we perform the rebalancing procedure on P, starting at case 1.
         */
        void delete_case3(std::shared_ptr <TNode<K, T>> n) {
            std::shared_ptr <TNode<K, T>> s = n->getEnfantDuMParent();

            if ((n->getParent()->getColor() == 0) &&
                (s->getColor() == 0) &&
                (s->getGauche()->getColor() == 0) &&
                (s->getDroite()->getColor() == 0)) {
                s->setColor(1);
                delete_case1(n->getParent());
            } else
                delete_case4(n);
        }
        /*
         * S and S's children are black, but P is red. In this case, we simply exchange the colors of S and P.
         * This does not affect the number of black nodes on paths going through S, but it does add one to the number of black nodes on paths going through N, making up for the deleted black node on those paths.
         */
        void delete_case4(std::shared_ptr <TNode<K, T>> n) {
            std::shared_ptr <TNode<K, T>> s = n->getEnfantDuMParent();

            if ((n->getParent()->getColor() == 1) &&
                (s->getColor() == 0) &&
                (s->getGauche()->getColor() == 0) &&
                (s->getDroite()->getColor() == 0)) {
                s->setColor(1);
                n->getParent()->setColor(0);
            } else
                delete_case5(n);
        }
        /*
         * S is black, S's left child is red, S's right child is black, and N is the left child of its parent.
         * In this case we rotate right at S, so that S's left child becomes S's parent and N's new sibling.
         * We then exchange the colors of S and its new parent. All paths still have the same number of black nodes,
         * but now N has a black sibling whose right child is red, so we fall into case 6. Neither N nor its parent are affected by this transformation. (Again, for case 6, we relabel N's new sibling as S.)
         */
        void delete_case5(std::shared_ptr <TNode<K, T>> n) {
            std::shared_ptr <TNode<K, T>> s = n->getEnfantDuMParent();

            if  (s->getColor() == 0) { /* this if statement is trivial,
        due to case 2 (even though case 2 changed the sibling to a sibling's child,
        the sibling's child can't be red, since no red parent can have a red child). */
        /* the following statements just force the red to be on the left of the left of the parent,
           or right of the right, so case six will rotate correctly. */
                if ((n == n->getParent()->getGauche()) &&
                    (s->getDroite()->getColor() == 0) &&
                    (s->getGauche()->getColor() == 1)) { /* this last test is trivial too due to cases 2-4. */
                    s->setColor(1);
                    s->getGauche()->setColor(0);
                    n->getEnfantDuMParent()->rotation_droite();
                } else if ((n == n->getParent()->getDroite()) &&
                           (s->getGauche()->getColor() == 0) &&
                           (s->getDroite()->getColor() == 1)) {/* this last test is trivial too due to cases 2-4. */
                    s->setColor(1);
                    s->getDroite()->setColor(0);
                    n->getEnfantDuMParent()->rotation_gauche();
                }
            }
            delete_case6(n);
        }
        /*
         * S is black, S's right child is red, and N is the left child of its parent P. In this case we rotate left at P, so that S becomes the parent of P and S's right child. We then exchange the colors of P and S, and make S's right child black. The subtree still has the same color at its root, so Properties 4 (Both children of every red node are black) and 5 (All paths from any given node to its leaf nodes contain the same number of black nodes) are not violated. However, N now has one additional black ancestor: either P has become black, or it was black and S was added as a black grandparent. Thus, the paths passing through N pass through one additional black node.
         * Meanwhile, if a path does not go through N, then there are two possibilities:
         * It goes through N's new sibling SL, a node with arbitrary color and the root of the subtree labeled 3 (s. diagram). Then, it must go through S and P, both formerly and currently, as they have only exchanged colors and places. Thus the path contains the same number of black nodes.
         * It goes through N's new uncle, S's right child. Then, it formerly went through S, S's parent, and S's right child SR (which was red), but now only goes through S, which has assumed the color of its former parent, and S's right child, which has changed from red to black (assuming S's color: black). The net effect is that this path goes through the same number of black nodes.
         * Either way, the number of black nodes on these paths does not change. Thus, we have restored Properties 4 (Both children of every red node are black) and 5 (All paths from any given node to its leaf nodes contain the same number of black nodes). The white node in the diagram can be either red or black, but must refer to the same color both before and after the transformation.
         */
        void delete_case6(std::shared_ptr <TNode<K, T>> n) {
            std::shared_ptr <TNode<K, T>> s = n->getEnfantDuMParent();

            s->setColor(n->getParent()->getColor());
            n->getParent()->setColor(0);

            if (n == n->getParent()->getGauche()) {
                s->getDroite()->setColor(0);
                n->getParent()->rotation_gauche();
            } else {
                s->getGauche()->setColor(0);
                n->getParent()->rotation_droite();
            }
        }

        /* Element access */
        // retourne la valeur correspondant à la key passé entre [key]
        T operator[](K&& key) {
            std::cout << "operator[](K&& key) called" << std::endl;
            if(racine != NULL) {
                if(racine->getPair().getKey() == key) {
                    return racine->getPair().getItem();
                }
                else {
                    std::shared_ptr <TNode<K, T>> node_nxt_g = racine;
                    std::shared_ptr <TNode<K, T>> node_nxt_d = racine;
                    std::shared_ptr <TNode<K, T>> node_current = NULL;
                        // On parcours tous les fils gauche jusqu'au dernier et on supprime en remontant
                        while(node_nxt_g != NULL) {
                            node_current = node_nxt_g;
                            if(node_current->getPair().getKey() == key) {
                                std::cout << "node_current->getPair().getKey() = " << node_current->getPair().getKey() << std::endl;
                                std::cout << "key = " << key << std::endl;
                                return node_current->getPair().getItem();
                            }
                            else {
                                node_nxt_g = node_nxt_g->getGauche();
                            }
                        }
                        // On parcours tous les fils gauche jusqu'au dernier  et on supprime en remontant
                        while(node_nxt_d != NULL) {
                            node_current = node_nxt_d;
                            if(node_current->getPair().getKey() == key) {
                                std::cout << "node_current->getPair().getKey() = " << node_current->getPair().getKey() << std::endl;
                                std::cout << "key = " << key << std::endl;
                                return node_current->getPair().getItem();
                            }
                            else {
                                node_nxt_d = node_nxt_d->getDroite();
                            }
                        }
                    }
            }
        }
        T operator[](const K& key) {
            std::cout << "operator[](const K& key) called" << std::endl;
        if(racine != NULL) {
            if(racine->getPair().getKey() == key) {
                return racine->getPair().getItem();
            }
            else {
                std::shared_ptr <TNode<K, T>> node_nxt_g = racine;
                std::shared_ptr <TNode<K, T>> node_nxt_d = racine;
                std::shared_ptr <TNode<K, T>> node_current = NULL;
                // On parcours tous les fils gauche jusqu'au dernier et on supprime en remontant
                while(node_nxt_g != NULL) {
                    node_current = node_nxt_g;
                    if(node_current->getPair().getKey() == key) {
                        std::cout << "node_current->getPair().getKey() = " << node_current->getPair().getKey() << std::endl;
                        std::cout << "key = " << key << std::endl;
                        return node_current->getPair().getItem();
                    }
                    else {
                        node_nxt_g = node_nxt_g->getGauche();
                    }
                }
                // On parcours tous les fils gauche jusqu'au dernier  et on supprime en remontant
                while(node_nxt_d != NULL) {
                    node_current = node_nxt_d;
                    if(node_current->getPair().getKey() == key) {
                        std::cout << "node_current->getPair().getKey() = " << node_current->getPair().getKey() << std::endl;
                        std::cout << "key = " << key << std::endl;
                        return node_current->getPair().getItem();
                    }
                    else {
                        node_nxt_d = node_nxt_d->getDroite();
                    }
                }
            }
        }
    }
        // retourne l'élement correspondant à la key passée à at(key)
        T at(K& key){
            std::cout << "\nat(K& key) called" << std::endl;
            if(racine != NULL) {
                if(racine->getPair().getKey() == key) {
                    return racine->getPair().getItem();
                }
                else {
                    std::shared_ptr <TNode<K, T>> node_nxt_g = racine;
                    std::shared_ptr <TNode<K, T>> node_nxt_d = racine;
                    std::shared_ptr <TNode<K, T>> node_current = NULL;
                    // On parcours tous les fils gauche jusqu'au dernier et on supprime en remontant
                    while(node_nxt_g != NULL) {
                        node_current = node_nxt_g;
                        if(node_current->getPair().getKey() == key) {
                            std::cout << "node_current->getPair().getKey() = " << node_current->getPair().getKey() << std::endl;
                            std::cout << "key = " << key << std::endl;
                            return node_current->getPair().getItem();
                        }
                        else {
                            node_nxt_g = node_nxt_g->getGauche();
                        }
                    }
                    // On parcours tous les fils gauche jusqu'au dernier  et on supprime en remontant
                    while(node_nxt_d != NULL) {
                        node_current = node_nxt_d;
                        if(node_current->getPair().getKey() == key) {
                            std::cout << "node_current->getPair().getKey() = " << node_current->getPair().getKey() << std::endl;
                            std::cout << "key = " << key << std::endl;
                            return node_current->getPair().getItem();
                        }
                        else {
                            node_nxt_d = node_nxt_d->getDroite();
                        }
                    }
                }
            }
        }
        T at(const K& key) const {
            std::cout << "\nat(const K& key) called" << std::endl;
            if(racine != NULL) {
                if(racine->getPair().getKey() == key) {
                    return racine->getPair().getItem();
                }
                else {
                    std::shared_ptr <TNode<K, T>> node_nxt_g = racine;
                    std::shared_ptr <TNode<K, T>> node_nxt_d = racine;
                    std::shared_ptr <TNode<K, T>> node_current = NULL;
                    // On parcours tous les fils gauche jusqu'au dernier et on supprime en remontant
                    while(node_nxt_g != NULL) {
                        node_current = node_nxt_g;
                        if(node_current->getPair().getKey() == key) {
                            std::cout << "node_current->getPair().getKey() = " << node_current->getPair().getKey() << std::endl;
                            std::cout << "key = " << key << std::endl;
                            return node_current->getPair().getItem();
                        }
                        else {
                            node_nxt_g = node_nxt_g->getGauche();
                        }
                    }
                    // On parcours tous les fils gauche jusqu'au dernier  et on supprime en remontant
                    while(node_nxt_d != NULL) {
                        node_current = node_nxt_d;
                        if(node_current->getPair().getKey() == key) {
                            std::cout << "node_current->getPair().getKey() = " << node_current->getPair().getKey() << std::endl;
                            std::cout << "key = " << key << std::endl;
                            return node_current->getPair().getItem();
                        }
                        else {
                            node_nxt_d = node_nxt_d->getDroite();
                        }
                    }
                }
            }
        }
        /* capacity */
        // Teste si la map est vide
        bool isEmpty() const noexcept {
            if (racine == NULL) {
                std::cout << "racine nulle" << std::endl;
                return true;
            }
            else {
                std::cout << "racine non nulle" << std::endl;
                return false;
            }
        }

        /* Modifiers */
        // Supprime l'intervalle d'élement à partir du premier élement de key firt et le dernier élement de key last
        MyIterator<K, T>  erase(const MyIterator<K, T> position) {
            std::cout << "erase() called" << std::endl;
            if(racine != NULL) {
                if(racine->getPair().getKey() == position.getRoot()->getPair().getKey()) {
                   racine.reset();
                    std::cout << "node erased" << std::endl;
                }
                else {
                    std::shared_ptr <TNode<K, T>> node_nxt_g = racine;
                    std::shared_ptr <TNode<K, T>> node_nxt_d = racine;
                    std::shared_ptr <TNode<K, T>> node_current = NULL;
                    // On parcours tous les fils gauche jusqu'au dernier et on supprime en remontant
                    while(node_nxt_g != NULL) {
                        node_current = node_nxt_g;
                        if(node_current->getPair().getKey() == position.getRoot()->getPair().getKey()) {
                            //delete node_current;
                            node_current.reset();
                            std::cout << "node erased" << std::endl;
                        }
                        else {
                            node_nxt_g = node_nxt_g->getGauche();
                        }
                    }
                    // On parcours tous les fils gauche jusqu'au dernier  et on supprime en remontant
                    while(node_nxt_d != NULL) {
                        node_current = node_nxt_d;
                        if(node_current->getPair().getKey() == position.getRoot()->getPair().getKey()) {
                            //delete node_current;
                            node_current.reset();
                            std::cout << "node erased" << std::endl;
                        }
                        else {
                            node_nxt_d = node_nxt_d->getDroite();
                        }
                    }
                }
            }
        };
        int erase (const K& key) {
            std::cout << "erase() called" << std::endl;
            if(racine != NULL) {
                if(racine->getPair().getKey() == key) {
                    racine.reset();
                    std::cout << "node erased" << std::endl;
                }
                else {
                    std::shared_ptr <TNode<K, T>> node_nxt_g = racine;
                    std::shared_ptr <TNode<K, T>> node_nxt_d = racine;
                    std::shared_ptr <TNode<K, T>> node_current = NULL;
                    // On parcours tous les fils gauche jusqu'au dernier et on supprime en remontant
                    while(node_nxt_g != NULL) {
                        node_current = node_nxt_g;
                        if(node_current->getPair().getKey() == key) {
                            //delete node_current;
                            node_current.reset();
                            std::cout << "node erased" << std::endl;
                        }
                        else {
                            node_nxt_g = node_nxt_g->getGauche();
                        }
                    }
                    // On parcours tous les fils gauche jusqu'au dernier  et on supprime en remontant
                    while(node_nxt_d != NULL) {
                        node_current = node_nxt_d;
                        if(node_current->getPair().getKey() == key) {
                            //delete node_current;
                            node_current.reset();
                            std::cout << "node erased" << std::endl;
                        }
                        else {
                            node_nxt_d = node_nxt_d->getDroite();
                        }
                    }
                }
            }
        }
        MyIterator<K, T>  erase (const MyIterator<K, T> first, const MyIterator<K, T> last) {
            if(racine != NULL) {
                std::shared_ptr <TNode<K, T>> node_first = NULL;
                std::shared_ptr <TNode<K, T>> node_last = NULL;
                // si l'intervalle correspond à la racine (first=last)
                if(racine->getPair().getKey() == first.getRoot()->getPair().getKey() &&
                        racine->getPair().getKey() == last.getRoot()->getPair().getKey()) {
                    racine.reset(); // on supprime la racine
                }
                else {
                    // sinon on parcours jusqu'a trouvé le node_first et le node_last
                    std::shared_ptr <TNode<K, T>> node_nxt_g = racine;
                    std::shared_ptr <TNode<K, T>> node_nxt_d = racine;
                    std::shared_ptr <TNode<K, T>> node_current = NULL;
                    // On parcours tous les fils gauche jusqu'au dernier et on supprime en remontant
                    while(node_nxt_g != NULL) {
                        node_current = node_nxt_g;
                        if(node_current->getPair().getKey() == first.getRoot()->getPair().getKey()) {
                            node_first = node_current;
                        }
                        else if (node_current->getPair().getKey() == last.getRoot()->getPair().getKey()) {
                            node_last = node_current;
                        }
                        else {
                            node_nxt_g = node_nxt_g->getGauche();
                        }
                    }
                    // On parcours tous les fils gauche jusqu'au dernier  et on supprime en remontant
                    while(node_nxt_d != NULL) {
                        node_current = node_nxt_g;
                        if(node_current->getPair().getKey() == first.getRoot()->getPair().getKey()) {
                            node_first = node_current;
                        }
                        else if (node_current->getPair().getKey() == last.getRoot()->getPair().getKey()) {
                            node_last = node_current;
                        }
                        else {
                            node_nxt_g = node_nxt_g->getDroite();
                        }
                    }
                    // On supprime l'intervalle des TNode entre le last et le first
                    std::shared_ptr <TNode<K, T>> node_del = node_last;
                    node_current = node_last;
                    while(node_current->getParent()->getPair().getKey() != node_first->getParent()->getPair().getKey()) {
                        //delete node_current;
                        node_current.reset();
                        node_current = node_current->getParent();
                    }
                    //delete node_first;
                    node_first.reset();
                    std::cout << "range node erases" << std::endl;
                }
            }
        };
        // Supprime tous les élements d'une map et met la taille à zéro
        void deleteAllElement() {
            std::shared_ptr <TNode<K, T>> node_nxt_g = racine;
            std::shared_ptr <TNode<K, T>> node_nxt_d = racine;
            std::shared_ptr <TNode<K, T>> node_current = NULL;
            if(node_nxt_g != NULL) {
                // On parcours tous les fils gauche jusqu'au dernier et on supprime en remontant
                while(node_nxt_g != NULL) {
                    node_current = node_nxt_g;
                    node_nxt_g = node_nxt_g->getGauche();
                    //delete node_current;
                    node_current.reset();
                    std::cout << "node erased" << std::endl;
                }
                // On parcours tous les fils gauche jusqu'au dernier  et on supprime en remontant
                while(node_nxt_d != NULL) {
                    node_current = node_nxt_d;
                    node_nxt_d = node_nxt_d->getDroite();
                    //delete node_current;
                    node_current.reset();
                    std::cout << "node erased" << std::endl;
                }
                // On supprime la racine
                racine.reset();
                std::cout << "racine count " << racine.use_count() << std::endl;
            }
        }
        // construit et insère l'élement et renvoie une TPair de l'iterator vers le nouvel élement et la valeur true sinon un iterator vers un élement équivalent et une valeur false
        TPair<MyIterator<K, T>, bool> emplace(K key, T val) {
            this->insertion_recursif(racine, std::shared_ptr<TNode<K, T>>(new TNode<K, T>(key, val)));
        };
        // construit et insère l'élement à la position de l'iterator et renvoie un iterator vers l'élement inséré
        MyIterator<K, T> emplace_hint(MyIterator<K, T> it, K key, T val) {
            /* On insère l'objet en le construisant à l'emplacement correspondant à l'iterator */
            std::shared_ptr <TNode<K, T>> parent = nullptr;
            std::shared_ptr <TNode<K, T>> fils_good = nullptr;

            // on récupère le parent du Node pointé par it
            parent = it.getRoot().get()->getParent();

            // On vérifie si le node est une feuille
            if (is_feuille(it.getRoot())) {
                // le fils gauche deviendra le fils_good
                parent.get()->setGauche(std::shared_ptr<TNode<K, T>>(new TNode<K, T>(key, val)));
                // On fait pointée le fils gauche du nouveau node vers le node pointée par l'itérateur
                parent.get()->getGauche().get()->setGauche(it.getRoot());
            }
            else {
                // sinon le fils droit deviendra le fils good
                parent.get()->setDroite(std::shared_ptr<TNode<K, T>>(new TNode<K, T>(key, val)));
                // On fait pointée le fils droit du nouveau node vers le node pointée par l'itérateur
                parent.get()->getDroite().get()->setDroite(it.getRoot());
            }
            it.setRoot(parent.get()->getDroite().get()->getDroite());
            return it;
        }

        /* Observers */
        /* retourne une copie de l'objet de comparaison de clé (3eme argument de la template)
         * Returns a copy of the comparison object used by the container to compare keys.
         * The comparison object of a map object is set on construction. Its type (member key_compare) is the third template parameter of the map template. By default, this is a less object, which returns the same as operator<.
         * This object determines the order of the elements in the container: it is a function pointer or a function object that takes two arguments of the same type as the element keys, and returns true if the first argument is considered to go before the second in the strict weak ordering it defines, and false otherwise.
         * Two keys are considered equivalent if key_comp returns false reflexively (i.e., no matter the order in which the keys are passed as arguments).
         */
        Compare key_comp() const {
            return getKey_compare();
        }
        /* retourne une copie de l'objet de comparaison de valeur (3eme argument de la template)
         * Returns a comparison object that can be used to compare two elements to get whether the key of the first one goes before the second.
         * The public member of this comparison class returns true if the key of the first argument is considered to go before that of the
         * second (according to the strict weak ordering specified by the container's comparison object, key_comp), and false otherwise.
         */
        Compare value_comp() const {
            return getValue_compare();
        }

        /* Operations */
        // cherche un container portant la clé spécifié et retourne un iterator vers lui sinon retourne un iterator vers mpap::end
        MyIterator<K, T>* find(K key){
            std::cout << "\nfind(K key) called" << std::endl;
            if(racine != NULL) {
                if(racine->getPair().getKey() == key) {
                    return new MyIterator<K, T>(racine);
                }
                else {
                    std::shared_ptr <TNode<K, T>> node_nxt_g = racine;
                    std::shared_ptr <TNode<K, T>> node_nxt_d = racine;
                    std::shared_ptr <TNode<K, T>> node_current = NULL;
                    // On parcours tous les fils gauche jusqu'au dernier et on supprime en remontant
                    while(node_nxt_g != NULL) {
                        node_current = node_nxt_g;
                        if(node_current->getPair().getKey() == key) {
                            return new MyIterator<K, T>(node_current);
                        }
                        else {
                            node_nxt_g = node_nxt_g->getGauche();
                        }
                    }
                    // On parcours tous les fils gauche jusqu'au dernier  et on supprime en remontant
                    while(node_nxt_d != NULL) {
                        node_current = node_nxt_d;
                        if(node_current->getPair().getKey() == key) {
                            return new MyIterator<K, T>(node_current);
                        }
                        else {
                            node_nxt_d = node_nxt_d->getDroite();
                        }
                    }
                }
            }
        }
        int count(K& key){} // retourne le nombre d'élement portant la clé spécifié ( ne retourne que 1 si trouvé ou 0)
        MyIterator<K, T> lower_bound(){} // retourne un itérateur pointant sur le premier élement du conteneur  dont la clé est équivalent ou va avant celle passé en paramètre
        const MyIterator<K, T> lower_bound() const{} // retourne un itérateur pointant sur le premier élement du conteneur  dont la clé est équivalent ou va avant celle passé en paramètre
        MyIterator<K, T> upper_bound(){} // retourne un itérateur pointant sur le premier élement du conteneur  dont la clé va après celle passé en paramètre
        const MyIterator<K, T> upper_bound() const{} // retourne un itérateur pointant sur le premier élement du conteneur  dont la clé va après celle passé en paramètre
        // renvoie une TPair< TMap<K, T>::iterator_lower_bound, TMap<K, T>::iteratoriterator_upper_bound> > par rapport à la clé passé en paramère
        TPair<MyMap<K, T>, MyMap<K, T>>* equal_range(K& key) {
            return new TPair<K, T>(lower_bound(), upper_bound());
        }
        // renvoie une TPair< TMap<K, T>::iterator_lower_bound, TMap<K, T>::iteratoriterator_upper_bound> > par rapport à la clé passé en paramère
        TPair<const MyMap<K, T>, const MyMap<K, T>>* equal_range(K& key) const {
            return new TPair<K, T>(lower_bound(), upper_bound());
        }

    /* Méthodes et Fonctions externes/friend */
        // stream, envoie l'objet TMap dans le flux cout pour l'afficher
        friend std::ostream &operator<<(std::ostream &os, const MyMap &map) {
            os << "adresse node racine: " << map.racine;
            if(map.racine == nullptr) {
                os << "\nobjet node racine: null";
            }
            else {
                os << "\nobjet node racine: \n" << *map.racine;
            }
            os << std::endl;
        return os;
        }
        // swap pour permuter 2 MyMap (taille peut être différente
        friend void swap(const MyMap<K, T> &tm1, const MyMap<K, T> &tm2) {
            std::swap(tm1.racine, tm2.racine);
            std::swap(tm1.size, tm2.size);
            std::swap(tm1.maxSize, tm2.maxSize);
            std::swap(tm1.key_compare, tm2.key_compare);
            std::swap(tm1.value_compare, tm2.value_compare);
            std::swap(tm1.it, tm2.it);
        }
        friend void swap(MyMap<K, T> &tm1, MyMap<K, T> &tm2) {
        std::swap(tm1.racine, tm2.racine);
        std::swap(tm1.size, tm2.size);
        std::swap(tm1.maxSize, tm2.maxSize);
        std::swap(tm1.key_compare, tm2.key_compare);
        std::swap(tm1.value_compare, tm2.value_compare);
        std::swap(tm1.it, tm2.it);
    }
        /* Parcours de la Map */
        // parcours la racine, puis les fils gauche et enfin les fils droit
        friend void parcours_Prefixe(std::shared_ptr <TNode<K, T>> racine) {
            if(racine != NULL) {
                std::cout << *racine << std::endl;
                parcours_Prefixe(racine->getGauche());
                parcours_Prefixe(racine->getDroite());
            }
        }
        // parcours la racine, puis les fils gauche et enfin les fils droit
        friend void parcours_Infixe(std::shared_ptr <TNode<K, T>> racine) {
            if(racine != NULL) {
                parcours_Infixe(racine->getGauche());
                std::cout << *racine << std::endl;
                parcours_Infixe(racine->getDroite());
            }
        }
        // parcours la racine, puis les fils gauche et enfin les fils droit
        friend void parcours_Postfixe(std::shared_ptr <TNode<K, T>> racine) {
            if(racine != NULL) {
                parcours_Postfixe(racine->getGauche());
                parcours_Postfixe(racine->getDroite());
                std::cout << *racine << std::endl;
            }
        }
        /* Affichage de la Map */
        // affiche la racine, puis les fils gauche et enfin les fils droit
        friend void display_Prefixe(std::shared_ptr <TNode<K, T>> _racine) {
            if(_racine != NULL) {
                if(_racine->getParent() == NULL) {
                    std::cout << "Noeud Parent->";
                }
                std::cout << "Noeud " << *_racine->getPair().getKey() << "\n" << *_racine << std::endl;
                parcours_Prefixe(_racine->getGauche());
                parcours_Prefixe(_racine->getDroite());
            }
        }
        // affiche la racine, puis les fils gauche et enfin les fils droit
        friend void display_Infixe(std::shared_ptr <TNode<K, T>> racine) {
            if(racine != NULL) {
                std::cout << "Noeud " << *racine->getPair().getKey() << "\n" << *racine << std::endl;
                parcours_Infixe(racine->getGauche());
                if(racine->getParent() == NULL) {
                    std::cout << "Noeud Parent->";
                    std::cout << *racine << std::endl;
                }
                parcours_Infixe(racine->getDroite());
            }
        }
        // affiche la racine, puis les fils gauche et enfin les fils droit
        friend void display_Postfixe(std::shared_ptr <TNode<K, T>> racine) {
            if(racine != NULL) {
                std::cout << "Noeud " << *racine->getPair().getKey() << "\n" << *racine << std::endl;
                parcours_Postfixe(racine->getGauche());
                parcours_Postfixe(racine->getDroite());
                if(racine->getParent() == NULL) {
                    std::cout << "Noeud Parent->";
                    std::cout << *racine << std::endl;
                }
            }
        }


    /* Fonctions de parcours avec itérateurs et pile */
    // begin : Renvoie le TNode* correspondant au premier élément de la map (1er TNode à gauche de la racine) sinon renvoie la racine
    std::shared_ptr <TNode<K, T>> begin_pp() {
        std::cout << "begin_pp() called" << std::endl;
        try {
            if(racine->getGauche() == NULL)
                throw std::string("le 1er node gauche est null");
            else {
                return racine->getGauche();
            }
        }
        catch(std::string const& chaine) {
            std::cerr << chaine << std::endl;
            return racine;
        }
    }
    // end : Renvoie le TNode* correspondant au dernier élément de la map (dernier neoud à droite en bas) sinon renvoie null
    std::shared_ptr <TNode<K, T>> end_pp() {
        std::cout << "end_pp() called" << std::endl;
        try {
            if(racine.get()->getDroite() == NULL) {
                throw std::string("dernier noeud a droite en bas est null, NULL return");
            }
            else {
                std::shared_ptr<TNode<K, T>> n = racine->getDroite();
                while (n != NULL) {
                    n = n->getDroite();
                }
                return n;
            }
        }
        catch(std::string const& chaine) {
            std::cerr << chaine << std::endl;
            return NULL;
        }
    }
    // rbegin : Renvoie le TNode* correspondant au  premier élément de la map avec éléments inversés sinon renvoie la racine
    std::shared_ptr <TNode<K, T>> rbegin_pp() {
        std::cout << "rbegin_pp() called" << std::endl;
        try {
            if(racine.get()->getDroite() == NULL) {
                throw std::string("le 1er element de la map avec element inverses est null, racine return");
            }
            else {
                std::shared_ptr<TNode<K, T>> n = racine->getDroite();
                while (n != NULL) {
                    n = n->getDroite();
                }
                return n;
            }
        }
        catch(std::string const& chaine) {
            std::cerr << chaine << std::endl;
            return racine;
        }
    }
    // rend : Renvoie le TNode* correspondant au  dernier élément de la map avec éléments inversés sinon renvoie NULL
    std::shared_ptr <TNode<K, T>> rend_pp() {
        std::cout << "rend_pp() called" << std::endl;
        try {
            if(racine.get()->getDroite() == NULL) {
                throw std::string("le dernier element de la map avec element inverses est null, NULL return");
            }
            else {
                std::shared_ptr<TNode<K, T>> n = racine->getGauche();
                while (n != NULL) {
                    n = n->getGauche();
                }
                return n;
            }
        }
        catch(std::string const& chaine) {
            std::cerr << chaine << std::endl;
            return NULL;
        }
    }
    // cbegin : Renvoie le const TNode* correspondant au premier élément de la map sinon renvoie la racine
    const std::shared_ptr <TNode<K, T>> cbegin_pp() {
        std::cout << "cbegin_pp() called" << std::endl;
        try {
            if(racine->getGauche() == NULL)
                throw std::string("le 1er element de la map est null, racine return");
            else {
                return racine->getGauche();
            }
        }
        catch(std::string const& chaine) {
            std::cerr << chaine << std::endl;
            return racine;
        }
    }
    // cend : Renvoie le const TNode* correspondant au  dernier élément de la map sinon renvoie NULL
    const std::shared_ptr <TNode<K, T>> cend_pp() {
        std::cout << "cend_pp() called" << std::endl;
        try {
            if(racine.get()->getDroite() == NULL) {
                throw std::string("le dernier element de la map est null, NULL return");
            }
            else {
                std::shared_ptr<TNode<K, T>> n = racine->getDroite();
                while (n != NULL) {
                    n = n->getDroite();
                }
                return n;
            }
        }
        catch(std::string const& chaine) {
            std::cerr << chaine << std::endl;
            return racine;
        }
    }
    // crbegin : Renvoie le const TNode* correspondant au  premier élément de la map avec éléments inversés sinon renvoie la racine
    const std::shared_ptr <TNode<K, T>> crbegin_pp() {
        std::cout << "crbegin_pp() called" << std::endl;
        try {
            if(racine.get()->getDroite() == NULL) {
                throw std::string("le 1er element de la map avec element inverse est null, racine return");
            }
            else {
                std::shared_ptr<TNode<K, T>> n = racine->getDroite();
                while (n != NULL) {
                    n = n->getDroite();
                }
                return n;
            }
        }
        catch(std::string const& chaine) {
            std::cerr << chaine << std::endl;
            return racine;
        }
    }
    // crend : Renvoie le const TNode* correspondant au  dernier élément de la map avec éléments inversés sinon renvoie NULL
    const std::shared_ptr <TNode<K, T>> crend_pp() {
        std::cout << "crend_pp() called" << std::endl;
        try {
            if(racine->getGauche() == NULL)
                throw std::string("le dernier element de la map avec element inverse est null, NULL return");
            else {
                return racine->getGauche();
            }
        }
        catch(std::string const& chaine) {
            std::cerr << chaine << std::endl;
            return NULL;
        }
    }


private :

    std::shared_ptr <TNode<K, T>> racine;   // pointeur racine
    size_t size;                            // taille du container
    size_t maxSize;                         // taille maximal du container
    Compare key_compare;                    // copie de l'objet de comparaison de clé
    Compare value_compare;                  // copie de l'objet de comparaison de valeur
    MyIterator<K, T> it;                    // iterator

};


#endif
