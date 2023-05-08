package aula10;

public enum Genres {
    ACTION, ADVENTURE, COMEDY, CRIME, DRAMA, FANTASY, HISTORICAL, HORROR, MYSTERY, PHILOSOPHICAL, POLITICAL, ROMANCE, SAGA, SATIRE, SCIENCE_FICTION, THRILLER, URBAN, WESTERN;

    public static Genres fromString(String string) {
        return switch (string.toLowerCase()) {
            case "action" -> ACTION;
            case "adventure" -> ADVENTURE;
            case "comedy" -> COMEDY;
            case "crime" -> CRIME;
            case "drama" -> DRAMA;
            case "fantasy" -> FANTASY;
            case "historical" -> HISTORICAL;
            case "horror" -> HORROR;
            case "mystery" -> MYSTERY;
            case "philosophical" -> PHILOSOPHICAL;
            case "political" -> POLITICAL;
            case "romance" -> ROMANCE;
            case "saga" -> SAGA;
            case "satire" -> SATIRE;
            case "science fiction" -> SCIENCE_FICTION;
            case "thriller" -> THRILLER;
            case "urban" -> URBAN;
            case "western" -> WESTERN;
            default -> throw new IllegalArgumentException("Invalid genre: " + string);
        };
    }

    public String toString() {
        return switch (this) {
            case ACTION -> "Action";
            case ADVENTURE -> "Adventure";
            case COMEDY -> "Comedy";
            case CRIME -> "Crime";
            case DRAMA -> "Drama";
            case FANTASY -> "Fantasy";
            case HISTORICAL -> "Historical";
            case HORROR -> "Horror";
            case MYSTERY -> "Mystery";
            case PHILOSOPHICAL -> "Philosophical";
            case POLITICAL -> "Political";
            case ROMANCE -> "Romance";
            case SAGA -> "Saga";
            case SATIRE -> "Satire";
            case SCIENCE_FICTION -> "Science Fiction";
            case THRILLER -> "Thriller";
            case URBAN -> "Urban";
            case WESTERN -> "Western";
        };
    }
}
