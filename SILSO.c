#include <stdio.h>
#include <stdlib.h>

#define SILSOINPUT "SN_d_tot_V2.0.txt"
#define COUNT      "SILSOcount.txt"
#define STRLEN     1024
#define NCOLS      7

typedef FILE*     pfile;

int main(void)
     {
           int    i;
           pfile  pf,pfcount;
           char   s[STRLEN];

           
           if ((pf=fopen(SILSOINPUT,"r"))==NULL) goto file_err;
           if ((pfcount=fopen(COUNT,"w"))==NULL) goto file_err;


           for(;;)
           {
            for(i=0;i<NCOLS;i++)
             {
              fscanf(pf,"%s",s);
              if(s[0]=='*') break;
              if(i==0) fprintf(pfcount,"%s_",s);   /*year*/
              if(i==1) fprintf(pfcount,"%s",s);   /*month*/
              if(i==2) fprintf(pfcount,"_%s ",s);   /*day*/
              if(i==4) fprintf(pfcount,"%s\n",s);  /*nspot, the no-spots signal is "-1"*/
             }
            if(s[0]=='*') break;
           }
           

           fclose(pf);
           fclose(pfcount);

           return EXIT_SUCCESS;

           file_err: printf("Problem with the file!\n"); return EXIT_FAILURE;
     }


/*

To compile this file:     gcc SILSO.c -o SILSO
to execute this file:     ./SILSO
https://www.sidc.be/SILSO/infosndtot

*/