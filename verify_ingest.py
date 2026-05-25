import chromadb

client = chromadb.PersistentClient(path="./repo_db")
collection = client.get_collection(name="music_player_repo")

print(f"Collection count: {collection.count()}")
results = collection.get()
for i, doc in enumerate(results['documents']):
    meta = results['metadatas'][i]
    print(f"--- Document {i} ---")
    print(f"File: {meta['file']}")
    print(f"Type: {meta['type']}")
    print(f"Name: {meta['name']}")
    print(f"Snippet: {doc[:50]}...")
