package aula12;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Arrays;
import java.util.TreeMap;

public class Ex2 {
    public static void main(String[] args) throws IOException {
        TreeMap<Character, TreeMap<String, Integer>> file = new TreeMap<>();

        Arrays.stream(Files.readString(Path.of("src/aula12/A_cidade_e_as_serras.txt")).split("[\\s.,:'‘’;?!\\-*{}=+&/()\\[\\]”“\"]+"))
                .filter(word -> word.length() >= 3)
                .forEach(word -> {
                    char firstLetter = word.charAt(0);

                    file.putIfAbsent(firstLetter, new TreeMap<>());

                    TreeMap<String, Integer> words = file.get(firstLetter);

                    file.get(firstLetter).put(word, words.getOrDefault(word, 0) + 1);
                });

        System.out.println(file);
    }
}
