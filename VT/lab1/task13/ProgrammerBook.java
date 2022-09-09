
import java.util.*;
import java.lang.reflect.Field;

class ProgrammerBook extends Book {
	private String language;
	private int level;

	public boolean equals(Object obj) {
		if (obj == this) 
			return true;
		if (!(obj instanceof Book)) 
			return false;

		ProgrammerBook tmp = (ProgrammerBook)obj;

		return this.author == tmp.author && this.price == tmp.price && this.title == tmp.title && this.language == tmp.language && this.level == tmp.level; 
	}	

	public int hashCode() {
		int hash = 3;
		hash = 31 * hash + (title == null ? 0 : title.hashCode());
		hash = 31 * hash + (author == null ? 0 : title.hashCode());
		hash = 31 * hash + (language == null ? 0 : language.hashCode());
		hash = 31 * hash + level;
		hash = 31 * hash + price;
		hash = 31 * hash + edition;
		return hash;
	}

	public String toString() {
		return this.author + "\n" + this.title + "\n"  + this.language + "\n" + this.level + "\n"  + Integer.toString(this.price) + "\n"; 
	}
}
