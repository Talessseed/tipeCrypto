/* le sous programme qui étant donné un bit à changer i,
   message de départ et celui auquel le compare, fait subir 
   AES_Encrypt puis renvoie le nombre de bits qui ont changé 
   par rapport à l'état "origin_state" */
   
void aux(byte* origin_state, byte* message, byte* turn_keys, byte* state, unsigned int KEY_SIZE, unsigned int i, len_msg)
{
    state[i] = 1 - state[i]
    AES_Encrypt(message, turn_keys, state, KEY_size);
    unsigned int tmp = 0;
    
    for (unsigned int j = 0; j < len_msg; j++)
        tmp += (state[j] ^ origin_state[j];
    
    return tmp;
}


void test_diffusion_1 (byte* message, byte* turn_keys, byte* state, unsigned int KEY_SIZE, unsigned int len_msg)
{
    byte* origin_state = new byte [len_msg];
    AES_Encrypt (message, turn_keys, origin_state, KEY_SIZE);
    unsigned int sum_tmp = 0;
    
    for (unsigned int i = 0; i < len_msg; i++)
    {
        byte* state = new byte [len_msg];
        sum_tmp += aux(message, turn_keys, state, KEY_SIZE, int i, len_msg);
    }
    
    // la fréquence d'une fois est tmp / len_msg
    // celle du total est donc sum_tmp / "nombre de rounds"
    return (sum_tmp / len_msg * len_msg);
}

void test_diffusion_2 (byte* message, byte* turn_keys, byte* state, unsigned int KEY_SIZE, unsigned int len_msg, No_ROUNDS)
{
    int resultat[No_ROUNDS];
    
    for (unsigned int i = 0; i < No_ROUNDS; i++)
        resultat[i] = test_diffusion_1(message, turn_keys, state, KEY_SIZE, int len_msg);
    
    return resultat
}
