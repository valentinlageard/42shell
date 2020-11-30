# minishell

## TODO

- Gérer les variables d'environnement. Les stocker qqpart ?
- Dans `exec_cmd` utiliser $PATH pour exécuter des commandes en chemin relatif :
	- Tester si la commande existe dans les dossiers stockés dans $PATH
	- Si oui, concaténer avec le path pertinent.
	- Gérer `.` et `..` ?
- Faire une fonction `exec` qui sélectionne l'exécution d'un builtin ou d'une commande.
- Séparation des commandes avec ``;`` :
	- Splitter la ligne selon `;`
	- Pour chaque split, créer une commande en splittant selon les whitespaces
	- Pour chaque commande, exécuter.
- Gestion de `'` et `"`
- Gestion des redirections :
	- `<` utilise un fichier comme stdin
	- `>` écrit stdout dans un fichier
	- `>>` ajoute stdout à la fin d'un fichier
- Gestion des pipes `|`
- Gestion des variables d'environnement `$FOO`
- Gestion de `$?` : donne le statut de ?
- Gestion de `Ctrl-C`, `Ctrl-D` et `Ctrl-\`
- builtin : echo (avec l'option -n)
- builtin : cd
- builtin : pwd
- builtin : export
- builtin : unset
- builtin : env
- builtin : exit

## Architecture

1. **Initialiser le shell**
	1. Récupérer et stocker les variables d'environnement.
2. **Boucle d'interprétation** :
	1. *Prompter* l'utilisateur.
	2. *Lire* : lire des parties et stocker dans un buffer à taille variable.
	3. *Parser la ligne* :
		- Pour l'instant on split simplement.
		1. *Executer* :
			- Si le premier token est un builtin, lancer le builtin avec le reste des tokens en arguments.
			- Sinon, créer un processus enfant et le faire exécuter la commande avec le reste des tokens en argument. Gérer le cas ou la commande ne correspond à rien.
		3. *Répéter* pour chaque commande.
	4. *Répéter* pour chaque ligne.
3. **Fermer le programme**

### Prototype
Pour l'instant, le programme ne fait que splitter la ligne et transmettre une liste de string à l'exécution.

### Interface parsing / exécution

Idéalement le parsing construit des structures de données qui stockent les commandes. La fonction d'éxécution prend cette commande en entrée. Les commandes ont , dossier local, ...une structure de données.

struct command :
- char *main_command
- char **parameters

### Exécution

Pour chaque commande :
1. Si la commande transmise est un builtin, éxécuter le builtin.
2. Sinon, exécuter la commande avec execve en utilisant la variable d'environnement PATH ou un chemin absolu.

**`pid_t fork(void)`** : creates a children process by duplicating the current process.
- Returns : In the parent, the child pid is returned. In the child, 0 is returned. On failure, -1 is returned in the parent and errno is set appropriately.

## Structures de données

### Shell configuration

La configuration du shell contient :
- Les variables d'environnement.

### Commande

- Chemin absolu de la commande ?
- Arguments.

Le parsing de la ligne crée une ou plusieurs commandes qui sont transmises à la boucle d'éxécution.

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
