package aula10;

public class Book {
    private String title, author;
    private int year;
    private Genres genre;

    public Book(String title, String author, int year, Genres genre) {
        this.title = title;
        this.author = author;
        this.year = year;
        this.genre = genre;
    }

    public String getTitle() {
        return title;
    }

    public String getAuthor() {
        return author;
    }

    public Genres getGenre() {
        return genre;
    }

    public int getYear() {
        return year;
    }

    public String toString() {
        return String.format("%s (%d) by %s (%s)", title, year, author, genre);
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public void setAuthor(String author) {
        this.author = author;
    }

    public void setYear(int year) {
        this.year = year;
    }

    public void setGenre(Genres genre) {
        this.genre = genre;
    }
}
