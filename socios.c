#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "socios.h"

void fusionar_archivos_ALU(const char * path_envios_c, const char * path_envios_d, const char * path_envios_fus){
    FILE *archC, *archD, *archFus;
    t_envios envioC, envioD;
    t_envios_fus envioFus;
    int leyo, cmp;

    archC=fopen(path_envios_c,"rb");
    if(!archC)
    {
        printf("Error al abrir el archivo %s", path_envios_c);
        exit(1);
    }

    archD=fopen(path_envios_d,"rt");
    if(!archD)
    {
        printf("Error al abrir el archivo %s", path_envios_d);
        fclose(archC);
        exit(1);
    }

    archFus=fopen(path_envios_fus,"wt");
    if(!archFus)
    {
        printf("Error al abrir el archivo %s", path_envios_fus);
        fclose(archC);
        fclose(archD);
        exit(1);
    }

    // LECTURA EN AMBOS ARCHIVOS //
    fread(&envioC, sizeof(t_envios),1,archC);
    leyo=lectura_arch_txt(&envioD,archD);

    while(!feof(archC) && leyo)
    {
        cmp = cmp_envios_ALU(&envioC, &envioD);
        if (cmp == 0)
        {
            elegir_envio_ALU(&envioC,&envioD,&envioFus);
            fprintf(archFus,"%s|%s|%.1f|%d\n",envioFus.cod_envio,envioFus.destinatario,envioFus.peso,envioFus.prioridad);
            fread(&envioC, sizeof(t_envios),1,archC);
            leyo=lectura_arch_txt(&envioD,archD);
        }
        if (cmp < 0)
        {
            arma_envio_final_ALU(&envioC,&envioFus,"-C");
            fprintf(archFus,"%s|%s|%.1f|%d\n",envioFus.cod_envio,envioFus.destinatario,envioFus.peso,envioFus.prioridad);
            fread(&envioC, sizeof(t_envios),1,archC);
        }
        if (cmp > 0)
        {
            arma_envio_final_ALU(&envioD,&envioFus,"-D");
            fprintf(archFus,"%s|%s|%.1f|%d\n",envioFus.cod_envio,envioFus.destinatario,envioFus.peso,envioFus.prioridad);
            leyo=lectura_arch_txt(&envioD,archD);
        }
    }
    while(!feof(archC))
        {
            arma_envio_final_ALU(&envioC,&envioFus,"-C");
            fprintf(archFus,"%s|%s|%.1f|%d\n",envioFus.cod_envio,envioFus.destinatario,envioFus.peso,envioFus.prioridad);
            fread(&envioC, sizeof(t_envios),1,archC);
        }

    while(leyo)
        {
            arma_envio_final_ALU(&envioD,&envioFus,"-D");
            fprintf(archFus,"%s|%s|%.1f|%d\n",envioFus.cod_envio,envioFus.destinatario,envioFus.peso,envioFus.prioridad);
            leyo=lectura_arch_txt(&envioD,archD);
        }
    fclose(archC);
    fclose(archD);
    fclose(archFus);
}

int lectura_arch_txt(t_envios* envioD,FILE * archD){
    char linea[TAM_LINEA], *aux;

    if(!fgets(linea,TAM_LINEA, archD))
        return 0;

    aux = strchr(linea,'\n');
    if(!aux)
        aux = strchr(linea, '\0');
    else
        *aux ='\0';
    aux = strrchr (linea, '|');
    sscanf(aux+1,"%d", &envioD->prioridad);
    *aux = '\0';

    aux = strrchr (linea, '|');
    sscanf(aux+1,"%f", &envioD->peso);
    *aux = '\0';

    aux = strrchr (linea, '|');
    strncpy(envioD->destinatario,aux+1,TAM_DEST);
    envioD->destinatario[TAM_DEST-1]= '\0';
    *aux = '\0';

    sscanf(linea,"%d", &envioD->cod_envio);

    return 1;
}

int cmp_envios_ALU(const void *v1, const void *v2)
{
    t_envios *a = (t_envios*) v1;
    t_envios *b = (t_envios*) v2;
    return a->cod_envio - b->cod_envio;
}

void elegir_envio_ALU(t_envios* envioC, t_envios* envioD, t_envios* envioFus){
    t_envios aux;

    aux.cod_envio = envioC->cod_envio;

    if(envioC->prioridad > envioD->prioridad)
    {
        strcpy(aux.destinatario, envioD->destinatario);
        aux.prioridad = envioD->prioridad;
    }
        else if(envioC->prioridad < envioD->prioridad)
        {
            strcpy(aux.destinatario, envioC->destinatario);
            aux.prioridad = envioC->prioridad;
        }
            else
            {
                strcpy(aux.destinatario, envioD->destinatario);
                aux.prioridad = envioD->prioridad;
            }
    aux.peso = envioC->peso + envioD->peso;

    arma_envio_final_ALU(&aux, envioFus, "-CD");
}

void arma_envio_final_ALU(t_envios *v_envio, t_envios_fus *v_envio_fusion , char *tipo){
    sprintf(v_envio_fusion->cod_envio,"%d%s",v_envio->cod_envio, tipo);
    strcpy(v_envio_fusion->destinatario,v_envio->destinatario);
    v_envio_fusion->peso = v_envio->peso;
    v_envio_fusion->prioridad = v_envio->prioridad;

}
