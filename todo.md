Fonctions à implémenter
=======================

*Edition de ligne
*Lexing
*Parsing
*Expansion (expand tilde; globbing...)
*Exec

*Signal Handling
*Autocompletion

ft-sh2
======
	
La shell grammar et tous les tokens particuliers

 ;
 |
 <
 >
 << (heredoc)
 >>

**BONUS**

agrégation de descripteur/sortie de fichiers
Table de hash pour les binaires
Droits dans le PATH (message d'erreur approprié)
Autocomplétion avec 'tab' (en fonction des fichiers, des variables d'environnement...)

ft-sh3
======

#Edition de ligne au niveau du curseur
#bouger à gauche et à droite

#UP-KEY ou CTRL-P
#DOWN-KEY ou CTRL-N
#CTRL-O	run the command
#CTRL-B letter back
#CTRL-F letter forward

builtin `history`, avec des options pour modifier le comportement
*CTRL-R	(navigating history, while you're typing)
*CTRL-G	leave the history without executing the command

*ALT-R	Revert changes made to a command pulled from the history __NOPE__

CTRL-haut, CTRL-bas (pour changer de ligne) quand on edite sur plusieurs lignes
CTRL-left pour aller d'un mot a gauche
CTRL-right pour aller d'un mot à droite
HOME et END pour respectivement le debut et la fin de ligne

CTRL-SHIFT-C Copier
MODE SELECTION pour Couper avec CTRL-SHIFT-X
CTRL-SHIFT-V Coller

CTRL-C pour réafficher le prompt
CTRL-D exit le shell quand la ligne est vide, ignorer si c'est caractere vide, sinon l'effacer

catch CTRL-\ and other signals, don't do nuts

Alt-U	Capitalize every characters from the cursor to the end of the current word
Alt-L	Uncapitalize -		-	-	-	-		-	-	-	-	-	-	-	-	-
Alt-C	Capitalize the character under the cursor and move the cursor to the end of the word

!! execute last command
!# (where # is a number) execute the #nth command in histlist
!abc (where abc is a string)	execute the last command beginning with 'abc'
(:p) 	add this after a `bang` expression, it will print the command rather than executing it


Keys to catch
=============

*CTRL-W (erase a word, put it in the clipboard)
*CTRL-K (cut the line from the cursor 'til the end)
*CTRL-U (cut the line before the cursor, not included, to the beginning)
*CTRL-Y (paste what's inside the clipboard)

*CTRL-A || Home-key (Go to the line beginning)
*CTRL-e || end-key (Go to the end)

Alt-b	one word backward
Ctrl-b	one letter backward
Alt-f	one word forward
Ctrl-f	one letter forward 

Ctrl-D or Delete		Delete the character under the cursor
Alt-D					Delete all the characters after the cursor on the current line
Ctrl-H	or Backspace	Delete the character before the cursor

Alt-T		Swap the current word with the previous
Ctrl-T		Swap the last two characters (not the current one)
Ctrl-_		Undo last action to edit the line

CTRL-S stop output to the screen
CTRL-Q resume the screen output
CTRL-L clear the screen

*RETURN


*Split on multiple lines*

heredoc
single quote
double quote
back quotes
backslash

crochets
accolades
parenthèses

**BONUS**

CTRL-R pour rechercher dans l'historique
(SHIFT)PAGE-UP
(SHIFT)PAGE-DOWN
Mode bindings Vim/Emacs ?
De la Couleur...


42sh
====

Builtins POSIX
Gestion des erreurs et de la valeur de retour des commandes

le Globbing

'&&'
'||'

les sous shells avec "()"
variables locales + export + unset
l'historique (builtin history) et "!"
les descripteurs de fichiers et le builtin 'read' (+ses options)
Le Job control (jobs, fg, bg, & et CTRL-Z) (group id, session id)
le shell script

Se référer à POSIX en cas de doute

New42sh
=======

*Suspens*


Others
======

gestion d'alias ?

shell script ?
--> si oui, reserved words

avoir une fonction qui expand le prompt en fonction des caracteres set
launch options pour changer l'edition de ligne
'aliases' are handled during line edition, not when executed
switch qui trigger les bonnes fonctions quand on change l'env ou les localvar

Avoir différentes listes pour l'autocompletion (Variables locales, Variables d'env, Dossiers ouvrables, fichiers du répertoire courantm binaires trouves dans le PATH...)
history builtin (OPT: [n] + -c)


Si tu es un mec tres chaud, ajouter des dependances au prompt et a certaines parties du programme pour qu'elles ne soient mises a jour que si tel evenement est trigger... alors oui mais non en fait tu as pas le temps

Lire un fichier de config pour set des trucs eventuellement
passer des options au lancement pour ne pas lire ce fichier ou etre en mode raw
builtin pour switcher du mode normal au mode raw et inversement si c'est possible

tester des KEYS
HOME, END, BACKSPACE, des trucs que ya pas la...

Lire le man de readline pour les keystrokes
