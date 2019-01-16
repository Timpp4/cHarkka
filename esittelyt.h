/*****************************************************************************/
/* CT60A0220 C-ohjelmoinnin ja testauksen periaatteet 
 * Tekijä: Tuomas Ikonen
 * Opiskelijanumero: 
 * Päivämäärä: 2.4.2018
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto: moodle, ohjelmointiopas, google
 *
 * esittelyt.h
 */
/*****************************************************************************/
struct NodeN { /* Nimitiedot */
	char nimi[30];
	long int maara;
	struct NodeN *pNext;
};
typedef struct NodeN nimilista;

struct NodeT { /* Tulostiedot */
	char nimi[10];
	float maara;
	int pienin;
	int suurin;
	float ka;
	long int muisti_max;
	double prosentti;
	struct NodeT *pNext;
};
typedef struct NodeT tuloslista;

/* Nimitiedot, esittelyt */
nimilista* lisaaN(nimilista* pA, char *merkki, long int i);
void tulostaN(nimilista *pA);
nimilista *vapautaMuistiN(nimilista *pA);

/* Tulostiedot, esittelyt */
tuloslista* lisaa(tuloslista* pA, char *merkki, float i, int x, int y, float f, long int max, double prosentti);
void tulosta(tuloslista *pA);
tuloslista *vapautaMuisti(tuloslista *pA);

/* Muut aliohjelmat */
int valikko(void);
void *lueTiedosto(nimilista *pA);
void *analysoi(nimilista *pAn, tuloslista *pA);
void tallenna(tuloslista *pA);

/*****************************************************************************/
/* eof */
