#include <stdio.h>

/**
Este programa recebe 2 entradas que serão os valores X e Y e retornará em qual região do plano cartesiano esta localizada a coordenada.
*/

/**
Funcao coordenadas() que analisa as coordenadas x e y no plano cartesiano.
Retorna: 0 para ponto origem; 1 para sobre o eixo y; 2 para sobre o eixo x; 3 para primeiro quadrante; 4 para segundo quadrante; 5 para terceiro quadrante; 6 para quarto quadrante.
*/
int coordenadas(float pontoX, float pontoY)
{
    if (pontoX == 0 && pontoY == 0){
      return 0;
    } else if (pontoX == 0 && pontoY !=0)
    {
      return 1;
    } else if (pontoX != 0 && pontoY ==0)
    {
      return 2;
    } else if (pontoX > 0 && pontoY > 0)
    {
      return 3;        
    } else if (pontoX < 0 && pontoY > 0)
    {
      return 4;        
    } else if (pontoX < 0 && pontoY < 0)
    {
      return 5;  
    } else if (pontoX > 0 && pontoY < 0)
    {
      return 6;        
    }
    return -1;
}

//funcao main
int main(){
    //declara as variaveis como float
    float pontoX, pontoY;
  
    //Le as coordenadas X e Y. 
    printf("\n=======\n");
    printf("Qual as coordenadas do ponto sobre o eixo X: ");
    scanf("%f",&pontoX);
    printf("Qual as coordenadas do ponto sobre o eixo Y: ");
    scanf("%f",&pontoY);
    printf("\n=======\n\n");

    printf("--RESULTADO--\n");
    //Chama a funcao coordenadas() e utiliza um switch para printar o resultado de acordo com o retorno da função.
    switch (coordenadas(pontoX, pontoY)){
      case 0:
        printf("O ponto esta no Ponto Origem");
        break;
      case 1:
        printf("O ponto esta sobre o eixo Y");
        break;
      case 2:
        printf("O ponto esta sobre o eixo X");
        break;
      case 3:
        printf("O ponto esta no Quadrante 1");
        break;
      case 4:
        printf("O ponto esta no Quadrante 2");
        break;
      case 5:
        printf("O ponto esta no Quadrante 3");
        break;
      case 6:
        printf("O ponto esta no Quadrante 4");
        break;
      default:
        break;
    }
    printf("\n-------------\n");
    return 0;
}