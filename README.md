# minishell

A reimplementation of a simplified shell as a 42 project. By Valentin Lageard.

Features :
- `echo` (with `-n`)
- `cd`
- `pwd`
- `env`, `export`, `unset`
- `exit`
- Command separation : `;`
- Concurrent pipes : `|`
- Quotes : simple `''` and double `""`
- Redirections : `<`, `>` and `>>`
- Variable expansion : `$`
- Exit code : `$?`
- `SIGINT`, `SIGQUIT` and `EOF` handling.
