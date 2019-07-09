#ifndef PAGINA_H
#define PAGINA_H


class Pagina
{
    public:
        Pagina();
        Pagina(int minChaves);
        Pagina(int minChaves, bool ehFolha);
        virtual ~Pagina();
        //void insere(Registro registro);//adiciona chave na folha. Ordenar imediatamente ap�s inser��o.
        Pagina **filhos;//vetor de ponteiros para os filhos
        int *chaves;
        //Registro chaves[];//chaves da p�gina
        int minChaves;//m�ximo de chaves
        int numChaves;//n�mero de chaves atuais
        bool ehFolha;//boolean se a p�gina � uma folha
        Pagina *busca(int n);

    protected:

    private:

};

#endif // PAGINA_H
