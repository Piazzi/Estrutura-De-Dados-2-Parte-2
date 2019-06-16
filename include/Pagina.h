#ifndef PAGINA_H
#define PAGINA_H


class Pagina
{
    public:
        Pagina();
        Pagina(int numChaves);
        Pagina(int numChaves, bool ehFolha);
        virtual ~Pagina();
        //void insere(Registro registro);//adiciona chave na folha. Ordenar imediatamente ap�s inser��o.


    protected:

    private:
        Pagina **filhos;//vetor de ponteiros para os filhos
        //Registro chaves[];//chaves da p�gina
        int maxChaves;//m�ximo de chaves
        int numChaves;//n�mero de chaves atuais
        bool ehFolha;//boolean se a p�gina � uma folha
};

#endif // PAGINA_H
