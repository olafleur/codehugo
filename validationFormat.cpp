/*
 * Fonctions.cpp
 *
 *  Created on: 2017-02-06
 *      Author: etudiant
 */

#include <iostream>
#include <sstream>
#include <iomanip>
#include <locale>
using namespace std;
#include "fonctions.h"


bool validerTelephone(const std::string& p_telephone)
{
		/*
		 *  on verifie en premier la longueur pour etre sur que ca correspond
		 *  a 12 caracteres (code regional + espace + 3 chiffres + tiret + 4 chiffres)
		 */
		int longueur = p_telephone.length();
		char tableauchar[longueur];
		if (longueur != 12)
			{
			return false;
			}

		/*
		 * on met chacun des caracteres dans un tableau (j'ai realise plus tard que c'etait inutile,
		 * mais je n'avais pas envie de tout changer).
		 *
		 */
		for (int i=0; i<= longueur; i++ )
			{
				tableauchar[i] = p_telephone[i];
			}

		/*
		 * on verifie s'il y a des chiffres, des espace et des tirets a la bonne place
		 * il y aurait maniere d'alleger le code en enlevant la verification des trois premiers chiffres,
		 * etant donne que je verifie si le code regional est valide.
		 */
		for (int i=0; i < 3; i++)
			{
				if (isdigit(tableauchar[i]))
				{

				}
				else
				{
					return false;
				}
			}
		if (tableauchar[3] != ' ')
			{
			return false;
			}
		for (int i=4; i < 7; i++)
			{
				if (isdigit(tableauchar[i]))
				{

				}
				else
				{
					return false;
				}
			}
		if (tableauchar[7] != '-')
			{
			return false;
			}
		for (int i=8; i < 12; i++)
			{
				if (isdigit(tableauchar[i]))
				{

				}
				else
				{
					return false;
				}
			}
		/*
		 * on verifie si le code regional est valide en generant un tableau qui contient toutes les possibilites
		 * et en comparant les trois premieres valeurs a chaque entree de ce tableau
		 */

		string indicateur;
		for (int i = 0; i < 3; i++)
			{
			 indicateur += (tableauchar[i]);
			}
		string listeregion[35] = {
				"800", "866", "877", "888", "855", "900", "976", "403", "780", "604", "236", "250", "778", "902", "204", "506", "902", "905", "519",
				"289", "705", "613", "807", "416", "647", "438", "514", "450", "579", "418", "581", "819", "306", "709", "867"
		};
		for (int i = 0; i < 35; i++)
			{
				if (indicateur == listeregion[i])
					{
						return true;
					}
			}
		return false;
}

bool validerNumRAMQ(const std::string& p_numero, const std::string& p_nom, const
std::string& p_prenom, int p_jourNaissance, int p_moisNaissance, int
p_anneeNaissance, char p_sex)
{

	/*
	 * je cree des strings qui vont contenir des extraits du code complet pour les comparer
	 * aux autres entrees de la fonction plus tard
	 */

	locale loc;
	string nonom;
	for (int i = 0; i < 3; i++)
	{

		nonom += (p_numero[i]);
	}
	string noprenom;
	noprenom += (p_numero[3]);

	/*
	 * on verifie aussi si les espaces sont aux bons endroits
	 */

	if (p_numero[4] != ' ')
	{
		return false;
	}

	string noannee;
	for (int i = 5; i < 7; i++)
	{
		noannee += (p_numero[i]);
	}

	string nomois;
	for (int i = 7; i < 9; i++)
	{
		nomois += (p_numero[i]);
	}
	string nojour;

	if (p_numero[9] != ' ')
	{
		return false;
	}


	for (int i = 10; i < 12; i++)
	{
		nojour += (p_numero[i]);
	}

	/*
	 * on prend maintenant des extraits du nom et prenom pour avoir le morceau a comparer avec les
	 * morceaux du code d'assurance maladie complet
	 */

	string nom;
	for (int i = 0; i < 3; i++)
	{
		nom += (p_nom[i]);
	}

	for (size_t up = 0; up < nom.size(); up++)
	{
		nom[up] = toupper(nom[up], loc);
	}


	string prenom;
	prenom += (p_prenom[0]);
	prenom [0] = toupper(prenom[0], loc);

	/*
	 * on change les int de mois et jour en string pour faciliter la comparaison. On fait la meme chose
	 * avec l'annee mais on garde seulement la valeur des deux derniers chifres.
	 */

	stringstream ss;
	ss << p_jourNaissance;
	string jour = ss.str();
	ss.str("");

	int moismodifie;

	if (p_sex == 'F' || p_sex == 'f' || p_sex == 'M' || p_sex == 'm')
	{

	}
	else
	{
		return false;
	}

	if (p_sex == 'F' || p_sex == 'f')
	{
		moismodifie = p_moisNaissance + 50;
	}
	if (p_sex == 'M' || p_sex == 'm')
	{
		moismodifie = p_moisNaissance;
	}

	ss << std::setw(2) << std::setfill('0') << moismodifie;
	string mois = ss.str();
	ss.str("");

	ss << p_anneeNaissance;
	string annee = ss.str();
	string anneedernier;
	for (int i = 2; i < 4 ; i++)
	{
		anneedernier += annee[i];
	}

	/*
	 * on fait maintenant une batterie de comparaisons pour etre sur que tout concorde.
	 */

	if (nonom != nom)
	{
		return false;
	}
	if (noprenom != prenom)
	{
		return false;
	}
	if (noannee != anneedernier)
	{
		return false;
	}
	if (nomois != mois)
	{
		return false;
	}
	if (nojour != jour)
	{
		return false;
	}
	return true;
}

