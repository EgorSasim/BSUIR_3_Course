using Tracer.Serialization.Abstraction.Classes;
using Tracer.Serialization.Abstractions;
using System.Text;
namespace Tracer.Serialization.Json
{
    public class JsonTraceResultsSerializer : ITraceResultsSerializer
    {
        public void Serialize(List<ThreadInfo> threads, Stream to)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine("{");
            sb.AppendLine("\t\"threads\": [");
            foreach (var thread in threads)
            {
                sb.AppendLine("\t\t{");
                sb.AppendLine($"\t\t\t\"id\": \"{thread.Id}\"");
                sb.AppendLine($"\t\t\t\"time\": \"{thread.Time}ms\"");
                sb.AppendLine($"\t\t\t\"methods\": [");
                sb.Append(SerializeMethods(thread.Methods, "\t\t\t\t"));
                sb.AppendLine("\t\t\t]");
                sb.AppendLine("\t\t},");
            }
            sb.AppendLine("\t]");
            sb.AppendLine("}");
            using (StreamWriter writer = new StreamWriter(to))
            {
                writer.Write(sb);
            }
        }

        private string SerializeMethods(List<MethodInfo> methods, string offset)
        {
            StringBuilder sb = new();
            foreach (var method in methods)
            {
                sb.AppendLine($"{offset}{{");
                sb.AppendLine($"{offset}\t\"name\": \"{method.Name}\"");
                sb.AppendLine($"{offset}\t\"class\": \"{method.Class}\"");
                sb.AppendLine($"{offset}\t\"time\": \"{method.Time}ms\"");
                sb.AppendLine($"{offset}\t\"methods\": [");
                sb.Append(SerializeMethods(method.Methods, offset + "\t"));
                sb.AppendLine($"{offset}\t]");
                sb.AppendLine($"{offset}}},");
            }
            return sb.ToString();
        }
    }
}