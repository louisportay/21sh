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
#CTRL-O always run the command
#CTRL-J run the command in nornal mode/ acquire it in C-R mode
#CTRL-B letter back
#CTRL-F letter forward
#CTRL-haut, CTRL-bas (pour changer de ligne) quand on edite sur plusieurs lignes
#CTRL-A / HOME 
#CTRL-E / END pour respectivement le debut et la fin de ligne
#Alt-b (CTRL-left) 	one word backward
#Alt-f (CTRL-right) 	one word forward
#Ctrl-D or Delete		Delete the character under the cursor
#CTRL-D exit le shell quand la ligne est vide|ignorer si c'est caractere vide|sinon effacer le caractere
#Ctrl-H	or Backspace	Delete the character before the cursor
#CTRL-L clear the screen
#CTRL-K cut the line from the cursor 'til the end
#CTRL-Y (paste what's inside the clipboard)
#CTRL-U (cut the line before the cursor, not included, to the beginning)
#CTRL-W (cut the previous word, put it in the clipboard)

CTRL-C pour réafficher le prompt 			*SIGINT to catch*
CTRL-\ and other signals, block them

*Alt-D	Delete the word after the cursor on the current line, put it on the clipboard

*CTRL-R	navigating history
*CTRL-G	leave the history without executing the command (abort)
*CTRL-J print the command to maybe execute it
*CTRL-O execute the command

builtin `history`, avec des options pour modifier le comportement (-c -d)

!! execute last command
!# (where # is a number) execute the #nth command in histlist
!abc (where abc is a string)	execute the last command beginning with 'abc'

*Split on multiple lines*

heredoc
single quote
double quote
back quotes --> 42SH
backslash

accolades
parenthèses
$crochets

**BONUS**

CTRL-R pour rechercher dans l'historique
(SHIFT|CTRL|META)PAGE-UP/DOWN pour naviguer dans la pagination
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

Se référer à POSIX/manuel de bash en cas de doute

New42sh
=======

*Suspens*
builtin fc

Others
======

For future improvements, make the whole line edition library work on a single pointer called "Current Line"
See signal.c
