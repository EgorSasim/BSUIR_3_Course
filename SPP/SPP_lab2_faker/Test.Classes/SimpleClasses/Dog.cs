namespace Test.Classes.SimpleClasses
{
    public class Dog 
    {
        public string ownerName;
        public int legsAmount;
        private string name;
        private double tailSize;

        public Dog(string _name) 
        {
            name = _name;
        }

        public Dog(string _name, double _tailSize)
        {
            name = _name;
            tailSize = _tailSize;
        }

        public void showInfo()
        {
            Console.WriteLine($"Dog name: {name}, Owner name: {ownerName}, Legs amount: {legsAmount}, Tail size: {tailSize}");
        }
    }
}