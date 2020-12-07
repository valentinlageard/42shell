# minishell

## TODO

- Implémenter `change_env(key, new_value, env)` qui change la valeur d'une variable d'environnement.
- Gestion de `'` et `"`
- Gestion des redirections :
	- `<` utilise un fichier comme stdin
	- `>` écrit stdout dans un fichier
	- `>>` ajoute stdout à la fin d'un fichier
- Gestion des pipes `|` (may use `dup`, `dup2`, `pipe`)
- Gestion de `$?` : donne le statut de ?
- Gestion de `Ctrl-C`, `Ctrl-D` et `Ctrl-\`
- builtin : echo (avec l'option -n)
- builtin : cd
- builtin : pwd
- builtin : export : Implémenter `new_env(key, value, env)` qui crée une nouvelle variable d'environnement.
- builtin : unset : Implémenter `delete_env(key, env)` qui supprime une variable d'environnement.

### DONE
- [x] DEBUG : After launching another shell, the shell bugs.
- [x] DEBUG : Erreur de double free quand un zsh est lancé via minishell en utilisant $SHELL !
- [x] DEBUG : Seul le premier `=` sépare la clé de la valeur dans les variables d'environnement !
- [x] ARCHITECTURE : Faire que les variables d'environnment sont stockés comme liste chaînée.
- [x] Gestion des variables d'environnement `$FOO`
- [x] builtin : env (no options or arguments !) : prints env variables
- [x] builtin : exit
- [x] Stocker cmds dans shell afin qu'elles puissent être libérée lors d'un exit !
- [x] Faire que`exec` sélectionne entre builtin ou commande.
- [x] Créer une fonction `parse` qui crée une liste de struct cmd et qui la passe à `exec` qui exécute
- [x] Séparation des commandes avec ``;``
- [x] Implémenter `select_binpath` et `get_binpath` qui cherchent et remplacent le chemin du binaire.
- [x] Récupérer les variables d'environnement et les stocker.
- [x] Implémenter une fonction `get_envval(key, env)`.

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

Idéalement le parsing construit des structures de données qui stockent les commandes. La fonction d'éxécution prend cette commande en entrée. Les commandes ont une structure de données.

struct s_cmd (t_cmd):
- char *main : contient le bpath de la commande ou le nom du builtin
- char **parameters : contient les paramètres de la commande.
- int is_builtin : 1 si la commande est un builtin, sinon 0.
- int is_valid : 1 si la commande est valide, sinon 0.
- int is_piped : 1 si la commande est pipée dans la prochaine, sinon 0.

### Parsing

- TODO : (Traiter `""` et `''` : comment ?)
- Découper la ligne en plusieurs commandes selon `;` (TODO : et `|` ?)
	- Pour chaque commande :
	- Découper les commandes selon les whitespaces en args.
	- Si la commande est un builtin.
		- Mettre le flag is_builtin.
	- Sinon :
		- Détecter si le binaire existe relativement ou absolument selon $PATH.
		- Si c'est le cas, stocker le chemin absolu dans cmd.
	- Dans les args, détecter les appels aux variables. Si des variables sont appelées, remplacer la string par la valeur de cette variable (désallouer l'appel, allouer la variable, changer l'adresse du pointeur).
	- Stocker args dans args.

### Exécution

Pour chaque commande :
1. Si la commande transmise est un builtin, éxécuter le builtin.
2. Sinon, exécuter la commande avec execve en utilisant la variable d'environnement PATH ou un chemin absolu.

**`pid_t fork(void)`** : creates a children process by duplicating the current process.
- Returns : In the parent, the child pid is returned. In the child, 0 is returned. On failure, -1 is returned in the parent and errno is set appropriately.

## Structures de données

### Shell configuration

La configuration du shell contient :
- `t_cmd **cmds` : Une liste de commande stockant vers la liste de commande créée par `parse` et transmise à `exec`.
- `char **env` : Les variables d'environnement.

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
int main (int argc, char **argv, char **envp)
{
	// ...
}
```

### Pipe
