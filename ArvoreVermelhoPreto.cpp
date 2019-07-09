#include "ArvoreVermelhoPreto.h"
#include <stdio.h>

using namespace std;

ArvoreVermelhoPreto::ArvoreVermelhoPreto()
{
    numRotacoes = 0;
}

ArvoreVermelhoPreto::~ArvoreVermelhoPreto()
{
    raiz = libera(raiz);
}

/**
 * Funcao para auxiliar o destrutor da classe. Deixa como nulo
 * o filho da direita e da esquerda do no passado como parametro,
 * alem de deixaro proprio no como nulo.
 * @param No
 * @return null
*/
No *ArvoreVermelhoPreto::libera(No *no)
{
    if (no != nullptr)
    {
        no->setEsquerda(libera(no->getEsquerda()));
        no->setDireita(libera(no->getDireita()));
        no = nullptr;
    }
    return nullptr;
}

/**
 * Verifica se a arvore esta vazia ou nao. Retorna true caso esteja
 * e false caso contrario
 * @return bool
*/
bool ArvoreVermelhoPreto::ehVazia()
{
    if(raiz->getValor() == NULL)
        return true;
    else
        return false;
}

/**
 * Verifica se a propriedade da altura negra esta sendo respeitada.
 * Os dois lados da arvore precisam ter o mesmo numero de nos pretos
 * @return bool
*/
bool ArvoreVermelhoPreto::alturaNegra()
{
    No *no = raiz;
    int contDireita = 0 ;
    int contEsquerda = 0;
    for(; no->getDireita() != nullptr; no = no->getDireita())
    {
        if(no->getCor())
            contDireita++;
    }

    for(no = raiz; no->getEsquerda() != nullptr; no = no->getEsquerda())
    {
        if(no->getCor())
            contEsquerda++;
    }

    if(contDireita == contEsquerda)
        return true;
    else
        return false;
}

/**
 * Retorna o tio do no passado por par�metro
 * @param No
 * @return No
*/
No* ArvoreVermelhoPreto::getTio(No* no)
{
    No *avo = no->getPai()->getPai();
    if(avo != nullptr)
    {
        /// verifica qual � o tio do n�
        if(avo->getEsquerda() == no->getPai())
            return avo->getDireita();
        else
            return avo->getEsquerda();
    }
    else
        return nullptr;
}


/**
 * Retorna o irm�o do no passado por par�metro
 * @param No
 * @return No
*/
No* ArvoreVermelhoPreto::getIrmao(No* no)
{
    No *pai = no->getPai();
    if(pai != nullptr)
    {
        /// verifica quem � o irm�o
        if(pai->getDireita() == no)
            return pai->getEsquerda();
        else
            return pai->getDireita();
    }
    else
        return nullptr;
}

/**
 * Recolore o n� passado por par�metro. Se for vermelho vira preto
 * e se for preto vira vermelho.
 * @param No
 * @return
*/
void ArvoreVermelhoPreto::recolore(No*no)
{
    if(no->getCor())
        no->setCor(false);
    else
        no->setCor(true);
}

/**
 * Retorna o n� que possui o valor passado por par�metro
 *
 * @param int, No
 * @return No
*/
No* ArvoreVermelhoPreto::buscaValor(int valor)
{
    No *no = this->raiz;
    if(no == nullptr)
        return nullptr;
    else
    {
        while(no != nullptr)
        {
            if(valor == no->getValor())
                return no;
            else
            {
                if(valor < no->getValor())
                    no = no->getEsquerda();
                else
                    no = no->getDireita();
            }
        }
        return nullptr;
    }
}

/**
 * Fun��o de imprimir auxiliar
 *
 * @param int
 * @return
*/
void ArvoreVermelhoPreto::imprimir()
{
    imprimirNivel(this->raiz,0);
}

/**
 * Imprime a �rvore por n�veis
 *
 * @param No, int
 * @return
*/
void ArvoreVermelhoPreto::imprimirNivel(No*no, int nivel)
{
    if (no != nullptr)
    {
        cout << "(" << nivel << ")";
        for(int i = 1; i <= nivel; i++)
        {
            cout << "--";
        }

        cout << no->getValor();
        if(no->getCor())
        {
            cout << " (P)" << endl;
        }
        else
        {
            cout << " (V)" << endl;
        }
        imprimirNivel(no->getEsquerda(), nivel+1);
        imprimirNivel(no->getDireita(), nivel+1);
    }
}

/**
 * Insere um novo n� na �rvore usando uma fun��o auxiliar
 *
 * @param int, Registro
 * @return
*/
void ArvoreVermelhoPreto::inserir(int valor, Registro &registro)
{
    inserirNo(valor, this->raiz, registro);
}

