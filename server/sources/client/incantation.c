/*
** EPITECH PROJECT, 2019
** incantation.c
** File description:
** Incantation command.
*/

#include "client.h"

//TODO: Complete incantation command.
static int is_incant_possible(client_t *client, server_t *server)
{
    return 1;
}

char *incante(client_t *client, server_t *server)
{
    if (!is_incant_possible(client, server))
        return "ko";
    client->cooldown = 700;
    return "Elevation underway\nCurrent level: %d";
}
