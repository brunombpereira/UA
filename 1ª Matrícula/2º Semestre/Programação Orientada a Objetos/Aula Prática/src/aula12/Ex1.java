package aula12;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.*;

public class Ex1 {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner sc = new Scanner(new FileReader("src/aula12/A_cidade_e_as_serras.txt"));
        LinkedList<String> words = new LinkedList<>();

        while (sc.hasNext()) {
            String[] lines = sc.nextLine().split(" ");

            Collections.addAll(words, lines);
        }

        HashSet<String> uniqueWords = new HashSet<>(words);

        System.out.println("Número total de palavras: " + words.size() + "\nNúmero de diferentes palavras: " + uniqueWords.size());
    }
}
