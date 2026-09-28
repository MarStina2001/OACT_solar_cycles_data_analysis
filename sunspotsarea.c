#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define DIRNAME "dati_ussps_txt"
//#define USSPS   "dati_ussps_txt/260807.txt" /*è salvato in memoria*/
#define AREA     "sunspotsarea.txt"
#define STRLEN  1024

typedef int*      pint;
typedef FILE*     pfile;

int main(void)
     {
           int    i,j,e1,e2,e3,eeesum;
//           int    n=100;
           pint   pa;
           pfile  pf,pfarea;
           char   s[STRLEN],filename[STRLEN];
           DIR *d;
           struct dirent *dir;


           if ((pfarea=fopen(AREA,"w"))==NULL) goto file_err;
           
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

           fprintf(pfarea, "%s\n", filename);

           for(i=0;i<4;i++)     //*this is always file intro*//
            {
                fscanf(pf,"%s",s);
                //pa[i]=atoi(s);
                //printf("pa[%d]=%d\n",i,pa[i]);
                //printf("i=%d, s=%s\n",i,s);
            }

           eeesum=0;
           for(i=4;;i++)
            {
                for(j=0;j<3;j++)
                 {
                    if(strcmp(s,"INAF-CATANIA")==0) break;
                    //printf("macchia %d\n",i-3);
                    //printf("j=%d\n",j);
                    fscanf(pf,"%s",s);
                    //printf("i=%d, s=%s\n",i,s);
                    if(!j)
                      {
                        e1=s[2]-'0'; /*conversione da stringa a integer*/
                        e2=s[3]-'0';
                        e3=s[4]-'0';
                        switch(e1) /*mi assicuro che sia una cifra tra 0 e 9*/
                         {
                          case 0: eeesum+=e1*100+e2*10+e3; break; //fprintf(pfarea,"%d%d%d\n",e1,e2,e3); //printf("e1=%d, e2=%d, e3=%d, eeesum=%d\n",e1,e2,e3,eeesum); break;
                          case 1: eeesum+=e1*100+e2*10+e3; break; //fprintf(pfarea,"%d%d%d\n",e1,e2,e3); //printf("e1=%d, e2=%d, e3=%d, eeesum=%d\n",e1,e2,e3,eeesum); break;
                          case 2: eeesum+=e1*100+e2*10+e3; break; //fprintf(pfarea,"%d%d%d\n",e1,e2,e3); //printf("e1=%d, e2=%d, e3=%d, eeesum=%d\n",e1,e2,e3,eeesum); break;
                          case 3: eeesum+=e1*100+e2*10+e3; break; //fprintf(pfarea,"%d%d%d\n",e1,e2,e3); //printf("e1=%d, e2=%d, e3=%d, eeesum=%d\n",e1,e2,e3,eeesum); break;
                          case 4: eeesum+=e1*100+e2*10+e3; break; //fprintf(pfarea,"%d%d%d\n",e1,e2,e3); //printf("e1=%d, e2=%d, e3=%d, eeesum=%d\n",e1,e2,e3,eeesum); break;
                          case 5: eeesum+=e1*100+e2*10+e3; break; //fprintf(pfarea,"%d%d%d\n",e1,e2,e3); //printf("e1=%d, e2=%d, e3=%d, eeesum=%d\n",e1,e2,e3,eeesum); break;
                          case 6: eeesum+=e1*100+e2*10+e3; break; //fprintf(pfarea,"%d%d%d\n",e1,e2,e3); //printf("e1=%d, e2=%d, e3=%d, eeesum=%d\n",e1,e2,e3,eeesum); break;
                          case 7: eeesum+=e1*100+e2*10+e3; break; //fprintf(pfarea,"%d%d%d\n",e1,e2,e3); //printf("e1=%d, e2=%d, e3=%d, eeesum=%d\n",e1,e2,e3,eeesum); break;
                          case 8: eeesum+=e1*100+e2*10+e3; break; //fprintf(pfarea,"%d%d%d\n",e1,e2,e3); //printf("e1=%d, e2=%d, e3=%d, eeesum=%d\n",e1,e2,e3,eeesum); break;
                          case 9: eeesum+=e1*100+e2*10+e3; break; //fprintf(pfarea,"%d%d%d\n",e1,e2,e3); //printf("e1=%d, e2=%d, e3=%d, eeesum=%d\n",e1,e2,e3,eeesum); break;
                          default: //printf("ERRORE\n");                    /*così printerà errore anche i giorni senza macchie*/
                         }
                        
                      }
                 }
                if(strcmp(s,"INAF-CATANIA")==0) break;
                //pa[i]=atoi(s);
                //printf("pa[%d]=%d\n",i,pa[i]);
            }


           fprintf(pfarea,"%d\n",eeesum);

           fclose(pf);
                        }
              closedir(d);


           }

           fclose(pfarea);

           //           free(pa);

           return EXIT_SUCCESS;

           mem_err:  printf("Memoria esaurita!\n"); return EXIT_FAILURE;
           file_err: printf("Prob con il file!\n"); return EXIT_FAILURE;
     }


/*

Per compilare queste file:     gcc sunspotsarea.c -o sunspotsarea
e per esegurilo:               ./sunspotsarea
attento ad avere la sottocartella dati_ussps_txt con solo i txt dei dati dentro

*/