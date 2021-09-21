• Implémentation d'un container from scratch
- Développement C++
- STL
- Template : Généricité
- Arbre

- Template TPair<class K, class T>
Un objet TPair utilise 2 types génériques K et T et pour représenter les types des pairs<key,
item>qui seront utilisés pour stocker les données de l’utilisateur.

- Template TNode<class K, class T>
La classe TNode représente l’objet intermédiaire qui contiendra les données de
l’utilisateur(TPair) et qui sera stocké dans l’arbre de la Map

- Template MyMap<class K, class T, class Compare=std::less<K>>
La template MyMap est la class finale représentant la map, elle gère les TNode et les
organise en un arbre de type rouge-noir
