using System.Reflection;
using System.Runtime.CompilerServices;

namespace Faker.Core.Generators
{
    internal abstract class Generator
    {

        public static IReadOnlyDictionary<Type, Func<object>> SimpleGenerators => simpleGenerators;
        protected readonly static Dictionary<Type, Func<object>> simpleGenerators = new();
        protected readonly static Random _random = new(1);

        static Generator()
        {
            InitAll();
        }

        protected static byte[] GetBytes(int length)
        {
            byte[] bytes = new byte[length];
            _random.NextBytes(bytes);
            return bytes;
        }

        private static void InitAll() {
            var subClasses = Assembly.GetExecutingAssembly().GetTypes().Where(x => x.IsAssignableTo(typeof(Generator)) && x != typeof(Generator));
            foreach (var subClass in subClasses) RuntimeHelpers.RunClassConstructor(subClass.TypeHandle);
        }
    }
}