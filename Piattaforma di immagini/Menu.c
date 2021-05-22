#include "Menu.h"


bool MenuIniziale(bool* isCreatore, char nomeUtente[])
{
	bool inEsecuzione = true;
	do
	{
		red();
		printf("Benvenuto sulla piattaforma di immagini!");
		reset();
		printf("\n\n1. Registrazione utente\n2. Accesso utente\n3. Esci\n\n");

		unsigned int sceltaMenu;
		bool errore = false;
		scanf("%1u", &sceltaMenu);


		switch (sceltaMenu)
		{
			case 1: // Registrazione utente
			{
				system("cls");
				do
				{
					errore = false;
					Creatore_t creatore = { 0 };
					Utilizzatore_t utilizzatore = { 0 };

					red();
					puts("Che tipologia di utente sei?");
					reset();
					printf("\n1.Creatore\n2.Utilizzatore\n3.Indietro\n");
					scanf("%1u", &sceltaMenu);

					system("cls");

					switch (sceltaMenu)
					{
						// Registrazione utente Creatore
						case 1: 
						{
							InserisciDatiCreatore(file, &creatore, nomeUtente);
						
							// Fase di salvataggio dei dati su file
							file = ApriFile(PERCORSO_FILE_CREATORI);
							SalvaDatiCreatore(file, &creatore);

							fclose(file);

							red();
							printf("\nCreatore correttamente registrato! Verrai ora reindirizzato al menu principale.\n\n");
							reset();
							system("pause");
							*isCreatore = true; // Do l'accesso al menu principale creatore
							return true;
							break;
						}
					


						// Registrazione utente Utilizzatore
						case 2:
						{
							InserisciDatiUtilizzatore(file, &utilizzatore, nomeUtente);

							// Fase di salvataggio dei dati su file
							file = ApriFile(PERCORSO_FILE_UTILIZZATORI);
						
							SalvaDatiUtilizzatore(file, &utilizzatore);

							fclose(file);

							red();
							printf("\nUtilizzatore correttamente registrato! Verrai ora reindirizzato al menu principale.\n\n");
							reset();
							system("pause");
							*isCreatore = false;
							return true;
							break;
						}
						// Indietro
						case 3:
							errore = false;
							break;
						default:
							errore = true;
							red();
							printf("\nErrore! Selezionare un'opzione valida!\n\n");
							reset();
							break;
						}
				} while (errore);
				break;
			}

			// Accesso utente
			case 2:
			{
				do
				{
					errore = false;
					*isCreatore = false;
					bool indietro = false; // flag indietro
					system("cls");
					green();
					printf("Inserire il nome utente: ");
					reset();
					char buffer[MAX_BUFFER] = { 0 };

					scanf("%100s", buffer);

					// Controlla se l'utente ha inserito '0', nel caso flagga indietro
					if (buffer[0] == '0')
					{
						if (buffer[1] == '\0')
						{
							errore = false;
							indietro = true;
						}
					}

					// Se invece ha messo un input valido per il nome utente prosegui
					// Controlla prima creatori e poi utilizzatori se necessario
					if (indietro == false)
					{
						file = ApriFile(PERCORSO_FILE_CREATORI);

						bool esisteNomeUtente = ControllaNomeUtenteCreatore(file, buffer);
						if (esisteNomeUtente)
							*isCreatore = true;
					

						if (!esisteNomeUtente)
						{
							fclose(file);
							file = ApriFile(PERCORSO_FILE_UTILIZZATORI);

							esisteNomeUtente = ControllaNomeUtenteUtilizzatore(file, buffer);
							*isCreatore = false;
							fclose(file);
						}


						// Se il nome utente inserito esiste, chiedi la password
						if (esisteNomeUtente)
						{
							strcpy(nomeUtente, buffer);
							green();
							printf("Inserire la password: ");
							reset();
							char buffer[MAX_BUFFER] = { 0 };
							SvuotaInput();
							scanf("%100s", buffer);
						

							bool passwordCorretta = ControllaPassword(file, buffer, nomeUtente);

							if (passwordCorretta)
							{
								fclose(file);
								return true;
								// Esci dal menu iniziale e prosegui nel main col menu principale
							}
							else
							{
								red();
								printf("\nErrore! Password non corretta! Riprovare.\n\n");
								reset();
								system("pause");
								errore = true;
							}

						}
						else
						{
							red();
							printf("\nErrore! Nome utente non esistente. \nControllare il nome utente digitato oppure digita 0 per tornare al menu iniziale e registrarsi.\n\n");
							reset();
							system("pause");
							errore = true;
						}
						fclose(file);
					}
				} while (errore);
		
				break;
			}


			case 3:
				inEsecuzione = false;
				break;
			default:
				red();
				puts("\nErrore! Selezionare un'opzione valida!\n\n");
				reset();
				system("pause");
				break;
		}

		system("cls");

	} while (inEsecuzione == true);

	return false;
}

void MenuPrincipale(bool* isCreatore, char nomeUtente[])
{
	
	bool inEsecuzione = true;
	if (*isCreatore)
	{
		// Menu Creatore
		do
		{
			system("cls");

			red();
			printf("Benvenuto sulla piattaforma di immagini %s! \n\n", nomeUtente);
			reset();
			printf("1. Gestione creatore\n2. Ricerca immagine\n3. Statistiche creatore\n4. Classifiche\n5. Esci\n");

			unsigned int sceltaMenu;
			bool ripeti = false;
			scanf("%1u", &sceltaMenu);

			switch (sceltaMenu)
			{
				// Gestione creatore
				case 1:
				{
					GestioneCreatore(nomeUtente);
					break;
				}
				// Ricerca immagine
				case 2:
				{
					RicercaImmagineCreatore(nomeUtente);
					break;
				}
				// Statistiche creatore
				case 3:
				{
					StatisticheCreatore();
					break;
				}
				// Classifiche
				case 4:
				{
					Classifiche();
					break;
				}
				// Esci
				case 5:
				{
					inEsecuzione = false;
					system("cls");
					break;
				}
				default:
					red();
					printf("\nSelezionare un opzione valida!\n\n");
					reset();
					system("pause");
					break;
			}
		} while (inEsecuzione == true);
	}
	
	else
	{
		// Menu Utilizzatore
		do
		{
			system("cls");

			red();
			printf("Benvenuto sulla piattaforma di immagini %s! \n\n", nomeUtente);
			reset();
			printf("1. Ricerca immagine\n2. Statistiche creatore\n3. Classifiche\n4. Esci\n");

			unsigned int sceltaMenu;
			bool ripeti = false;
			scanf("%1u", &sceltaMenu);

			switch (sceltaMenu)
			{
			// Ricerca immagine
			case 1:
			{
				RicercaImmagineUtilizzatore(nomeUtente);
				break;
			}
			// Statistiche creatore
			case 2:
			{
				StatisticheCreatore();
				break;
			}
			// Classifiche
			case 3:
			{
				Classifiche();
				break;
			}
			// Esci
			case 4:
			{
				inEsecuzione = false;
				system("cls");
				break;
			}
			default:
				red();
				printf("\nSelezionare un opzione valida!\n\n");
				reset();
				system("pause");
				break;
			}
		} while (inEsecuzione == true);
	}
}