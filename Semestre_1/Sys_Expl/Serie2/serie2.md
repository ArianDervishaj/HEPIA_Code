# Exercice 1

## a) Structure du superbloc et structures d’allocations de blocs/inodes

### 1) Quel est le nombre de blocs du FS ?
0x5000 => 20'480 blocs

### 2) Quel est le nombre maximum d’inodes que l’on peut créer ?

0x1ac0 = 6848

### 3) Quel(s) sont le/les numéros de blocs qui contient/nent le bitmap des inodes disponibles ?

0x0001 => 1 bloc
donc bloc numero 2

### 4) Quel(s) sont le/les numéros de blocs qui contient/nent le bitmap des blocs disponibles ?
0x0003 => 3 blocs

bloc 3 à 5

### 5) Quel(s) sont le/les numéros de blocs qui contiennent la table des inodes ?

nb d'inode * taille d'inode / taille d'un bloc
6848 * 32 / 1024 = 214
6 à 219


### 6) Combien y-a-t-il d’inodes par bloc ?
taille de bloc / taille d'inode

1024 / 32 = 32

## b) Navigation dans le FS

### 1) Quel sont le ou les numéros de blocs contenant les entrées du répertoire racine (/), ainsi que la taille du répertoire ?


00010000
size = 0x00000100 = 256 bytes
256 < 1024 => 1 seul bloc
bloc 220

### 2) Quel est le numéro d’inode du répertoire /usr ?

4

### 3) Quels sont le ou les numéros des blocs contenant les entrées du répertoire /usr ainsi que la taille de ce répertoire ?

(80 81) (00 00) (30 01 00 00) (93 c2 09 55) (00) (01) (da 09) (00 00) (00 00)

0x00003001 = 12289 bytes

12289 / 1024 = 12.0000un truc  => 13 blocs

### 4) Quel est le numéro d’inode du répertoire /usr/src ?
### 5) Quels sont le ou les numéros des blocs contenant les entrées du répertoire /usr/src ainsi que la taille de ce répertoire ?
### 6) Quel est le numéro d’inode du répertoire /usr/src/archives ?
### 7) Quels sont le ou les numéros de blocs contenant les entrées du répertoire /usr/src/archives ainsi que la taille de ce répertoire ?
### 8) Quel est le numéro d’inode du fichier /usr/src/archives/linux-0.95.tgz ?
### 9) Quelle est la taille de ce fichier ?
### 10) Quelle est le nombre total de blocs occupés par ce fichier (incluant les blocs stoquant des pointeurs) ?
### 11) Quel est le numéro du dernier bloc du fichier ? Combien de bytes réellement utilisés sont contenus dans ce bloc ?
### 12) Quel est le contenu des bytes aux adresses 600000 à 600009 du fichier ?