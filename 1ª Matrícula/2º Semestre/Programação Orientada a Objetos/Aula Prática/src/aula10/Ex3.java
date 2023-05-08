package aula10;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

public class Ex3 {
    public static void main(String[] args) {
        String string = "Hello World";

        Map<Character, List<Integer>> characterListMap = new HashMap<>();

        for (int i = 0; i < string.length(); i++) {
            char character = string.charAt(i);
            if (!characterListMap.containsKey(character)) {
                characterListMap.put(character, new LinkedList<>());
            }
            characterListMap.get(character).add(i);
        }

        System.out.println(characterListMap);
    }
}
