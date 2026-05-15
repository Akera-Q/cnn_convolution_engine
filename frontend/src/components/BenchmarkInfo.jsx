export default function BenchmarkInfo({ stats })
{
  const formatStats = (text) => {
    if (!text) return "";

    return text.replace(/-?\d+(?:\.\d+)?/g, (match) => {
      const num = Number(match);
      return Number.isFinite(num) ? num.toFixed(10) : match;
    });
  };

  return (
    <div className="bg-black text-green-400 p-4 rounded-xl w-full max-w-2xl font-mono">
      <pre>{formatStats(stats)}</pre>
    </div>
  );
}