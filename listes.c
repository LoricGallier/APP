#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "listes.h"

/* fichier à compléter au besoin */

cellule_t * nouv_noeud(string c)
{
	cellule_t * nouv = (cellule_t *)malloc(sizeof(cellule_t));
	nouv -> val = c;
	nouv -> suivant = NULL;
	return nouv;
}

void init_liste_vide(liste_t* L)
{
  L -> tete = NULL;
}

int ajouter_tete(liste_t* L, string c) 
{
  cellule_t * noeud = nouv_noeud(c);
  if (noeud == NULL)
  {
    return 1;
  }
  noeud -> suivant = L -> tete;
  L -> tete = noeud;
  return 0;
}
