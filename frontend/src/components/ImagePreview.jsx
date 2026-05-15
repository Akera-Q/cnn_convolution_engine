export default function ImagePreview({ title, src })
{
  return (
    <div className="flex flex-col items-center gap-3">
      <h2 className="text-xl font-semibold">{title}</h2>

      {
        src && (
          <img
            src={src}
            alt={title}
            className="w-87.5% rounded-xl shadow-lg"
          />
        )
      }
    </div>
  );
}