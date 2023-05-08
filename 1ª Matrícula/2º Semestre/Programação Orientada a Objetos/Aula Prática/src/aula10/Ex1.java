package aula10;

import java.util.LinkedList;
import java.util.Scanner;

public class Ex1 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        LinkedList<Book> books = new LinkedList<>();

        while (true) {
            System.out.println("\nBooks and Literary Genres\n-------------------------------\n1 - Add book\n2 - List books\n3 - Search book\n4 - Remove book\n5 - Edit book\n0 - Exit\n-------------------------------\n");
            System.out.print("Option: ");
            try {
                int option = sc.nextInt();
                sc.nextLine();

                switch (option) {
                    case 1 -> {
                        while (true) {
                            try {
                                System.out.print("\nTitle: ");
                                String title = sc.nextLine();
                                System.out.print("Author: ");
                                String author = sc.next();
                                System.out.print("Year: ");
                                int year = sc.nextInt();
                                sc.nextLine();
                                System.out.print("Genre: ");
                                String genre = sc.next();
                                books.add(new Book(title, author, year, Genres.fromString(genre)));
                                System.out.println("Book added successfully!");
                                break;
                            } catch (IllegalArgumentException e) {
                                System.out.println(e.getMessage());
                                sc.nextLine();
                            }
                        }
                    }
                    case 2 -> {
                        for (Book book : books) {
                            System.out.println("\n" + book);
                        }
                    }
                    case 3 -> {
                        System.out.print("\nTitle: ");
                        String searchTitle = sc.nextLine();

                        for (Book book : books) {
                            if (book.getTitle().equals(searchTitle)) {
                                System.out.println("\n" + book);
                            }
                        }
                    }
                    case 4 -> {
                        System.out.print("\nTitle: ");
                        String removeTitle = sc.nextLine();

                        for (Book book : books) {
                            if (book.getTitle().equals(removeTitle)) {
                                books.remove(book);
                                System.out.println("Book removed successfully!");
                                break;
                            }
                        }
                    }
                    case 5 -> {
                        System.out.print("\nTitle: ");
                        String editTitle = sc.nextLine();

                        for (Book book : books) {
                            if (book.getTitle().equals(editTitle)) {
                                System.out.println("\nWhat do you want to edit?\n1 - Title\n2 - Author\n3 - Year\n4 - Genre\n0 - Cancel\n");
                                System.out.print("Option: ");
                                int editOption = sc.nextInt();

                                while (true) {
                                    try {
                                        switch (editOption) {
                                            case 1 -> {
                                                System.out.print("\nNew title: ");
                                                sc.nextLine();
                                                String newTitle = sc.nextLine();

                                                for (Book b : books) {
                                                    if (b.getTitle().equals(newTitle)) {
                                                        throw new IllegalArgumentException("Title already exists.");
                                                    } else {
                                                        b.setTitle(newTitle);
                                                        break;
                                                    }
                                                }
                                                System.out.println("Title changed successfully!");
                                            }
                                            case 2 -> {
                                                System.out.print("\nNew author: ");
                                                sc.nextLine();
                                                String newAuthor = sc.nextLine();
                                                book.setAuthor(newAuthor);
                                                System.out.println("Author changed successfully!");
                                            }
                                            case 3 -> {
                                                System.out.print("\nNew year: ");
                                                int newYear = sc.nextInt();
                                                book.setYear(newYear);
                                                System.out.println("Year changed successfully!");
                                            }
                                            case 4 -> {
                                                System.out.print("\nNew genre: ");
                                                String newGenre = sc.nextLine();
                                                book.setGenre(Genres.fromString(newGenre));
                                                System.out.println("Genre changed successfully!");
                                            }
                                            case 0 -> System.out.println("Operation canceled.");
                                            default -> System.out.println("Invalid option.");
                                        }
                                        break;
                                    } catch (IllegalArgumentException e) {
                                        System.out.println(e.getMessage());
                                    }
                                }
                                break;
                            }
                        }
                    }
                    case 0 -> System.exit(0);
                    default -> System.out.println("Invalid option.");
                }
            } catch (Exception e) {
                System.out.println("Invalid option.");
                sc.nextLine();
            }
        }
    }
}
