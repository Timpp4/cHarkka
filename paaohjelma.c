/*****************************************************************************/
/* CT60A0220 C-ohjelmoinnin ja testauksen periaatteet 
 * Tekijä: Tuomas Ikonen
 * Opiskelijanumero: 
 * Päivämäärä: 2.4.2018
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto: moodle, ohjelmointiopas, google
 *
 * paaohjelma.c
 */
/*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esittelyt.h"

int main(void) {
	int valinta = -1;
	nimilista *pAlkuN = NULL;
	tuloslista *pAlku = NULL;
	printf("Tämä ohjelma tutkii nimitietoja sisältäviä tiedostoja.\n");
	while (valinta != 0) {
		valinta = valikko();
		switch (valinta) {
			case 1:
				pAlkuN = lueTiedosto(pAlkuN);
				break;
			case 2:
				tulostaN(pAlkuN);
				break;
			case 3:
				pAlku = analysoi(pAlkuN, pAlku);
				break;
			case 4:
				tulosta(pAlku);
				break;
			case 5:
				tallenna(pAlku);
				break;
			case 6:
				pAlku = vapautaMuisti(pAlku);
				break;
			case 0:
				printf("Kiitos ohjelman käytöstä.\n");
				break;
			default:
				printf("Tuntematon valinta.\n");
				break;
		}
	}
	return 0;
}

/*****************************************************************************/
/* eof */

