#pragma once
#include "stdafx.h"
#include "stdio.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

//TODO: mettre KeyExpansion dans le main

#include "windows.h"
using namespace std;

typedef unsigned char byte;



void AES_Decrypt(byte * message, byte * turn_keys, byte * state, unsigned int KEY_SIZE);

void AES_Encrypt(byte * message, byte * turn_keys, byte * state, unsigned int KEY_SIZE);

void KeyExpansion(byte * state, byte * turn_keys, unsigned int KEY_SIZE);
