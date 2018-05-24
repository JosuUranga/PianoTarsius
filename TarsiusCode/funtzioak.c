#include "funtzioak.h"





void soinuakGrabatu(int nota,SOINUAKGRABATU **soinuak){
  SOINUAKGRABATU *aux1;
  aux1=*(soinuak);
  SOINUAKGRABATU *aux2;
  aux2=(SOINUAKGRABATU*)malloc(sizeof(SOINUAKGRABATU));
  aux2->soinua=nota;
  aux2->hurrengoSoinua=NULL;
  if (aux1==NULL) {
    aux2->noizSakatu=clock();
    aux2->diferentzia=0;
    sartuHasieran(soinuak,aux2);
  }else  {
	aux2->noizSakatu=clock();
    sartuSoinuakBuztanean(*soinuak,aux2);
  }
}



void sartuHasieran(SOINUAKGRABATU** burua, SOINUAKGRABATU *ptrBerria) {
	ptrBerria->hurrengoSoinua = *burua;
	*(burua) = ptrBerria;
}
void sartuSoinuakBuztanean(SOINUAKGRABATU *burua, SOINUAKGRABATU*berria) {
	SOINUAKGRABATU*ptrAux = NULL;
	ptrAux = burua;
	while (ptrAux->hurrengoSoinua != NULL) {

		ptrAux = ptrAux->hurrengoSoinua;
	}
	berria->diferentzia=((double)(berria->noizSakatu - ptrAux->noizSakatu)/CLOCKS_PER_SEC);
	ptrAux->hurrengoSoinua = berria;
}

void bistaratuSoinuak(SOINUAKGRABATU* burua) {
	SOINUAKGRABATU* ptr;
	ptr = burua;
	while (ptr != NULL) {
		bistaratuSoinuaBat(*ptr);
		ptr = ptr->hurrengoSoinua;
	}
}
void bistaratuSoinuaBat(SOINUAKGRABATU pelikula) {
	printf("%i,%lf\n",pelikula.soinua,pelikula.diferentzia);
}


void soinuaErreproduzitu(SOINUAKGRABATU *soinuak){
	SOINUAKGRABATU* ptr;
	ptr = soinuak;
	while (ptr != NULL) {
		SDL_Delay((int)((ptr->diferentzia)*1000));
		playSound(ptr->soinua,ptr->soinua);
		printf("%d nota \n",ptr->soinua);
		ptr = ptr->hurrengoSoinua;
	}
}

void garbituZerrenda(SOINUAKGRABATU** burua) {
  SOINUAKGRABATU* aux;
  SOINUAKGRABATU* freeptr;
  aux = *burua;
  while (aux->hurrengoSoinua != NULL) {
    freeptr = aux;
    aux = aux->hurrengoSoinua;
    free(freeptr);
  }
  *burua = NULL;
}
int simon(int gameOver,SOINUAKGRABATU **soinuakSimon){
	SOINUAKGRABATU*aux;
	SOINUAKGRABATU*aux2=*soinuakSimon;
	aux=(SOINUAKGRABATU*)malloc(sizeof(SOINUAKGRABATU));
	int x;
	if(gameOver==0){
		x=rand()%8;
		aux->diferentzia=0.7;
		aux->soinua=x;
		aux->hurrengoSoinua=NULL;
		aux->noizSakatu=0;
		if(aux2 == NULL) {
			sartuHasieran(soinuakSimon,aux);
		}
		else{
			while (aux2->hurrengoSoinua != NULL) {
				aux2 = aux2->hurrengoSoinua;
			}
			aux2->hurrengoSoinua = aux;
		}
		SDL_Delay(500);
		playSound(9,8);
		SDL_Delay(1500);
		soinuaErreproduzitu(*soinuakSimon);
		gameOver=2;

	}
	return gameOver;
}
int sartuSimon(SOINUAKGRABATU *soinuakSimon, int nota){
	SOINUAKGRABATU *aux = soinuakSimon;
	int gameOver=2, kont=0;
	while (aux->noizSakatu!=0){
		aux=aux->hurrengoSoinua;
		kont++;
		if(kont==5) {
			SDL_Delay(500);
			simonSoinuak();
			playSound(10,9);
			SDL_Delay(1500);
			gameOver=1;
		}
	}
	aux->noizSakatu=(clock_t)nota;
	if(aux->soinua != (int)aux->noizSakatu){
		gameOver =1;
		SDL_Delay(500);
		simonSoinuak();
		playSound(11,10);

	}
	else {
		if(aux->hurrengoSoinua==NULL&&gameOver!=1) {
			aux=soinuakSimon;
			while(aux!=NULL){
				aux->noizSakatu=0;
				aux=aux->hurrengoSoinua;
			}
			gameOver=0;
		}
	}
	return gameOver;
}
