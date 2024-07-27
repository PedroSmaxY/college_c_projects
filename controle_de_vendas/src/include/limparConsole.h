#ifndef LIMPARCONSOLE_H
#define LIMPARCONSOLE_H

void limparConsole()
{
#ifdef _WIN32
    system("CLS");
#else
    system("CLEAR");
#endif
}

#endif