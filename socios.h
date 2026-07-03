#ifndef SOCIOS_H_INCLUDED
#define SOCIOS_H_INCLUDED

#define TAM_COD_ENV 12
#define TAM_DEST 51
#define TAM_LINEA 100

typedef struct{
    int cod_envio;
    char destinatario[TAM_DEST];
    float peso;
    int prioridad;
}t_envios;

typedef struct{
    char cod_envio[TAM_COD_ENV];
    char destinatario[TAM_DEST];
    float peso;
    int prioridad;
}t_envios_fus;

void fusionar_archivos_ALU(const char * path_envios_c, const char * path_envios_d, const char * path_envios_fus);
int lectura_arch_txt(t_envios* envioD,FILE * archD);
int cmp_envios_ALU(const void *v1, const void *v2);
void elegir_envio_ALU(t_envios* envioC, t_envios* envioD, t_envios* envioFus);
void arma_envio_final_ALU(t_envios *v_envio, t_envios_fus *v_envio_fusion , char *tipo);


#endif // SOCIOS_H_INCLUDED
