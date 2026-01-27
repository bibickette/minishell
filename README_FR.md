🇬🇧 English version available [here](README.md)
* * *
# Présentation du projet `minishell`
## Description
Ce projet consiste à créer un **mini shell Unix** en langage C.

L’objectif est d’implémenter un interpréteur de commandes entièrement fonctionnel, capable d’exécuter des commandes, de gérer les built-ins, les pipes, les redirections, les variables d’environnement et les signaux. Il reproduit le comportement d’un shell réel tout en mettant l’accent sur la gestion de la mémoire, la gestion des processus et l’analyse de l’entrée utilisateur.

Ce projet implique :
- L’analyse de l’entrée utilisateur et la tokenisation des commandes
- La gestion des processus enfants et de la communication inter-processus
- La gestion des signaux (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`)
- L’implémentation des redirections d’entrée/sortie (`<`, `>`, `>>`, `<<`)
- La gestion des pipes (`|`)
- L’expansion des variables d’environnement (`$VAR`) et de `$?` (dernier code de retour)
- L’implémentation des commandes internes obligatoires
- L’affichage d’un prompt et la gestion de l’historique des commandes

* * *
## Langages & Technologies

**Langage**
- C (standard C99)

**Technologies**
- Makefile
- Appels système Unix (`fork`, `execve`, `pipe`, `dup2`, `waitpid`)
- Redirections d’entrées/sorties
- Gestion des signaux (`SIGINT`, `SIGQUIT`)
- Gestion des variables d’environnement
- Listes chaînées (gestion des commandes et des tokens)
- Allocation dynamique de mémoire
- Analyse et manipulation de chaînes de caractères
  
* * *
## Fonctionnalités du shell

### Prompt & saisie des commandes

- Le shell affiche un prompt en attente d’une nouvelle commande.
- Les commandes sont lues depuis l’entrée standard.
- L’historique des commandes est conservé durant la session.

### Commandes intégrées (built-ins)

| Commande |                     Description                      |
|:--------:|:----------------------------------------------------:|
|   echo   |       Affiche du texte ; supporte l’option -n        |
|    cd    | Change le répertoire courant (chemin relatif/absolu) |
|   pwd    |       Affiche le répertoire de travail courant       |
|  export  |        Définit des variables d’environnement         |
|  unset   |        Supprime des variables d’environnement        |
|   env    |        Affiche les variables d’environnement         |
|   exit   |                   Quitte le shell                    |

### Exécution des commandes

Le programme :
- exécute les commandes externes à l’aide de `execve`
- recherche les exécutables via la variable `$PATH` ou via des chemins relatifs/absolus
- utilise une seule variable globale pour stocker les signaux reçus (`SIGINT`, `SIGQUIT`) ; le gestionnaire de signaux n’accède pas aux structures de données principales

### Redirections
- `<` redirige l’**entrée**
- `>` redirige la **sortie** (écrasement)
- `>>` redirige la **sortie** en mode ajout
- `<<` (`here-doc`) : lit l’entrée jusqu’à rencontrer le délimiteur. L’historique n’est pas mis à jour pour l’entrée du here-doc

### Pipes
- Les commandes peuvent être chaînées avec `|` : la sortie d’une commande devient l’entrée de la suivante via un pipe

### Guillemets & caractères spéciaux
- Les guillemets **simples** `'...'` empêchent l’interprétation des méta-caractères
- Les guillemets **doubles** `"..."` empêchent l’interprétation des méta-caractères **sauf** `$` pour l’expansion des variables
- Les autres méta-caractères tels que `\` et `;` ne sont pas interprétés
- Les jokers (`*`) ne sont pas pris en charge

### Variables d’environnement
- `$VAR` est remplacée par la valeur de la variable
- `$?` est remplacé par le code de sortie de la dernière commande exécutée au premier plan

### Gestion des signaux
- `Ctrl-C` affiche un nouveau prompt sur une nouvelle ligne
- `Ctrl-D` quitte le shell
- `Ctrl-\` n’a aucun effet en mode interactif

* * *
## Notes
Comprendre et implémenter [pipex](https://github.com/bibickette/pipex) est extrêmement utile pour `minishell`, car ce projet introduit des concepts fondamentaux tels que les pipes, la création de processus et les redirections d’entrées/sorties. Ces mécanismes sont essentiels au fonctionnement de `minishell` pour l’exécution de pipelines (`cmd1 | cmd2`) et la gestion correcte des redirections. Réaliser [pipex](https://github.com/bibickette/pipex) au préalable constitue une base solide pour développer minishell.

* * *
# Utilisation de `minishell`

## **Règles du Makefile**
1. **all** comme *règle par défaut* : compile le projet, transforme tous les fichiers `.c` en `.o` et **construit** le programme  (`minishell`)
2. **clean** : supprime les fichiers objets compilés (`.o`)
3. **fclean** : exécute la règle *clean* et supprime l'éxecutable (`minishell`)
4. **re** : exécute *fclean* puis *all*


* * *

## **Comment utiliser `minishell`**

*Note : le projet `minishell` fonctionne de manière autonome et utilise la bibliothèque [libft](https://github.com/bibickette/libft). Celle-ci étant ajoutée comme sous-module, il est nécessaire de cloner le dépôt avec.*
1. Clonez `minishell` dans un dossier : `git clone --recurse-submodules https://github.com/bibickette/minishell.git`
2. Accédez au dossier `minishell` et compilez le projet : `cd minishell && make`
3. Lancez `./minishell` sans argument
4. Vous pouvez maintenant saisir des commandes comme dans un shell classique : `echo "hello world !" | cat -e`

### Valgrind & vérification mémoire

*`minishell` a été testé avec **Valgrind** afin de garantir l’absence de fuites mémoire et la libération correcte de toute la mémoire allouée. Comme pour le projet [pipex](https://github.com/bibickette/pipex), le programme repose sur des appels système tels que `fork`, `execve` et `pipe`... certaines allocations peuvent apparaître comme still reachable en raison de la gestion interne du système. Pour obtenir des résultats clairs et pertinents, un **fichier de suppression** est utilisé.*

Vous pouvez exécuter `minishell` avec **Valgrind** à l’aide de la commande suivante : `valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=all.supp ./minishell`

Le fichier `all.supp` permet de filtrer les fuites connues et inévitables, afin que **Valgrind** se concentre uniquement sur les véritables fuites mémoire liées au projet.

Vous pouvez maintenant tester mon `minishell` !

* * *

*Date de validation du projet : 2 octobre 2024*