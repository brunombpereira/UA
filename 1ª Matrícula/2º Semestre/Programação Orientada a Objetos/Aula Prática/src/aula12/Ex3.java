package aula12;

import aula12.Class.Movie;

import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashSet;
import java.util.Scanner;
import java.util.TreeSet;

public class Ex3 {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(new FileReader("src/aula12/movies.txt"));
        FileWriter myselection = new FileWriter("src/aula12/myselection.txt");
        TreeSet<Movie> movies = new TreeSet<>();
        HashSet<String> genres = new HashSet<>();

        sc.nextLine();

        while (sc.hasNextLine()) {
            String[] line = sc.nextLine().split("\t");

            movies.add(new Movie(line[0], Double.parseDouble(line[1]), line[2], line[3], Integer.parseInt(line[4])));
            genres.add(line[3]);
        }

        for (Movie movie : movies) {
            System.out.println(movie);

            if (movie.getScore() > 60.0) myselection.write(movie.toString());
        }
    }
}
