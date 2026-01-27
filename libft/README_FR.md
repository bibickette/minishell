🇬🇧 English version available [here](README.md)
* * *
# Présentation du projet `libft`
## Description

Ce projet consiste à créer une bibliothèque statique personnelle réutilisable (libft.a) en réimplémentant des fonctions utiles de la bibliothèque standard C, ainsi que des fonctions supplémentaires qui seront utiles dans des projets futurs.

L’objectif est de mieux comprendre les structures de données et les algorithmes de base. À 42, certaines bibliothèques standard sont interdites, donc nous construisons et développons notre propre bibliothèque au fur et à mesure du cursus.

Par exemple :
- `ft_printf` (avec son propre Makefile), un projet 42 ajouté à la bibliothèque, voir plus [ici](https://github.com/bibickette/ft_printf).
- `get_next_line`, un projet 42 intégré à libft, voir plus [ici](https://github.com/bibickette/get_next_line).

* * *
## Langages & Technologies

**Langage**
- C (standard C99)

**Technologies**
- Makefile
- Bibliothèque statique (.a)
- Allocation dynamique de mémoire
- Manipulation de la mémoire
- Manipulation de chaînes de caractères
- Listes chaînées

* * *

## Contenu de la bibliothèque

Le projet est divisé en quatre sections :
1. Fonctions Libc – Réimplémentations de certaines fonctions standard C.
2. Fonctions supplémentaires – Fonctions utilitaires supplémentaires utiles pour les projets futurs.
3. Fonctions listes chaînées – Fonctions pour manipuler des listes chaînées.
4. Fonctions personnelles – Fonctions que j’ai ajoutées moi-même.


| Fonctions Libc |                            Description                            |
|:--------------:|:-----------------------------------------------------------------:|
|   ft_isalnum   |            Vérifie si un caractère est alphanumérique             |
|   ft_isalpha   |              Vérifie si un caractère est une lettre               |
|   ft_isascii   |       Vérifie si un caractère appartient à l’ensemble ASCII       |
|   ft_isdigit   |           Vérifie si un caractère est un chiffre (0-9)            |
|   ft_isprint   |              Vérifie si un caractère est imprimable               |
|   ft_tolower   |            Convertit une lettre majuscule en minuscule            |
|   ft_toupper   |            Convertit une lettre minuscule en majuscule            |
|    ft_bzero    |              Remplit un bloc mémoire avec des zéros               |
|   ft_calloc    |            Alloue et initialise un bloc mémoire à zéro            |
|   ft_strncmp   |    Compare deux chaînes jusqu’à un nombre donné de caractères     |
|   ft_strnstr   | Cherche une sous-chaîne dans une chaîne, limitée par une longueur |
|   ft_memchr    |               Cherche un octet dans un bloc mémoire               |
|   ft_memcmp    |                    Compare deux blocs mémoire                     |
|   ft_memcpy    |           Copie un bloc mémoire source vers destination           |
|   ft_memmove   |        Copie un bloc mémoire en gérant les chevauchements         |
|   ft_memset    |          Remplit un bloc mémoire avec un octet constant           |
|    ft_atoi     |                  Convertit une chaîne en entier                   |
|   ft_strlcat   |         Concatène deux chaînes avec limitation de taille          |
|   ft_strlcpy   |            Copie une chaîne avec limitation de taille             |
|   ft_strlen    |                 Retourne la longueur d’une chaîne                 |
|   ft_strrchr   |   Trouve la dernière occurrence d’un caractère dans une chaîne    |
|   ft_strchr    |   Trouve la première occurrence d’un caractère dans une chaîne    |
|   ft_strdup    |     Duplique une chaîne dans une mémoire nouvellement allouée     |

| Fonctions supplémentaires |                                      Description                                       |
|:-------------------------:|:--------------------------------------------------------------------------------------:|
|         ft_substr         |                          Extrait une sous-chaîne d’une chaîne                          |
|        ft_strjoin         |                         Concatène deux chaînes en une nouvelle                         |
|        ft_strtrim         |            Supprime les caractères donnés au début et à la fin d’une chaîne            |
|         ft_split          |        Découpe une chaîne en tableau en utilisant un caractère comme séparateur        |
|          ft_itoa          |                             Convertit un entier en chaîne                              |
|        ft_strmapi         |         Crée une nouvelle chaîne en appliquant une fonction à chaque caractère         |
|        ft_striteri        | Applique une fonction à chaque caractère d’une chaîne en modifiant la chaîne sur place |
|       ft_putchar_fd       |                    Écrit un caractère sur un descripteur de fichier                    |
|       ft_putstr_fd        |                     Écrit une chaîne sur un descripteur de fichier                     |
|       ft_putendl_fd       |      Écrit une chaîne suivie d’un retour à la ligne sur un descripteur de fichier      |
|       ft_putnbr_fd        |                     Écrit un entier sur un descripteur de fichier                      |

| Fonctions listes chaînées |                             Description                             |
|:-------------------------:|:-------------------------------------------------------------------:|
|      ft_lstadd_back       |               Ajoute un élément à la fin d’une liste                |
|      ft_lstadd_front      |               Ajoute un élément au début d’une liste                |
|        ft_lstclear        |          Supprime et libère tous les éléments d’une liste           |
|       ft_lstdelone        |              Supprime et libère un élément de la liste              |
|        ft_lstiter         |         Applique une fonction à chaque élément d’une liste          |
|        ft_lstlast         |               Retourne le dernier élément d’une liste               |
|         ft_lstmap         | Crée une nouvelle liste en appliquant une fonction à chaque élément |
|         ft_lstnew         |                   Crée un nouvel élément de liste                   |
|        ft_lstsize         |            Retourne le nombre d’éléments dans une liste             |

| Fonctions  personnelles |                                          Description                                          |
|:-----------------------:|:---------------------------------------------------------------------------------------------:|
|        ft_printf        | Implémentation personnalisée de printf, gérant les spécificateurs c, s, p, d, i, u, x, X et % |
|      get_next_line      |                         Lit un descripteur de fichier ligne par ligne                         |
|       countwords        |             Retourne le nombre de mots dans une chaîne séparés par un délimiteur              |
|      strjoin_wfree      |                         Concatène deux chaînes et libère la première                          |
|        factorial        |                        Calcule le factoriel d’un nombre récursivement                         |
|        fibonacci        |                Retourne le nombre de Fibonacci correspondant à un index donné                 |
|     find_next_prime     |           Retourne le plus petit nombre premier supérieur ou égal à un nombre donné           |
|   int_overflow_check    |                       Vérifie si une chaîne représente un entier valide                       |
|       nb_is_prime       |                               Vérifie si un nombre est premier                                |
|         nb_sqrt         |                 Retourne la racine carrée entière d’un nombre si elle existe                  |
|        power_nb         |                 Calcule un nombre élevé à une puissance donnée récursivement                  |
|    ft_is_white_space    |              Vérifie si un caractère est un espace, tabulation ou saut de ligne               |

* * *
# Utilisation de `libft`

## **Règles du Makefile**
1. **all** comme *règle par défaut* : compile le projet, transforme tous les fichiers `.c` en `.o` et **construit** la bibliothèque (`.a`)
2. **clean** : supprime les fichiers objets compilés (`.o`)
3. **fclean** : exécute la règle *clean* et supprime la bibliothèque (`.a`)
4. **re** : exécute *fclean* puis *all*

* * *

## **Comment utiliser `libft`**
1. Clonez `libft` dans le dossier de votre projet : `git clone https://github.com/bibickette/libft`
2. Compilez `libft` avec son Makefile : `make -s -C libft`, cela exécutera le Makefile dans le dossier `libft`.
3. Ajoutez le header `libft.h` dans votre projet pour accéder aux fonctions.
4. Compilez votre projet avec la bibliothèque `libft` : `cc vos_fichiers.o -L./libft -lft -o votre_programme`

Maintenant votre projet peut utiliser les fonctions de `libft` !

* * *

*Date de validation du projet : 23 décembre 2023*
