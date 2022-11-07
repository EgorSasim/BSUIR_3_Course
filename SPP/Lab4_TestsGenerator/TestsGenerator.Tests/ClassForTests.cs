namespace TestsGenerator.Tests
{
    public class ClassForTests
    {
        public void MethodName(int a) { }
        public void MethodName(int a, int b) { }

        public class InnerClass
        {
            public void MethodName(int a) { }
            public void MethodName(int a, int b) { }
        }
    }
}

public class ClassForTests
{
    public void MethodName(int a) { }
    public void MethodName(int a, int b) { }

    public class InnerClass
    {
        public void MethodName(int a) { }
        public void MethodName(int a, int b) { }
    }
}
