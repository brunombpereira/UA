
#include "image8bit.c" 
#include <time.h>
#include <stdlib.h>

// Define your test functions here
int test (int width,int  height, int depth){
    Image image = ImageCreate(width,height,depth);
    srand(time(NULL));   // Initialization, should only be called once.


    for (int i =0; i<(width*height); i++  ){  //loop para preencher o array de pixels com valores aleatorios
        image->pixel[i]= rand() %depth;
    }
    int cropsizeh = height/2;
    int cropsizew = width/2;
    int croph= rand()%cropsizeh;
    int cropw= rand()%cropsizew;
    
    Image crop =ImageCrop(image, rand()% croph , rand()%cropw , cropsizeh, cropsizeh);// random crop de 1 quarto da imagem
    int iLx;
    int iLy;
    ImageLocateSubImage(image, &iLx, &iLy,crop);
    if (iLx == cropw && iLy == croph){
        printf("Teste LocateSubImage passou\n");
    }
    else{
        printf("Teste LocateSubImage falhou\n");
    }



}



int main() {




    test(100,100,8);


    // Call your test functions here
    
    return 0;
}
