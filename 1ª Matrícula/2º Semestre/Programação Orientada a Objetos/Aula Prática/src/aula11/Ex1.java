package aula11;

import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class Ex1 {
    public static void main(String[] args) throws IOException {
        //
        Scanner sc = new Scanner(new FileReader("src/aula11/major.txt"));
        TreeMap<String, HashMap<String, Integer>> mape = new TreeMap<>();
        StringBuilder sb = new StringBuilder();

        while (sc.hasNext()) {
            sb.append(sc.next()).append(" ");
        }

        String[] words = Arrays.stream(sb.toString().split("[\\s.,:'‘’;?!\\-*{}=+&/()\\[\\]”“\"]+")).filter(word -> word.length() > 2).map(String::toLowerCase).toArray(String[]::new);

        for (int i = 1; i < words.length; i++) {
            int count;
            String word1 = words[i - 1];
            String word2 = words[i];

            if (mape.containsKey(word1)) {
                if (mape.get(word1).containsKey(word2)) {
                    count = mape.get(word1).get(word2) + 1;
                } else {
                    count = 1;
                }
            } else {
                count = 1;

                mape.put(word1, new HashMap<>());
            }

            mape.get(word1).put(word2, count);

        }

        mape.entrySet().forEach(System.out::println);
    }
}
