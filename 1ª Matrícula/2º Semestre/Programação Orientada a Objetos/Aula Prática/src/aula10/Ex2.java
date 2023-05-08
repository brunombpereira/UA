package aula10;

import java.util.LinkedList;
import java.util.Map;
import java.util.Scanner;
import java.util.TreeMap;

public class Ex2 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        TreeMap<String, LinkedList<Book>> booksByGenre = new TreeMap<>();

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
                                String author = sc.nextLine();
                                System.out.print("Year: ");
                                int year = sc.nextInt();
                                sc.nextLine();
                                System.out.print("Genre: ");
                                String genre = sc.nextLine();

                                if (!booksByGenre.containsKey(genre)) {
                                    booksByGenre.put(genre, new LinkedList<Book>());
                                }
                                booksByGenre.get(genre).add(new Book(title, author, year, Genres.fromString(genre)));
                                System.out.println("Book added successfully!");
                                break;
                            } catch (IllegalArgumentException e) {
                                System.out.println(e.getMessage());
                                sc.nextLine();
                            }
                        }
                    }
                    case 2 -> {
                        for (Map.Entry<String, LinkedList<Book>> entry : booksByGenre.entrySet()) {
                            System.out.println("\n" + entry.getKey() + ":");
                            for (Book book : entry.getValue()) {
                                System.out.println(book);
                            }
                        }
                    }
                    case 3 -> {
                        System.out.print("\nTitle: ");
                        String searchTitle = sc.nextLine();
                        boolean found = false;

                        for (Map.Entry<String, LinkedList<Book>> entry : booksByGenre.entrySet()) {
                            for (Book book : entry.getValue()) {
                                if (book.getTitle().equals(searchTitle)) {
                                    System.out.println("\n" + book);
                                    found = true;
                                }
                            }
                        }
                        if (!found) {
                            System.out.println("Book not found.");
                        }
                    }
                    case 4 -> {
                        System.out.print("\nTitle: ");
                        String removeTitle = sc.nextLine();
                        boolean found = false;

                        for (Map.Entry<String, LinkedList<Book>> entry : booksByGenre.entrySet()) {
                            for (Book book : entry.getValue()) {
                                if (book.getTitle().equals(removeTitle)) {
                                    entry.getValue().remove(book);
                                    System.out.println("Book removed successfully!");
                                    found = true;
                                    break;
                                }
                            }
                            if (found) {
                                break;
                            }
                        }
                        if (!found) {
                            System.out.println("Book not found.");
                        }
                    }
                    case 5 -> {
                        System.out.print("\nTitle: ");
                        String editTitle = sc.nextLine();
                        boolean found = false;

                        Book bookToEdit = null;
                        for (Map.Entry<String, LinkedList<Book>> entry : booksByGenre.entrySet()) {
                            for (Book book : entry.getValue()) {
                                if (book.getTitle().equals(editTitle)) {
                                    bookToEdit = book;
                                    found = true;
                                    break;
                                }
                            }
                            if (found) {
                                break;
                            }
                        }
                        if (!found) {
                            System.out.println("Book not found.");
                            break;
                        }

                        System.out.println("\nWhat do you want to edit?\n1 - Title\n2 - Author\n3 - Year\n4 - Genre\n0 - Cancel\n");
                        System.out.print("Option: ");
                        int editOption = sc.nextInt();
                        sc.nextLine();

                        while (true) {
                            try {
                                switch (editOption) {
                                    case 1 -> {
                                        System.out.print("\nNew title: ");
                                        String newTitle = sc.nextLine();

                                        boolean titleExists = false;
                                        for (Map.Entry<String, LinkedList<Book>> entry : booksByGenre.entrySet()) {
                                            for (Book book : entry.getValue()) {
                                                if (book.getTitle().equals(newTitle)) {
                                                    titleExists = true;
                                                    break;
                                                }
                                            }
                                        }
                                        if (titleExists) {
                                            throw new IllegalArgumentException("Title already exists.");
                                        }

                                        bookToEdit.setTitle(newTitle);
                                        System.out.println("Title changed successfully!");
                                    }
                                    case 2 -> {
                                        System.out.print("\nNew author: ");
                                        String newAuthor = sc.nextLine();
                                        bookToEdit.setAuthor(newAuthor);
                                        System.out.println("Author changed successfully!");
                                    }
                                    case 3 -> {
                                        System.out.print("\nNew year: ");
                                        int newYear = sc.nextInt();
                                        bookToEdit.setYear(newYear);
                                        System.out.println("Year changed successfully!");
                                    }
                                    case 4 -> {
                                        System.out.print("\nNew genre: ");
                                        String newGenre = sc.nextLine();
                                        bookToEdit.setGenre(Genres.fromString(newGenre));
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
