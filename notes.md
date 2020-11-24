# minishell

## Architecture

1. **Initialiser le shell** : variables d'environnement, dossier local, ...
2. **Boucle d'interprétation** :
	1. *Prompter* l'utilisateur.
	2. *Lire* : lire des parties et stocker dans un buffer à taille variable.
	3. *Splitter* en liste de commandes avec ";". Pour chaque commande :
		1. *Parser* : tokenizer la commande en splittant avec les espaces. (Comment gérer " et ' ?)
		2. *Executer* :
			- Si le premier token est un builtin, lancer le builtin avec le reste des tokens en arguments.
			- Sinon, créer un processus enfant et le faire exécuter la commande avec le reste des tokens en argument. Gérer le cas ou la commande ne correspond à rien.
		3. *Répéter* pour chaque commande.
	4. *Répéter*.
3. **Fermer le programme**

## Prototype

Un shell qui exécute une seule commande avec ses arguments.

## Structure de données

### Shell configuration

Un type qui stocker la configuration du shell.

### Tokens typés ?

Au lieu de simplement split l'entrée en mots, analyser chaque mot et créer un typedef token stockant le mot et un identificateur de token.

## Notions

### Création de processus

`fork()` crée un processus enfant.
`exec()` remplace le programme d'un processus.
`waitpid()` permet d'attendre qu'un processus termine.

Procédure de génération de processus enfants.
1. Forker le processus parent.
2. Identifier le processus enfant.
3. Executer un nouveau programme dans le processus enfant.
4. Dans le processus parent, attendre que l'enfant termine.

### Variables d'environnement

Récupérées par le main comme troisième argument :
```c
int main (int argc, char **argv, char **env)
{
	// ...
}
```

### Pipe
