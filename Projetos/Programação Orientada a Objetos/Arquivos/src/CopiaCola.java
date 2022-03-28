import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.FileWriter;

public class CopiaCola {
    public void CtrlC_CtrlV(String origem, String destino) throws IOException {
        BufferedReader inputStream = null;
        PrintWriter outputStream = null;
        try {
            inputStream = new BufferedReader(new FileReader(origem + ".txt"));
            outputStream = new PrintWriter(new FileWriter(destino + ".txt"));
            String aux;
            while ((aux = inputStream.readLine()) != null){
                outputStream.println(aux);
            }
        }
        finally {
            if (inputStream != null)
                inputStream.close();
            if (outputStream != null)
                outputStream.close();
        }
    }
}
