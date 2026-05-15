import { useState } from "react";
import { processImage } from "../services/api";
import ImageUploader from "../components/ImageUploader";
import FilterSelector from "../components/FilterSelector";
import ImagePreview from "../components/ImagePreview";
import BenchmarkInfo from "../components/BenchmarkInfo";

export default function Home()
{
  const [file, setFile] = useState(null);
  const [filter, setFilter] = useState("blur");

  const [original, setOriginal] = useState(null);
  const [processed, setProcessed] = useState(null);
  const [stats, setStats] = useState("");

  const handleProcess = async () =>
  {
    if (!file)
      return;

    setOriginal(URL.createObjectURL(file));

    try {
      const data = await processImage(file, filter);

      setProcessed(data.imageUrl);
      setStats(data.stats);
    } catch (error) {
      console.error("Processing failed:", error);
      setStats("Processing failed. Check the server logs.");
    }
  };

  return (
    <div className="min-h-screen bg-gray-100 p-10">
      <div className="flex gap-4 items-center mb-8">
        <ImageUploader setFile={setFile} />

        <FilterSelector
          filter={filter}
          setFilter={setFilter}
        />

        <button
          onClick={handleProcess}
          className="bg-black text-white px-5 py-2 rounded-lg"
        >
          Process
        </button>
      </div>

      <div className="flex gap-10 mb-10">
        <ImagePreview
          title="Original"
          src={original}
        />

        <ImagePreview
          title="Processed"
          src={processed}
        />
      </div>

      <BenchmarkInfo stats={stats} />
    </div>
  );
}