namespace Tracer.Serialization.Abstraction.Classes
{
    public class MethodInfo
    {
        public string Name { get; set; }
        public string Class { get; set; }
        public long Time { get; set; }
        public List<MethodInfo> Methods { get; set; }

        public MethodInfo(string name, string @class, long time, List<MethodInfo> methods)
        {
            Name = name;
            Class = @class;
            Time = time;
            Methods = methods;
        }
    }
}