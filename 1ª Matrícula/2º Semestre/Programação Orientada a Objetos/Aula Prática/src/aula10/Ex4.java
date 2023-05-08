package aula10;

import java.io.FileReader;
import java.io.IOException;
import java.util.LinkedList;
import java.util.Scanner;

public class Ex4 {
    public static void main(String[] args) throws IOException{
        Scanner sc = new Scanner(new FileReader("src/aula10/Teste.txt"));
        LinkedList<String> lines = new LinkedList<>();

        while (sc.hasNext()) {
            lines.add(sc.next());
        }

        lines.removeIf(line -> line.length() <= 2);

        for (String line : lines) {
            for (int i = 0; i < line.length(); i++) {
                if (Character.isDigit(line.charAt(i))) {
                    lines.remove(line);
                    break;
                }
            }
        }

        for (String line : lines) {
            if (line.endsWith("s")){
                System.out.println(line);
            }
        }
    }
}
