# Use a lightweight Python base image
FROM python:3.11-slim

# Install system dependencies for C++ parsing (tree-sitter needs gcc)
RUN apt-get update && apt-get install -y \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory
WORKDIR /app

# Copy the requirements file and install dependencies
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

# Copy the rest of the application code
COPY . .

# Expose the FastAPI port
EXPOSE 8001

# Command to run the FastAPI backend
CMD ["python", "main_api.py"]