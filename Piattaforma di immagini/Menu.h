#ifndef _MENU_H_
#define _MENU_H_

#define _CRT_SECURE_NO_WARNINGS

#include "Utenti.h"

FILE* file;

// Gestisce le funzionalitą del Menu Iniziale, quali registrazione e accesso utente
bool MenuIniziale(bool* isCreatore);

void MenuPrincipale(bool* isCreatore);

#endif