Fonctions à implémenter
=======================

*Edition de ligne
*Lexing
*Parsing
*Exec

*Signal Handling

*Expansion (expand tilde; globbing...)
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
haut et bas pour naviguer dans l'historique (builtin `history`, avec des options pour modifier le comportement)
CTRL-haut, CTRL-bas (pour changer de ligne) quand on edite sur plusieurs lignes
CTRL-left pour aller d'un mot a gauche
CTRL-right pour aller d'un mot à droite
HOME et END pour respectivement le debut et la fin de ligne

CTRL-SHIFT-C Copier
MODE SELECTION pour Couper avec CTRL-SHIFT-X
CTRL-SHIFT-V Coller

CTRL-C pour réafficher le prompt
CTRL-D exit le shell quand la ligne est vide sinon ignorer

catch CTRL-\ and other signals, don't do nuts

*Split on multiple lines*

heredoc
single quote
double quote
back quotes
backslash

**BONUS**

CTRL-R pour rechercher dans l'historique
(SHIFT)PAGE-UP
(SHIFT)PAGE-DOWN
Mode bindings Vim/Emacs ?
De la Couleur...

crochets
accolades
parenthèses

Keys to catch
=============

*CTRL-W (erase a word)

*CTRL-R (navigating history)

*CTRL-A || Home-key (Go to the line beginning)
*CTRL-e || end-key (Go to the end)


*RETURN



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


Regarder le code de Hotrace (et l'algo de hash)
GIT Clone le minishell et mettre a jour github si VGS + recent
checker la (g)libC présente sur les macs -- voir si c'est possible d'en mettre une plus recente et de linker avec


avoir une fonction qui expand le prompt en fonction des caracteres set
launch options pour changer l'edition de ligne
switch qui trigger les bonnes fonctions quand on change l'env ou les localvar
