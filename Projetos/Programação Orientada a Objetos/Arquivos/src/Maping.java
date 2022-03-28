import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Maping {
    public Map CriaMap(String filename) throws IOException {
        Map<String, Integer> lista = new HashMap<String, Integer>();
        Scanner s = null;
        try {
            s = new Scanner(new BufferedReader(new FileReader(filename + ".txt")));
            while (s.hasNext()){
                lista.put(s.next(), s.nextInt());
            }
        }finally {
            if (s != null) { s.close(); }
        }
        System.out.println("Map: ");
        System.out.println(lista);
        return lista;
    }
}
