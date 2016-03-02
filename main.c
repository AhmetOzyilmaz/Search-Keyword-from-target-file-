/* 
 * File:   main.c
 * Author: ahmet
 *
 * Created on March 1, 2016, 7:14 PM
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>


/*
 * 
 */

#define MAXL 2048           /* the use of a define will become apparent when you  */
size_t maxl = MAXL;         /* need to check to determine if a realloc is needed  */

int grepfromFile(char* fileName , char* Key);



int main(int argc, char** argv) {

    int fd1;

        if (argc != 3 ) {
            fprintf(stderr, "Usage: grepfromFile  %s %s \n",argv[1],argv[2]);
            return 1;
        }
    
   	if ((fd1 = open(argv[1], O_RDONLY)) == -1) {
            fprintf(stderr, "Failed to open file %s:%s\n", argv[1], strerror(errno));
            return 1;
        }
        
    close(fd1);
    grepfromFile(argv[1],argv[2]);
    
    return (EXIT_SUCCESS);
}

int grepfromFile(char* fileName , char* Key){
    
    int RowCoun = 0,ColumnCoun = 0,check = 2 ,temp = 0,index= 0, i =0 ,j = 0,k=0,
            result = 0,t = 0;
    int keyLenght = 0,currentRow  = 0,lineLenght = 0;
    char red=' ',*line;
    FILE * fp1,*fp2;
    
    
    fp1= fopen(fileName, "r");
    fp2 = fopen ("gfF.log", "a");
    fprintf(fp2,"%s\n",fileName);

    while(Key[keyLenght] != '\0'){
        keyLenght++;
    }
    /*printf(" Key  %d\n",keyLenght);*/
    
    if (fp2 == NULL ) {
            fprintf(stderr, "Failed to not exist file :%s\n",  strerror(errno));
        }
    else
    {
        while(check!=0)
        {
            check = fscanf(fp1,"%c",&red);
            
            if(red== '\n')
            {
                RowCoun ++;
                if( ColumnCoun> temp)
                    temp = ColumnCoun;
                ColumnCoun=0;
            }
            else
            {
                ColumnCoun++;
            }
            if(check == EOF){
                RowCoun++;
                
                if( ColumnCoun > temp)
                    temp = ColumnCoun;
                else
                    ColumnCoun = temp;
                
                break;
            }
        }
        fclose(fp1);
        fp1= fopen(fileName, "r");
           
        line = (char *) malloc(ColumnCoun+2);
        /*fprintf(stderr,"%d\n",RowCoun);*/
        
        for(t= 0; t<RowCoun ;++t)
        { 
            while(1)/* Line take*/
            {
               check =fscanf(fp1,"%c",&line[index]);
               /*fprintf(stderr,"%c",line[index]);*/
               if(line[index] == '\n' || check == EOF){
                   currentRow++;
                   break;
               }
                index++;
            }
            lineLenght = index;
            /*fprintf(stderr,"Row Count = %d Line Lenght = %d Line = %s \n",currentRow,lineLenght,line);*/
            
           for(i = 0 ; i < lineLenght  ; i++ ){ 
               for(j = 0 ; j < keyLenght ; ++j  )
               {
                   if(line[j+i] == Key[j] )
                   {
                       result++;
                   }
               }

               if( result ==  keyLenght){
                   j+=i-keyLenght;

                  fprintf(stderr,"Key Column = %d CURRRENT ROW =  %d\n",j+1,  t+1);
                  fprintf(fp2,"Key Column = %d CURRRENT ROW =  %d\n",j+1,  t+1);

               }
             
               result= 0;
               
            }
            
            index =0 ;
            for(k = 0 ; k< ColumnCoun+2; ++k ){
                line[k]=' ';
            }
     
        }
    }
    fclose(fp1);
    fclose(fp2);
    free(line);
   return 1;

}

