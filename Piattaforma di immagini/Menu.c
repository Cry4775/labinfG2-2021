#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"

void MenuIniziale()
{
	unsigned int inEsecuzione = true;
	do
	{
		puts("Benvenuto sulla piattaforma di immagini! \n\n1. Registrazione utente\n2. Accesso utente\n3. Esci\n");

		unsigned int sceltaMenu;
		unsigned short int errore = false;
		scanf("%1d", &sceltaMenu);


		switch (sceltaMenu)
		{
		case 1: // Registrazione utente
		{
			do
			{
				errore = false;
				Creatore_t creatore = { 0 };
				Utilizzatore_t utilizzatore = { 0 };

				puts("\nChe tipologia di utente sei?\n1. Creatore\n2. Utilizzatore\n3. Indietro\n");
				scanf("%1d", &sceltaMenu);

				switch (sceltaMenu)
				{
					// Registrazione utente Creatore
					case 1: 
					{
						do
						{
							errore = false;
							printf("\nInserire un nome utente (min. 4 caratteri): ");
							char buffer[MAX_BUFFER] = { 0 };

							// METTERE GLI INPUT DA FILE
							scanf("%100s", buffer);

							file = fopen("creatori.dat", "r");
							unsigned int giaEsistente = false;

							// Se il file non esiste, creane uno
							if (file == NULL)
							{
								file = fopen("creatori.dat", "w");
								file = fopen("creatori.dat", "r");
							}
							
							char buf[BUFSIZ];
							char* ptr = NULL;

							// Controlla il file creatori.dat
							while (fgets(buf, sizeof(buf), file) && giaEsistente == false) // Leggo la riga del file su buf
							{
								ptr = buf; // Assegno a ptr la stringa appena copiata dal file (buf)
								while ((ptr = strtok(ptr, ":")) != NULL) // Quando trova un : (quindi user:) dividi la stringa
								{
									if (strcmp(ptr, "user") == 0)
									{
										ptr = strtok(NULL, " \n\0"); // Quando trova uno spazio o un delimitatore \r o \n o \0 dividi la stringa ptr
										if (strcmp(ptr, buffer) == 0) // Controlla ogni riga nel file
											giaEsistente = true;
									}
									ptr = NULL;
								}
							}
							fclose(file);

							if (giaEsistente == false)
							{
								file = fopen("utilizzatori.dat", "r");
								// Se il file non esiste, creane uno
								if (file == NULL)
								{
									file = fopen("utilizzatori.dat", "w");
									file = fopen("utilizzatori.dat", "r");
								}

								// Controlla il file utilizzatori.dat
								while (fgets(buf, sizeof(buf), file) && giaEsistente == false) // Leggo la riga del file su buf
								{
									ptr = buf; // Assegno a ptr la stringa appena copiata dal file (buf)
									while ((ptr = strtok(ptr, ":")) != NULL) // Quando trova un : (quindi user:) dividi la stringa
									{
										if (strcmp(ptr, "user") == 0)
										{
											ptr = strtok(NULL, " \r\n\0"); // Quando trova uno spazio o un delimitatore \r o \n o \0 dividi la stringa ptr
											if (strcmp(ptr, buffer) == 0) // Controlla ogni riga nel file
												giaEsistente = true;
										}
										ptr = NULL;
									}
								}

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
								AssegnaStringa(&creatore.nomeUtente, buffer);
						} while (errore == true);

						do
						{
							errore = false;
							printf("Inserire una password (min. 8 caratteri): ");
							char buffer[MAX_BUFFER] = { 0 };
							scanf("%100s", buffer);

							// Controlla che il minimo sia rispettato
							if (strlen(buffer) < MIN_CAR_PASSWORD)
							{
								errore = true;
								puts("Errore! Inserire una password di almeno 8 caratteri!\n");
							}

							// Altrimenti procedi
							else
								AssegnaStringa(&creatore.password, buffer);
						} while (errore == true);

						do
						{
							errore = false;
							printf("Inserire il nome: ");
							char buffer[MAX_BUFFER] = { 0 };
							scanf("%100s", buffer);
							// FAI TUTTO MINUSCOLO
							buffer[0] = toupper(buffer[0]);

							// Controlla che non si inseriscano numeri
							size_t i = 0;
							while (i < strlen(buffer) && errore == false)
							{
								if (buffer[i] >= '0' && buffer[i] <= '9')
								{
									errore = true;
									printf("Errore! I numeri non sono ammessi!\n");
								}
								i++;
							}

							// Altrimenti procedi
							if (errore == false)
								AssegnaStringa(&creatore.nome, buffer);
						} while (errore == true);

						do
						{
							errore = false;
							printf("Inserire il cognome: ");
							char buffer[MAX_BUFFER] = { 0 };
							scanf("%100s", buffer);
							buffer[0] = toupper(buffer[0]);

							// Controlla che non si inseriscano numeri
							size_t i = 0;
							while (i < strlen(buffer) && errore == false)
							{
								if (buffer[i] >= '0' && buffer[i] <= '9')
								{
									errore = true;
									printf("Errore! I numeri non sono ammessi!\n");
								}
								i++;
							}

							// Altrimenti procedi
							if (errore == false)
								AssegnaStringa(&creatore.cognome, buffer);
						} while (errore == true);

						do
						{
							errore = false;
							printf("Inserire il sesso (M/F): ");
							SvuotaInput();
							scanf("%c", &creatore.sesso);
							creatore.sesso = toupper(creatore.sesso);

							// Controllo errori
							if (creatore.sesso != 'M' && creatore.sesso != 'F')
							{
								errore = true;
								printf("Errore! Inserire M o F!\n");
							}
						} while (errore == true);

						errore = false;
						printf("Inserire la professione: ");
						char buffer[MAX_BUFFER] = { 0 };
						scanf("%100s", buffer);
						buffer[0] = toupper(buffer[0]);
						AssegnaStringa(&creatore.professione, buffer);

						do
						{
							errore = false;
							printf("Inserire la nazionalita': ");
							char buffer[MAX_BUFFER] = { 0 };
							scanf("%100s", buffer);
							buffer[0] = toupper(buffer[0]);

							// Controlla che non si inseriscano numeri
							size_t i = 0;
							while (i < strlen(buffer) && errore == false)
							{
								if (buffer[i] >= '0' && buffer[i] <= '9')
								{
									errore = true;
									printf("Errore! I numeri non sono ammessi!\n");
								}
								i++;
							}

							// Altrimenti procedi
							if (errore == false)
								AssegnaStringa(&creatore.nazionalita, buffer);
						} while (errore == true);

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
						} while (errore == true);

						// Assegna data di iscrizione
						time_t t = time(NULL);
						struct tm tm = *localtime(&t);
						creatore.dataIscrizione.giorno = tm.tm_mday;
						creatore.dataIscrizione.mese = tm.tm_mon + 1;
						creatore.dataIscrizione.anno = tm.tm_year + 1900;

						file = fopen("creatori.dat", "a");
						if (file == NULL)
						{
							printf("\n\n\nERRORE FATALE! Non e' stato possibile aprire il file\n");
							exit(0);
						}
						else
						{
							fputs("user:", file);
							fputs(creatore.nomeUtente, file);
							fputs("\n", file);
							free(creatore.nomeUtente);

							fputs(creatore.password, file);
							fputs("\n", file);
							free(creatore.password);

							fputs(creatore.nome, file);
							fputs("\n", file);
							free(creatore.nome);

							fputs(creatore.cognome, file);
							fputs("\n", file);
							free(creatore.cognome);

							fputc(creatore.sesso, file);
							fputs("\n", file);

							fputs(creatore.professione, file);
							fputs("\n", file);
							free(creatore.professione);

							fputs(creatore.nazionalita, file);
							fputs("\n", file);
							free(creatore.nazionalita);

							fprintf(file, "%u/%u/%u\n", creatore.dataNascita.giorno, creatore.dataNascita.mese, creatore.dataNascita.anno);

							fprintf(file, "%u/%u/%u\n\n", creatore.dataIscrizione.giorno, creatore.dataIscrizione.mese, creatore.dataIscrizione.anno);

							fclose(file);

							
						}
						break;
					}




					// Registrazione utente Utilizzatore
					case 2:
					{
						do
						{
							errore = false;
							printf("\nInserire un nome utente (min. 4 caratteri): ");
							char buffer[MAX_BUFFER] = { 0 };
							scanf("%100s", buffer);

							file = fopen("creatori.dat", "r");
							char string[101] = { 0 };
							unsigned int giaEsistente = false;

							// Se il file non esiste, creane uno
							if (file == NULL)
							{
								file = fopen("creatori.dat", "w");
								file = fopen("creatori.dat", "r");
							}

							char buf[BUFSIZ];
							char* ptr = NULL;

							// Controlla il file creatori.dat
							while (fgets(buf, sizeof(buf), file) && giaEsistente == false) // Leggo la riga del file su buf
							{
								ptr = buf; // Assegno a ptr la stringa appena copiata dal file (buf)
								while ((ptr = strtok(ptr, ":")) != NULL) // Quando trova un : (quindi user:) dividi la stringa
								{
									if (strcmp(ptr, "user") == 0)
									{
										ptr = strtok(NULL, " \r\n\0"); // Quando trova uno spazio o un delimitatore \r o \n o \0 dividi la stringa ptr
										if (strcmp(ptr, buffer) == 0) // Controlla ogni riga nel file
											giaEsistente = true;
									}
									ptr = NULL;
								}
							}
							fclose(file);

							if (giaEsistente == false)
							{
								file = fopen("utilizzatori.dat", "r");
								// Se il file non esiste, creane uno
								if (file == NULL)
								{
									file = fopen("utilizzatori.dat", "w");
									file = fopen("utilizzatori.dat", "r");
								}

								// Controlla il file utilizzatori.dat
								while (fgets(buf, sizeof(buf), file) && giaEsistente == false) // Leggo la riga del file su buf
								{
									ptr = buf; // Assegno a ptr la stringa appena copiata dal file (buf)
									while ((ptr = strtok(ptr, ":")) != NULL) // Quando trova un : (quindi user:) dividi la stringa
									{
										if (strcmp(ptr, "user") == 0)
										{
											ptr = strtok(NULL, " \r\n\0"); // Quando trova uno spazio o un delimitatore \r o \n o \0 dividi la stringa ptr
											if (strcmp(ptr, buffer) == 0) // Controlla ogni riga nel file
												giaEsistente = true;
										}
										ptr = NULL;
									}
								}

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
								AssegnaStringa(&utilizzatore.nomeUtente, buffer);
						} while (errore == true);

						do
						{
							errore = false;
							printf("Inserire una password (min. 8 caratteri): ");
							char buffer[MAX_BUFFER] = { 0 };
							scanf("%100s", buffer);

							// Controlla che il minimo sia rispettato
							if (strlen(buffer) < MIN_CAR_PASSWORD)
							{
								errore = true;
								puts("Errore! Inserire una password di almeno 8 caratteri!\n");
							}

							// Altrimenti procedi
							else
								AssegnaStringa(&utilizzatore.password, buffer);
						} while (errore == true);

						do
						{
							errore = false;
							printf("Inserire il nome: ");
							char buffer[MAX_BUFFER] = { 0 };
							scanf("%100s", buffer);
							buffer[0] = toupper(buffer[0]);

							// Controlla che non si inseriscano numeri
							size_t i = 0;
							while (i < strlen(buffer) && errore == false)
							{
								if (buffer[i] >= '0' && buffer[i] <= '9')
								{
									//errore = true;
									printf("Errore! I numeri non sono ammessi!\n");
								}
								i++;
							}

							// Altrimenti procedi
							if (errore == false)
								AssegnaStringa(&utilizzatore.nome, buffer);
						} while (errore == true);

						do
						{
							errore = false;
							printf("Inserire il cognome: ");
							char buffer[MAX_BUFFER] = { 0 };
							scanf("%100s", buffer);
							buffer[0] = toupper(buffer[0]);

							// Controlla che non si inseriscano numeri
							size_t i = 0;
							while (i < strlen(buffer) && errore == false)
							{
								if (buffer[i] >= '0' && buffer[i] <= '9')
								{
									errore = true;
									printf("Errore! I numeri non sono ammessi!\n");
								}
								i++;
							}

							// Altrimenti procedi
							if (errore == false)
								AssegnaStringa(&utilizzatore.cognome, buffer);
						} while (errore == true);

						do
						{
							errore = false;
							printf("Inserire il sesso (M/F): ");
							SvuotaInput();
							scanf("%c", &utilizzatore.sesso);
							utilizzatore.sesso = toupper(utilizzatore.sesso);

							// Controllo errori
							if (utilizzatore.sesso != 'M' && utilizzatore.sesso != 'F')
							{
								errore = true;
								printf("Errore! Inserire M o F!\n");
							}
						} while (errore == true);

						errore = false;
						printf("Inserire la professione: ");
						char buffer[MAX_BUFFER] = { 0 };
						scanf("%100s", buffer);
						buffer[0] = toupper(buffer[0]);
						AssegnaStringa(&utilizzatore.professione, buffer);

						do
						{
							errore = false;
							printf("Inserire la nazionalita': ");
							char buffer[MAX_BUFFER] = { 0 };
							scanf("%100s", buffer);
							buffer[0] = toupper(buffer[0]);

							// Controlla che non si inseriscano numeri
							size_t i = 0;
							while (i < strlen(buffer) && errore == false)
							{
								if (buffer[i] >= '0' && buffer[i] <= '9')
								{
									errore = true;
									printf("Errore! I numeri non sono ammessi!\n");
								}
								i++;
							}

							// Altrimenti procedi
							if (errore == false)
								AssegnaStringa(&utilizzatore.nazionalita, buffer);
						} while (errore == true);

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
						} while (errore == true);

						// Assegna data di iscrizione
						time_t t = time(NULL);
						struct tm tm = *localtime(&t);
						utilizzatore.dataIscrizione.giorno = tm.tm_mday;
						utilizzatore.dataIscrizione.mese = tm.tm_mon + 1;
						utilizzatore.dataIscrizione.anno = tm.tm_year + 1900;

						file = fopen("utilizzatori.dat", "a");
						if (file == NULL)
						{
							printf("\n\n\nERRORE FATALE! Non e' stato possibile aprire il file\n");
							return;
						}
						else
						{
							fputs("user:", file);
							fputs(utilizzatore.nomeUtente, file);
							fputs("\n", file);
							free(utilizzatore.nomeUtente);

							fputs(utilizzatore.password, file);
							fputs("\n", file);
							free(utilizzatore.password);

							fputs(utilizzatore.nome, file);
							fputs("\n", file);
							free(utilizzatore.nome);

							fputs(utilizzatore.cognome, file);
							fputs("\n", file);
							free(utilizzatore.cognome);

							fputc(utilizzatore.sesso, file);
							fputs("\n", file);

							fputs(utilizzatore.professione, file);
							fputs("\n", file);
							free(utilizzatore.professione);

							fputs(utilizzatore.nazionalita, file);
							fputs("\n", file);
							free(utilizzatore.nazionalita);

							fprintf(file, "%u/%u/%u\n", utilizzatore.dataNascita.giorno, utilizzatore.dataNascita.mese, utilizzatore.dataNascita.anno);

							fprintf(file, "%u/%u/%u\n\n", utilizzatore.dataIscrizione.giorno, utilizzatore.dataIscrizione.mese, utilizzatore.dataIscrizione.anno);

							fclose(file);
						}
						break;
					}
					case 3:
						errore = false;
						break;
					default:
						errore = true;
						printf("Errore! Selezionare un'opzione valida!");
						break;
					}
			} while (errore == true);
			break;
		}
		case 2:
			break;
		case 3:
			inEsecuzione = false;
			break;
		default:
			puts("Errore! Selezionare un'opzione valida!");
			break;
		}
	} while (inEsecuzione == true);
}