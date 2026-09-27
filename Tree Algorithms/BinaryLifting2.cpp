const int LOG = 20;

int up[N][LOG];

//ya tenemos preprocesada la informacion de los padres directos
//up[v][0] ya contiene el padre de v
//no importa el orden

for(int j = 1; j < LOG; j++){

    for(int v = 1; v <= n; v++){

        up[v][j] = up[up[v][j-1]][j-1];

    }

}
