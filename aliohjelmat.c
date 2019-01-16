/*****************************************************************************/
/* CT60A0220 C-ohjelmoinnin ja testauksen periaatteet 
 * Tekijä: Tuomas Ikonen
 * Opiskelijanumero: 
 * Päivämäärä: 2.4.2018
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto: moodle, ohjelmointiopas, google
 *
 * aliohjelmat.c
 */
/*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "esittelyt.h"

/* Valikkopohja */
int valikko(void) {
	int syote;
	printf("1) Lue nimitiedosto\n");
	printf("2) Tulosta listassa olevat tiedot\n");
	printf("3) Analysoi tiedot\n");
	printf("4) Tulosta kaikki tulostiedot\n");
	printf("5) Tallenna kaikki tulostiedot tiedostoon\n");
	printf("6) Tyhjennä tuloslista\n");
	printf("0) Lopeta\n");
	printf("Anna valintasi: ");
	scanf("%d", &syote);
	return syote;
}

/* Tiedoston lukeminen ja nimilistan teko */
void *lueTiedosto(nimilista *pA) {
	char rivi[64];
	char nimi[30];
	int nro, pituus;
	int laskin = -1;
	char *p1, *p2;
	
	getchar();
	printf("Anna luettavan tiedoston nimi: ");
	fgets(nimi, 29, stdin);
	pituus = strlen(nimi);
	if (nimi[pituus-1] == '\n') {
		nimi[pituus-1] = '\0';
	}
	FILE* tiedosto;
	if ((tiedosto = fopen(nimi, "r")) == NULL) {
		perror("Tiedoston avaaminen epäonnistui");
		exit(1);
	}
	if (pA != NULL) {
		printf("Poistetaan aiemmat tiedot ja luetaan uudet.\n");
		pA = vapautaMuistiN(pA);
	}
	printf("Luetaan tiedosto %s.\n", nimi);
	while (fgets(rivi, 63, tiedosto) != NULL) {
		if (laskin < 0) {
			laskin++;
		} else {
			pituus = strlen(rivi);
			if (rivi[pituus-1] == '\n') {
				rivi[pituus-1] = '\0';
			}
			p1 = strtok(rivi, ";");
			p2 = strtok(NULL, "\0");
			nro = atoi(p2);
			pA = lisaaN(pA, p1, nro);
			laskin++;
		}	
	}
	printf("Tiedosto %s luettu, %d nimiriviä.\n", nimi, laskin);
	laskin = -1;
	return pA;
}

/* Nimilistan analysointi */
void *analysoi(nimilista *pAn, tuloslista *pA) {
	char nimi[30];
	char *pNimi;
	int pituus;
	float laskin, ka;
	int pituus_nimi;
	int pienin = 50;
	int suurin = 0;
	int yht = 0;
	long int muisti_vapaa_yht, muisti_max;
	double prosentti;
	pNimi = nimi;
	nimilista *ptr = pAn;

	getchar();
	printf("Anna analysoitavalle datasetille nimi: ");
	fgets(nimi, 29, stdin);
	pituus = strlen(nimi);
	if (nimi[pituus-1] == '\n') {
		nimi[pituus-1] = '\0';
	}
	printf("Analysoidaan listassa olevat tiedot.\n");
	while(ptr != NULL) {
		laskin++;
		pituus_nimi = strlen(ptr->nimi);
		if (pituus_nimi > suurin) {
			suurin = pituus_nimi;
			yht = yht + pituus_nimi;
			ptr=ptr->pNext;
		} else if (pituus_nimi < pienin) {
			pienin = pituus_nimi;
			ptr=ptr->pNext;
		} else {
			yht = yht + pituus_nimi;
			ptr=ptr->pNext;
		}
	}
	/* Lasketaan tiedot */
	ka = yht / laskin;
	muisti_vapaa_yht = laskin*(30-(ka+1));
	muisti_max = laskin*sizeof(struct NodeN);
	prosentti = (double) muisti_vapaa_yht / muisti_max * 100.0;
	prosentti = ceil(100 - prosentti);
	muisti_max = muisti_max / 1000;
	/* Tulostus näytölle */
	printf("Datasetti Nimiä MinPit MaxPit KA Muistinkäyttö\n");
	printf("%s     %.0f    %d       %d   %.0f  %ld kB / %.0f%%\n", nimi, laskin, pienin, suurin, ka, muisti_max, prosentti);
	/* Listaan lisäys myöhempää käyttöä varten */
	pA = lisaa(pA, pNimi, laskin, pienin, suurin, ka, muisti_max, prosentti);

	return pA;
}

