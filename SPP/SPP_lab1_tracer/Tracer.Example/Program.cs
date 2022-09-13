using Tracer.Core.Interfaces;
using Tracer.Core.Structs;
using Tracer.Core;
using Tracer.Serialization.Abstraction.Classes;
using Tracer.Serialization.Abstractions;
using System.Reflection;

namespace Tracer.Example
{
    public class Foo
    {
        private Bar _bar;
        private ITracer _tracer;

        internal Foo(ITracer tracer)
        {
            _tracer = tracer;
            _bar = new Bar(_tracer);
        }

        public void MyMethod()
        {
            _tracer.StartTrace();
            Thread.Sleep(200);

            _bar.InnerMethod();

            _tracer.StopTrace();
        }
    }

    public class Bar
    {
        private ITracer _tracer;

        internal Bar(ITracer tracer)
        {
            _tracer = tracer;
        }

        public void InnerMethod()
        {
            _tracer.StartTrace();
            Thread.Sleep(500);
            _tracer.StopTrace();
        }
    }

    public class C
    {
        private ITracer _tracer;

        public C(ITracer tracer)
        {
            _tracer = tracer;
        }

        public void M0()
        {
            M1();
            M2();
        }

        private void M1()
        {
            _tracer.StartTrace();
            Thread.Sleep(100);
            _tracer.StopTrace();
        }

        private void M2()
        {
            _tracer.StartTrace();
            Thread.Sleep(200);
            _tracer.StopTrace();
        }
    }

    public class Example
    {
        static void Main(string[] args)
        {
            ITracer tracer = new Core.Tracer();
            C c = new(tracer);
            Thread thread = new(new ThreadStart(c.M0));
            thread.Start();
            Foo foo = new(tracer);
            foo.MyMethod();
            Thread.Sleep(500); 
            TraceResult traceResult = tracer.GetTraceResult();
            TraceResultsParser parser = new();
            var hierarchy = parser.GetMethodsAndThreadsHierarchy(traceResult);
            SerializeToJson(hierarchy);
            SerializeToXml(hierarchy);
            SerializeToYaml(hierarchy);
        }

        public static void SerializeToJson(List<ThreadInfo> threads)
        {
            Assembly a = Assembly.LoadFrom(@"./Tracer.Serialization/Tracer.Serialization.Json/bin/Debug/net6.0/Tracer.Serialization.Json.dll");
            Type type = a.GetType("Tracer.Serialization.Json.JsonTraceResultsSerializer", true);
            var serializer = (ITraceResultsSerializer)Activator.CreateInstance(type);
            using (var to = File.Open("result.json", FileMode.Create))
            {
                serializer.Serialize(threads, to);
            }
        }

        public static void SerializeToXml(List<ThreadInfo> threads)
        {
            Assembly a = Assembly.LoadFrom(@"./Tracer.Serialization/Tracer.Serialization.Xml/bin/Debug/net6.0/Tracer.Serialization.Xml.dll");
            Type type = a.GetType("Tracer.Serialization.Xml.XmlTraceResultsSerializer", true);
            var serializer = (ITraceResultsSerializer)Activator.CreateInstance(type);
            using (var to = File.Open("result.xml", FileMode.Create))
            {
                serializer.Serialize(threads, to);
            }
        }

        public static void SerializeToYaml(List<ThreadInfo> threads)
        {
            Assembly a = Assembly.LoadFrom(@"./Tracer.Serialization/Tracer.Serialization.Yaml/bin/Debug/net6.0/Tracer.Serialization.Yaml.dll");
            Type type = a.GetType("Tracer.Serializaton.Yaml.YamlTraceResultsSerializer", true);
            var serializer = (ITraceResultsSerializer)Activator.CreateInstance(type);
            using (var to = File.Open("result.yaml", FileMode.Create))
            {
                serializer.Serialize(threads, to);
            }
        }
    }
}