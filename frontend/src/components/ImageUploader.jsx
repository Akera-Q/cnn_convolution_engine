export default function ImageUploader({ setFile })
{
  return (
    <input
      type="file"
      accept="image/*"
      onChange={(e) => setFile(e.target.files[0])}
      className="border p-2 rounded-lg bg-white"
    />
  );
}