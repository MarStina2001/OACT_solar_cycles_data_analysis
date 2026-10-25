#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define DIRNAME "dati_ussps_txt"
#define LAT     "lat.txt"
#define STRLEN  1024

typedef FILE*     pfile;

int main(void)
     {
           int    i,j,q,y1,y2;
           pfile  pf,pflat;
           char   s[STRLEN],filename[STRLEN];
           DIR *d;
           struct dirent *dir;


           if ((pflat=fopen(LAT,"w"))==NULL) goto file_err;
           
           d = opendir(DIRNAME);  //* This folder is "." *//
           if (d) 
           {
             while ((dir = readdir(d)) != NULL) {

               if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
                 continue;
               }

               snprintf(filename, sizeof(filename), "%s/%s", DIRNAME, dir->d_name);


               
           if ((pf=fopen(filename,"r"))==NULL) goto file_err;
           
           fprintf(pflat, "%s\n", filename+15); /*+15 avoids the DIRNAME*/

           for(i=0;i<4;i++)     //*this is always file intro*//
            {
                fscanf(pf,"%s",s);
            }


           for(i=4;;i++)
            {
                for(j=0;j<3;j++)
                 {
                    if(strcmp(s,"INAF-CATANIA")==0) break;
                    fscanf(pf,"%s",s);
                    if(j==1)
                      {
                        q=s[0]-'0'; /*string to integer conversion*/
                        y1=s[3]-'0';
                        y2=s[4]-'0';
                        switch(q)
                         {
                          case 1: fprintf(pflat,"%d%dNE\n",y1,y2); break;
                          case 2: fprintf(pflat,"%d%dSE\n",y1,y2); break;
                          case 3: fprintf(pflat,"%d%dSW\n",y1,y2); break;
                          case 4: fprintf(pflat,"%d%dNW\n",y1,y2); break;
                          default: //printf("ERRORE\n");  /*it would print in spot-less days also*/
                         }
                        
                      }
                 }
                if(strcmp(s,"INAF-CATANIA")==0) break;
            }


           fclose(pf);
                        }
              closedir(d);
           }

           fclose(pflat);

           return EXIT_SUCCESS;

           file_err: printf("Problems with the file!\n"); return EXIT_FAILURE;
     }


/*

To compile this file on terminal:     gcc lat.c -o lat
and to execute:                       ./lat
Remember you must have the folder 'dati_ussps_txt' with USSPS txt into only

*/