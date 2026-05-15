const express = require("express");
const cors = require("cors");
const multer = require("multer");
const { execFile } = require("child_process");
const path = require("path");

const app = express();

app.use(cors());
app.use("/outputs", express.static(path.join(__dirname, "outputs")));

const storage = multer.diskStorage({
  destination: (req, file, cb) => {
    cb(null, "uploads/");
  },
  filename: (req, file, cb) => {
    cb(null, Date.now() + "-" + file.originalname);
  },
});

const upload = multer({ storage });

app.post("/process", upload.single("image"), (req, res) => {
  const filter = req.body.filter;

  const inputPath = req.file.path;

  const outputName = `output-${Date.now()}.png`;

  const outputPath = path.join("outputs", outputName);
  const processorPath = path.resolve(__dirname, "../backend/build/cnn_processor.exe");

  execFile(processorPath, [inputPath, outputPath, filter], (error, stdout, stderr) => {
    if (error)
    {
      console.error("Image processing failed:", error);
      console.error(stderr);
      return res.status(500).json({ error: "Processing failed", details: stderr });
    }

    res.json({
      imageUrl: `http://localhost:5000/outputs/${outputName}`,
      stats: stdout,
    });
  });
});

app.listen(5000, () => {
  console.log("Server running on port 5000");
});