#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define DIRNAME "dati_ussps_txt"
#define SEEING  "seeing.txt"
#define STRLEN  1024

typedef FILE*     pfile;

int main(void)
     {
           int    i,j,seeing;
           pfile  pf,pflat;
           char   s[STRLEN],filename[STRLEN];
           DIR *d;
           struct dirent *dir;


           if ((pflat=fopen(SEEING,"w"))==NULL) goto file_err;
           
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
                if(i==3) 
                 {
                    seeing=s[3]-'0';
                    fprintf(pflat,"%d\n",seeing);
                 }
            }


           for(i=4;;i++)
            {
                fscanf(pf,"%s",s);
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

To compile this file on terminal:     gcc seeing.c -o seeing
and to execute:                       ./seeing
Remember you must have the folder 'dati_ussps_txt' with USSPS txt into only

*/