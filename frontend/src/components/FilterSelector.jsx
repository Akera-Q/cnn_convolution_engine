export default function FilterSelector({ filter, setFilter })
{
  return (
    <select
      value={filter}
      onChange={(e) => setFilter(e.target.value)}
      className="border p-2 rounded-lg"
    >
      <option value="blur">Blur</option>
      <option value="edge">Edge Detection</option>
      <option value="sharpen">Sharpen</option>
    </select>
  );
}