import axios from "axios";

export const processImage = async (file, filter) => {
  const formData = new FormData();

  formData.append("image", file);
  formData.append("filter", filter);

  const response = await axios.post(
    "http://localhost:5000/process",
    formData
  );

  return response.data;
};