/**
 * Insere um novo no na Arvore.
 * @param int, No, Registro
 * @return No
*/
No* ArvoreVermelhoPreto::inserirNo(int valor, No *no, Registro &registro)
{
    /// Caso 1: se a raiz est� vazia, o n� a ser inserido ser� a nova raiz(de cor preta).
    if(ehVazia())
    {
        numComparacoes++;
        no->setValor(valor);
        no->setCor(1); /// preto
        cout << "Raiz adicionada" << endl;
        return no;
    }
    else
    {
        No *pai;
        /// procura aonde o no vai se encaixar e acha seu pai.
        while(no != nullptr)
        {
            numComparacoes++;
            pai = no;
                    cout << "aaa";

            if(valor < no->getValor())
                no = no->getEsquerda();
            else
                no = no->getDireita();
        }

        no->setCor(0); /// vermelho
        no->setPai(pai);
        no->setValor(valor);
        cout << "No adicionado com sucesso, valor: " << valor << endl;

        /// descobre se o no � filho esquerdo ou direito do pai
        if(valor > pai->getValor())
            pai->setDireita(no);
        else
            pai->setEsquerda(no);

        No*raiz;
        /// percorre a arvore para verificar se � necess�rio fazer alguma corre��o.
        while(no != nullptr)
        {
            numComparacoes++;
            no = verificarPropriedades(no);
            raiz = no;
            no = no->getPai();
        }
        return raiz;
    }
}

/**
 * Verifica se alguma propriedade da �rvore Vermelha-Preto foi quebrada
 * @param int, No, Registro
 * @return No
*/
No* ArvoreVermelhoPreto::verificarPropriedades(No*no)
{
    /// Caso 1: O n� � a raiz, nesse caso, o n� deve ser preto.
    if(ehVazia())
    {
        no->setCor(1);
        return no;
    }
    else
    {
        No *pai = no->getPai();
        No *tio = getTio(no);
        No *avo = pai->getPai();

        numComparacoes++;
        if(tio != nullptr)
        {
            /// Caso 2: Pai e tio s�o vermelhos, recolore pai, tio e av�
            if(!(tio->getCor() && pai->getCor()))
            {
                avo->recolore();
                tio->recolore();
                pai->recolore();
            }
            /// Caso 3: Pai � vermelho e tio � preto. � necess�rio fazer alguma rota��o.
            else
            {
                /// verifica qual rota��o dever� ser feita
                no = verificarRotacao(no);
            }
        }

        return no;
    }

}

/**
 * Verifica qual rota��o deve ser executada e em seguida � executa
 * @param No
 * @return No
*/
No* ArvoreVermelhoPreto::verificarRotacao(No*no)
{
    No *pai = no->getPai();
    No *avo = pai->getPai();

    numComparacoes++;
    if(avo->getEsquerda() == pai)
    {
        numComparacoes++;
        if(pai->getDireita() == no)
            avo = rotacaoDuplaEsquerdaDireita(avo);
        else
            avo = rotacaoSimplesDireita(avo);
    }
    else
    {
        numComparacoes++;
        if(pai->getDireita() == no)
            avo = rotacaoSimplesEsquerda(avo);
        else
            avo = rotacaoDuplaDireitaEsquerda(avo);
    }

    avo->recolore();
    avo->getEsquerda()->recolore();
    avo->getDireita()->recolore();
    return avo;
}

/**
 * Aplica uma rota��o simples para a esquerda e retorna a posi��o certa do n�
 * @param No
 * @return No
*/
No* ArvoreVermelhoPreto::rotacaoSimplesEsquerda(No*avo)
{
    No *pai = avo->getDireita();
    No *a = avo->getEsquerda();
    No *b = pai->getEsquerda();
    No *p = avo->getPai();

    pai->setEsquerda(avo);
    avo->setEsquerda(a);
    avo->setDireita(b);

    if(!a)
        a->setPai(avo);

    if(!b)
        b->setPai(avo);

    avo->setPai(pai);
    pai->setPai(p);
    if(!p)
        p->setEsquerda(pai);

    return pai;
}

/**
 * Aplica uma rota��o simples para a direita e retorna a posi��o certa do n�
 * @param No
 * @return No
*/
No* ArvoreVermelhoPreto::rotacaoSimplesDireita(No*avo)
{
    No *pai = avo->getEsquerda();
    No *a = avo->getDireita();
    No *b = pai->getDireita();
    No *p = avo->getPai();

    pai->setDireita(avo);
    avo->setDireita(a);
    avo->setEsquerda(b);

    if(!a)
        a->setPai(avo);

    if(!b)
        b->setPai(avo);

    avo->setPai(pai);
    pai->setPai(p);
    if(!p)
        p->setDireita(pai);

    return pai;
}

