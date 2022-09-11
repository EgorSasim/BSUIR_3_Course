import java.util.Comparator;

class sortByTitleAuthor implements Comparator<Book> {
	public int compare(Book book1, Book book2) {
		int titleCompare = book1.title.compareTo(book2.title);
        int authorCompare = book1.author.compareTo(book2.author);

        return (titleCompare == 0) ? authorCompare : titleCompare;
	} 
}