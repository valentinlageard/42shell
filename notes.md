# minishell

## TODO

- DEBUG : Faire en sorte que si on interrompt un pipe mais que la dernière commande n'a pas été interrompue (car déjà terminée), alors l'exit code n'est pas changé à 130, mais à son exit_code à elle.
- Tout mettre à la norme.

### DONE
- [x] Implémenter OLDPWD dans cd
- [x] Remettre -Werror dans le Makefile
- [x] SIGINT should quit all commands if several command groups are given.
- [x] DEBUG : Redirections should work even if stated before the command !
- [x] Manage errors in tokenization and parsing.
- [x] Manage all enomem errors
- [x] Single letters are detected as builtin
- [x] Mettre le prompt sur stderr plutot que stdout
- [x] Token error si quote unclosed !
- [x] DEBUG : `echo $` prints a random variable...
- [x] "" should not exit
- [x] DEBUG : `/bin/zinz` prints "command not found" instead of "no such file or directory"
- [x] Faire qu'un identifier ne soit considéré comme executable que s'il existe dans $PATH ou soit en chemin absolu.
- [x] Si la commande précédente est un builtin, l'attendre ?
- Return values of builtins :
	- [x] echo : always 0
	- [x] cd : 0 ou 1 si une erreur
	- [x] pwd : 0 ou errno si une erreur
	- [x] export : 0 ou errno si une erreur
	- [x] unset : 0 ou errno si une erreur
	- [x] env : 0
	- [x] exit : l'exit code si spécifié sinon le dernier exit code
- Manage errors in builtins :
	- [x] echo
	- [x] cd
	- [x] pwd
	- [x] export
	- [x] unset
	- [x] env
	- [x] exit
