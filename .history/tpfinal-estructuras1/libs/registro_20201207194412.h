#ifndef __REGISTRO_H__
#define __REGISTRO_H__


typedef void (*FuncionVisitante)(double *intervalo);

typedef struct _REGISTRO {
    double intervalo[2];
    double max;
    struct _ITNodo *left;
    struct _ITNodo *right;
} REGISTRO;

typedef REGISTRO *ITree;

ITree itree_crear();

void itree_destruir(ITree it);

int itree_altura(ITree it);

void itree_imprimir_2d(ITree root);

ITree itree_insertar(ITree it, double inter[2]);

ITree itree_eliminar(ITree it, double inter[2]);

ITree itree_intersecar(ITree it, double inter[2]);

void itree_recorrer_dfs(ITree it, ITreeOrdenDeRecorrido orden, FuncionVisitante visit);

void itree_recorrer_bfs(ITree it, FuncionVisitante visit);

#endif
