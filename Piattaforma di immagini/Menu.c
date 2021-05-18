#define _CRT_SECURE_NO_WARNINGS

#include "Menu.h"

bool MenuIniziale(bool* isCreatore, char nomeUtente[])
{
	bool inEsecuzione = true;
	do
	{
		puts("Benvenuto sulla piattaforma di immagini! \n\n1. Registrazione utente\n2. Accesso utente\n3. Esci\n");

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

				puts("Che tipologia di utente sei?\n1. Creatore\n2. Utilizzatore\n3. Indietro\n");
				scanf("%1u", &sceltaMenu);

				system("cls");

				switch (sceltaMenu)
				{
					// Registrazione utente Creatore
					case 1: 
					{
						puts("Registrazione utente creatore");
						// Inserimento NOME UTENTE
						do
						{
							errore = false;
							printf("\nInserire un nome utente (min. 4 caratteri): ");
							char buffer[MAX_BUFFER] = { 0 };
							scanf("%100s", buffer);
							SvuotaInputFGets(buffer);


							file = fopen(PERCORSO_FILE_CREATORI, "r");
							bool giaEsistente = false;

							// Se il file non esiste, creane uno
							if (file == NULL)
							{
								file = fopen(PERCORSO_FILE_CREATORI, "w");
								fclose(file);
								file = fopen(PERCORSO_FILE_CREATORI, "r");
							}
							
							giaEsistente = ControllaNomeUtente(file, buffer);
							fclose(file);

							// Controlliamo anche il file utilizzatori.dat se non l'ha gi� trovato
							if (giaEsistente == false)
							{
								file = fopen(PERCORSO_FILE_UTILIZZATORI, "r");
								// Se � la prima esecuzione e/o il file non esiste, creane uno
								if (file == NULL)
								{
									file = fopen(PERCORSO_FILE_UTILIZZATORI, "w");
									fclose(file);
									file = fopen(PERCORSO_FILE_UTILIZZATORI, "r");
								}

								giaEsistente = ControllaNomeUtente(file, buffer);

								fclose(file);
							}

							if (strlen(buffer) < MIN_CAR_NOME_UTENTE)
							{
								errore = true;
								puts("Errore! Inserire un nome utente di almeno 4 caratteri!\n");
							}
							else if (giaEsistente == true)
							{
								errore = true;
								puts("Errore! Nome utente gia' esistente!\n");
							}
							// Altrimenti procedi
							else
							{
								AssegnaStringa(creatore.nomeUtente, buffer, false);
								AssegnaStringa(nomeUtente, buffer, false); // Passo al main il nomeUtente (per il menu principale)
							}
						} while (errore);

						// Inserimento PASSWORD
						do
						{
							errore = false;
							printf("Inserire una password (min. 8 caratteri): ");
							char buffer[MAX_BUFFER] = { 0 };
							scanf("%100s", buffer);
							SvuotaInputFGets(buffer);

							// Controlla che il minimo sia rispettato
							if (strlen(buffer) < MIN_CAR_PASSWORD)
							{
								errore = true;
								puts("Errore! Inserire una password di almeno 8 caratteri!\n");
							}

							// Altrimenti procedi
							else
								AssegnaStringa(creatore.password, buffer, false);
						} while (errore);

						// Inserimento NOME
						do
						{
							errore = false;
							printf("Inserire il nome: ");
							char buffer[MAX_BUFFER] = { 0 };
							fgets(buffer, 100, stdin); // FGETS PER PRENDERE ANCHE GLI SPAZI EVENTUALMENTE
							SvuotaInputFGets(buffer);

							// Conversione della stringa in minuscolo
							ConversioneMinuscolo(buffer);

							// Controlla che non contenga simboli
							errore = ContieneSimboli(buffer, false);

							// Altrimenti procedi
							if (!errore)
								AssegnaStringa(creatore.nome, buffer, true);
						} while (errore);

						// Inserimento COGNOME
						do
						{
							errore = false;
							printf("Inserire il cognome: ");
							char buffer[MAX_BUFFER] = { 0 };
							fgets(buffer, 100, stdin);
							SvuotaInputFGets(buffer);

							// Conversione della stringa in minuscolo
							ConversioneMinuscolo(buffer);

							// Controlla che non contenga simboli
							errore = ContieneSimboli(buffer, false);

							// Altrimenti procedi
							if (!errore)
								AssegnaStringa(creatore.cognome, buffer, true);
						} while (errore);

						// Inserimento SESSO
						do
						{
							errore = false;
							printf("Inserire il sesso (M/F): ");
							scanf("%c", &creatore.sesso);
							creatore.sesso = toupper(creatore.sesso);
							SvuotaInputGetChar();

							// Controllo errori
							if (creatore.sesso != 'M' && creatore.sesso != 'F')
							{
								errore = true;
								printf("Errore! Inserire M o F!\n");
							}
						} while (errore);

						// Inserimento PROFESSIONE
						do
						{
							errore = false;
							printf("Inserire la professione: ");
							char buffer[MAX_BUFFER] = { 0 };
							fgets(buffer, 100, stdin);
							SvuotaInputFGets(buffer);

							// Conversione della stringa in minuscolo
							ConversioneMinuscolo(buffer);

							// Controlla che non contenga simboli
							errore = ContieneSimboli(buffer, false);

							if (!errore)
								AssegnaStringa(creatore.professione, buffer, true);
						} while (errore);

						// Inserimento NAZIONALITA
						do
						{
							errore = false;
							printf("Inserire la nazionalita': ");
							char buffer[MAX_BUFFER] = { 0 };
							fgets(buffer, 100, stdin);
							SvuotaInputFGets(buffer);

							// Conversione della stringa in minuscolo
							ConversioneMinuscolo(buffer);

							// Controlla che non contenga simboli
							errore = ContieneSimboli(buffer, false);

							// Altrimenti procedi
							if (!errore)
								AssegnaStringa(creatore.nazionalita, buffer, true);
						} while (errore);

						// Inserimento DATA DI NASCITA
						do
						{
							errore = false;
							printf("Inserire la data di nascita (GG/MM/AAAA): ");
							scanf("%u/%u/%u", &creatore.dataNascita.giorno, &creatore.dataNascita.mese, &creatore.dataNascita.anno);

							if (DataCorretta(creatore.dataNascita.giorno, creatore.dataNascita.mese, creatore.dataNascita.anno) == false)
							{
								errore = true;
								printf("Errore! La data e' incorretta!\n");
							}
						} while (errore);

						// Assegnazione data di iscrizione
						time_t t = time(NULL);
						struct tm tm = *localtime(&t);
						creatore.dataIscrizione.giorno = tm.tm_mday;
						creatore.dataIscrizione.mese = tm.tm_mon + 1;
						creatore.dataIscrizione.anno = tm.tm_year + 1900;

						// Fase di salvataggio dei dati su file
						file = fopen(PERCORSO_FILE_CREATORI, "a");
						if (file == NULL)
						{
							printf("\n\n\nERRORE FATALE! Non e' stato possibile aprire il file\n");
							exit(EXIT_SUCCESS);
						}
						else
						{
							SalvaDatiCreatore(file, &creatore);

							fclose(file);

							printf("Creatore correttamente registrato! Verrai ora reindirizzato al menu principale.\n\n");
							InvioPerContinuare();
							*isCreatore = true; // Do l'accesso al menu principale creatore
							return true;
						}
						break;
					}
					


					// Registrazione utente Utilizzatore
					case 2:
					{
						puts("Registrazione utente utilizzatore");
						// Inserimento NOME UTENTE
						do
						{
							errore = false;
							printf("\nInserire un nome utente (min. 4 caratteri): ");
							char buffer[MAX_BUFFER] = { 0 };
							scanf("%100s", buffer);
							SvuotaInputFGets(buffer);

							file = fopen(PERCORSO_FILE_CREATORI, "r");
							bool giaEsistente = false;

							// Se il file non esiste, creane uno
							if (file == NULL)
							{
								file = fopen(PERCORSO_FILE_CREATORI, "w");
								fclose(file);
								file = fopen(PERCORSO_FILE_CREATORI, "r");
							}

							giaEsistente = ControllaNomeUtente(file, buffer);

							fclose(file);

							if (giaEsistente == false)
							{
								file = fopen(PERCORSO_FILE_UTILIZZATORI, "r");
								// Se il file non esiste, creane uno
								if (file == NULL)
								{
									file = fopen(PERCORSO_FILE_UTILIZZATORI, "w");
									fclose(file);
									file = fopen(PERCORSO_FILE_UTILIZZATORI, "r");
								}

								giaEsistente = ControllaNomeUtente(file, buffer);

								fclose(file);
							}

							if (strlen(buffer) < MIN_CAR_NOME_UTENTE)
							{
								errore = true;
								puts("Errore! Inserire un nome utente di almeno 4 caratteri!\n");
							}
							else if (giaEsistente == true)
							{
								errore = true;
								puts("Errore! Nome utente gia' esistente!\n");
							}
							// Altrimenti procedi
							else
							{
								AssegnaStringa(utilizzatore.nomeUtente, buffer, false);
								AssegnaStringa(nomeUtente, buffer, false);
							}
						} while (errore);

						// Inserimento PASSWORD
						do
						{
							errore = false;
							printf("Inserire una password (min. 8 caratteri): ");
							char buffer[MAX_BUFFER] = { 0 };
							scanf("%100s", buffer);
							SvuotaInputFGets(buffer);

							// Controlla che il minimo sia rispettato
							if (strlen(buffer) < MIN_CAR_PASSWORD)
							{
								errore = true;
								puts("Errore! Inserire una password di almeno 8 caratteri!\n");
							}

							// Altrimenti procedi
							else
								AssegnaStringa(utilizzatore.password, buffer, false);
						} while (errore);

						// Inserimento NOME
						do
						{
							errore = false;
							printf("Inserire il nome: ");
							char buffer[MAX_BUFFER] = { 0 };
							fgets(buffer, 100, stdin);
							SvuotaInputFGets(buffer);

							// Conversione della stringa in minuscolo
							ConversioneMinuscolo(buffer);

							// Controlla che non contenga simboli
							errore = ContieneSimboli(buffer, false);

							// Altrimenti procedi
							if (!errore)
								AssegnaStringa(utilizzatore.nome, buffer, true);
						} while (errore);

						// Inserimento COGNOME
						do
						{
							errore = false;
							printf("Inserire il cognome: ");
							char buffer[MAX_BUFFER] = { 0 };
							fgets(buffer, 100, stdin);
							SvuotaInputFGets(buffer);
							
							// Conversione della stringa in minuscolo
							ConversioneMinuscolo(buffer);

							// Controlla che non contenga simboli
							errore = ContieneSimboli(buffer, false);

							// Altrimenti procedi
							if (!errore)
								AssegnaStringa(utilizzatore.cognome, buffer, true);
						} while (errore);

						// Inserimento SESSO
						do
						{
							errore = false;
							printf("Inserire il sesso (M/F): ");
							scanf("%c", &utilizzatore.sesso);
							utilizzatore.sesso = toupper(utilizzatore.sesso);
							SvuotaInputGetChar();

							// Controllo errori
							if (utilizzatore.sesso != 'M' && utilizzatore.sesso != 'F')
							{
								errore = true;
								printf("Errore! Inserire M o F!\n");
							}
						} while (errore);

						// Inserimento PROFESSIONE
						do
						{
							errore = false;
							printf("Inserire la professione: ");
							char buffer[MAX_BUFFER] = { 0 };
							fgets(buffer, 100, stdin);
							SvuotaInputFGets(buffer);

							// Conversione della stringa in minuscolo
							ConversioneMinuscolo(buffer);

							// Controlla che non contenga simboli
							errore = ContieneSimboli(buffer, false);

							if (!errore)
								AssegnaStringa(utilizzatore.professione, buffer, true);
						} while (errore);

						// Inserimento NAZIONALITA
						do
						{
							errore = false;
							printf("Inserire la nazionalita': ");
							char buffer[MAX_BUFFER] = { 0 };
							fgets(buffer, 100, stdin);
							SvuotaInputFGets(buffer);

							// Conversione della stringa in minuscolo
							ConversioneMinuscolo(buffer);

							// Controlla che non contenga simboli
							errore = ContieneSimboli(buffer, false);

							// Altrimenti procedi
							if (!errore)
								AssegnaStringa(utilizzatore.nazionalita, buffer, true);
						} while (errore);

						// Inserimento DATA DI NASCITA
						do
						{
							errore = false;
							printf("Inserire la data di nascita (GG/MM/AAAA): ");
							scanf("%u/%u/%u", &utilizzatore.dataNascita.giorno, &utilizzatore.dataNascita.mese, &utilizzatore.dataNascita.anno);

							if (DataCorretta(utilizzatore.dataNascita.giorno, utilizzatore.dataNascita.mese, utilizzatore.dataNascita.anno) == false)
							{
								errore = true;
								printf("Errore! La data e' incorretta!\n");
							}
						} while (errore);

						// Assegnazione data di iscrizione
						time_t t = time(NULL);
						struct tm tm = *localtime(&t);
						utilizzatore.dataIscrizione.giorno = tm.tm_mday;
						utilizzatore.dataIscrizione.mese = tm.tm_mon + 1;
						utilizzatore.dataIscrizione.anno = tm.tm_year + 1900;

						// Fase di salvataggio dei dati su file
						file = fopen(PERCORSO_FILE_UTILIZZATORI, "a");
						if (file == NULL)
						{
							printf("\n\n\nERRORE FATALE! Non e' stato possibile aprire il file\n");
							exit(EXIT_SUCCESS);
						}
						else
						{	
							SalvaDatiUtilizzatore(file, &utilizzatore);

							fclose(file);

							printf("\n\nUtilizzatore correttamente registrato! Verrai ora reindirizzato al menu principale.\n\n");
							InvioPerContinuare();
							*isCreatore = false;
							return true;
						}
						break;
					}
					// Indietro
					case 3:
						errore = false;
						break;
					default:
						errore = true;
						printf("Errore! Selezionare un'opzione valida!");
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
				printf("Inserire il nome utente: ");
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
					file = fopen(PERCORSO_FILE_CREATORI, "r");
					// Se il file non esiste, creane uno
					if (file == NULL)
					{
						file = fopen(PERCORSO_FILE_CREATORI, "w");
						fclose(file);
						file = fopen(PERCORSO_FILE_CREATORI, "r");
					}

					bool esisteNomeUtente = ControllaNomeUtente(file, buffer);
					if (esisteNomeUtente)
						*isCreatore = true;
					

					if (!esisteNomeUtente)
					{
						fclose(file);
						file = fopen(PERCORSO_FILE_UTILIZZATORI, "r");
						// Se � la prima esecuzione e/o il file non esiste, creane uno
						if (file == NULL)
						{
							file = fopen(PERCORSO_FILE_UTILIZZATORI, "w");
							fclose(file);
							file = fopen(PERCORSO_FILE_UTILIZZATORI, "r");
						}

						esisteNomeUtente = ControllaNomeUtente(file, buffer);
						*isCreatore = false;
					}


					// Se il nome utente inserito esiste, chiedi la password
					// N.B. Il file non � stato ancora chiuso! Quindi la lettura riprender� dall'ultimo strtok,
					// N.B. ovvero esattamente alla riga della password corrispondente al nome utente inserito.
					if (esisteNomeUtente)
					{
						AssegnaStringa(&*nomeUtente, buffer, false);
						printf("Inserire la password: ");
						char buffer[MAX_BUFFER] = { 0 };
						scanf("%100s", buffer);
						SvuotaInputFGets(buffer);

						bool passwordCorretta = ControllaPassword(file, buffer);

						if (passwordCorretta)
						{
							fclose(file);
							return true;
							// Esci dal menu iniziale e prosegui nel main col menu principale
						}
						else
						{
							printf("Errore! Password non corretta! Riprovare.\n\n");
							InvioPerContinuare();
							errore = true;
						}

					}
					else
					{
						printf("Errore! Nome utente non esistente. \nControllare il nome utente digitato oppure digita 0 per tornare al menu iniziale e registrarsi.\n\n");
						InvioPerContinuare();
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
			puts("Errore! Selezionare un'opzione valida!\n");
			InvioPerContinuare();
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
		do
		{
			system("cls");

			puts("Benvenuto sulla piattaforma di immagini! \n\n1. Gestione creatore\n2. Ricerca immagine\n3. Statistiche creatore\n4. Classifiche\n5. Esci");

			unsigned int sceltaMenu;
			bool errore = false;
			scanf("%1u", &sceltaMenu);

			switch (sceltaMenu)
			{
				// Gestione creatore
				case 1:
				{
					system("cls");

					puts("1. Carica immagine\n2. Modifica immagine\n3. Rimuovi immagine\n4. Visualizza statistiche\n5. Indietro");
					scanf("%1u", &sceltaMenu);

					Immagine_t immagine = { 0 };

					// Sottomenu gestione creatore
					switch (sceltaMenu)
					{
						// Carica immagine
						case 1:
						{
							// Inserimento TITOLO
							bool errore = false;
							do
							{
								SvuotaInputGetChar();
								errore = false;
								system("cls");
								printf("Inserire il titolo dell'immagine: ");

								char buffer[MAX_BUFFER] = { 0 };
								fgets(buffer, 100, stdin);
								SvuotaInputFGets(buffer);

								// Controlla che non contenga simboli
								errore = ContieneSimboli(buffer, true);

								// Altrimenti procedi
								if (!errore)
									AssegnaStringa(immagine.titolo, buffer, true);
								
							} while (errore);

							// Inserimento CATEGORIA
							do
							{
								errore = false;
								printf("\n");
								for (size_t i = 0; i < NUM_CATEGORIE; i++)
								{
									if (i % 2 == 0)
										printf("%d. %-30s", i+1, categoria[i]);
									else
										printf("%d. %-30s\n", i+1, categoria[i]);
								}
								printf("\n\nInserire il numero della categoria scelta: ");

								unsigned int categoriaScelta;
								scanf("%u", &categoriaScelta);

								if (categoriaScelta >= 1 && categoriaScelta <= NUM_CATEGORIE)
								{

									AssegnaStringa(immagine.categoria, categoria[categoriaScelta-1], false);
								}
								else
								{
									errore = true;
									printf("Errore! Inserire un'opzione valida!");
									InvioPerContinuare();
								}

							} while (errore);

							// Inserimento TAGS
							do
							{
								printf("\n");
								errore = false;
								for (size_t i = 0; i < NUM_TAGS; i++)
								{
									if (i % 2 == 0)
										printf("%d. %-30s", i + 1, tags[i]);
									else
										printf("%d. %-30s\n", i + 1, tags[i]);
								}

								size_t j = 0;
								for (size_t i = 3; i > 0; i--)
								{
									do
									{
										// Bisogna aggiungere il controllo per la selezione di tags uguali
										errore = false;
										printf("\n\nInserire il numero del tag scelto (%d scelte rimanenti - Inserire 0 per terminare): ", i);

										unsigned int tagScelto;
										scanf("%u", &tagScelto);

										if (tagScelto >= 1 && tagScelto <= NUM_TAGS)
										{
											AssegnaStringa(immagine.tags[j], tags[tagScelto - 1], false);
											j++;
										}
										else if (tagScelto == 0)
										{
											if (i == MAX_TAGS)
											{
												errore = true;
												printf("\nErrore! Selezionare almeno un tag!\n");
											}
											else
												i = 1;
												// Esci dal ciclo
										}
										else
										{
											errore = true;
											printf("Errore! Inserire un'opzione valida!");
											InvioPerContinuare();
										}
									} while (errore);
								}
								
							} while (errore);

							// Assegnazione AUTORE
							AssegnaStringa(immagine.nomeUtente, *nomeUtente, false);

							// Assegnazione FORMATO e TIPOLOGIA
							int indiceFormato = RNG(0, NUM_FORMATI);
							AssegnaStringa(immagine.formato, formato[indiceFormato], false);
							AssegnaStringa(immagine.tipologia, tipologia[indiceFormato], false);

							// Assegnazione NOME FILE
							char buffer[MAX_BUFFER] = { 0 };
							strcpy(buffer, immagine.titolo);
							strcat(buffer, immagine.formato);
							AssegnaStringa(immagine.nomeFile, buffer, false);

							// Assegnazione DATA DI CREAZIONE
							time_t t = time(NULL);
							struct tm tm = *localtime(&t);
							immagine.dataCaricamento.giorno = tm.tm_mday;
							immagine.dataCaricamento.mese = tm.tm_mon + 1;
							immagine.dataCaricamento.anno = tm.tm_year + 1900;

							// Assegnazione RISOLUZIONE (supponiamo proporzioni 16:9)
							immagine.risoluzione.x = RNG(480, 3840);
							immagine.risoluzione.y = immagine.risoluzione.x / 1.7777;

							// Assegnazione DIMENSIONE (in MB) - Moltiplichiamo il numero totale dei pixel per 3 byte ovvero il peso di ogni pixel e dividiamo per ottenere i megabyte
							immagine.dimensione = (float)((immagine.risoluzione.x * immagine.risoluzione.y) * 3) / 1000000;

							// Fase di salvataggio dei dati su file
							file = fopen(PERCORSO_FILE_IMMAGINI, "a");
							if (file == NULL)
							{
								printf("\n\n\nERRORE FATALE! Non e' stato possibile aprire il file\n");
								exit(EXIT_SUCCESS);
							}
							else
							{
								SalvaDatiImmagine(file, &immagine);
								fclose(file);

								/*if (file = fopen(PERCORSO_FILE_CREATORI, "r+"))
								{
									if (!AggiornaNumImmaginiCreatore(file, *nomeUtente))
									{
										printf("Errore nell'aggiornamento del profilo creatore!");
										InvioPerContinuare();
									}
									else
									{
										printf("Immagine caricata con successo!\n\n");
										InvioPerContinuare();
									}
									fclose(file);
								}*/
							}
							break;
						}
						// Modifica immagine
						case 2:
						{
							


							break;
						}
						
					}
				}
			}






		} while (inEsecuzione == true);
	}
	
	else
	{
		// Menu Utilizzatore
	}
}