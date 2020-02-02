#include <sys/types.h>
#include <sys/wait.h>

#include "../parser/inimngr.h"
#include "../loader/loader.h"

#define MAX_MODULE 100

/* return 0 if hostname is found otherwise -1 */
int istarget(char *hostname)
{
   int i, ret;
   for (i=0; i<MAX_HOST; i++)
      if( !(ret = strcmp(hostname, thost[i])) )
	return ret; 
   return -1;
}

//lanceur de module
int spawn (char* program, char** arg_list)
{
  pid_t child_pid;
 /* Duplique ce processus. */
 child_pid = fork ();
 if (child_pid != 0)
    /* Nous sommes dans le processus parent. */
    return child_pid;
 else {
    /* Exécute PROGRAM en le recherchant dans le path. */
    execvp (program, arg_list);
    /* On ne sort de la fonction execlp uniquement si une erreur survient. */
    fprintf (stderr, "une erreur est survenue au sein de execlp\n");
    abort ();
 }
}

int main ()
{

   char value[VALUE_LENGTH];  		// valeur renvoyée par association d'une section et d'un clé
   char *modules[MAX_MODULE];		// liste des modules
   char *toexec[MAX_MODULE];		// liste des modules à exécuter sur cette ECU
   char  hostname[HOSTNAME_LENGTH];	// hostname de l'ecu qui execute ce launcher
   int tpid[MAX_MODULE], wstatus;	// table des pid des modules qui ont été lancés
   int mindex = 0, lexec = 0; 		// indices  pour balayer les tableaux modules et toexec
   char  *arg_list[2];			// liste d'argument à passer aux modules lancés par execv

   //déclarer les sections et les clés dont on veut les valeurs
   const SK sk1 = {"modlist", "m1"}, sk2 = {"modlist", "m2"}, sk3 = {"modlist", "m3"}, sk4 = {"modlist", "m4"}, sk5 = {"modlist", "m5"};

   // les mettre dans un tableau
   const SK tsk[]={sk1, sk2, sk3, sk4, sk5};

   // toujours déclarer un objet de la classe ScavIni comme ci-dessous
   ScavIni sci ("scav.ini", tsk, sizeof(tsk)/sizeof(SK));

   // y a plus qu'a récupérer les valeurs par exemple avec cette boucle ou tout autre façon
   // on ne conserve pas les valeurs à nil
   for (int i=0; i<sizeof(tsk)/sizeof(SK); i++)
      if (sci.getvalue(&tsk[i], value) == EXIT_SUCCESS){
         if(!strcmp("nil", value)) continue;
         modules[mindex] = (char *)malloc(strlen(value)+1);
         strcpy(modules[mindex], value);
         fprintf(stderr, "Section: %s - Clé:%s - Valeur:%s\n", tsk[i].section, tsk[i].key, value);
         mindex++;
      } 
      else
         fprintf(stderr, "Section: %s- Key: %s not found\n", tsk[i].section, tsk[i].key);

   //pour savoir quels modules lancer, faut savoir quelle ecu ce launcher est en train de s'exécuter
   //getting the hostname 
   if(gethostname(hostname, HOSTNAME_LENGTH) == -1){
      fprintf(stderr, "Unable to get hostname\n");
      exit(EXIT_FAILURE);
   }
   if (istarget(hostname)){
      fprintf(stderr, "Sorry : this hostname %s is not a target for SCAV. Should be on the form ecuX (X=0, 1...6)\n", hostname);
      exit(EXIT_FAILURE);
   }
   fprintf(stderr, "Hostname: %s\n", hostname);

   //à ce stade on connait la liste des modules à charger
   //il faut récupérer leur allocation aux ECU
   SK tsk2[MAX_MODULE];
   for (int i=0; i<mindex; i++){
      tsk2[i].section = "modallocation";
      tsk2[i].key = modules[i];
      //fprintf(stderr, "Looking for value linked to Section: %s- Key: %s\n", tsk2[i].section, tsk2[i].key);
   }

   // A présent on va récupérer l'allocation module-ecu
   ScavIni sci2 ("scav.ini", tsk2, mindex);

   // y a plus qu'a récupérer les valeurs et conserver celles qui concerent l'ecu courante
   for (int i=0; i<mindex; i++){
      if (sci2.getvalue(&tsk2[i], value) == EXIT_SUCCESS){
         //fprintf(stderr, "Section: %s - Clé:%s - Valeur:%s\n", tsk2[i].section, tsk2[i].key, value);
         if (!strcmp(value, hostname)){
            fprintf(stderr, "Le module %s doit être lancé sur cette ecu (%s)\n", tsk2[i].key, hostname);
            toexec[lexec] = (char*)tsk2[i].key;
            lexec++;
         }
      } 
      else
         fprintf(stderr, "Section: %s- Key: %s not found\n", tsk2[i].section, tsk2[i].key);
   }

   // à présent on connait la liste des modules à lancer sur cette ecu
   // il ne reste plus qu'à les lancer avec des fork-exec ...
   for (int i=0; i< lexec; i++){
      arg_list[0] = toexec[i];
      arg_list[1] = NULL;
      // c'est la fonction qui lance le module
      tpid[i] = spawn(toexec[i], arg_list);
      fprintf(stderr, "Le module: %s a été lancé sur l'ecu: %s avec le PID: %d\n", toexec[i], hostname, tpid[i]);
   }
   // ... et attendre que tous les processus lancés se terminent 
   for (int i=0; i<lexec; i++){
      fprintf(stderr, "Waiting now for child module termination\n");
      wait(&wstatus);
      fprintf(stderr, "A child module has terminated ... maybe waiting now for another\n");
   }
   // tous les modules lancés se sont terminé... bye bye
   fprintf(stderr, "launcher: normal termination\n");
   return 0;
}
