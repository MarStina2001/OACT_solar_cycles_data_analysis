#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define DIRNAME "dati_ussps_txt"
//#define USSPS   "dati_ussps_txt/260807.txt" /*è salvato in memoria*/
#define LAT     "lat.txt"
#define STRLEN  1024

typedef int*      pint;
typedef FILE*     pfile;

int main(void)
     {
           int    i,j,q,y1,y2;
//           int    n=100;
           pint   pa;
           pfile  pf,pflat;
           char   s[STRLEN],filename[STRLEN];
           DIR *d;
           struct dirent *dir;


           if ((pflat=fopen(LAT,"w"))==NULL) goto file_err;
           
           d = opendir(DIRNAME);  //* Cartella corrente sarenne "." *//
           if (d) 
           {
             while ((dir = readdir(d)) != NULL) {

               if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
                 continue;
               }

               snprintf(filename, sizeof(filename), "%s/%s", DIRNAME, dir->d_name);
//               printf("filename: %s\n", filename);


               
           if ((pf=fopen(filename,"r"))==NULL) goto file_err;

//           if ((pa=(pint)malloc(sizeof(int)*n))==NULL) goto mem_err;

           fprintf(pflat, "%s\n", filename);

           for(i=0;i<4;i++)     //*this is always file intro*//
            {
                fscanf(pf,"%s",s);
                //pa[i]=atoi(s);
                //printf("pa[%d]=%d\n",i,pa[i]);
                //printf("i=%d, s=%s\n",i,s);
            }


           for(i=4;;i++)
            {
                for(j=0;j<3;j++)
                 {
                    if(strcmp(s,"INAF-CATANIA")==0) break;
                    //printf("macchia %d\n",i-3);
                    //printf("j=%d\n",j);
                    fscanf(pf,"%s",s);
                    //printf("i=%d, s=%s\n",i,s);
                    if(j==1)
                      {
                        q=s[0]-'0'; /*conversione da stringa a integer*/
                        y1=s[3]-'0';
                        y2=s[4]-'0';
                        switch(q)
                         {
                          case 1: fprintf(pflat,"%d%dNE\n",y1,y2); break;
                          case 2: fprintf(pflat,"%d%dSE\n",y1,y2); break;
                          case 3: fprintf(pflat,"%d%dSW\n",y1,y2); break;
                          case 4: fprintf(pflat,"%d%dNW\n",y1,y2); break;
                          default: //printf("ERRORE\n");                    /*così printerà errore anche i giorni senza macchie*/
                         }
                        
                      }
                 }
                if(strcmp(s,"INAF-CATANIA")==0) break;
                //pa[i]=atoi(s);
                //printf("pa[%d]=%d\n",i,pa[i]);
            }


           fclose(pf);
                        }
              closedir(d);
           }

           fclose(pflat);

           //           free(pa);

           return EXIT_SUCCESS;

           mem_err:  printf("Memoria esaurita!\n"); return EXIT_FAILURE;
           file_err: printf("Prob con il file!\n"); return EXIT_FAILURE;
     }


/*

Per compilare queste file:     gcc lat.c -o lat
e per esegurilo:               ./lat
attento ad avere la sottocartella dati_ussps_txt con solo i txt dei dati dentro

*/