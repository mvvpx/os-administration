#!/bin/bash
TASKS_FILE="tasks.txt"

create_task() {
    [[ ! -e "$TASKS_FILE" ]] && touch "$TASKS_FILE" && echo "Fichier des tâches créé."
    while true; do
        read -p "Entrez le titre de la tâche : " title
        [[ -z "$title" ]] && echo "Erreur : Le titre ne peut pas être vide." >&2 || break
    done
    while true; do
        read -p "Entrez la date d'échéance de la tâche (AAAA-MM-JJ) : " due_date
        if [[ -z "$due_date" ]]; then
            echo "Erreur : La date d'échéance ne peut pas être vide." >&2
        elif ! date -d "$due_date" &>/dev/null; then
            echo "Erreur : Format de date invalide. Veuillez entrer la date au format AAAA-MM-JJ." >&2
        else
            break
        fi
    done
    read -p "Entrez la description de la tâche : " description
    read -p "Entrez le lieu de la tâche : " location
    read -p "La tâche est-elle terminée ? (oui/non) : " completion
    completion=${completion:-"non terminée"}
    [[ "$completion" == "oui" ]] && completion="terminée" || completion="non terminée"
    task_id=$(awk 'END{print $1+1}' "$TASKS_FILE" 2>/dev/null || echo 1)
    echo "$task_id    $title    $description    $location    $due_date    $completion" >> "$TASKS_FILE"
    echo "Tâche ajoutée avec succès."
}

update_task() {
    read -p "Entrez l'ID de la tâche que vous souhaitez mettre à jour : " task_id
    read -p "Que voulez-vous mettre à jour ? (1. Titre, 2. Description, 3. Lieu, 4. Date d'échéance, 5. Achèvement) : " choice
    read -p "Entrez la nouvelle valeur : " new_value
    awk -v id="$task_id" -v c="$choice" -v val="$new_value" 'BEGIN {FS=OFS="    "} $1 == id {
        if (c == 1) $2 = val;
        else if (c == 2) $3 = val;
        else if (c == 3) $4 = val;
        else if (c == 4) $5 = val;
        else if (c == 5) $6 = val;
    } 1' "$TASKS_FILE" > temp && mv temp "$TASKS_FILE"
    echo "Tâche mise à jour avec succès."
}

delete_task() {
    read -p "Entrez l'ID de la tâche que vous souhaitez supprimer : " task_id
    awk -v id="$task_id" 'BEGIN {FS=OFS="    "} $1 != id' "$TASKS_FILE" > temp && mv temp "$TASKS_FILE"
    echo "Tâche supprimée avec succès."
}

task_info() {
    read -p "Entrez l'ID de la tâche dont vous souhaitez voir les informations : " task_id
    awk -v id="$task_id" -F '    ' 'BEGIN {found=0}
        $1 == id {
            print "ID de la tâche : " $1
            print "Titre : " $2
            print "Description : " $3
            print "Lieu : " $4
            print "Date d\'échéance : " $5
            print "Achèvement : " $6
            found=1
            exit
        }
        END {if(found==0) print "Tâche avec l\'ID " id " non trouvée."}
    ' "$TASKS_FILE"
}

list_tasks_by_day() {
    read -p "Entrez la date (AAAA-MM-JJ) pour lister les tâches : " input_date
    [[ ! "$input_date" =~ ^[0-9]{4}-[0-9]{2}-[0-9]{2}$ ]] && echo "Format de date invalide. Veuillez entrer la date au format AAAA-MM-JJ." && return
    awk -v date="$input_date" -F '    ' '
        $5 == date {
            print ($6 == "terminée" ? "Terminée" : "Non terminée") " : ID " $1 ", Titre " $2 ", Lieu " $4 ", Date d\'échéance " $5
        }
    ' "$TASKS_FILE"
}

search_task_by_title() {
    read -p "Entrez le titre de la tâche que vous recherchez : " search_title
    awk -v title="$search_title" -F '    ' '
        $2 == title {
            print "Tâche trouvée : ID " $1 ", Titre " $2 ", Lieu " $4 ", Date d\'échéance " $5 ", Achèvement " $6
        }
    ' "$TASKS_FILE"
}

show_help() {
    echo "Utilisation : $0 <commande>"
    echo "Commandes :"
    echo "  create      Créer une nouvelle tâche"
    echo "  update      Mettre à jour une tâche existante"
    echo "  delete      Supprimer une tâche"
    echo "  info        Afficher les informations d'une tâche"
    echo "  list        Lister les tâches d'un jour donné"
    echo "  search      Rechercher une tâche par son titre"
}

[[ "$1" == "--help" ]] && show_help && exit 0
[[ $# -eq 0 ]] && list_tasks_by_day "$(date +'%Y-%m-%d')" && exit 0

case "$1" in
    create) create_task ;;
    update) update_task ;;
    delete) delete_task ;;
    info) task_info ;;
    list) list_tasks_by_day ;;
    search) search_task_by_title ;;
    *) echo "Erreur : Commande inconnue '$1'. Utilisez --help pour l'aide." && exit 1 ;;
esac

