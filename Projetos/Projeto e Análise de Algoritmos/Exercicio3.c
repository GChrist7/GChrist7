
struct HeapNode{
    int element;
    int indexfrom;
    int nextindex;
};
//Estrutura de Nó do heap.

struct Heap{
    HeapNode[] harr;
    int size;
}
//Estrutura do heap.

Heapify(int i){
    int left = 2*i + 1;
    int right = 2*i + 2;
    int smallest = i;
    if(left < Heap.size && harr[left].element < harr[i].element)
        smallest = left;
    if(right < Heap.size && harr[right].element < harr[smallest].element)
        smallest = right;
    if(smallest != i){
        swap(harr, i, smallest);
        Heapify(smallest);
    }
}
//A função heapify estabelece a condição de heap.

void BuildHeap(HeapNode a[], int n){
    Heap.size = n;
    harr = a;
    int i = (Heap.size -1)/2;
    while(i>=0){
        Heapify(i);
        i--;
    }
}
//A função BuildHeap cria um heap de n elementos.

HeapNode getMin(Heap h){
    if(heap <= 0)
        return null;
    return h[0];
}
//Retorna a raiz do heap.

void replaceMin(HeapNode root){
    harr[0] = root;
    Heapify(0);
}
//Troca a raiz pelo nó "root" e reestabelece a condição de heap.

void swap (HeapNode[] arr, int i, int j) {
        HeapNode aux = arr[i];
        arr[i] = arr[j];
        arr[j] = aux;
}
//Troca dois nós do heap.

int MergeKSortedArrays(int[][] arr, int k){
    HeapNode hArr[k];
    int resultsize = 0;
    int i;
    for(i=0 ; i<arr.length ; i++){
        HeapNode node;
        node.element = arr[i][0]
        node.indexform = i;
        node.nextindex = 1;
        hArr[i] = node;
        resultsize += arr[i].length;
    }
    Heap mh;
    BuildHeap(hArr, k);
    int result[resultsize];
    for(i=0 ; i<resultsize ; i++){
        HeapNode root = getMin(mh);
        result[i] = root.element;
        if(root.j < arr[root.i].length)
            root.element = arr[root.i][root.j++];
        else
            root.element = infinito;
        mh.replaceMin(root);
    }
    return result; //Vetor ordenado de n posições;
}
//Recebe uma matriz que guarda os k vetores ordenados de entrada em suas linhas e retorna um vetor ordenado, criado a partir dos k vetores de enttrada, de n posições.











































//2)

struct v{
    int indice;
    v result;
}; //Vamos definir um vértice v como uma estrutura que armazena o indice desse vertice
   //E o vertice result tal que f(v.indice) = result.indice.

RemoveVertexOutOfList(v){
    valordev = v.indice;
    v = (vertice r que f(r) = valorv);
    valorder = v.indice;
    v = v.result;
    v = v.result; //Esses dois passos eliminam a etapa em que v.indice valordev
                  //Uma vez que isso sempre acontece quando atribuimos r a v.
    while(v.indice != valordev){ //O ciclo se encerra caso o valor de v esteja presente duas vezes na lista de r.
                                 //Isso, significa que r não está na lista de v, logo deve ser removido.
        if(v.indice == valorder){
            v = (outro vertice r que f(r) = valordev);
            v = v.result;
            v = v.result; //Essa etapa reinicia o ciclo para um novo vértice r, uma vez que o indice de r for encontrado
                          //Na lista de v.
        }
        v = v.result;
    }
    return v; //Retorna o índice que deve ser removido.
}

MaximalSubset(A, n){
    if(n = 1)
        S = ;
    else if(Se todos os vertices tiverem grau igual a 2)
        S = A;
    else{
        v = vertice com grau != 2;
        if(grau de v < 2)
            S = MaximalSubset(A-v, n-1);
        else{
            A = A - RemoveVertexOutOfList(v);
            S = MaximalSubset(A, n-1);
        }
    }
    return S;
}







//3: 8 rainhas)


bool Seguro(int coluna, int linha, int tabulerio[][]){
    int lcima, lbaixo, c;
    for(c=coluna ; c<8 ; c++){
        if(tabulerio[linha][c] == 1){
            return false;
        }
    }
    c = coluna;
    lcima = linha;
    lbaixo = linha;
    while(c >= 0){
        if(lcima >= 0 && lbaixo <= 7){
            if(tabulerio[c][lcima] == 1 || tabulerio[c][lbaixo] == 1)
                return false;
        }
        if(lcima >= 0){
            if(tabulerio[c][lcima] == 1)
                return false;
        }
        if(lbaixo <= 7){
            if(tabulerio[c][lbaixo] == 1)
                return false;
        }
        c--;
        lcima--;
        lbaixo++;
    }
    return true;
}

void Backtracking(int coluna, int linha, int S[], int tabuleiro[][]){
    int i, l;
    l = linha;
    tabuleiro[linha - 1][coluna + 1] = 0;
    for(i=linha ; i<8 ; i++){
        while(!Seguro(coluna, l, tabuleiro)){
            l++;
            if(l == 8){
                break;
            }
        }
        if(l == 8){
            Backtracking((coluna-1), (S[coluna-1] + 1), S, tabuleiro);
            i = 0;
        }
        else{
            S[coluna] = l;
            tabuleiro[l][coluna] = 1;
        }
    }
}

int PosicionaRainha(int Saida[], int tabuleiro[][]){ //considerar 0 como posições vazias no tabuleiro e 1 como rainhas
    int linha, coluna;
    coluna = 0;
    linha = 0;
    for(coluna=0 ; coluna<8 ; coluna++){
        while(!Seguro(coluna, linha, tabuleiro)){
            linha++;
            if(linha == 8){
                break;
            }
        }
        if(linha == 8){
            Backtracking((coluna-1), (Saida[coluna-1] + 1), Saida, tabuleiro);
            coluna--;
        }
        else{
            Saida[coluna] = linha;
            tabuleiro[linha][coluna] = 1;
        }
    }
    return Saida; //Retorna um vetor Saida de 8 posições, tal que se Saida[1] = 3, significa que:
}                 //há uma rainha posicionada na primeira coluna e na terceira linha do tabuleiro.
                  //Isso, considerando tanto o vetor como as linhas e colunas do tabuleiro inde de 0 a 7.



