#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define DIRNAME "dati_ussps_txt"
#define AREA     "sunspotsarea.txt"
#define STRLEN  1024

typedef FILE*     pfile;

int main(void)
     {
           int    i,j,e1,e2,e3,eeesum;
           pfile  pf,pfarea;
           char   s[STRLEN],filename[STRLEN];
           DIR *d;
           struct dirent *dir;


           if ((pfarea=fopen(AREA,"w"))==NULL) goto file_err;
           
           d = opendir(DIRNAME);  //* This folder is "." *//
           if (d) 
           {
             while ((dir = readdir(d)) != NULL) {

               if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
                 continue;
               }

               snprintf(filename, sizeof(filename), "%s/%s", DIRNAME, dir->d_name);
               
           if ((pf=fopen(filename,"r"))==NULL) goto file_err;

           fprintf(pfarea, "%s\n", filename);

           for(i=0;i<4;i++)     //*this is always file intro*//
            {
                fscanf(pf,"%s",s);
            }

           eeesum=0;
           for(i=4;;i++)
            {
                for(j=0;j<3;j++)
                 {
                    if(strcmp(s,"INAF-CATANIA")==0) break;
                    fscanf(pf,"%s",s);
                    if(!j)
                      {
                        e1=s[2]-'0'; /*string to integer conversion*/
                        e2=s[3]-'0';
                        e3=s[4]-'0';
                        if(((e1>=0)&&(e1<10))&&((e2>=0)&&(e2<10))&&((e3>=0)&&(e3<10))) eeesum+=e1*100+e2*10+e3;
                      }
                 }
                if(strcmp(s,"INAF-CATANIA")==0) break;
            }

           fprintf(pfarea,"%d\n",eeesum);

           fclose(pf);
                        }
              closedir(d);

           }

           fclose(pfarea);

           return EXIT_SUCCESS;

           file_err: printf("Problem with the file!\n"); return EXIT_FAILURE;
     }


/*

To compile this file:     gcc sunspotsarea.c -o sunspotsarea
to execute this file:     ./sunspotsarea
You must have the folder dati_ussps_txt with only USSPS text files inside. 

*/