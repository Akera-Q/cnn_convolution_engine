export default function BenchmarkInfo({ stats })
{
  return (
    <div className="bg-black text-green-400 p-4 rounded-xl w-full max-w-2xl font-mono">
      <pre>{stats}</pre>
    </div>
  );
}