- [x] Faire que exit peut prendre un exit code.
- [x] DEBUG : `echo -nnnnnn zinz`, `echo -nope zinz`, `echo -n -n zinz -n`
- [x] DEBUG : gérer cd sans arguments
- [x] DEBUG : Si on est en train d'écrire une ligne, EOF ne doit pas stopper le shell.
- [x] DEBUG : Faire entrée ne doit pas stopper le shell !
- [x] Gestion de `Ctrl-D` : sends an EOF to stdin.
- [x] Faire en sorte que l'exit code = 130 si stoppé.
- [x] Gestion de `Ctrl-C` : `SIGINT`.
- [x] Gestion de `Ctrl-\` : `SIGQUIT` doit être ignoré et ne rien afficher sur stdout.
- [x] DEBUG : If no input, there is a segfault.
- [x] REFACTORING : Quand on fork, on crée une structure de donnée qui stocke la relation pid/cmd. Si le pid du wait est la dernière commande, on récupère son exit code. Si l'enfant renvoit 127, c'est le parent qui affiche le message d'erreur.
- [x] DEBUG : Seul le code d'erreur du dernier enfant doit être récupéré, même s'il ne termine pas en dernier. (ex `sleep 5 | grep a | zinz` doit return 127).
- [x] DEBUG : `nexistepas | touche lol` fait un print weird. Probablement qu'il faut gérer le groupe de process trankilement.
- [x] REFACTORING : Changer l'execution afin que le parent attende que TOUS LES ENFANTS terminent !
- [x] REFACTORING : la repl doit déparer les tokens par groupe de commandes, puis pour chacun, parser le groupe de commande et l'executer.
- [x] REFACTORING : les processus enfants valident si la commande existe ou non et pas le parent.
- [x] Gestion de `$?` :
	- Refactorer l'exec afin de récupérer le return des commandes et le stocker dans une variable spéciale.
	- Dans la phase d'expansion de variables, faire une fonction spéciale pour expandre spécifiquement cette variable.
- [x] REFACTORING : Ne pas allouer fds afin qu'exit ne leak pas.
- [x] Avant l'exécution : si une des commande du groupe est invalide, ne pas executer le groupe et passer au suivant + message d'erreur.
- [x] Gérer les redirections dans pour un simple builtin !
- [x] Avant l'exécution : vérifier si les output paths sont corrects.
- [x] Avant l'exécution : vérifier si les input paths sont corrects.
- [x] Gestion de `>>` :
	- [x] Refactorer le separate_token pour qu'il isole des séparateurs multicharacters.
	- [x] Séparer `>>` et append_as_next_redirection avec le bon flag.
	- [x] Ajouter l'append_redir à cmdg.
	- [x] Dans l'exécution, ouvrir avec O_APPEND.
- [x] Gestion de `>`
- [x] Gestion de `<`
- [x] Gestion des pipes `|` (may use `dup`, `dup2`, `pipe`)
- [x] Refactor cmds comme une liste chaînée.
- [x] Gestion de `'` et `"`
- [x] OPTIONAL : gérer les espaces dans cd ?
- [x] builtin : cd
- [x] builtin : echo (avec l'option -n)
- [x] builtin : pwd
- [x] builtin : export : Implémenter `new_env(key, value, env)` qui crée une nouvelle variable d'environnement.
- [x] builtin : unset : Implémenter `delete_env(key, env)` qui supprime une variable d'environnement.
- [x] Implémenter `change_env(key, new_value, env)` qui change la valeur d'une variable d'environnement.
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
2. **Read/Eval/Prompt/Loop** :
	1. *Prompter* l'utilisateur.
	2. *Lire* : lire des parties et stocker dans un buffer à taille variable.
	3. *Parser la ligne*.
	4. *Executer les commandes*.
	5. *Répéter* pour chaque ligne.
3. **Fermer le programme**

### Groupes de commandes

Pendant la tokenization :
- Splitter selon `;`.
- Splitter selon `|`.
- Splitter selon `>, <, >>`.

Pendant le parsing :
- Utiliser les séparateurs `;` pour séparer des groupes de commandes.
- Utiliser les séparateurs `|` pour séparer des commandes dans un même groupe de commandes.
- Utiliser les séparateurs `>, <, >>` et sélectionner le token suivant immédiatement comme path à stocker dans le groupe de commandes.

Pendant l'éxecution pour chaque groupe de commandes :
- S'il y a plusieurs commandes dans le groupe, piper chacune dans la suivante.
- S'il y a une redirection entrante, rediriger le fichier dans la première commande.
- S'il y a une redirection sortante, rediriger la sortie de la dernière commande dans le fichier de sortie.

---

- `cmdgs` : liste de groupe de commandes
	- `cmdg` :
		- `cmds` :
			- `cmd`
				- `main`
				- `args`
				- `is_valid`
				- `is_builtin`
			- ...
		- `in_redirs`
		- `out_redir`
		- `out_app_redir`
	- ...

### Redirections et pipes

#### `a > b`

Réecrit le stdout de a dans b.

Si plusieurs fichiers sont stipulés, tous sont créés mais seul le dernier contient l'output :
`a > b > c` créera b et c mais seul c contiendra le stdout de a.

Si l'un existe déjà quand plusieurs sont stipulés, leur contenu sera effacé.

#### `a >> b`

Ajoute le stdout de a dans b.

#### `a < b`

Utilise b comme stdin pour a.

Si plusieurs fichiers sont stipulés, seul le dernier est pris en compte :
Dans `a < b < c`, a utilise c comme stdin et non b.

#### `a | b`

Utilise le stdout de a comme stdin de b.

#### Parsing and execution

A faire entre le split `;` et l'expansion de variables.

**Tokenization part :**

Ajouter des token types pour les redirections et pipes :
- input redirection : <
- output redirection : >
- appending outpur redirection : >>
- piping : |

**Parsing part :**
Quand un token de redirection est découvert, le token qui suit immédiatement est utilisé comme paramètre de la redirection et c'est stocké comme une propriété de la commande.

Quand un token de piping est découvert, séparer la commande de ce qui suit et activer un flag is_piped.

**Execution part :**

Si les redirections sont activées dans la commande :
- Ouvrir ces redirections.
- Opérer ces redirections une fois l'enfant créé mais avant l'execution.

Si un is_piped est activé :
- créer un pipe
- forker les enfants
- rediriger stdout de l'enfant 1 dans le pipe
- rediriger stdin de l'enfant 2 par le pipe
- executer les enfants.

### Parsing

1. Split quotes and text from read line to token list.
2. Split tokens by commands separators.
3. Add flag tokens for pipings and redirections.
4. Expand variables in tokens.
5. Split tokens by whitespaces.
6. Convert token list to commands array.

#### Token structure and type

typedef struct s_tok {
	char *str;
	int	type;
}

Types :
0 : text
1 : single-quote text ''
2 : double-quote text ""
3 : command separator ;

### Interface parsing / exécution

Idéalement le parsing construit des structures de données qui stockent les commandes. La fonction d'éxécution prend cette commande en entrée. Les commandes ont une structure de données.

struct s_cmd (t_cmd):
- char *main : contient le bpath de la commande ou le nom du builtin
- char **parameters : contient les paramètres de la commande.
- int is_builtin : 1 si la commande est un builtin, sinon 0.
- int is_valid : 1 si la commande est valide, sinon 0.
- int is_piped : 1 si la commande est pipée dans la prochaine, sinon 0.

### Exécution

1. Fork the parent process.
2. Have the parent process wait until the child finishes.
3. Have the child process change its redirections if relevant.
4. Execute the binary in the child process.

**`pid_t fork(void)`** : creates a children process by duplicating the current process.
- Returns : In the parent, the child pid is returned. In the child, 0 is returned. On failure, -1 is returned in the parent and errno is set appropriately.

#### Logique de l'éxecution

1. Pour chaque groupe de commandes :
	1. S'il n'y a qu'une seule commande dans le groupe et que c'est un builtin.
		1. Si la commande est valide : executer la fonction correspondante.
	2. Sinon :
		1. Pour chaque commande dans le groupe :
			1. Si la commande n'est pas la dernière commande du groupe.
				1. Créer un pipe.
				2. ???
			2. Si la commande est la dernière commande.
				1.

## Structures de données

### Shell configuration

La configuration du shell contient :
- `t_cmd **cmds` : Une liste de commande stockant vers la liste de commande créée par `parse` et transmise à `exec`.
- `char **env` : Les variables d'environnement.

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
