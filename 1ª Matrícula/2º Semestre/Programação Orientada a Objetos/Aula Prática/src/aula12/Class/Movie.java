package aula12.Class;

import aula12.Utils.Validate;

import java.util.Objects;

public class Movie implements Comparable<Movie>{
    private String name, rating, genre;
    private double score;
    private int runningTime;

    public Movie(String name, double score, String rating, String genre, int runningTime) {
        if (Validate.validateScore(score) && Validate.validateRunningTime(runningTime)) {
            this.name = name;
            this.rating = rating;
            this.genre = genre;
            this.score = score;
            this.runningTime = runningTime;
        }
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getRating() {
        return rating;
    }

    public void setRating(String rating) {
        this.rating = rating;
    }

    public String getGenre() {
        return genre;
    }

    public void setGenre(String genre) {
        this.genre = genre;
    }

    public double getScore() {
        return score;
    }

    public void setScore(double score) {
        this.score = score;
    }

    public int getRunningTime() {
        return runningTime;
    }

    public void setRunningTime(int runningTime) {
        this.runningTime = runningTime;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Movie movie = (Movie) o;
        return Double.compare(movie.score, score) == 0 && runningTime == movie.runningTime && Objects.equals(name, movie.name) && Objects.equals(rating, movie.rating) && Objects.equals(genre, movie.genre);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name, rating, genre, score, runningTime);
    }

    @Override
    public String toString() {
        return name + ":\n\nScore -> " + score + "\nRating -> " + rating + "\nGenre -> " + genre + "\nRunning Time -> " + runningTime + "\n";
    }

    @Override
    public int compareTo(Movie o) {
        return Double.compare(this.score, o.score);
    }
}
