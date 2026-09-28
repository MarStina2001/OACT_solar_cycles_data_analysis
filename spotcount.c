#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define DIRNAME "dati_ussps_txt"
#define COUNT     "sunspotscount.txt"
#define STRLEN  1024

typedef FILE*     pfile;

int main(void)
     {
           int    i,j,count;
           pfile  pf,pfcount;
           char   s[STRLEN],filename[STRLEN];
           DIR *d;
           struct dirent *dir;


           if ((pfcount=fopen(COUNT,"w"))==NULL) goto file_err;
           
           d = opendir(DIRNAME);  //* This folder is "." *//
           if (d) 
           {
             while ((dir = readdir(d)) != NULL) {

               if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
                 continue;
               }

               snprintf(filename, sizeof(filename), "%s/%s", DIRNAME, dir->d_name);
               
           if ((pf=fopen(filename,"r"))==NULL) goto file_err;

           fprintf(pfcount, "%s\n", filename);

           for(i=0;i<4;i++)     //*this is always file intro*//
            {
                fscanf(pf,"%s",s);
            }

           count=0;
           for(i=4;;i++)
            {
                for(j=0;j<3;j++)
                 {
                    if(strcmp(s,"INAF-CATANIA")==0) break;
                    fscanf(pf,"%s",s);
                    if(!j) count++;
                 }
                if(strcmp(s,"INAF-CATANIA")==0) break;
            }

           fprintf(pfcount,"%d\n",count-1);

           fclose(pf);
                        }
              closedir(d);

           }

           fclose(pfcount);

           return EXIT_SUCCESS;

           file_err: printf("Problem with the file!\n"); return EXIT_FAILURE;
     }


/*

To compile this file:     gcc sunspotsCOUNT.c -o sunspotsCOUNT
to execute this file:     ./sunspotsCOUNT
You must have the folder dati_ussps_txt with only USSPS text files inside. 

*/