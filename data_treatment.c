#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "data.h"
#include "data_treatment.h"
#include "lists.h"


void TreatmentDataFilter(int* aux_df, int starting_yearmonth[2], int monthspan[2]){ //função que trata a filtragem de dados
     int i = 0;
     char buffer[BUFFER_SIZE] = {0};
     char *request_df[2] = {"ano", "mês"};

     if (*aux_df == 1){
          for (i = 0; i < 2; i++){
               starting_yearmonth[i] = 0;
               monthspan[i] = 0;
          }
           printf("Os critérios foram limpos.");
     }

     if (*aux_df == 2){
          for (i = 0; i < 2; i++){
               printf("A partir de que %s quer analisar os dados: ", request_df[i]);
               while(1){
                     if(fgets(buffer, BUFFER_SIZE, stdin)==NULL) exit(-1);

                     if (i==0){
                           if((sscanf(buffer,"%d",&starting_yearmonth[i])==1)&&(1600<starting_yearmonth[i]&&starting_yearmonth[i]<2014))
                              break;
                           else
                              printf("Introduza um valor entre 1600 e 2014: ");
                     }
                     else if (i==1){
                           if((sscanf(buffer,"%d",&starting_yearmonth[i])==1)&&(0<starting_yearmonth[i]&&starting_yearmonth[i]<13))
                              break;
                           else
                              printf("Introduza um valor entre 1 e 12: ");
                     }
               }
          }
          printf("Os dados a analisar estão agora a ser reduzidos.\n");
     }

     if (*aux_df == 3){

               printf("Que intervalo de meses pertende analisar em cada ano( [mes1][espaço][mes2] ): ");
               while (1) {
                    if (fgets(buffer, BUFFER_SIZE, stdin)==NULL) exit(-1);

                    if ((sscanf(buffer," %d %d",&monthspan[0], &monthspan[1])==2)&&(monthspan[0]<=monthspan[1]))
                       break;
                    else
                       (printf("Verifique o formato dos dados introduzidos: "));
               }
      }

}


void PrintTH(node_th_t *extreme){
      node_th_t *aux = extreme;

      while(aux->next!= NULL){
            printf("%d--%d--tempMAX__%f\n",aux->payload.begin_period, aux->payload.end_period, aux->payload.maximum_temp );
            aux=aux->next;
      }
}




void TreatmentTemperatureHistory(list_t *extremes_countries,int  T,int auxth,char place_in_analysis[BUFFER_SIZE],int extremes_dates[4]){
      list_th_t *temp_hist_list=NULL;
      node_t *aux = extremes_countries->head;
      node_th_t *newNode=NULL, *delayed_aux=NULL, *th_list_iterator=NULL;
      int i=0, num_of_periods=0;

      PrintCompleteNode(*aux, COUNTRIES);


      temp_hist_list = (list_th_t*)malloc(sizeof(list_th_t));
            if (temp_hist_list== NULL){
                  printf(ANSI_COLOR_ERRORS "ERROR:" ANSI_COLOR_RESET "in memory allocation of temp_hist_list!");
                  exit(EXIT_FAILURE);
            }
      temp_hist_list->head=NULL;

      for(i=extremes_dates[0]; i<extremes_dates[1]; i=i+(T*10000)){
            num_of_periods++;
            newNode=NewTHListNode(i, T);

            if (temp_hist_list->head==NULL){
                  temp_hist_list->head=newNode;
                  delayed_aux=newNode;
            }
            else{
                  newNode->prev=delayed_aux;
                  delayed_aux->next=newNode;
                  delayed_aux=newNode;
            }
      }
      PrintTH(temp_hist_list->head);

      PrintCompleteNode(*aux, COUNTRIES);

      while(aux->next != NULL){
      th_list_iterator=temp_hist_list->head;
            while(th_list_iterator != NULL){
                  //printf("%d___%d\n", aux->payload.ordering_identifier,th_list_iterator->payload.begin_period);
                  if(aux->payload.ordering_identifier>=th_list_iterator->payload.begin_period && aux->payload.ordering_identifier<=th_list_iterator->payload.end_period){
                        printf("YYYYYYY");
                        if(aux->payload.temperature>th_list_iterator->payload.maximum_temp){
                              th_list_iterator->payload.maximum_temp=aux->payload.temperature;
                              printf("XXXXXX");
                              break;
                        }
                  }
                  th_list_iterator=th_list_iterator->next;
            }
            aux=aux->next;
      }
      printf("SEGUNDO PRINT");
      PrintTH(temp_hist_list->head);

      free(temp_hist_list);

}


