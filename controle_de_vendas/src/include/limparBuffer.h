#ifndef LIMPARBUFFER_H
#define LIMPARBUFFER_H

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

#endif