/**
 * Aplica uma rota��o dupla e retorna a posi��o certa do n�
 * @param No
 * @return No
*/
No* ArvoreVermelhoPreto::rotacaoDuplaEsquerdaDireita(No *avo)
{
    No *pai = avo->getEsquerda();

    avo->setEsquerda(rotacaoSimplesEsquerda(pai));
    avo->getEsquerda()->setPai(avo);
    return rotacaoSimplesDireita(avo);
}

/**
 * Aplica uma rota��o dupla e retorna a posi��o certa do n�
 * @param No
 * @return No
*/
No* ArvoreVermelhoPreto::rotacaoDuplaDireitaEsquerda(No*avo)
{
    No *pai = avo->getEsquerda();

    avo->setDireita(rotacaoSimplesDireita(pai));
    avo->getDireita()->setPai(avo);
    return rotacaoSimplesEsquerda(avo);
}

/**
 * Fun��o auxiliar na hora de remover um n�
 * @param No
 * @return No
*/
No* ArvoreVermelhoPreto::casoNoUmFilho(No *p){
    No *aux; // auxiliar para a troca de valores

    // Verificar a existencia do filho direito ou esquerdo
    // Em ambos fazer a troca de valores, atualiza��o dos filhos e remover o n�.
    numComparacoes++;
    if(p->getEsquerda() == nullptr){
        aux = p->getDireita();
        p->setValor(aux->getValor());
        p->setDireita(aux->getDireita());
        p->setEsquerda(aux->getEsquerda());
        delete aux;
    }
    else{
        aux = p->getEsquerda();
        p->setValor(aux->getValor());
        p->setDireita(aux->getDireita());
        p->setEsquerda(aux->getEsquerda());
        delete aux;
    }
    return p;
}

/**
 * Func�o auxiliar para fazer a troca de valores do n� que possui dois filhos.
 * Troca-se com o valor sucessor do n� p
 * @param No, long int
 * @return No
*/
No* ArvoreVermelhoPreto::casoNoDoisFilhos(No *p, long int valor){
    No *aux;

    aux = p->getDireita();
    while(aux->getEsquerda() != nullptr){
        numComparacoes++;
        aux = aux->getEsquerda();
    }
    /// Faz a troca de valores e depois faz a remo��o do n� que agora
    /// cont�m o valor que quer retirar.
    p->setValor(aux->getValor());
    aux->setValor(valor);
    removerNo(valor, p->getDireita());
    return p;
}

/**
 * Fun��o auxiliar na hora de remover um n�. Verifica se o n�
 * folha a ser retirado � a raiz
 * @param No
 * @return No
*/
No* ArvoreVermelhoPreto::casoNoFolha(No *p){
    // Verificar se o n� folha a ser retirada � a raiz, atrav�s da exist�ncia do pai.
    // Caso n�o seja a raiz, verifica se a cor do n� p � vermelha.
    numComparacoes++;
    if(p->getPai() == nullptr)
    {
        // Se n�o existir o pai, o n� � a raiz e faz a remo��o simples.
        delete p;
    }
    else if(!p->getCor())
    {
        // Se o n� p n�o for a raiz mas for da cor vermelha, faz a remo��o da folha com a atualiza��o da informa��o do pai.
        numComparacoes++;
        No *pai = p->getPai();
        numComparacoes++;
        if(pai->getDireita() == p){
            pai->setDireita(nullptr);
        }else{
            pai->setEsquerda(nullptr);
        }
        delete p;
    }else{
        // Se o n� p n�o for a raiz mas for da cor preta, faz-se a verifica��o da cor do irm�o.
        if(!getIrmao(p)->getCor()){
            numComparacoes++;
            // Se tiver irm�o vermelho, remova o n� e faz a rota��o a direita ou a esquerda.
            No *pai = p->getPai();
            numComparacoes++;
            if(pai->getDireita() == p){
                pai->setDireita(nullptr);
                delete p;
                pai = rotacaoSimplesDireita(pai);
            }else{
                pai->setEsquerda(nullptr);
                delete p;
                pai = rotacaoSimplesEsquerda(pai);
            }
        }else{
            // Se tiver irm�o preto, verifica se cont�m um dos filhos da cor vermelha.
            No *irmao = getIrmao(p);
            No *pai = p->getPai();
            numComparacoes = numComparacoes + 2;
            if(irmao->getDireita()->getCor() && irmao->getEsquerda()->getCor()){
                //Se o irm�o tiver dois filhos pretos, faz-se a remo��o do n� e realiza a troca de cores do irm�o e do pai.
                numComparacoes++;
                if(pai->getDireita() == p){
                    pai->setDireita(nullptr);
                    delete p;
                }else{
                    pai->setEsquerda(nullptr);
                    delete p;
                }
                recolore(pai);
                recolore(irmao);
            }else{
                // Se o irm�o tiver pelo menos um filho da cor vermelha, faz a remo��o do n� e realiza a
                // rota��o necess�ria e altera a cor do neto vermelho.
                No *neto = netoVermelho(p); // busca o neto da cor vermelha para a an�lise da rota��o.
                numComparacoes++;
                if(pai->getDireita() == p){
                    pai->setDireita(nullptr);
                    delete p;
                }else{
                    pai->setEsquerda(nullptr);
                    delete p;
                }
                pai = verificarRotacao(neto); // faz a rota��o necess�ria
                //irmao = getIrmao(neto);
                recolore(neto); // troca a cor.
                recolore(getIrmao(neto));
            }
        }
    }
    return nullptr;
    // em todos os casos, foram deletados os n�s com o valor procurado e com altera��es necess�rias na �rvore.
}

