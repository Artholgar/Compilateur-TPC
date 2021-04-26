#!/bin/bash
# Projet d'analyse synthaxique Arthur PAIRAUD

if [ $# -le 1 ] || [ $# -gt 3 ]
then
    echo "./test.sh [analyseur] [fichier tests correct] [fichier tests incorrects]"

else
    valides=0
    total=0

    liste_valide=$(ls $2)

    liste_invalide=$(ls $3)

    echo ""
    echo "______fichiers de tests valides______"
    echo ""

    for fich in $liste_valide
    do
        echo "./$2$fich :"
        ./$1 ./$2$fich
        tmp=$?
        echo "valeur de retour : $tmp"
        echo ""

        ((total=$total+1))
        if [ $tmp -eq 0 ]
        then
            ((valides=$valides+1))
        fi

    done

    echo ""
    echo "______fichiers de tests invalides______"
    echo ""

    for fich in $liste_invalide
    do
        echo "./$3$fich :"
        ./$1 ./$3$fich
        tmp=$?
        echo "valeur de retour : $tmp"
        echo ""

        ((total=$total+1))
        if [ $tmp -ne 0 ]
        then
            ((valides=$valides+1))
        fi

    done

    echo "Score : $valides / $total"
fi