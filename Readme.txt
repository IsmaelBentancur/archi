void listado_morosos_ALU(const t_miembro *vec, int cantidad,
                          const t_fecha *fec_proceso)
{
    int indices[500];          /* índices al vector original */
    int cant_morosos;
    int i, j, min;
    long dias;
    int tmp;
    const t_miembro *m;

    cant_morosos = 0;

    /* 1) Filtrar: activos + más de 90 días sin pagar */
    for (i = 0; i < cantidad; i++) {
        if (vec[i].estado != 'A')
            continue;
        dias = fecha_diferencia_dias(&vec[i].fecha_ult_cuota, fec_proceso);
        if (dias > 90)
            indices[cant_morosos++] = i;
    }

    /* 2) Ordenar índices ascendente por fecha de última cuota (selección) */
    for (i = 0; i < cant_morosos - 1; i++) {
        min = i;
        for (j = i + 1; j < cant_morosos; j++) {
            if (fecha_comparar(&vec[indices[j]].fecha_ult_cuota,
                              &vec[indices[min]].fecha_ult_cuota) < 0)
                min = j;
        }
        if (min != i) {
            tmp = indices[i];
            indices[i] = indices[min];
            indices[min] = tmp;
        }
    }

    /* 3) Imprimir con máscara exacta del enunciado */
    printf("DNI\tAPELLIDO Y NOMBRE\tFECHA NACIMIENTO\tSEXO\t"
           "FECHA AFILIACION\tCATEGORIA\tFECHA ULTIMA_CUOTA_PAGA\t"
           "ESTADO\tPLAN\tEMAIL TUTOR\n");

    for (i = 0; i < cant_morosos; i++) {
        m = &vec[indices[i]];
        printf("%-10ld %-20s %02d/%02d/%4d %6c\t %02d/%02d/%4d \t%-15s "
               "%02d/%02d/%4d %15c \t%-15s \t%-15s\n",
               m->dni, m->apyn,
               m->fecha_nac.dia, m->fecha_nac.mes, m->fecha_nac.anio,
               m->sexo,
               m->fecha_afil.dia, m->fecha_afil.mes, m->fecha_afil.anio,
               m->categoria,
               m->fecha_ult_cuota.dia, m->fecha_ult_cuota.mes,
               m->fecha_ult_cuota.anio,
               m->estado, m->plan, m->email_tutor);
    }

    if (cant_morosos == 0)
        printf("No hay morosos.\n");
}

void listado_titulos_mas_alquilados_ALU(const t_titulo *tit, int cant_tit,
                                         const t_alquiler *alq, int cant_alq,
                                         int n_top)
{
    int conteo[500] = {0};
    int orden[500];
    int i, j, max, tmp;

    /* contar alquileres por titulo */
    for (i = 0; i < cant_alq; i++) {
        for (j = 0; j < cant_tit; j++) {
            if (tit[j].id == alq[i].id_titulo) {
                conteo[j]++;
                break;
            }
        }
    }

    for (i = 0; i < cant_tit; i++) orden[i] = i;

    /* ordenar top N descendente */
    for (i = 0; i < n_top && i < cant_tit; i++) {
        max = i;
        for (j = i + 1; j < cant_tit; j++)
            if (conteo[orden[j]] > conteo[orden[max]]) max = j;
        if (max != i) { tmp = orden[i]; orden[i] = orden[max]; orden[max] = tmp; }
    }

    printf("Top %d titulos mas alquilados:\n", n_top);
    printf("%-4s %-5s %-30s %-10s %-6s %s\n",
           "POS", "ID", "TITULO", "GENERO", "STOCK", "ALQUILADO X");
    for (i = 0; i < n_top && i < cant_tit; i++) {
        printf("%-4d %-5d %-30s %-10s %-6d %d\n",
               i + 1,
               tit[orden[i]].id, tit[orden[i]].titulo,
               tit[orden[i]].genero, tit[orden[i]].stock,
               conteo[orden[i]]);
    }
}

void estadistica_por_plan_ALU(const t_miembro *vec, int cant)
{
    int basic = 0, premium = 0, vip = 0, family = 0;
    int total;
    int i;

    for (i = 0; i < cant; i++) {
        if (vec[i].estado != 'A') continue;
        if      (strcmp(vec[i].plan, "BASIC")   == 0) basic++;
        else if (strcmp(vec[i].plan, "PREMIUM") == 0) premium++;
        else if (strcmp(vec[i].plan, "VIP")     == 0) vip++;
        else if (strcmp(vec[i].plan, "FAMILY")  == 0) family++;
    }
    total = basic + premium + vip + family;

    printf("Distribucion de miembros activos por plan (total: %d):\n", total);
    printf("  BASIC   : %3d  (%.1f%%)\n", basic,   total ? (100.0 * basic   / total) : 0.0);
    printf("  PREMIUM : %3d  (%.1f%%)\n", premium, total ? (100.0 * premium / total) : 0.0);
    printf("  VIP     : %3d  (%.1f%%)\n", vip,     total ? (100.0 * vip     / total) : 0.0);
    printf("  FAMILY  : %3d  (%.1f%%)\n", family,  total ? (100.0 * family  / total) : 0.0);
}

void genero_mas_alquilado_ALU(const t_titulo *titulos, int cant_tit,
                                const t_alquiler *alq, int cant_alq)
{
    const char *generos[] = {"Accion", "Drama", "Comedia", "Terror"};
    int conteo[4] = {0};
    int i, j, k, max;

    for (i = 0; i < cant_alq; i++) {
        for (j = 0; j < cant_tit; j++) {
            if (titulos[j].id == alq[i].id_titulo) {
                for (k = 0; k < 4; k++) {
                    if (strcmp(titulos[j].genero, generos[k]) == 0) {
                        conteo[k]++;
                        break;
                    }
                }
                break;
            }
        }
    }

    max = 0;
    for (i = 1; i < 4; i++)
        if (conteo[i] > conteo[max]) max = i;

    printf("Genero mas alquilado: %s (%d alquileres)\n", generos[max], conteo[max]);
    printf("\nDistribucion completa:\n");
    for (i = 0; i < 4; i++)
        printf("  %-10s : %d\n", generos[i], conteo[i]);
}