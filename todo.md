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
#CTRL-O/CTRL-J run the command
#CTRL-B letter back
#CTRL-F letter forward
#CTRL-haut, CTRL-bas (pour changer de ligne) quand on edite sur plusieurs lignes
#CTRL-A / HOME 
#CTRL-E / END pour respectivement le debut et la fin de ligne
#CTRL-D exit le shell quand la ligne est vide|ignorer si c'est caractere vide|sinon effacer le caractere
#Alt-b (CTRL-left) 	one word backward
#Alt-f (CTRL-right) 	one word forward
#Ctrl-D or Delete		Delete the character under the cursor
#Ctrl-H	or Backspace	Delete the character before the cursor
#CTRL-L clear the screen
#CTRL-K cut the line from the cursor 'til the end
#CTRL-Y (paste what's inside the clipboard)
#CTRL-U (cut the line before the cursor, not included, to the beginning)

CTRL-C pour réafficher le prompt 			*SIGNAL to catch*
CTRL-\ and other signals, don't do nothing

*Alt-D	Delete the word after the cursor on the current line
*CTRL-W (cut the previous word, put it in the clipboard)

*CTRL-R	(navigating history, while you're typing)
*CTRL-G	leave the history without executing the command
*CTRL-J print the command to execute it
*CTRL-O execute the command then print it

builtin `history`, avec des options pour modifier le comportement

!! execute last command
!# (where # is a number) execute the #nth command in histlist
!abc (where abc is a string)	execute the last command beginning with 'abc'


(:p) 	add this after a `bang` expression, it will print the command rather than executing it

*Split on multiple lines*

heredoc
single quote
double quote
back quotes
backslash

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
builtin fc

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
passer des options au lancement pour ne pas lire ce fichier ou etre en mode rawa ou ne pas avoir d'historique
builtin pour switcher du mode normal au mode raw et inversement si c'est possible

tester des KEYS
HOME, END, BACKSPACE, des trucs que ya pas la...

Lire le man de readline pour les keystrokes

Splitter les .h
