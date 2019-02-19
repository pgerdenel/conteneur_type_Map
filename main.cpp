#include <iostream>
#include "MyMap.h"

int main() {

        // création de la Map<int, int>
        auto* r = new TNode<int, int>(); // racine
        MyMap<int, int> mmap = MyMap<int, int>(std::shared_ptr <TNode<int, int>>(r), 1, 1);
        MyMap<int, int, std::less<int>> mmap2 = MyMap<int, int>();
        std::cout << "\nadresse racine init : " << mmap.getRacine() << std::endl;
        std::cout << "\n-map current : -\n" << mmap << std::endl;

    return 0;
}