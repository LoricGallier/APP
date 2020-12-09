#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "arbres.h"
#include "arbresphylo.h"
#include "listes.h"

void analyse_arbre (arbre racine, int* nb_esp, int* nb_carac)
{
    (*nb_carac)= 0;
    (*nb_esp)= 0;
    compte_arbre(racine, nb_esp, nb_carac);
}



void compte_arbre (arbre racine, int* nb_esp, int* nb_carac)
{
  if (racine == NULL)
  {
    return;
  }
  if ((racine -> gauche == NULL) && (racine -> droit == NULL))
  {
    (*nb_esp)++;
  }
  else 
  {
    (*nb_carac)++;
    compte_arbre(racine -> gauche, nb_esp, nb_carac);
    compte_arbre(racine -> droit, nb_esp, nb_carac);
  }
}

void dessine_arbre(arbre a, FILE * f)
{
    if (a == NULL)
    {
        return;
    }
	if (a -> gauche == NULL || a -> droit == NULL)
	{
		return;
	}
    
	fprintf (f, "\t%s -> %s [label = \"non\"]\n", a -> valeur, a -> gauche -> valeur);
    dessine_arbre(a -> gauche, f);
	fprintf (f, "\t%s -> %s [label = \"oui\"]\n", a -> valeur, a -> droit -> valeur);
	dessine_arbre(a -> droit, f);
}




/* ACTE II */
/* Recherche l'espece dans l'arbre. Modifie la liste passée en paramètre pour y mettre les
 * caractéristiques. Retourne 0 si l'espèce a été retrouvée, 1 sinon.
 */
int rechercher (arbre racine, char *espece, liste_t* seq)
{
  if (racine == NULL)
  { 
    return 1;
  }
  if (strcmp(racine -> valeur, espece) == 0 )
  {
    return 0;
  }

  int gauche = rechercher( racine -> gauche, espece, seq);
  int droit = rechercher( racine -> droit, espece, seq);

 if (droit == 0)
  {
    ajouter_tete(seq, racine -> valeur);
    return 0;
  }
  else 
  {
    return gauche;
  }
}

int rechercher_espece(arbre racine,char * espece, liste_t * seq)
{
	int trouve = rechercher(racine,espece,seq);
	if (trouve == 0)
	{
		printf("Caracteristiques de l'espece %s: ", espece);
		cellule_t * tmp = seq -> tete;
		while (tmp -> suivant != NULL)
		{
			printf("%s,", tmp -> val);
			tmp = tmp -> suivant;
		}
		printf("%s\n", tmp -> val);
		return 0;
	}
	printf("L'espece \"%s\" n'appartient pas dans l'arbre\n", espece);
	return 1;
}







/* Doit renvoyer 0 si l'espece a bien ete ajoutee, 1 sinon, et ecrire un 
 * message d'erreur.
 */
int ajouter_espece (arbre* a, char *espece, cellule_t* seq)
{
  if (NULL == (*a))
  {
    if (seq == NULL)
    {
      (*a) = malloc(sizeof(noeud));
      (*a)->droit=NULL;
      (*a)->gauche=NULL;
      (*a)->valeur = malloc(strlen(espece)+1);
      strcpy((*a)->valeur,espece);
      return 0;
    }
    else 
    {
      (*a) = malloc(sizeof(noeud));
      (*a)->droit=NULL;
      (*a)->gauche=NULL;
      (*a)->valeur = malloc(strlen(seq->val)+1);
      strcpy((*a)->valeur,seq -> val);
      int vale = ajouter_espece(&(*a) -> droit, espece, seq->suivant);
      return vale;
    }

  }

  else if(((*a)->droit==NULL)&&((*a)->gauche==NULL)&&(seq == NULL))
  {
    printf("Ne peut ajouter %s : possède les meme caracteres que %s ", espece, (*a)->valeur);
    return 1;
  }
  


  else 
  {
    if ((seq != NULL)&&(strcmp((*a) -> valeur, seq->val) == 0 ))
    {
      return (ajouter_espece(&(*a)->droit,espece,seq->suivant)); 
    }
    else
    {
      return (ajouter_espece(&(*a)->gauche,espece,seq));
    }
  }
}


 /*
int ajouter_espece (arbre* a, char *espece, cellule_t* seq) {
  if (a == NULL)
  {  
    if (seq == NULL)
    {
      (*a)=(arbre)malloc(sizeof(noeud));
      (*a)->valeur= espece;
      (*a)->gauche=NULL;
      (*a)->droit=NULL;
      return 0;
    } 
    else 
    {
      (*a)=(arbre)malloc(sizeof(noeud));
      (*a)->valeur= seq -> val;
      (*a)->gauche=NULL;
      (*a)->droit=NULL;
      
      int vale = ajouter_espece(&(*a)->droit, espece, seq->suivant);
      return vale;
    }

  }
  else
  {
    if (seq == NULL)
    {
      printf("Ne peut ajouter %s : possède les meme caracteres que %s ", espece, (*a)->valeur);
      return 1;
    }

    else
    {
      if (strcmp((*a) -> valeur, seq->val) == 0 )
      {
        int vale = ajouter_espece(&(*a)->droit, espece, seq->suivant);
        return vale;
      }
      else
      {
        int vale = ajouter_espece(&(*a)->gauche, espece, seq);
        return vale;
      }
    }
    
  }

}

*/