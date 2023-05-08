package aula09;

import java.util.*;
import Class.*;

public class Ex1 {
    public static void main(String[] args) {
        ArrayList<Integer> c1 = new ArrayList<>();

        for (int i = 10; i <= 100; i+=10)
            c1.add(i);

        System.out.println("Size: " + c1.size());

        for (Integer integer : c1) System.out.println("Elemento: " + integer);

        ArrayList<String> c2 = new ArrayList<>();

        c2.add("Vento");
        c2.add("Calor");
        c2.add("Frio");
        c2.add("Chuva");

        System.out.println(c2);

        Collections.sort(c2);

        System.out.println(c2);

        c2.remove("Frio");
        c2.remove(0);

        System.out.println(c2);

        Set<Pessoa> c3 = new HashSet<>();

        Pessoa p1 = new Pessoa("Bruno", 30335630, new DateYMD(2004, 9, 10));
        Pessoa p2 = new Pessoa("Marta", 11111111, new DateYMD(2004, 9, 7));
        Pessoa p3 = new Pessoa("Martina", 22222222, new DateYMD(2004, 8, 18));
        Pessoa p4 = new Pessoa("Diogo", 33333333, new DateYMD(2004, 9, 3));
        Pessoa p5 = new Pessoa("Pedro", 44444444, new DateYMD(2004, 6, 17));
        Pessoa p6 = new Pessoa("Pedro", 44444444, new DateYMD(2004, 6, 17));

        c3.add(p1);
        c3.add(p2);
        c3.add(p3);
        c3.add(p4);
        c3.add(p5);
        c3.add(p6);

        for (Pessoa pessoa : c3) System.out.println(pessoa);

        Set<DateYMD> c4 = new TreeSet<>();

        DateYMD d1 = new DateYMD(2004, 1, 1);
        DateYMD d2 = new DateYMD(2004, 2, 2);
        DateYMD d3 = new DateYMD(2004, 3, 3);
        DateYMD d4 = new DateYMD(2004, 4, 4);
        DateYMD d5 = new DateYMD(2004, 5, 5);

        c4.add(d1);
        c4.add(d2);
        c4.add(d3);
        c4.add(d4);
        c4.add(d5);

        for (DateYMD date : c4) System.out.println(date);
    }
}
