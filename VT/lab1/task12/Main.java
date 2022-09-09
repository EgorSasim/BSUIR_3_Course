class Main {
	public static void main(String args[]) {
		Book book = new Book();
		book.author = "John konor";
		book.price = 3;
		book.title = "Terminator 3";

		Book book2 = new Book();
		book2.author = "John konor";
		book2.price = 3;
		book2.title = "Terminator 3";

		boolean res = book.equals(book2);

		System.out.println(res);

	}
}
