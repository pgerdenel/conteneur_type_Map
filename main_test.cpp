#include <iostream>
#include "MyMap.h"

int main() {

    /******************************************* TEST TPAIR ***********************************************************

        TPair<int, int>* tp_def = new TPair<int, int>();
        std::cout << *tp_def << std::endl;
        TPair<int, int>* tp_init = new TPair<int, int>(1, 102);
        TPair<int, int>* tp1_init = new TPair<int, int>(9, 99);
        TPair<char, char>* tp2_init = new TPair<char, char>('A', 'B');
        const TPair<char, char>* tp3_init = new TPair<char, char>('A', 'B');
        const TPair<char, char>* tp4_init = new TPair<char, char>('A', 'B');
        std::cout << *tp_init << std::endl;
        std::cout << tp2_init->calcSize() << std::endl;
        std::cout << tp2_init->giveType() << std::endl;
        swap(const_cast<TPair<int, int>&>(*tp_init), const_cast<TPair<int, int>&>(*tp1_init));

    ****************************************** FIN TEST TPAIR ********************************************************/

    /****************************************** TEST TNODE ************************************************************

        TNode<std::string, int>* tn_def = new TNode<std::string, int>();
        //std::cout << *tn_def << std::endl;
        TNode<int, int>* tn_init = new TNode<int, int>(TPair<int, int>(55, 65), std::shared_ptr <TNode<int, int>>(NULL), std::shared_ptr <TNode<int, int>>(NULL),std::shared_ptr <TNode<int, int>>(NULL), 0);
        TNode<int, int>* tn2_init = new TNode<int, int>(TPair<int, int>(88, 76), std::shared_ptr <TNode<int, int>>(NULL), std::shared_ptr <TNode<int, int>>(NULL),std::shared_ptr <TNode<int, int>>(NULL), 0);
        //tn_def->rotation_droite();
        //tn_def->rotation_gauche();
        swap(const_cast<TNode<int, int>&>(*tn_init), const_cast<TNode<int, int>&>(*tn2_init));

    ****************************************** FIN TEST TNODE ********************************************************/

    /****************************************** TEST MyMap ************************************************************/

        // création de la Map<int, int>
        TNode<int, int>* r = new TNode<int, int>(); // racine
        MyMap<int, int> mmap = MyMap<int, int>(std::shared_ptr <TNode<int, int>>(r), 1, 1);
        MyMap<int, int, std::less<int>> mmap2 = MyMap<int, int>();
        std::cout << "\nadresse racine init : " << mmap.getRacine() << std::endl;
        std::cout << "\n-map current : -\n" << mmap << std::endl;

        /* Test de fonctions
        std::cout << "\n\nTEST DE FONCTIONS" << std::endl;
        mmap.getSize();
        mmap.getMaxSize();
        mmap.getKey_compare();
        mmap.getValue_compare();

        std::cout << "\n-map current : -\n" << mmap << std::endl;

        const int a = 5563;
        std::cout << "element.getItem = " << mmap.getRacine()->getPair().getItem() << std::endl;
        std::cout << "element[a] = " << mmap[mmap.getRacine()->getPair().getKey()] << std::endl;

        std::cout << "element.at(a) = " << mmap.at(mmap.getRacine()->getPair().getKey()) << std::endl;
        mmap.isEmpty();*/


        /* iterator
        std::cout << "\n\nITERATOR" << std::endl;
        MyMap<int, int>::MyIterator<int, int> myIt = MyMap<int, int>::MyIterator<int, int>(mmap.getRacine());
        std::cout << *myIt.getRoot() << std::endl;
        //mmap.erase(myIt);
        //mmap.erase(mmap.getRacine()->getPair().getKey());
        //mmap.deleteAllElement();
        std::cout << "\n-map current 2 : -\n" << mmap << std::endl;
        mmap.begin_pp();
        mmap.end_pp();
        mmap.rbegin_pp();
        mmap.rend_pp();
        mmap.cbegin_pp();
        mmap.cend_pp();
        mmap.crbegin_pp();
        mmap.crend_pp();

        try {
                if(mmap.end_pp() == NULL) {
                        throw std::string("le 1er node et le dernier sont les memes");
                }
                else {
                        for (MyMap<int, int>::MyIterator<int, int> it = mmap.begin_pp(); it >= mmap.end_pp(); ++it) {
                                std::cout << "on est dans l'itération" << std::endl;
                                std::cout << "KEY = " << it.getFirst() << std::endl;// accede à la clé
                                std::cout << "ITEM = " << it.getSecond() << std::endl; // accede à la valeur
                        }
                }
        }
        catch(std::string const& chaine) {
                std::cerr << chaine << std::endl;
                std::cout << "il n'y a que la racine dans la map" << std::endl;
                std::cout << "KEY = " << mmap.getRacine().get()->getPair().getKey() << std::endl;// accede à la clé
                std::cout << "ITEM = " << mmap.getRacine().get()->getPair().getItem() << std::endl; // accede à la valeur
        }
        */


        /* insertion
        std::cout << "\n\nINSERTION" << std::endl;
        std::shared_ptr <TNode<int, int>> tn1(new TNode<int, int>());
        std::cout << "\nobjet tn1 " << tn1 << "\n" << std::endl;
        // mmap.insertion(tn1);
        // mmap.emplace(1, 2);
        MyMap<int, int>::MyIterator<int, int> myIt = MyMap<int, int>::MyIterator<int, int>(mmap.getRacine());
        mmap.emplace_hint(myIt, 1, 2);
        std::cout << "\n-map second : -\n" << mmap;*/

        // mmap.find(mmap.getRacine()->getPair().getKey());

        //std::shared_ptr <TNode<int, int>> tn2(new TNode<int, int>());
        //std::cout << "objet tn2 " << tn2 << "\n" << std::endl;
        //mmap.insertion(tn2);
        //std::cout << "\n-map third : -\n" << mmap << std::endl;

        //std::cout << "\nadresse racine init : " << mmap.getRacine() << std::endl;
        //std::cout << "objet racine init : " << mmap.getRacine().get() << std::endl;*/

        //TPair<std::string, int>* t = new TPair<std::string, int>();
        //std::cout << t->giveType() << std::endl;
        //std::cout << t->calcSize() << std::endl;

    /****************************************** FIN TEST MyMap ********************************************************/

    return 0;
}