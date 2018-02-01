#include <stdio.h>
#include <stdlib.h>

FILE *inicioLexema, *avance;
char ultimoLexema[100];

enum token {OPERADOR_RELACION= 0};

void aceptarPalabra() {
    long inicioPalabra = ftell(inicioLexema);
    long finPalabra = ftell(avance);
    fread(ultimoLexema, finPalabra - inicioPalabra, 1, inicioLexema);
    fseek(inicioLexema, finPalabra, SEEK_SET);
}
void rechazarPalabra() {
    fseek(avance, ftell(inicioLexema), SEEK_SET);
}

char obtenerSiguienteCaracter(){
    printf("%c", avance);
    return fgetc( avance );
}

int oprel() {
    int estadoActual = 0;
    char c = obtenerSiguienteCaracter();
    while(c != ' '&& c != '\n'&& c != '\t'&& c != EOF&& estadoActual != -1)
    {
        switch(estadoActual){
            case 0:
            switch(c){
                case '=':
                    estadoActual = 1;
                    break;
                case '!':
                    estadoActual = 3;
                case '>':
                    estadoActual = 5;
                case '<':
                    estadoActual = 7;
                default:
                    estadoActual = -1;
                    break;
                }
                break;
            case 1:
                if ( c== '=')
                    estadoActual = 2;
                else
                    estadoActual  = -1;
                break;
            case 3:
                estadoActual = (c == '=') ? 4 : -1;
                break;
            case 5:
                estadoActual = ( c== '=') ? 6: -1;
                break;
            case 7:
                estadoActual = (c == '=') ? 8: 1;
                break;
            default:
            estadoActual = -1;
            break;
        }
        c = obtenerSiguienteCaracter();
    }

    if(estadoActual == 2 || estadoActual == 4 || estadoActual == 5
        || estadoActual == 6 || estadoActual == 7 || estadoActual == 8){
            return OPERADOR_RELACION;
        }
    return -1;
}

int isfeof(){
    char c = obtenerSiguienteCaracter();
    rechazarPalabra();
    return c == EOF;
}

int main(){
    FILE *inicioLexema = fopen("archivo_fuente.txt", "r");
    FILE *avance = fopen("archivo_fuente.txt", "r");
    while(!isfeof()){
        if(oprel()!= -1){
            aceptarPalabra();
            printf("Operador relacion \n");
        }
        else
        {
            rechazarPalabra;
        }
    }

    fclose(inicioLexema);
    fclose(avance);
    system("PAUSE");
    //getc(stdin);
    return 0;
}