/* Tulostustietojen aliohjelmat */
tuloslista* lisaa(tuloslista* pA, char *merkki, float i, int x, int y, float f, long int max, double prosentti) {
	tuloslista *ptr, *ptrUusi;
	if ((ptrUusi=(tuloslista*)malloc(sizeof(tuloslista))) == NULL) {
		perror("Muistin varaus epäonnistui");
		exit(1);
	}
	strcpy(ptrUusi->nimi, merkki);
	ptrUusi->maara = i;
	ptrUusi->pienin = x;
	ptrUusi->suurin = y;
	ptrUusi->ka = f;
	ptrUusi->muisti_max = max;
	ptrUusi->prosentti = prosentti;
	ptrUusi->pNext = NULL;
	if (pA == NULL) {
		pA = ptrUusi;
	} else {
		ptr = pA;
		while (ptr->pNext != NULL) {
			ptr = ptr->pNext;
		}
		ptr->pNext = ptrUusi;
	}
	return pA;
}

void tulosta(tuloslista *pA) {
	tuloslista *ptr = pA;
	printf("Datasetti Nimiä MinPit MaxPit KA Muistinkäyttö\n");
	while (ptr != NULL) {
		printf("%s     %.0f    %d       %d   %.0f  %ld kB / %.0f%%\n", ptr->nimi, ptr->maara, ptr->pienin, ptr->suurin, ptr->ka, ptr->muisti_max, ptr->prosentti);
		ptr = ptr->pNext;
	}
}

tuloslista *vapautaMuisti(tuloslista *pA) {
	tuloslista *ptr = pA;
	while (ptr != NULL) {
		pA = ptr->pNext;
		free(ptr);
		ptr = pA;
	}
	printf("Tuloslista tyhjennetty.\n");
	return pA;
}

/* Tallennus tiedostoon */
void tallenna(tuloslista *pA) {
	char nimi[30];
	int pituus;
	tuloslista *ptr = pA;

	getchar();
	printf("Anna tallennettavan tulostiedoston nimi: ");
	fgets(nimi, 29, stdin);
	pituus = strlen(nimi);
	if (nimi[pituus-1] == '\n') {
		nimi[pituus-1] = '\0';
	}
	FILE* tiedosto;
	if ((tiedosto = fopen(nimi, "w")) == NULL) {
		perror("Tiedoston avaaminen epäonnistui");
		exit(1);
	}
	
	fprintf(tiedosto, "Datasetti Nimiä MinPit MaxPit KA Muistinkäyttö\n");
	while (ptr != NULL) {
		fprintf(tiedosto, "%s     %.0f    %d       %d   %.0f  %ld kB / %.0f%%\n", ptr->nimi, ptr->maara, ptr->pienin, ptr->suurin, ptr->ka, ptr->muisti_max, ptr->prosentti);
		ptr = ptr->pNext;
	}
	fclose(tiedosto);
	printf("Tiedosto tallennettu.\n");
}

/* Nimilistan aliohjelmat */
nimilista* lisaaN(nimilista* pA, char *merkki, long int i) {
	nimilista *ptr, *ptrUusi;
	if ((ptrUusi=(nimilista*)malloc(sizeof(nimilista))) == NULL) {
		perror("Muistin varaus epäonnistui");
		exit(1);
	}
	strcpy(ptrUusi->nimi, merkki);
	ptrUusi->maara = i;
	ptrUusi->pNext = NULL;
	if (pA == NULL) {
		pA = ptrUusi;
	} else {
		ptr = pA;
		while (ptr->pNext != NULL) {
			ptr = ptr->pNext;
		}
		ptr->pNext = ptrUusi;
	}
	return pA;
}

void tulostaN(nimilista *pA) {
	nimilista *ptr = pA;
	printf("Listan tiedot\n");
	while (ptr != NULL) {
		printf("%s;%ld\n", ptr->nimi, ptr->maara);
		ptr = ptr->pNext;
	}
}

nimilista *vapautaMuistiN(nimilista *pA) {
	nimilista *ptr = pA;
	while (ptr != NULL) {
		pA = ptr->pNext;
		free(ptr);
		ptr = pA;
	}
	return pA;
}

/*****************************************************************************/
/* eof */

