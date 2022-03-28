import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class ContCaracter {
    public static void main(String[] args) throws IOException {
        String filename, aux, aux2, aux3;
        CopiaCola C = new CopiaCola();
        Maping M = new Maping();
        Map<String, Integer> lista = new HashMap<String, Integer>();
        WriteMap W = new WriteMap();
        char caracter;
        int i, cont = 0;
        Scanner sc = new Scanner(System.in);
        System.out.println("Digite o caracter a ser procurado: ");
        caracter = sc.next().charAt(0);;
        System.out.println("Digite o nome do arquivo: ");
        filename = sc.next();
        Scanner s = null;
        try {
            s = new Scanner(new BufferedReader(new FileReader(filename + ".txt")));
            while (s.hasNext()) {
                aux = s.next();
                for (i = 0; i < aux.length(); i++) {
                    if (aux.charAt(i) == caracter) {
                        cont++;
                    }
                }
            }
        } finally {
            if (s != null) {
                s.close();
            }
        }
        System.out.println("O caracter " + caracter + " aparece " + cont + " vezes.");


        System.out.println("Digite o arquivo de origem: ");//Teste dos outros exercícios
        aux2 = sc.next();
        System.out.println("Digite o arquivo de destino: ");
        aux3 = sc.next();
        C.CtrlC_CtrlV(aux2, aux3);
        System.out.println("Digite o arquivo do Map: ");
        aux = sc.next();
        lista = M.CriaMap(aux);
        System.out.println("Digite o arquivo destino do Map: ");
        aux = sc.next();
        W.Write(lista, aux);

        sc.close();
    }
}