/**
 * Fun��o que remove um n� da �rvore chamando uma fun��o auxiliar
 * @param long int
 * @return
*/
void ArvoreVermelhoPreto::remover(long int valor)
{
    this->raiz = removerNo(valor, this->raiz);
}

/**
 * Fun��o auxiliar para remover um n�, que verifica quais modifica��es
 * devem ser feitas ap�s a remo��o.
 * @param long int, No
 * @return No
*/
No* ArvoreVermelhoPreto::removerNo(long int valor, No *p)
{
    // Caso o n� p n�o exista, quer dizer que chegou no fim da �rvore ou o valor n�o existe. Retorna NULL.
    // Caso contr�rio, verifico se o valor est� a direita (maior) ou a esquerda (menor).
    // De forma recusiva, atualizo os novos n�s, caso seja necess�rio.
    numComparacoes++;
    if(p == nullptr)
        return nullptr;
    else if(valor < p->getValor()){
        numComparacoes++;
        removerNo(valor, p->getEsquerda());
    }else if(valor > p->getValor()){
        numComparacoes++;
        removerNo(valor, p->getDireita());
    }
    else{
        // Caso consiga achar o valor, verifico se o n� � folha ou
        // possui um filho ou possui dois filhos
        if(p->getDireita() == nullptr && p->getEsquerda() == nullptr){
            numComparacoes = numComparacoes + 2;
            // Caso seja um n� folha, verifico qual caso ir� recair e corrigir.
            p = casoNoFolha(p);
        }else if((p->getDireita() == nullptr) || (p->getEsquerda() == nullptr)){
            // Caso o n� n�o seja folha mas tenha um filho, apenas troco
            // os valores com o filho esquerdo ou o filho direito.
            numComparacoes = numComparacoes + 2;
            p = casoNoUmFilho(p);
        }else{
            // Caso o n� n�o seja folha mas tenha dois filhos, ter� a
            // troca de valores com a menor sub�rvore direita.
            p = casoNoDoisFilhos(p, valor);
        }
    }
    return p;
}

/**
 * Fun��o auxiliar para verificar qual rota��o fa�o na remo��o, quando possui um irm�o vermelho.
 * Precisa-se ir no n� neto vermelho para a utiliza��o da funcao verificarRotacao.
 * @param No
 * @return No
*/
No* ArvoreVermelhoPreto::netoVermelho(No *p){
    No *pai = p->getPai();
    No *aux;
    if(pai->getDireita() == p){
        aux = pai->getEsquerda();
        // Caso possui um neto mais a esquerda e da cor vermelha, retorno ele, para fazer uma rota��o mais simples.
        // Caso contr�rio, retorno o filho direito.
        if(aux->getEsquerda() != nullptr && !aux->getEsquerda()->getCor()){
            return aux->getEsquerda();
        }else{
            return aux->getDireita();
        }
    }else{
        aux = pai->getDireita();
        // Caso possui um neto mais a direita e da cor vermelha, retorno ele, para fazer uma rota��o mais simples.
        // Caso contr�rio, retorno o filho esquerdo.
        if(aux->getDireita() != nullptr && !aux->getDireita()->getCor()){
            return aux->getDireita();
        }else{
            return aux->getEsquerda();
        }
    }
}
