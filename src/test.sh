#!/bin/bash
# Projet d'analyse synthaxique Arthur PAIRAUD

if [ $# -le 4 ] || [ $# -gt 6 ]
then
    echo "./test.sh [analyseur] [fichier tests correct] [fichier tests incorrects]"

else
    valides=0
    total=0

    liste_good=$(ls $2)

    liste_warn=$(ls $3)

    liste_syn_err=$(ls $4)

    liste_sem_err=$(ls $5)

    echo ""
    echo "______fichiers de tests valides______"
    echo ""

    for fich in $liste_good
    do
        extenssion=$(echo ${fich#*.})
        if [ "$extenssion" = "tpc" ]
        then
            echo "$2$fich :"
            $1 $2$fich
            tmp=$?
            echo "valeur de retour : $tmp"
            echo ""

            ((total=$total+1))
            if [ $tmp -eq 0 ]
            then
                ((valides=$valides+1))
            fi
        fi

    done

    echo ""
    echo "______fichiers de tests avertissements______"
    echo ""

    for fich in $liste_warn
    do
        extenssion=$(echo ${fich#*.})
        if [ "$extenssion" = "tpc" ]
        then
            echo "$3$fich :"
            $1 $3$fich
            tmp=$?
            echo "valeur de retour : $tmp"
            echo ""

            ((total=$total+1))
            if [ $tmp -eq 0 ]
            then
                ((valides=$valides+1))
            fi
        fi

    done

    echo ""
    echo "______fichiers de tests erreurs syntaxiques______"
    echo ""

    for fich in $liste_syn_err
    do
        extenssion=$(echo ${fich#*.})
        if [ "$extenssion" = "tpc" ]
        then
            echo "$4$fich :"
            $1 $4$fich
            tmp=$?
            echo "valeur de retour : $tmp"
            echo ""

            ((total=$total+1))
            if [ $tmp -eq 1 ]
            then
                ((valides=$valides+1))
            fi
        fi

    done

    echo ""
    echo "______fichiers de tests erreurs semantiques______"
    echo ""

    for fich in $liste_sem_err
    do
        extenssion=$(echo ${fich#*.})
        if [ "$extenssion" = "tpc" ]
        then
            echo "$5$fich :"
            $1 $5$fich
            tmp=$?
            echo "valeur de retour : $tmp"
            echo ""

            ((total=$total+1))
            if [ $tmp -eq 2 ]
            then
                ((valides=$valides+1))
            fi
        fi

    done

    echo "Score : $valides / $total"
fi