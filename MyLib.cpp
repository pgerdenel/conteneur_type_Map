#include <c++/4.8.3/string>
#include "MyLib.h"


// génère une clé aléatoirement
static std::string genKey() {
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