node_th_t* NewTHListNode(int i,int T){
      node_th_t *newNode=NULL;

      newNode = (node_th_t*)malloc(sizeof(node_th_t));

      if (newNode == NULL){
            printf(ANSI_COLOR_ERRORS "ERROR:" ANSI_COLOR_RESET "in memory allocation of a TH node.");
            exit(EXIT_FAILURE);
      }
printf("%s\n","FUNCIONAAAAAAAAAAAAAAAAAA" );
      newNode-> payload.begin_period= i;
      newNode-> payload.end_period=i+(T*10000);
      printf("%d %d \n",newNode-> payload.begin_period,newNode-> payload.end_period );
      newNode-> next = NULL;
      newNode-> prev = NULL;

      return newNode;
}

/*
void TreatmentYearTempAnalises(list_t *extremes_countries, int _auxyta, int ano){

	int i = 0;
	int j = 0;
	float auxciclo = 0;
     node_t *aux = extremes_countries->head;
     char countries[1][150] = {{0}};
     char countryaux;
     float infocountry[6][150] = {{0}};
     int numberc = 0;
     int dontdo = 0;
     //char countries[1][150] = {{0}}; //vai servir pa copia
     //float infocountry[6][150] = {{0}}; //same


     if (_auxyta == 1){
		 
		while (aux->payload.dt.year != ano) aux = aux->next;

        while (aux->next != NULL && aux->payload.dt.year == ano){
			
			for (i = 0; i < numberc; i++){
				if( strcmp(aux->payload.country, &countries[0][i]) == 0){
					if (aux->payload.temperature > infocountry[0][i]) infocountry[0][i] = aux->payload.temperature;
					if (aux->payload.temperature < infocountry[1][i]) infocountry[1][i] = aux->payload.temperature;
					infocountry[3][i] = infocountry[2][i] + aux->payload.temperature;
					infocountry[4][i] = infocountry[3][i] + 1;
					dontdo = 1; 
				}
				break;
			}
				
			if (dontdo == 0){	
			infocountry[0][numberc] = aux->payload.temperature;
			infocountry[1][numberc] = aux->payload.temperature;
			infocountry[2][numberc] = aux->payload.temperature;
			infocountry[3][numberc] = 1;
			numberc++;
			}
			
        dontdo = 0;  
        aux = aux->next;      
		}
		
		for (i = 0; i < numberc; i++){
			infocountry[4][i] = infocountry[2][i]/infocountry[3][i];
			infocountry[5][i] = infocountry[0][i]-infocountry[1][i];
		}
	}
		
		//fazer copia
	
		for (i=1; i < numberc; i++){
			auxciclo = infocountry[4][i];
			strcpy(&countryaux,&countries[0][i]);
			for ( j = i-1; j >= 0 && infocountry[4][j]>auxciclo; j--){
				infocountry[4][j+1] = infocountry[4][j];
				strcpy(&countries[0][j+1],&countries[0][j]);
				
			}
			infocountry[4][j+1] = auxciclo;
			strcpy(&countries[0][j+1],&countryaux);
			
		}
	}
	
	for (i = 0; i < numberc; i++){
		printf("\n%s-----%f----\n",&countries[0][i], infocountry[4][i]);
	}
		
		//dar logo aqui os prints
		
		
		

     if (_auxyta == 2){

     }


}
*/
