using System.Reflection;

namespace Faker.Core.Generators
{
    internal sealed class TimeGenerator : Generator
    {
        static TimeGenerator()
        {
            var genFunctions = typeof(TimeGenerator).GetMethods(BindingFlags.NonPublic | BindingFlags.Static);

            foreach (var func in genFunctions) simpleGenerators[func.ReturnType] = () => func.Invoke(null, null);
        }

        private static TimeSpan TimeStamp() => new(_random.NextInt64(TimeSpan.TicksPerDay*7));
        private static DateTime GetDateTime() => new(_random.NextInt64(DateTime.Today.Ticks));
    }
}