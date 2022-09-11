import java.util.*;
import java.lang.reflect.Field;

class Book {
	public 	String title;
	public 	String author;
	public 	int price;
	public 	static int edition;

	public Book(String _title, String _author, int _price) {
		title = _title;
		author = _author;
		price = _price;
	}

	public boolean equals(Object obj) {
		if (obj == this) 
			return true;
		if (!(obj instanceof Book)) 
			return false;
		Field[] thisField = this.getClass().getDeclaredFields(); 
		Field[] objFields = obj.getClass().getDeclaredFields();

		if (thisField.length != objFields.length) 
			return false;
		Book tmp = (Book)obj;


		return this.author == tmp.author && this.price == tmp.price && this.title == tmp.title; 
	}	

	public int hashCode() {
		int hash = 3;
		hash = 31 * hash + (title == null ? 0 : title.hashCode());
		hash = 31 * hash + (author == null ? 0 : title.hashCode());
		hash = 31 * hash + price;
		hash = 31 * hash + edition;
		return hash;
	}

	public String toString() {
		return this.author + "\n" + this.title + "\n" + Integer.toString(this.price) + "\n"; 
	}

}

class sortByTitle implements Comparator<Book> {
	public int compare(Book book1, Book book2) {
		return book1.title.compareTo(book2.title);
	} 
}