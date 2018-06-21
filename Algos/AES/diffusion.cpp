#include "stdafx.h"
#include "diffusion.h"

/* le sous programme qui étant donné un bit à changer i,
message de départ et celui auquel le compare, fait subir
AES_Encrypt puis renvoie le nombre de bits qui ont changé
par rapport à l'état "origin_state" */

unsigned int aux(byte* origin_state, byte* message, byte* turn_keys, byte* state, unsigned int KEY_SIZE, unsigned int i, unsigned int j)
{
	byte temp = message[i];
	message[i] = message[i] ^ (1 << j);
	printf(" (%u %u) ", i, j);
	AES_Encrypt(message, turn_keys, state, KEY_SIZE);
	
	unsigned int tmp = 0, nb = 0;

	for (unsigned int k = 0; k < 16; k++)
	{
		tmp = state[k] ^ origin_state[k];
		while (tmp != 0)
		{
			nb += tmp & 1;
			tmp = tmp >> 1;
		}
	}

	message[i] = temp;

	return nb;
}

double test_diffusion_1(byte* message, byte* turn_keys, unsigned int KEY_SIZE)
{
	byte origin_state[17];
	AES_Encrypt(message, turn_keys, origin_state, KEY_SIZE);
	
	unsigned int sum_tmp = 0;
	unsigned int tmp = 0;

	ofstream myfile;
	myfile.open("diffusion.txt");

	byte state[17];

	for (unsigned int i = 0; i < 16; i++)
	{
		for (unsigned int j = 0; j < 8; j++)
		{
			tmp = aux(origin_state, message, turn_keys, state, KEY_SIZE, i, j);

			myfile << tmp << ", ";

			sum_tmp += tmp;
		}
			
	}

	myfile.close();

	// la fréquence d'une fois est tmp / (len_msg * 8)
	// celle du total est donc sum_tmp / ("nombre de rounds" * len_msg)
	return (double)sum_tmp / 16384.;
}

double* test_diffusion_2(byte* message, byte* turn_keys, byte* state, unsigned int KEY_SIZE, unsigned int len_msg, unsigned int NB_ROUNDS)
{
	double* resultat = new double[NB_ROUNDS];

	for (unsigned int i = 0; i < NB_ROUNDS; i++)
		resultat[i] = test_diffusion_1(message, turn_keys, KEY_SIZE);

	return resultat;
}

void main()
{
	unsigned int numberOfRounds = 10;
	unsigned int KEY_SIZE = 128;
	byte turn_keys[(10 + 1) * 16];		// 10 = number of rounds
	byte message[200];
	strcpy((char *)message, "mdrelovs zqdsf c'etg skd");

	KeyExpansion((byte *)"ceci est un test", turn_keys, KEY_SIZE);

	float f;
	f = test_diffusion_1(message, turn_keys, KEY_SIZE);

	printf("%f", f);
	printf("\n");
}