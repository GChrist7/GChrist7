import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Map;

public class WriteMap {
    public void Write(Map M, String filename) throws IOException {
        PrintWriter outputStream = null;
        try {
            outputStream = new PrintWriter(new FileWriter(filename + ".txt"));

            for (Object key : M.keySet()){
                outputStream.println(key + " " + M.get(key));
            }
        } finally {
            if (outputStream != null)
                outputStream.close();
        }
    }
}
